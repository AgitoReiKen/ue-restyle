// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "PathDrawingSlateElement.h"

#include "CanvasItem.h"
#include "DefaultConnectionDrawingPolicy.h"
#include "GlobalShader.h"

#include "Engine/Canvas.h"
#include "SlateRHIRenderer/Public/Interfaces/ISlate3DRenderer.h"
#include <Runtime/SlateRHIRenderer/Private/SlateRHIRenderer.h>
#include <Runtime/SlateRHIRenderer/Private/SlateShaders.h>

#include "IHeadMountedDisplayModule.h"
#include "PixelShaderUtils.h"
#include "ScreenRendering.h"
#include <Runtime/HeadMountedDisplay/Public/IHeadMountedDisplayModule.h>

#include "Themes/Default/WireRestyleDefault.h"

void FPath::Init(TArray<FVector2f> InPoints, FRestylePathSettings InSettings)
{
	Segments.Empty();
	SegmentData.Empty();
	Settings = MoveTemp(InSettings);
	HalfThickness = FVector2f(Settings.Thickness + 2) * .5f;
	Calculate(InPoints);
}

FGenerateLineVerticesResult FPath::MakeRenderData()

{
	FGenerateLineVerticesResult r;

	InitWithPoints(r);
	SegmentData.AddUninitialized(Segments.Num());
	for (uint32 i = 0; i < (uint32)Segments.Num(); i++)
	{
		bool bIsBeginning = i == 0u;
		bool bIsEnd = i == Segments.Num() - 1;
		auto& it = Segments[i];
		auto pA = r.Vertices[it.PointA].Position;
		auto pB = r.Vertices[it.PointB].Position;

		uint32 Id = r.Vertices.Num();
		FSegmentData SD(Id, Id + 1, Id + 2, Id + 3);
		SegmentData[i] = SD;
		r.Vertices.Append({
			{pA + it.Width, UpperUV},
			{pA - it.Width, LowerUV},
			{pB + it.Width, UpperUV},
			{pB - it.Width, LowerUV}
			});
		MakeLineGeometry(r, it.PointA, SD.AU, SD.AL, it.PointB, SD.BU, SD.BL);
		if (!bIsBeginning)
		{
			FixAdjacentGeometry(r, i - 1, i, Settings.Join);
		}

	}
	if (Segments.Num() > 0)
	{
		MakeCap(r, 0, true);
		MakeCap(r, Segments.Num() - 1, false);
	}
	return r;
}

FVector2f FPath::GetWidth(const FVector2f& A, const FVector2f& B)
{
	FVector2f Normal = FVector2f(A.Y - B.Y, B.X - A.X).GetSafeNormal();
	return Normal * HalfThickness;
}

TOptional<FVector2f> FPath::DoesIntersect(const FVector2f& P1, const FVector2f& P2, const FVector2f& P3,
	const FVector2f& P4, bool bReturnPossible)
{


	float Denom = (P1.X - P2.X) * (P3.Y - P4.Y) - (P1.Y - P2.Y) * (P3.X - P4.X);
	if (bReturnPossible)
	{
		float A = (P1.X * P2.Y - P1.Y * P2.X);
		float B = (P3.X * P4.Y - P3.Y * P4.X);
		float NumA = A * (P3.X - P4.X) - (P1.X - P2.X) * B;
		float NumB = A * (P3.Y - P4.Y) - (P1.Y - P2.Y) * B;
		if (!FMath::IsNearlyZero(Denom))
		{
			FVector2f Point(NumA / Denom, NumB / Denom);
			return Point;
		}
	}
	else
	{
		float T = ((P1.X - P3.X) * (P3.Y - P4.Y) - (P1.Y - P3.Y) * (P3.X - P4.X)) / Denom;
		float U = ((P1.X - P3.X) * (P1.Y - P2.Y) - (P1.Y - P3.Y) * (P1.X - P2.X)) / Denom;

		if (FMath::IsNearlyZero(T) && FMath::IsNearlyZero(U))
		{
			// Lines are the same
			return P2;
		}

		if (FMath::IsNearlyZero(Denom))
		{
			// Lines are parallel
			return {};
		}

		if (0 <= T && T <= 1)
		{
			FVector2f Point(P1.X + T * (P2.X - P1.X), P1.Y + T * (P2.Y - P1.Y));
			return Point;
		}
		if (0 <= U && U <= 1)
		{
			FVector2f Point(P3.X + U * (P4.X - P3.X), P3.Y + U * (P4.Y - P3.Y));
			return Point;
		}
	}


	return {};
}

