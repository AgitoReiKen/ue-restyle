// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "DefaultConnectionDrawingPolicy.h"
#include "ImageUtils.h"
#include "PackageTools.h"

#include "Engine/Texture2DArray.h"
#include "Themes/Default/WireRestyleDefault.h"
#include "PathDrawingSlateElement.h"
#include "SlateMaterialBrush.h"

#include "Brushes/SlateImageBrush.h"
#include "Brushes/SlateRoundedBoxBrush.h"

#include "Factories/MaterialFactoryNew.h"

#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Slate/DeferredCleanupSlateBrush.h"

#include "UObject/ConstructorHelpers.h"
namespace
{
	namespace SGraphPin_Private_internal
	{
		template <typename PtrType, PtrType PtrValue, typename TagType>
		struct getter {
			friend PtrType get(TagType) { return PtrValue; }
		};

		struct Tag {};

		using Type = TWeakPtr<SGraphNode>;
		using TypePtr = Type SGraphPin::*;
		template struct getter<Type(SGraphPin::*), &SGraphPin::OwnerNodePtr, Tag>;
		TypePtr get(Tag);
	}

	namespace SGraphPin_Private
	{
		TWeakPtr<SGraphNode>& OwnerNodePtr(SGraphPin& Class)
		{
			return Class.*get(SGraphPin_Private_internal::Tag{});
		}
	}
}

class FPathDrawerHolder
{
	class FRunnableCleaner : public FRunnable
	{
	public:
		virtual bool Init() override
		{
			bUpdate = true;
			return true;
		}

		virtual uint32 Run() override
		{
			while (bUpdate)
			{
				{
					ENQUEUE_RENDER_COMMAND(FreeDestroyedWires)(
						[](FRHICommandListImmediate& RHICmdList)
						{
							FScopeLock ScopeLock(&Get().Mutex);
							Get().Data.RemoveAll([](const TSharedPtr<FPathDrawingSlateElement>& p)-> bool
							{
								if (!p.IsValid()) return true;
								if (p->bDestroyed)
								{
									return true;
								}
								return false;
							});
						});
				}
				FPlatformProcess::Sleep(3.0);
			}
			return 0;
		}

		virtual void Stop() override
		{
			bUpdate = false;
		}

		virtual void Exit() override
		{
			bUpdate = false;
		}

		virtual FSingleThreadRunnable* GetSingleThreadInterface() override
		{
			return nullptr;
		}

		virtual ~FRunnableCleaner() override
		{
			bUpdate = false;
		}

		bool bUpdate;
	};

public:
	static FPathDrawerHolder& Get()
	{
		static FPathDrawerHolder This;
		return This;
	}

	TSharedPtr<FPathDrawingSlateElement>& Add()
	{
		FScopeLock ScopeLock(&Mutex);
		Data.Add(MakeShared<FPathDrawingSlateElement>());
		return Data.Last();
	}

private:
	void SetupGC()
	{
		Cleaner = new FRunnableCleaner();
		checkf(FPlatformProcess::SupportsMultithreading(), L"Platform doesn't support multithreading")
		CleanerThread = FRunnableThread::Create(Cleaner, TEXT("Restyle_Default_Wire_Update"));
		//if (TimerHandle.IsValid()) return;
		//TimerDelegate.BindLambda([this]()
		//{
		//	UE_LOG(LogTemp, Warning, L"Timer");
		//	FScopeLock ScopeLock(&Mutex);
		//	Data.RemoveAll([](const TSharedPtr<FPathDrawingSlateElement>& p)-> bool
		//	{
		//		// Is only referenced to this
		//		return p->bDestroyed;
		//	});
		//});
		//
		//World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5, true);
	}

	void RemoveGC()
	{
		if (CleanerThread) CleanerThread->Kill(false);
	}

	FPathDrawerHolder()
		: TimerHandle(FTimerHandle())
		  , TimerDelegate(FTimerDelegate())
	{
		SetupGC();
	}

	FRunnableThread* CleanerThread;
	FRunnableCleaner* Cleaner;
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	FCriticalSection Mutex;
	TArray<TSharedPtr<FPathDrawingSlateElement>> Data;
};

