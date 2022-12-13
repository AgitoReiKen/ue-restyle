// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "DefaultAnimGraphConnectionDrawingPolicy.h"
#include "AnimationGraphSchema.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Animation/AnimBlueprint.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "AnimGraphNode_Base.h"
#include "AnimGraphAttributes.h"

#include "Themes/Default/WireRestyleDefault.h"
//////////////////////////////////////////////
// FDefaultAnimGraphConnectionDrawingPolicy

FDefaultAnimGraphConnectionDrawingPolicy::FDefaultAnimGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj)
	: FDefaultConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements, InGraphObj)
{
}

bool FDefaultAnimGraphConnectionDrawingPolicy::TreatWireAsExecutionPin(UEdGraphPin* InputPin, UEdGraphPin* OutputPin) const
{
	const UAnimationGraphSchema* Schema = GetDefault<UAnimationGraphSchema>();

	return (InputPin != NULL) && (Schema->IsPosePin(OutputPin->PinType));
}

void FDefaultAnimGraphConnectionDrawingPolicy::BuildExecutionRoadmap()
{
	if(UAnimBlueprint* TargetBP = Cast<UAnimBlueprint>(FBlueprintEditorUtils::FindBlueprintForGraph(GraphObj)))
	{
		UAnimBlueprintGeneratedClass* AnimBlueprintClass = (UAnimBlueprintGeneratedClass*)(*(TargetBP->GeneratedClass));

		if (TargetBP->GetObjectBeingDebugged() == NULL)
		{
			return;
		}
		
		FAnimBlueprintDebugData& DebugInfo = AnimBlueprintClass->GetAnimBlueprintDebugData();
		for (auto VisitIt = DebugInfo.UpdatedNodesThisFrame.CreateIterator(); VisitIt; ++VisitIt)
		{
			const FAnimBlueprintDebugData::FNodeVisit& VisitRecord = *VisitIt;

			const int32 NumAnimNodeProperties = AnimBlueprintClass->GetAnimNodeProperties().Num();
			if ((VisitRecord.SourceID >= 0) && (VisitRecord.SourceID < NumAnimNodeProperties) && (VisitRecord.TargetID >= 0) && (VisitRecord.TargetID < NumAnimNodeProperties))
			{
				const int32 ReverseSourceID = NumAnimNodeProperties - 1 - VisitRecord.SourceID;
				const int32 ReverseTargetID = NumAnimNodeProperties - 1 - VisitRecord.TargetID;
				
				if (const UAnimGraphNode_Base* SourceNode = Cast<const UAnimGraphNode_Base>(DebugInfo.NodePropertyIndexToNodeMap.FindRef(ReverseSourceID)))
				{
					if (const UAnimGraphNode_Base* TargetNode = Cast<const UAnimGraphNode_Base>(DebugInfo.NodePropertyIndexToNodeMap.FindRef(ReverseTargetID)))
					{
						UEdGraphPin* PoseNet = NULL;

						UAnimationGraphSchema const* AnimSchema = GetDefault<UAnimationGraphSchema>();
						for (int32 PinIndex = 0; PinIndex < TargetNode->Pins.Num(); ++PinIndex)
						{
							UEdGraphPin* Pin = TargetNode->Pins[PinIndex];
							check(Pin);
							if (AnimSchema->IsPosePin(Pin->PinType) && (Pin->Direction == EGPD_Output))
							{
								PoseNet = Pin;
								break;
							}
						}

						if (PoseNet != NULL)
						{
							//@TODO: Extend the rendering code to allow using the recorded blend weight instead of faked exec times
							FExecPairingMap& Predecessors = PredecessorPins.FindOrAdd((UEdGraphNode*)SourceNode);
							FTimePair& Timings = Predecessors.FindOrAdd(PoseNet);
							Timings.PredExecTime = 0.0;
							Timings.ThisExecTime = FMath::Clamp(VisitRecord.Weight, 0.f, 1.f);
						}
					}
				}
			}
		}
	}
}