void FPath::AppendRoundJoin(FGenerateLineVerticesResult& r, FSegment& aSeg, FSegmentData& aSegData,
	FSegmentData& bSegData, bool bIsUpper, float Resolution)
{
		int dResolution = (int)Resolution + 1;
		const FVector2f& Origin = Points[aSeg.PointB];
		const uint32 iA = bIsUpper ? aSegData.BU : aSegData.BL;
		const uint32 iB = bIsUpper ? bSegData.AU : bSegData.AL;
		const FVector2f A = r.Vertices[iA].Position;
		const FVector2f B = r.Vertices[iB].Position;
		float FromRad = FMath::Atan2(A.Y - Origin.Y, A.X - Origin.X);
		float ToRad = FMath::Atan2(B.Y - Origin.Y, B.X - Origin.X);
		if (FromRad - ToRad > PI) ToRad += TWO_PI;
		if (ToRad - FromRad > PI) FromRad += TWO_PI;
		float DeltaRad = ToRad - FromRad;
		/*
		 * 0
		 * 1
		 */
		uint32 Id = r.Vertices.Num() - 1;

		for (int i = 1; i < dResolution; i++)
		{
			const float theta = FromRad + (DeltaRad * (i / Resolution));
			float Cos = FMath::Cos(theta);
			float Sin = FMath::Sin(theta);

			FScreenVertex Append = {
				{
					Origin.X + HalfThickness.X * Cos,
					Origin.Y + HalfThickness.Y * Sin
				},
				bIsUpper ? UpperUV : LowerUV
			};
			r.Vertices.Add(Append);
		}
		for (int i = dResolution; i > 0; i--)
		{
			if (i == dResolution)
			{
				r.Indices.Append({ aSeg.PointB, iB, Id + i - 1 });
			}
			else if (i == 1)
			{
				r.Indices.Append({ aSeg.PointB, Id + i, iA });
			}
			else
			{
				r.Indices.Append({ aSeg.PointB, Id + i, Id + i - 1 });
			}
		}
}