FDefaultConnectionDrawingPolicy::FDefaultConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID,
                                                                 float InZoomFactor, const FSlateRect& InClippingRect,
                                                                 FSlateWindowElementList& InDrawElements,
                                                                 UEdGraph* InGraphObj)
	: FKismetConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements,
	                                 InGraphObj)
{
}


void FDefaultConnectionDrawingPolicy::UpdateSplineHover(const TArray<FVector2f>& PointsF,
                                                        const FConnectionParams& Params, float ZoomValue)
{
	if (Settings->bTreatSplinesLikePins)
	{
		const float QueryDistanceTriggerThresholdSquared = FMath::Square(
			ZoomValue * Settings->SplineHoverTolerance + Params.WireThickness * 0.5f * ZoomValue);
		const float QueryDistanceForCloseSquared = FMath::Square(
			FMath::Sqrt(QueryDistanceTriggerThresholdSquared) + ZoomValue * Settings->SplineCloseTolerance);

		float ClosestDistanceSquared = FLT_MAX;
		FVector2f ClosestPoint = FVector2f::ZeroVector;
		FVector2f fLocalMousePosition = FVector2f(static_cast<float>(LocalMousePosition.X), static_cast<float>(LocalMousePosition.Y));
		{
			for (int i = 1; i < PointsF.Num(); i++)
			{
				const auto& A = PointsF[i - 1];
				const auto& B = PointsF[i];
				FVector2D dClosestPoint = FMath::ClosestPointOnSegment2D(LocalMousePosition,
					FVector2D(A.X, A.Y), FVector2D(B.X, B.Y));
				ClosestPoint = FVector2f(static_cast<float>(dClosestPoint.X), static_cast<float>(dClosestPoint.Y));
				float DistanceSquared = FVector2f::DistSquared(ClosestPoint, fLocalMousePosition);
				if (DistanceSquared < ClosestDistanceSquared)
				{
					ClosestDistanceSquared = DistanceSquared;
				}
			}
		}

		// Record the overlap
		if (ClosestDistanceSquared < QueryDistanceTriggerThresholdSquared)
		{
			if (ClosestDistanceSquared < SplineOverlapResult.GetDistanceSquared())
			{
				const float SquaredDistToPin1 = (Params.AssociatedPin1 != nullptr)
					                                ? (PointsF[0] - ClosestPoint).SizeSquared()
					                                : FLT_MAX;
				const float SquaredDistToPin2 = (Params.AssociatedPin2 != nullptr)
					                                ? (PointsF.Last() - ClosestPoint).SizeSquared()
					                                : FLT_MAX;
				//@BUG editor crashes (saying something keeps ref to pin) if trying to delete node (or break the link via alt left-click) while in that state
				SplineOverlapResult = FGraphSplineOverlapResult(
					Params.AssociatedPin1, Params.AssociatedPin2,
					ClosestDistanceSquared, SquaredDistToPin1, SquaredDistToPin2,
					true);
			}
		}
		else if (ClosestDistanceSquared < QueryDistanceForCloseSquared)
		{
			SplineOverlapResult.SetCloseToSpline(true);
		}
	}
}

FGeometry FDefaultConnectionDrawingPolicy::GetNodeGeometryByPinWidget(SGraphPin& PinWidget,
	const FArrangedChildren& ArrangedNodes)
{
	auto NodeWidget = SGraphPin_Private::OwnerNodePtr(PinWidget);
	int32 NodeWidgetId = ArrangedNodes.FindLastByPredicate([&NodeWidget](const FArrangedWidget& c)->bool
		{
			return c.Widget == NodeWidget.Pin();
		});
	return NodeWidgetId < 0 ? FGeometry() : ArrangedNodes[NodeWidgetId].Geometry;
}