void FDefaultAnimGraphConnectionDrawingPolicy::DrawRestyleConnection(const FRestyleConnectionParams& Params,
	const FConnectionParams& WireParams, TArray<FVector2f>* InPoints)
{
	bool bCompositeWire = false;

	// Pose pins display attribute links
	if (WireParams.AssociatedPin1 && WireParams.AssociatedPin2)
	{
		if (UAnimationGraphSchema::IsPosePin(WireParams.AssociatedPin1->PinType))
		{
			// If either pin connects to a re-route (knot) node, traverse the link until a relevant pin is found
			UEdGraphPin* UsePin1 = WireParams.AssociatedPin1;
			if (WireParams.AssociatedPin1->GetOwningNode()->IsA<UK2Node_Knot>())
			{
				UsePin1 = FBlueprintEditorUtils::FindFirstCompilerRelevantLinkedPin(WireParams.AssociatedPin1);
			}

			UEdGraphPin* UsePin2 = WireParams.AssociatedPin2;
			if (WireParams.AssociatedPin2->GetOwningNode()->IsA<UK2Node_Knot>())
			{
				UsePin2 = FBlueprintEditorUtils::FindFirstCompilerRelevantLinkedPin(WireParams.AssociatedPin2);
			}

			if (UsePin1 && UsePin2)
			{
				UAnimGraphNode_Base* Node1 = Cast<UAnimGraphNode_Base>(UsePin1->GetOwningNode());
				UAnimGraphNode_Base* Node2 = Cast<UAnimGraphNode_Base>(UsePin2->GetOwningNode());
				if (Node1 && Node2)
				{
					const TArrayView<const SDefault_GraphPinPose::FAttributeInfo>& AdditionalAttributeInfo = PinAttributes.FindRef(WireParams.AssociatedPin1);

					if (AdditionalAttributeInfo.Num() > 0)
					{

						if (WireParams.WireThickness < 0 || !WireParams.AssociatedPin1 || !WireParams.AssociatedPin2) return;

						TArray<FVector2f> Points = MakePathPoints(Params, WireParams);
						TArray<FVector2f> _Points = Points;
						FConnectionParams _WireParams = WireParams;
						_WireParams.WireThickness *= UWireRestyleSettings::Get()->AttributeWireThicknessMultiplier;
						_WireParams.WireColor = UWireRestyleSettings::Get()->AttributeWireColor.Get();  FLinearColor(1.0, 0.5, 0.0, 1.0);
						_WireParams.bDrawBubbles = _WireParams.bDrawBubbles ? !UWireRestyleSettings::Get()->AttributeDisableBubbles : false;
						FDefaultConnectionDrawingPolicy::DrawRestyleConnection(Params, WireParams, &Points);
						FDefaultConnectionDrawingPolicy::DrawRestyleConnection(Params, _WireParams, &_Points);
						return;
					}
				}
			}
		}
	}

	if (!bCompositeWire)
	{
		//DefaultConnectionDrawingPolicy::DrawConnection(LayerId, Start, End, Params);
		FDefaultConnectionDrawingPolicy::DrawRestyleConnection(Params, WireParams);
	}
}

void FDefaultAnimGraphConnectionDrawingPolicy::BuildPinToPinWidgetMap(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries)
{
	FDefaultConnectionDrawingPolicy::BuildPinToPinWidgetMap(InPinGeometries);

	// Cache additional attributes
	PinAttributes.Reset();
	bool bFoundPanelZoom = false;
	PanelZoom = 1.0f;

	for(const TPair<UEdGraphPin*, TSharedPtr<SGraphPin>>& PinWidgetPair : PinToPinWidgetMap)
	{
		if(PinWidgetPair.Key->Direction == EGPD_Output && UAnimationGraphSchema::IsPosePin(PinWidgetPair.Key->PinType) && PinWidgetPair.Key->GetOwningNode()->IsA<UAnimGraphNode_Base>())
		{
			// Pose pins are assumed to be SDefault_GraphPinPose widgets here
			check(PinWidgetPair.Value->GetType() == TEXT("SDefault_GraphPinPose"));
			TSharedPtr<SDefault_GraphPinPose> PosePin = StaticCastSharedPtr<SDefault_GraphPinPose>(PinWidgetPair.Value);

			PinAttributes.Add(PinWidgetPair.Key, PosePin->GetAttributeInfo());

			if(!bFoundPanelZoom)
			{
				PanelZoom = PosePin->GetZoomAmount();
				bFoundPanelZoom = true;
			}
		}
	}
}

void FDefaultAnimGraphConnectionDrawingPolicy::DetermineStyleOfExecWire(float& Thickness, FLinearColor& WireColor, bool& bDrawBubbles, const FTimePair& Times)
{
	// It's a followed link, make it strong and yellowish but fading over time
	const double BlendWeight = Times.ThisExecTime;

	const float HeavyBlendThickness = AttackWireThickness;
	const float LightBlendThickness = SustainWireThickness;

	Thickness = FMath::Lerp<float>(LightBlendThickness, HeavyBlendThickness, BlendWeight);
	WireColor = WireColor * (BlendWeight * 0.5f + 0.5f);//FMath::Lerp<FLinearColor>(SustainColor, AttackColor, BlendWeight);

	bDrawBubbles = true;
}
 

void FDefaultAnimGraphConnectionDrawingPolicy::ApplyHoverDeemphasis(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, float& Thickness, FLinearColor& WireColor)
{
	bool bDebugging = Thickness > ReleaseWireThickness;
	if (!bDebugging) {
		FDefaultConnectionDrawingPolicy::ApplyHoverDeemphasis(OutputPin, InputPin, Thickness, WireColor);
	}
}