void FPath::FixAdjacentGeometry(FGenerateLineVerticesResult& r, uint32 SegmentA, uint32 SegmentB,
	ERestylePathJoinType JoinType)
{

		FSegment& sA = Segments[SegmentA];
		FSegment& sB = Segments[SegmentB];

		FSegmentData& sdA = SegmentData[SegmentA];
		FVector2f aAU = r.Vertices[sdA.AU].Position;
		FVector2f aAL = r.Vertices[sdA.AL].Position;
		FVector2f aBU = r.Vertices[sdA.BU].Position;
		FVector2f aBL = r.Vertices[sdA.BL].Position;

		FSegmentData& sdB = SegmentData[SegmentB];
		FVector2f bAU = r.Vertices[sdB.AU].Position;
		FVector2f bAL = r.Vertices[sdB.AL].Position;
		FVector2f bBU = r.Vertices[sdB.BU].Position;
		FVector2f bBL = r.Vertices[sdB.BL].Position;
		FVector2f pIntersectionLower = FVector2f::ZeroVector;
		bool bLowerIntersects = false;
		{
			if (auto IntersectionPoint = DoesIntersect(aAL, aBL, bAL, bBL, false);
				IntersectionPoint.IsSet())
			{
				pIntersectionLower = IntersectionPoint.GetValue();
				bLowerIntersects = true;
			}
		}
		FVector2f pIntersectionUpper = FVector2f::ZeroVector;
		bool bUpperIntersects = false;
		{
			if (auto IntersectionPoint = DoesIntersect(aAU, aBU, bAU, bBU, false);
				IntersectionPoint.IsSet())
			{
				pIntersectionUpper = IntersectionPoint.GetValue();
				bUpperIntersects = true;
			}
		}
		if (JoinType == ERestylePathJoinType::Miter || sA.bIsRadiusProduct || sB.bIsRadiusProduct)
		{
			if (bLowerIntersects)
			{
				r.Vertices[sdA.BL].Position = pIntersectionLower;
				r.Vertices[sdB.AL].Position = pIntersectionLower;
			}
			else
			{
				if (auto IntersectionPoint = DoesIntersect(aAL, aBL, bAL, bBL, true);
					IntersectionPoint.IsSet())
				{
					uint32 Intersection = r.Vertices.Num();
					r.Vertices.Add({ IntersectionPoint.GetValue(), LowerUV });
					r.Indices.Append(
						{
							sA.PointB,
							Intersection,
							sdA.BL,

							sA.PointB,
							sdB.AL,
							Intersection
						}
					);
				}
			}
			if (bUpperIntersects)
			{
				r.Vertices[sdA.BU].Position = pIntersectionUpper;
				r.Vertices[sdB.AU].Position = pIntersectionUpper;
			}
			else
			{
				if (auto IntersectionPoint = DoesIntersect(aAU, aBU, bAU, bBU, true);
					IntersectionPoint.IsSet())
				{
					uint32 Intersection = r.Vertices.Num();
					r.Vertices.Add({ IntersectionPoint.GetValue(), UpperUV });
					r.Indices.Append(
						{
							sA.PointB,
							Intersection,
							sdA.BU,

							sA.PointB,
							sdB.AU,
							Intersection
						}
					);
				}
			}
			return;
		}
		if (JoinType == ERestylePathJoinType::Round)
		{
			if (bLowerIntersects)
			{
				r.Vertices[sdA.BL].Position = pIntersectionLower;
				r.Vertices[sdB.AL].Position = pIntersectionLower;
			}
			else
			{
				AppendRoundJoin(r, sA, sdA, sdB, false, 4);
			}
			if (bUpperIntersects)
			{
				r.Vertices[sdA.BU].Position = pIntersectionUpper;
				r.Vertices[sdB.AU].Position = pIntersectionUpper;
			}
			else
			{
				AppendRoundJoin(r, sA, sdA, sdB, true, 4);
			}
			return;
		}

}

void FPath::MakeLineGeometry(FGenerateLineVerticesResult& r, uint32 iA, uint32 iAU, uint32 iAL, uint32 iB, uint32 iBU,
	uint32 iBL)

{
	r.Indices.Append({
		iA,
		iAU,
		iBU,

		iA,
		iAL,
		iBL,

		iA,
		iB,
		iBU,

		iA,
		iB,
		iBL
		});
}

void FPath::MakeCap(FGenerateLineVerticesResult& r, uint32 iSegment, bool bIsBegin)

{
	FSegment& Segment = Segments[iSegment];
	FSegmentData& Data = SegmentData[iSegment];
	FVector2f Direction = HalfThickness * (bIsBegin
		? (Points[Segment.PointA] - Points[Segment.PointB]).GetSafeNormal()
		: (Points[Segment.PointB] - Points[Segment.PointA]).GetSafeNormal()
		);
	uint32 iOrigin = bIsBegin ? Segment.PointA : Segment.PointB;
	uint32 iUpper = bIsBegin ? Data.AU : Data.BU;
	uint32 iLower = bIsBegin ? Data.AL : Data.BL;

	FVector2f Origin = Points[iOrigin];
	const auto& Width = Segment.Width;
	uint32 Id = r.Vertices.Num();
	r.Vertices.Append({
		{{Origin + Direction + Width}, UpperUV},
		{{Origin + Direction - Width}, LowerUV}
		});
	r.Indices.Append({
		iOrigin, iUpper, Id + 0,
		iOrigin, Id + 0, Id + 1,
		iOrigin, Id + 1, iLower
		});
}