void FDefaultConnectionDrawingPolicy::DrawConnection(const FRestyleConnectionParams& Params, const FConnectionParams& WireParams)
{
	/*
	 * @note FVector2f used instead of FVector2D due to FScreenVertex accepts float version
	 */
	if (WireParams.WireThickness < 0 || !WireParams.AssociatedPin1 || !WireParams.AssociatedPin2) return;
	auto Zoomed = [this](float Value) -> float
	{
		return Value * ZoomFactor;
	};
	const float StartFudgeX = Zoomed(4.0f);
	const float EndFudgeX = Zoomed(4.0f);
	FVector2D _Start = FGeometryHelper::VerticalMiddleRightOf(Params.Start) - FVector2D(StartFudgeX, 0.0f);;
	FVector2D _End = FGeometryHelper::VerticalMiddleLeftOf(Params.End) - FVector2D(ArrowRadius.X - EndFudgeX, 0);

	FVector2f Start(_Start.X, _Start.Y);
	FVector2f End(_End.X, _End.Y);
	auto& StartNode = Params.StartNodeGeometry;
	auto& EndNode = Params.EndNodeGeometry;

	FLinearColor WireColor = WireParams.WireColor;
	auto WireSettings = UWireRestyleSettings::Get();

	 
	// Zoomed(WireParams.WireThickness) prevents big lines have bad geometry on corners (due to fixation to intersection point), but also cause on-hover disturbance
	// Thickness > MinHorizontalLength is bad. Adding Thickness to MinHorizontalLength will result in line moving around while hover zooms it, and so hover will break
	// As a solution, user must provide MinHorizontalLength greater than WireThickness
	float MinXL = Zoomed(WireSettings->MinHorizontalLength);
	float XDif = End.X - Start.X;
	float XDifA = FMath::Abs(XDif);
	float YDif = End.Y - Start.Y;
	float YDifA = FMath::Abs(YDif);
	float XL = MinXL;
	float YL = YDif * .5f;
	TArray<FVector2f> PointsF;

	FVector2f Normalized = (End - Start).GetSafeNormal();
	float Tangent = FMath::Atan(Normalized.Y);
	bool bIs0Deg = FMath::IsNearlyZero(Tangent, 0.001f);
	bool bGoesBackward = Start.X + Zoomed(4) >= End.X;
	bool bTreatEqualLength = (!bGoesBackward && XDifA < MinXL) || FMath::IsNearlyEqual(XL, XDifA * .5f, MinXL);
	bool bIsPin1Knot = WireParams.AssociatedPin1->GetOwningNode()->IsA<UK2Node_Knot>();
	bool bIsPin2Knot = WireParams.AssociatedPin2->GetOwningNode()->IsA<UK2Node_Knot>();
	bool bIsPin1Exec = !bIsPin1Knot && WireParams.AssociatedPin1->PinType.PinCategory == UEdGraphSchema_K2::PC_Exec;
	bool bIsPin2Exec = !bIsPin2Knot && WireParams.AssociatedPin2->PinType.PinCategory == UEdGraphSchema_K2::PC_Exec;
	 
	bool bExecToExec = bIsPin1Exec && bIsPin2Exec;
	bool bExecToKnot = bIsPin1Exec && bIsPin2Knot;
	bool bKnotToExec = bIsPin1Knot && bIsPin2Exec;
	bool bPinToPin = !bIsPin1Exec && !bIsPin2Exec;
	bool b45DegreeStyle = WireSettings->b45DegreeStyle;
	EWireRestylePriority TransitionPriority = EWireRestylePriority::Equal;
	if (bPinToPin) TransitionPriority = WireSettings->TransitionPriority;
	else if (bExecToExec) TransitionPriority = WireSettings->ExecToExecTransitionPriority;
	else if (bExecToKnot) TransitionPriority = WireSettings->ExecToKnotTransitionPriority;
	else if (bKnotToExec) TransitionPriority = WireSettings->KnotToExecTransitionPriority;

	/*
	 * [a]---[b]
	 */
	if (bIs0Deg)
	{
		PointsF.Append({ Start, End });
	}
	/*
		 [a]--.
		 .___|
		 |__[b]
	 */
	else if (bGoesBackward)
	{
		// lower/upper

		float SnapPointY = 0.f;
		float Offset = Zoomed(WireSettings->BackwardSnapPointOffset);
		bool bStartIsHigher = Start.Y < End.Y;
		/* snap to start node */
		if (WireSettings->BackwardConnectionPriority == EWireRestylePriority::Output)
		{
			if (bStartIsHigher)
			{
				SnapPointY = StartNode.AbsolutePosition.Y + Zoomed(StartNode.Size.Y) + Offset;
			}
			else
			{
				SnapPointY = StartNode.AbsolutePosition.Y - Offset;
			}
		}
		else if (WireSettings->BackwardConnectionPriority == EWireRestylePriority::Input)
		{
			if (bStartIsHigher)
			{
				SnapPointY = EndNode.AbsolutePosition.Y - Offset;
			}
			else
			{ 
				SnapPointY = EndNode.AbsolutePosition.Y + Zoomed(EndNode.Size.Y) + Offset;

			}
		}
		else
		{
			if (bStartIsHigher)
			{
				float Length = EndNode.AbsolutePosition.Y - (StartNode.AbsolutePosition.Y + Zoomed(StartNode.Size.Y));

				SnapPointY = StartNode.AbsolutePosition.Y + Zoomed(StartNode.Size.Y) + Length * 0.5;
			}
			else
			{
				float Length = StartNode.AbsolutePosition.Y - (EndNode.AbsolutePosition.Y + Zoomed(EndNode.Size.Y));

				SnapPointY = EndNode.AbsolutePosition.Y + Zoomed(EndNode.Size.Y) + Length * 0.5;
			}
		}

		PointsF = {
			Start,
			FVector2f(Start.X + XL, Start.Y),
			FVector2f(Start.X + XL, SnapPointY),
			FVector2f(End.X - XL, SnapPointY),
			FVector2f(End.X - XL, End.Y),
			End
		};
	}
	/*
	 * [a]--.
	 *		|
	 *		|__[b]
	 */
	else if (bTreatEqualLength)
	{
		XL = XDifA * .5f;
		PointsF = {
			Start,
			{Start.X + XL, Start.Y},
			{End.X - XL, End.Y},
			End
		};
	}
	/*	
	 * [a]--\
	 *		 \__[b]
	 */
	else
	{
		FVector2f StartX;
		FVector2f EndX;

		if (b45DegreeStyle)
		{
			if (TransitionPriority == EWireRestylePriority::Output)
			{
				StartX = {
					End.X - XL - YDifA,
					Start.Y
				};
				EndX = {
					End.X - XL,
					End.Y
				};
			}
			else if (TransitionPriority == EWireRestylePriority::Input)
			{
				StartX = {
					Start.X + XL,
					Start.Y
				};

				EndX = {
					Start.X + XL + YDifA,
					End.Y
				};
			}
			else
			{
				StartX = {
					Start.X + XDif * 0.5f - YDifA * 0.5f,
					Start.Y
				};
				EndX = {
					End.X - XDif * 0.5f + YDifA * 0.5f,
					End.Y
				};
			}

			bool bBehindOutput = StartX.X - Start.X < XL;
			bool bAfterInput = End.X - EndX.X < XL;
			if (bBehindOutput && bAfterInput)
			{
				StartX.X = Start.X + XDifA * 0.5f;
				EndX.X = StartX.X;
			}
			else if (bBehindOutput)
			{
				StartX.X = EndX.X;
			}
			else if (bAfterInput)
			{
				EndX.X = StartX.X;
			}

		}
		else
		{
			if (TransitionPriority == EWireRestylePriority::Output)
			{
				 
				StartX = {
					End.X - XL,
					Start.Y
				};
				EndX = {
					End.X - XL,
					End.Y
				};
			}
			else if (TransitionPriority == EWireRestylePriority::Input)
			{
				StartX = {
					Start.X + XL,
					Start.Y
				};

				EndX = {
					Start.X + XL,
					End.Y
				};
			}
			else
			{
				StartX = {
					Start.X + XDif * 0.5f ,
					Start.Y
				};
				EndX = {
					End.X - XDif * 0.5f,
					End.Y
				};
			} 
		}
		 
		PointsF = {
			Start,
			StartX,
			EndX,
			End
		};
		 
	}

	if (WireSettings->bDebug)
	{
		const_cast<FConnectionParams*>(&WireParams)->bDrawBubbles = WireSettings->bDrawBubbles;
		/*if (SplineOverlapResult.GetCloseToSpline())
		{
			WireColor = FLinearColor::Green;
		}*/

		 
	}
	 
	FColor CorrectedWireColor = WireParams.WireColor.ToFColorSRGB();
	WireColor = {
		CorrectedWireColor.R / 255.f,
		CorrectedWireColor.G / 255.f,
		CorrectedWireColor.B / 255.f,
		WireColor.A
	};
	float WireThickness = FMath::Max(Zoomed(WireParams.WireThickness), 1.0f);

	LineDrawer = FPathDrawerHolder::Get().Add();
	FRestylePathSettings PathSettings;
	PathSettings.Thickness = WireThickness;
	PathSettings.Color = WireColor;
	PathSettings.bDrawWireframe = WireSettings->bDrawWireframe;
	PathSettings.Join = WireSettings->bRoundCorners ? ERestylePathJoinType::Round : ERestylePathJoinType::Miter;
	PathSettings.CornerRadius = WireSettings->CornerRadius;
	if (WireSettings->MinHorizontalLength > WireParams.WireThickness)
	{
		LineDrawer->ClippingRect = ClippingRect;
		LineDrawer->Path.Init(PointsF, PathSettings);
		PointsF = LineDrawer->Path.Points;
		FSlateDrawElement::MakeCustom(DrawElementsList, WireLayerID, LineDrawer);
	}
	else
	{
		static int Thrown = 0;
		if (!Thrown++)
		{
			UE_LOG(LogTemp, Error, TEXT("[Restyle] Wire->MinHorizontalLength must be greater than wire thickness. otherwise line's geometry will be messed up"));
		}
	}

	UpdateSplineHover(PointsF, WireParams, ZoomFactor);
	if (WireParams.bDrawBubbles || (MidpointImage != nullptr))
	{
		float TotalLength = 0.f;
		for (int i = 1; i < PointsF.Num(); i++)
		{
			const auto& A = PointsF[i - 1];
			const auto& B = PointsF[i];
			double Length = FVector2f::Distance(A, B);
			TotalLength += Length;
		}
		if (WireParams.bDrawBubbles) {
			 
			float NumBubbles = WireSettings->NumBubbles;
			float Interval = TotalLength / NumBubbles;
			int Instances = TotalLength / Interval;
			float Step = TotalLength / Instances;

			const float BubbleSpeed = Step * Zoomed(WireSettings->BubbleSpeed);
			FVector2f fBubbleImageSize(BubbleImage->ImageSize.X, BubbleImage->ImageSize.Y);
			const FVector2f BubbleSize = fBubbleImageSize * ZoomFactor * 0.2f * WireParams.WireThickness;
			const FVector2f BubbleHalfSize = BubbleSize * 0.5;
			float Time = (FPlatformTime::Seconds() - GStartTime);
			float Offset = 0.0f;
			float OffsetFromPrevious = 0.0f;
			int Drawn = 0;

			while (Drawn != Instances)
			{
				float SpeedOffset = FMath::Fmod(Time * BubbleSpeed, Interval);
				float DrawLength = 0.f + SpeedOffset + (Drawn * Step);
				float CurrentLength = 0.f;
				for (int i = 1; i < PointsF.Num(); i++)
				{
					const auto& A = PointsF[i - 1];
					const auto& B = PointsF[i];
					double Length = FVector2f::Distance(A, B);
					auto Normal = (B - A).GetSafeNormal();
					if (DrawLength < CurrentLength + Length)
					{
						Offset = DrawLength - CurrentLength;
						Drawn++;
						FVector2f BubblePos = A + (Normal * Offset) - BubbleHalfSize; // *BubbleOffset);
						FSlateDrawElement::MakeBox(
							DrawElementsList,
							WireLayerID,
							FPaintGeometry(FVector2D(BubblePos.X, BubblePos.Y), FVector2D(BubbleSize.X, BubbleSize.Y), ZoomFactor),
							BubbleImage,
							ESlateDrawEffect::None,
							WireParams.WireColor
						);
						break;
					}

					CurrentLength += Length;
					if (i + 1 == PointsF.Num())
					{
						DrawLength -= CurrentLength;
						i = 1;
					}
				}
			}
		}
		if (MidpointImage)
		{
			float DrawOn = TotalLength * 0.5f;
			float CurrentLength = 0.f;
			for (int i = 1; i < PointsF.Num(); i++)
			{
				const auto& A = PointsF[i - 1];
				const auto& B = PointsF[i];
				double Length = FVector2f::Distance(A, B);
				auto Normal = (B - A).GetSafeNormal();
				FVector2f MidpointImageSize(MidpointImage->ImageSize.X, MidpointImage->ImageSize.Y);
				FVector2f ImageSize = MidpointImageSize * ZoomFactor;
				FVector2f ImageHalfSize = ImageSize * 0.5;
				if (DrawOn < CurrentLength + Length)
				{
					float Offset = DrawOn - CurrentLength;
					FVector2f DrawPos = A + (Normal * Offset) - ImageHalfSize; // *BubbleOffset);
					const float AngleInRadians = FMath::Atan2(B.Y - A.Y, B.X - A.X);
					FSlateDrawElement::MakeRotatedBox(
						DrawElementsList,
						WireLayerID,
						FPaintGeometry(FVector2D(DrawPos.X, DrawPos.Y), MidpointImage->ImageSize * ZoomFactor, ZoomFactor),
						MidpointImage,
						ESlateDrawEffect::None,
						AngleInRadians,
						TOptional<FVector2D>(),
						FSlateDrawElement::RelativeToElement,
						WireParams.WireColor
					); 
					break;
				}

				CurrentLength += Length; 
			}
		} 
	}
}

