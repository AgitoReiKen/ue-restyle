// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once
#include "Rendering/RenderingCommon.h"
#include "CoreMinimal.h"
#include "RenderResource.h"
#include "RendererInterface.h"
#include "Rendering/RenderingCommon.h"
#include "CanvasTypes.h"
#include "Widgets/SLeafWidget.h"
#include "SlateRHIRenderer/Private/SlateElementIndexBuffer.h"
#include "SlateRHIRenderer/Private/SlateElementVertexBuffer.h"
#include "ScreenRendering.h"

enum class ERestylePathJoinType
{
	Miter,
	Round
}; 
struct FRestylePathSettings
{
	float Thickness;
	FLinearColor Color;
	bool bDrawWireframe;
	ERestylePathJoinType Join;
	float CornerRadius;
}; 
struct FPathRenderData
{
	TResourceArray<FScreenVertex, VERTEXBUFFER_ALIGNMENT> Vertices;
	TResourceArray<uint32, INDEXBUFFER_ALIGNMENT> Indices;
	FPathRenderData()
	{
	}

	FPathRenderData(const FPathRenderData& Other)
		: Vertices(Other.Vertices),
		  Indices(Other.Indices)
	{
	}

	FPathRenderData(FPathRenderData&& Other) noexcept
		: Vertices(MoveTemp(Other.Vertices)),
		  Indices(MoveTemp(Other.Indices))
	{
	}

	FPathRenderData& operator=(const FPathRenderData& Other)
	{
		if (this == &Other)
			return *this;
		Vertices = Other.Vertices;
		Indices = Other.Indices;
		return *this;
	}

	FPathRenderData& operator=(FPathRenderData&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		Vertices = MoveTemp(Other.Vertices);
		Indices = MoveTemp(Other.Indices);
		return *this;
	}
};
class FPath
{
	FVector2f HalfThickness;
	FVector2f LowerUV = { 1.0f, 0.0f };
	FVector2f MidUV = { 0.5f, 0.0f };
	FVector2f UpperUV = { 0.0f, 0.0f };

	struct FSegment
	{
		uint32 PointA;
		uint32 PointB;
		FVector2f Width;
		bool bIsRadiusProduct;

		FSegment(uint32 PointA, uint32 PointB, const FVector2f& Width, bool bIsRadiusProduct)
			: PointA(PointA),
			PointB(PointB),
			Width(Width),
			bIsRadiusProduct(bIsRadiusProduct)
		{
		}

		FSegment(const FSegment& Other)
			: PointA(Other.PointA),
			PointB(Other.PointB),
			Width(Other.Width),
			bIsRadiusProduct(Other.bIsRadiusProduct)
		{
		}

		FSegment(FSegment&& Other) noexcept
			: PointA(Other.PointA),
			PointB(Other.PointB),
			Width(std::move(Other.Width)),
			bIsRadiusProduct(Other.bIsRadiusProduct)
		{
		}

		FSegment& operator=(const FSegment& Other)
		{
			if (this == &Other)
				return *this;
			PointA = Other.PointA;
			PointB = Other.PointB;
			Width = Other.Width;
			bIsRadiusProduct = Other.bIsRadiusProduct;
			return *this;
		}

		FSegment& operator=(FSegment&& Other) noexcept
		{
			if (this == &Other)
				return *this;
			PointA = Other.PointA;
			PointB = Other.PointB;
			Width = std::move(Other.Width);
			bIsRadiusProduct = Other.bIsRadiusProduct;
			return *this;
		}
	};

	struct FJoin
	{
		uint32 SegmentA;
		uint32 SegmentB;
		FVector2f IntersectionPoint;
	};

	struct FSegmentData
	{
		uint32 AU;
		uint32 AL;
		uint32 BU;
		uint32 BL;

		FSegmentData(uint32 AU, uint32 AL, uint32 Bu, uint32 Bl)
			: AU(AU),
			AL(AL),
			BU(Bu),
			BL(Bl)
		{
		}

		FSegmentData(const FSegmentData& Other)
			: AU(Other.AU),
			AL(Other.AL),
			BU(Other.BU),
			BL(Other.BL)
		{
		}

		FSegmentData(FSegmentData&& Other) noexcept
			: AU(Other.AU),
			AL(Other.AL),
			BU(Other.BU),
			BL(Other.BL)
		{
		}

		FSegmentData& operator=(const FSegmentData& Other)
		{
			if (this == &Other)
				return *this;
			AU = Other.AU;
			AL = Other.AL;
			BU = Other.BU;
			BL = Other.BL;
			return *this;
		}

		FSegmentData& operator=(FSegmentData&& Other) noexcept
		{
			if (this == &Other)
				return *this;
			AU = Other.AU;
			AL = Other.AL;
			BU = Other.BU;
			BL = Other.BL;
			return *this;
		}
	};

	TArray<FSegment> Segments;
	TArray<FSegmentData> SegmentData;
public:
	TArray<FVector2f> Points;
	FRestylePathSettings Settings;

	void Init(TArray<FVector2f> InPoints, FRestylePathSettings InSettings);

	FPathRenderData MakeRenderData();

private:
	FVector2f GetWidth(const FVector2f& A, const FVector2f& B);

	TOptional<FVector2f> DoesIntersect(const FVector2f& P1, const FVector2f& P2,
		const FVector2f& P3, const FVector2f& P4,
		bool bReturnPossible);

	void AppendRoundJoin(FPathRenderData& r,
		FSegment& aSeg, FSegmentData& aSegData,
		FSegmentData& bSegData,
		bool bIsUpper, float Resolution);

	void FixAdjacentGeometry(FPathRenderData& r, uint32 SegmentA, uint32 SegmentB,
		ERestylePathJoinType JoinType);

	void MakeLineGeometry(FPathRenderData& r,
		uint32 iA, uint32 iAU, uint32 iAL,
		uint32 iB, uint32 iBU, uint32 iBL
	);

	void MakeCap(FPathRenderData& r, uint32 iSegment, bool bIsBegin);

	void InitWithPoints(FPathRenderData& r);

	void Calculate(TArray<FVector2f>& InPoints);

	float GetMinLength(const FVector2f& A, const FVector2f& B, const FVector2f& C)
	{
		float LengthAB = FVector2f::Distance(A, B);
		float LengthBC = FVector2f::Distance(B, C);
		return FMath::Min(LengthAB, LengthBC);
	}

	float GetCornerRadiusLength(float MinLength)
	{
		return MinLength * Settings.CornerRadius;;
	}

	float GetFixedCornerRadiusLength(float MinLength, float CornerRadiusLength)
	{
		return FMath::Min(MinLength * 0.5f - HalfThickness.X, CornerRadiusLength + HalfThickness.X);
	}
};
 

class FPathDrawingSlateElement : public ICustomSlateElement
{
public:
	FPathDrawingSlateElement();
	std::atomic<bool> bDestroyed;

	virtual void DrawRenderThread(FRHICommandListImmediate& RHICmdList, const void* InWindowBackBuffer) override;

	FPath Path;
	FSlateRect ClippingRect;
protected:
	FMatrix CreateProjectionMatrix(uint32 Width, uint32 Height);

};