void FPath::InitWithPoints(FGenerateLineVerticesResult& r)
{
	r.Vertices.AddUninitialized(Points.Num());
	for (int i = 0; i < Points.Num(); i++)
	{
		r.Vertices[i] = { Points[i], MidUV };
	}
}

void FPath::Calculate(TArray<FVector2f>& InPoints)

{
	for (int i = 1; i < InPoints.Num(); i++)
	{
		bool bIsEnd = (i + 1) >= InPoints.Num();
		bool bIsBeginning = (i - 1) == 0;
		bool bTryRadius = !bIsEnd && Settings.CornerRadius > 0.f;;
		bool bApplyRadius = false;


		FVector2f A = InPoints[i - 1];
		FVector2f B = InPoints[i];
		if (bIsBeginning)
		{
			Points.Add(A);
		}
		if (bTryRadius)
		{
			auto Is90Deg = [](FVector2f A, FVector2f B)
			{
				float Rad = FMath::Atan2(B.Y - A.Y, B.X - A.X);
				return FMath::IsNearlyEqual(FMath::Abs(Rad), HALF_PI, 0.001f);
			};
			//float MinLength = GetDefault<UWireRestyleSettings>()->DebugInteger;
			/*auto CheckMinLength = [&MinLength](FVector2f A, FVector2f B, FVector2f C) -> bool
			{
				float LengthAB = FVector2f::Distance(A, B);
				float LengthBC = FVector2f::Distance(B, C);
				return LengthAB >= MinLength && LengthBC >= MinLength;
			};*/
			const FVector2f& C = InPoints[i + 1];
			auto HasEnoughLength = [this, i, &InPoints, &A, &B, &C]()->bool
			{
				float LengthAB = FVector2f::Distance(A, B);
				float LengthBC = FVector2f::Distance(B, C);
				float MinLength = FMath::Min(LengthAB, LengthBC);
				float Length = MinLength * Settings.CornerRadius;
				// 0.001 tolerance, so value 2.06250763 will not get approved for thickness 4.125
				return Length - 0.001f > Settings.Thickness * 0.5f;
			};
			if (Is90Deg(B, C))
			{
				bApplyRadius = HasEnoughLength();
			}
			else if (!bIsBeginning && Is90Deg(A, B))
			{
				bApplyRadius = HasEnoughLength();
			}
		}
		if (bApplyRadius)
		{
			const FVector2f& C = InPoints[i + 1];
			float RadianB2A = FMath::Atan2(A.Y - B.Y, A.X - B.X);
			float RadianB2C = FMath::Atan2(C.Y - B.Y, C.X - B.X);
			float LengthAB = FVector2f::Distance(A, B);
			float LengthBC = FVector2f::Distance(B, C);
			float MinLength = FMath::Min(LengthAB, LengthBC);
			float Length = MinLength * Settings.CornerRadius + Settings.Thickness * 0.5f;
			const FVector2f B1 = { B.X + Length * FMath::Cos(RadianB2A), B.Y + Length * FMath::Sin(RadianB2A) };
			const FVector2f B2 = { B.X + Length * FMath::Cos(RadianB2C), B.Y + Length * FMath::Sin(RadianB2C) };
			if (Settings.Join == ERestylePathJoinType::Miter) {
				Points.Append({ B1, B2 });

				FSegment SegmentAB1(Points.Num() - 3, Points.Num() - 2, GetWidth(A, B1), false);
				FSegment SegmentB1B2(Points.Num() - 2, Points.Num() - 1, GetWidth(B1, B2), true);
				Segments.Append({ SegmentAB1, SegmentB1B2 });
			}
			else if (Settings.Join == ERestylePathJoinType::Round)
			{
				float Distance = FVector2f::Distance(B1, B2);
				//@todo this is not a solution to calculate resolution that way
				const int dResolution = FMath::Min(FMath::Max(4, Distance / 8.f), 16);
				//UWireRestyleSettings::Get()->DebugInteger;

				const FVector2f& MidPoint = B;
				FVector2f PreviousPoint = B1;

				Points.Add(B1);
				FSegment SegmentAB1(Points.Num() - 2, Points.Num() - 1, GetWidth(A, B1), false);
				Segments.Add(SegmentAB1);

				for (int x = 1; x <= dResolution; x++)
				{
					float theta = static_cast<float>(x) / static_cast<float>(dResolution);
					FVector2f CurrentPoint = FMath::Lerp(
						FMath::Lerp(B1, MidPoint, theta),
						FMath::Lerp(MidPoint, B2, theta),
						theta);

					Points.Add(CurrentPoint);
					FSegment SegmentPrevCurrent(Points.Num() - 2, Points.Num() - 1, GetWidth(PreviousPoint, CurrentPoint), true);
					PreviousPoint = CurrentPoint;
					Segments.Add(SegmentPrevCurrent);
				}
			}

		}
		else
		{
			Points.Add(B);

			FSegment Segment(
				Points.Num() - 2,
				Points.Num() - 1,
				GetWidth(A, B),
				false
			);
			Segments.Add(Segment);
		}
	}
}