void FDefaultConnectionDrawingPolicy::DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2D& StartPoint,
	const FVector2D& EndPoint, UEdGraphPin* Pin)
{
	FKismetConnectionDrawingPolicy::DrawPreviewConnector(PinGeometry, StartPoint, EndPoint, Pin);
}


void FDefaultConnectionDrawingPolicy::DrawPinGeometries(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries,
                                                        FArrangedChildren& ArrangedNodes)
{
	for (TMap<TSharedRef<SWidget>, FArrangedWidget>::TIterator ConnectorIt(InPinGeometries); ConnectorIt; ++ConnectorIt)
	{
		TSharedRef<SWidget> SomePinWidget = ConnectorIt.Key();
		SGraphPin& PinWidget = static_cast<SGraphPin&>(SomePinWidget.Get());

		UEdGraphPin* ThePin = PinWidget.GetPinObj();

		if (ThePin->Direction == EGPD_Output)
		{
			for (int32 LinkIndex = 0; LinkIndex < ThePin->LinkedTo.Num(); ++LinkIndex)
			{
				FArrangedWidget* LinkStartWidgetGeometry = nullptr;
				FArrangedWidget* LinkEndWidgetGeometry = nullptr;

				UEdGraphPin* TargetPin = ThePin->LinkedTo[LinkIndex];
				TSharedPtr<SGraphPin>* TargetPinWidget =  PinToPinWidgetMap.Find(TargetPin);
				DetermineLinkGeometry(ArrangedNodes, SomePinWidget, ThePin, TargetPin, /*out*/ LinkStartWidgetGeometry,
					/*out*/ LinkEndWidgetGeometry);

				if ((LinkEndWidgetGeometry && LinkStartWidgetGeometry) && !IsConnectionCulled(
					*LinkStartWidgetGeometry, *LinkEndWidgetGeometry)
					&& TargetPinWidget && TargetPinWidget->IsValid()
					)
				{
					FConnectionParams ConnectionParams;
					DetermineWiringStyle(ThePin, TargetPin, /*input*/ ConnectionParams);

					FGeometry StartNodeGeometry = GetNodeGeometryByPinWidget(PinWidget, ArrangedNodes);
					FGeometry EndNodeGeometry = GetNodeGeometryByPinWidget(**TargetPinWidget, ArrangedNodes);
				 
					DrawConnection(
						{
							LinkStartWidgetGeometry->Geometry,
							LinkEndWidgetGeometry->Geometry,
							StartNodeGeometry,
							EndNodeGeometry
						},
						ConnectionParams);
				}
			}
		}
	}
}
