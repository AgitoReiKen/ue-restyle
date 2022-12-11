// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#include "CoreMinimal.h"
#include "Default/Pins/SDefault_Pins.h"
#include "DefaultConnectionDrawingPolicy.h"
class FSlateWindowElementList;
class UEdGraph;
class FDefaultAnimGraphConnectionDrawingPolicy : public FDefaultConnectionDrawingPolicy
{
public:
	// Constructor
	FDefaultAnimGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);

	// FKismetConnectionDrawingPolicy interface
	virtual bool TreatWireAsExecutionPin(UEdGraphPin* InputPin, UEdGraphPin* OutputPin) const override;
	virtual void BuildExecutionRoadmap() override;
	virtual void
	DrawRestyleConnection(const FRestyleConnectionParams& Params, const FConnectionParams& WireParams) override;
	virtual void DetermineStyleOfExecWire(float& Thickness, FLinearColor& WireColor, bool& bDrawBubbles, const FTimePair& Times) override;
	virtual void BuildPinToPinWidgetMap(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries) override;
	virtual void ApplyHoverDeemphasis(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, /*inout*/ float& Thickness, /*inout*/ FLinearColor& WireColor) override;
	// End of FKismetConnectionDrawingPolicy interface

private:
	// Map to cached attribute array on the node
	TMap<UEdGraphPin*, TArrayView<const SDefault_GraphPinPose::FAttributeInfo>> PinAttributes;

	// Handle to compilation delegate
	FDelegateHandle OnBlueprintCompiledHandle;

	// Zoom level of the current panel
	float PanelZoom;
};
