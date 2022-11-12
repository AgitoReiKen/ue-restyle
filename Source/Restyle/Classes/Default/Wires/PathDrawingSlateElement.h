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
#include "WireShaders.h"
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
struct FGenerateLineVerticesResult
{
	TResourceArray<FScreenVertex, VERTEXBUFFER_ALIGNMENT> Vertices;
	TResourceArray<uint32, INDEXBUFFER_ALIGNMENT> Indices;
	FGenerateLineVerticesResult()
	{
	}

	FGenerateLineVerticesResult(const FGenerateLineVerticesResult& Other)
		: Vertices(Other.Vertices),
		  Indices(Other.Indices)
	{
	}

	FGenerateLineVerticesResult(FGenerateLineVerticesResult&& Other) noexcept
		: Vertices(MoveTemp(Other.Vertices)),
		  Indices(MoveTemp(Other.Indices))
	{
	}

	FGenerateLineVerticesResult& operator=(const FGenerateLineVerticesResult& Other)
	{
		if (this == &Other)
			return *this;
		Vertices = Other.Vertices;
		Indices = Other.Indices;
		return *this;
	}

	FGenerateLineVerticesResult& operator=(FGenerateLineVerticesResult&& Other) noexcept
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

	FGenerateLineVerticesResult MakeRenderData();

private:
	FVector2f GetWidth(const FVector2f& A, const FVector2f& B);

	TOptional<FVector2f> DoesIntersect(const FVector2f& P1, const FVector2f& P2,
		const FVector2f& P3, const FVector2f& P4,
		bool bReturnPossible);

	void AppendRoundJoin(FGenerateLineVerticesResult& r,
		FSegment& aSeg, FSegmentData& aSegData,
		FSegmentData& bSegData,
		bool bIsUpper, float Resolution);

	void FixAdjacentGeometry(FGenerateLineVerticesResult& r, uint32 SegmentA, uint32 SegmentB,
		ERestylePathJoinType JoinType);

	void MakeLineGeometry(FGenerateLineVerticesResult& r,
		uint32 iA, uint32 iAU, uint32 iAL,
		uint32 iB, uint32 iBU, uint32 iBL
	);

	void MakeCap(FGenerateLineVerticesResult& r, uint32 iSegment, bool bIsBegin);

	void InitWithPoints(FGenerateLineVerticesResult& r);

	void Calculate(TArray<FVector2f>& InPoints);
};
class FPathDrawingSlateElement : public ICustomSlateElement
{
public:
	FPathDrawingSlateElement();
	bool bDestroyed;

	virtual void DrawRenderThread(FRHICommandListImmediate& RHICmdList, const void* InWindowBackBuffer) override;

	FPath Path;
	FSlateRect ClippingRect;
protected:
	FGenerateLineVerticesResult GenerateLineVertices();
	FMatrix CreateProjectionMatrix(uint32 Width, uint32 Height);

};
