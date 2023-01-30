// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once
#include "BlueprintConnectionDrawingPolicy.h"
#include "ConnectionDrawingPolicy.h"

#include "UObject/ConstructorHelpers.h"
struct FRestyleConnectionParams
{
	FGeometry Start;
	FGeometry End;
	FGeometry StartNodeGeometry;
	FGeometry EndNodeGeometry;
	uint32 OutPinId;
	uint32 InPinId;
	uint32 NumInputPins;
	uint32 NumOutputPins;
};
/* Disable warning about hiding virtual function by DrawConnection */
#pragma warning (push)
#pragma warning (disable: 4263)
#pragma warning (disable: 4264)
class FDefaultConnectionDrawingPolicy : public FKismetConnectionDrawingPolicy
{
public:

	FDefaultConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor,
		const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);

	virtual void DrawRestyleConnection(const FRestyleConnectionParams& Params, const FConnectionParams& WireParams, TArray<FVector2f>* InPoints = nullptr);
	virtual void DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2D& StartPoint,
		const FVector2D& EndPoint, UEdGraphPin* Pin) override;
	virtual void ApplyHoverDeemphasis(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, float& Thickness,
		FLinearColor& WireColor) override;

protected:

	virtual void DrawPinGeometries(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries,
		FArrangedChildren& ArrangedNodes) override;
	void UpdateSplineHover(const TArray<FVector2f>& Points, const FConnectionParams& Params, float ZoomValue);
	FGeometry GetNodeGeometryByPinWidget(SGraphPin* PinWidget, const FArrangedChildren& ArrangedNodes);
	uint32 GetPinId(SGraphPin* PinWidget);
	void GetNumPinsAndPinId(SGraphPin* PinWidget, uint32& PinId, uint32& NumPins);


	TArray<FVector2f> MakePathPoints(const FRestyleConnectionParams& Params, const FConnectionParams& WireParams);
	void DrawPath(TArray<FVector2f>& Points, const FConnectionParams& WireParams);
	void DrawBubbles(const TArray<FVector2f>& Points, float TotalLength, const FConnectionParams& WireParams);
	void DrawMidpointImage(const TArray<FVector2f>& Points, float TotalLength, const FConnectionParams& WireParams);
	float Zoomed(float Value)
	{
		return Value * ZoomFactor;
	}
	// Example output for period 4, id 0,1,2..
	// 0 1 2 1 0 1 2 1 0
	int ApplyTriWave(int Id, int Period)
	{
		return abs(((Id + Period / 2) % Period) - Period / 2);
	}
};
#pragma warning(pop)