FPathDrawingSlateElement::FPathDrawingSlateElement()
{
	bDestroyed = false;
}
 
void FPathDrawingSlateElement::DrawRenderThread(
	FRHICommandListImmediate& RHICmdList, const void* InWindowBackBuffer)
{
	check(IsInRenderingThread());

	FVertexBuffer _VertexBuffer;
	FIndexBuffer _IndexBuffer;
	_VertexBuffer.InitResource();
	_IndexBuffer.InitResource();

	const FTexture2DRHIRef& Buffer = static_cast<const FTexture2DRHIRef*>(InWindowBackBuffer)->GetReference();
	FVector2f ViewportSize(Buffer->GetSizeX(), Buffer->GetSizeY());

	FRHIRenderPassInfo RPInfo(Buffer.GetReference(), ERenderTargetActions::Load_Store);
	RPInfo.DepthStencilRenderTarget.Action = EDepthStencilTargetActions::DontLoad_DontStore;
	RPInfo.DepthStencilRenderTarget.ExclusiveDepthStencil = FExclusiveDepthStencil::DepthNop_StencilNop;
	TransitionRenderPassTargets(RHICmdList, RPInfo);
	RHICmdList.BeginRenderPass(RPInfo, TEXT("FPathDrawingSlateElement"));
	{
		ClippingRect.Top = FMath::Min(FMath::Max(ClippingRect.Top, 0.f), ViewportSize.Y);
		ClippingRect.Bottom = FMath::Min(FMath::Max(ClippingRect.Bottom, 0.f), ViewportSize.Y);
		ClippingRect.Left = FMath::Min(FMath::Max(ClippingRect.Left, 0.f), ViewportSize.X);
		ClippingRect.Right = FMath::Min(FMath::Max(ClippingRect.Right, 0.f), ViewportSize.X);

		RHICmdList.SetViewport(0, 0, 0, ViewportSize.X, ViewportSize.Y, 1);
		RHICmdList.SetScissorRect(true,
		                          ClippingRect.Left,
		                          ClippingRect.Top,
		                          ClippingRect.Right,
		                          ClippingRect.Bottom);

		TShaderMapRef<FRestyleVertexShader> VertexShader(
			GGlobalShaderMap[GShaderPlatformForFeatureLevel[GMaxRHIFeatureLevel]]);
		TShaderMapRef<FRestylePixelShader> PixelShader(
			GGlobalShaderMap[GShaderPlatformForFeatureLevel[GMaxRHIFeatureLevel]]);
		{
			FSamplerStateRHIRef BilinearClamp1 = TStaticSamplerState<
				SF_Bilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
			FRHISamplerState* SamplerState1 = BilinearClamp1;
			PixelShader->SetShaderParams(RHICmdList, FShaderParams(
				                             FVector4f(Path.Settings.Thickness, 1.0),
				Path.Settings.Color));

			FMatrix ProjectionMatrix = CreateProjectionMatrix(ViewportSize.X, ViewportSize.Y);
			VertexShader->SetViewProjection(RHICmdList, FMatrix44f(ProjectionMatrix));
		}


		FGraphicsPipelineStateInitializer GraphicsPSO;
		RHICmdList.ApplyCachedRenderTargets(GraphicsPSO);
		{
			GraphicsPSO.BlendState = TStaticBlendState<
				CW_RGBA, BO_Add, BF_SourceAlpha, BF_InverseSourceAlpha, BO_Add>::GetRHI();
			if (Path.Settings.bDrawWireframe)
			{
				GraphicsPSO.RasterizerState = TStaticRasterizerState<FM_Wireframe>::GetRHI();
			}
			else
			{
				GraphicsPSO.RasterizerState = TStaticRasterizerState<FM_Solid>::GetRHI();
			}
			GraphicsPSO.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
			GraphicsPSO.BoundShaderState.VertexDeclarationRHI = GScreenVertexDeclaration.VertexDeclarationRHI;
			GraphicsPSO.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
			GraphicsPSO.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
			GraphicsPSO.PrimitiveType = PT_TriangleList;
		}
		SetGraphicsPipelineState(RHICmdList, GraphicsPSO, 0);

		auto [Vertices, Indices] = GenerateLineVertices();
		{
			FRHIResourceCreateInfo CreateInfo(TEXT("Restyle_Path_VertexBuffer"), &Vertices);
			_VertexBuffer.VertexBufferRHI = RHICreateVertexBuffer(Vertices.GetResourceDataSize(),
			                                                      BUF_Dynamic, CreateInfo);
		}

		{
			FRHIResourceCreateInfo CreateInfo(TEXT("Restyle_Path_IndexBuffer"), &Indices);
			_IndexBuffer.IndexBufferRHI = RHICreateIndexBuffer(sizeof(uint32), Indices.GetResourceDataSize(),
			                                                   BUF_Dynamic, CreateInfo);
		}

		RHICmdList.SetStreamSource(0, _VertexBuffer.VertexBufferRHI, 0);

		RHICmdList.DrawIndexedPrimitive(
			_IndexBuffer.IndexBufferRHI,
			/*BaseVertexIndex=*/ 0,
			/*MinIndex=*/ 0,
			/*NumVertices=*/ Vertices.Num(),
			/*StartIndex=*/ 0,
			/*NumPrimitives=*/ Indices.Num() / 3,
			/*NumInstances=*/ 1);
	}
	RHICmdList.EndRenderPass();
	_VertexBuffer.ReleaseResource();
	_IndexBuffer.ReleaseResource();
	bDestroyed = true;
}
 

FGenerateLineVerticesResult FPathDrawingSlateElement::GenerateLineVertices()
{
	return Path.MakeRenderData();
}

FMatrix FPathDrawingSlateElement::CreateProjectionMatrix(uint32 Width, uint32 Height)
{
	// Create ortho projection matrix
	const float Left = 0;
	const float Right = Left + Width;
	const float Top = 0;
	const float Bottom = Top + Height;
	const float ZNear = -100.0f;
	const float ZFar = 100.0f;
	return AdjustProjectionMatrixForRHI(
		FMatrix(
			FPlane(2.0f / (Right - Left), 0, 0, 0),
			FPlane(0, 2.0f / (Top - Bottom), 0, 0),
			FPlane(0, 0, 1 / (ZNear - ZFar), 0),
			FPlane((Left + Right) / (Left - Right), (Top + Bottom) / (Bottom - Top), ZNear / (ZNear - ZFar), 1)
		)
	);
} 
 
