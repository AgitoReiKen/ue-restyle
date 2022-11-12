// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SDefault_GraphNodeK2Default.h"

class SGraphPin;
class UK2Node_MakeStruct;
struct FOptionalPinFromProperty;

struct FOptionalPinOverrideState
{
	/** Display text to display for this item in the selection widget */
	FText DisplayText;

	/** Tooltip to display for this item on both the node and in the selection widget */
	FText TooltipText;

	/** TRUE if this option will enable the override */
	bool bIsOverrideEnabled;

	/** TRUE if this option will make the value visible/editable*/
	bool bIsValuePinVisible;

	/** TRUE if the override value can be edited */
	bool bIsOverridePinVisible;

	FOptionalPinOverrideState(FText InDisplayText, FText InTooltipText, bool bInIsOverridePinVisible, bool bInIsOverrideEnabled, bool bInIsValuePinVisible)
		: DisplayText(InDisplayText)
		, TooltipText(InTooltipText)
		, bIsOverrideEnabled(bInIsOverrideEnabled)
		, bIsValuePinVisible(bInIsValuePinVisible)
		, bIsOverridePinVisible(bInIsOverridePinVisible)
	{}

	bool operator== (const FOptionalPinOverrideState& InOther) const
	{
		return bIsOverrideEnabled == InOther.bIsOverrideEnabled && bIsValuePinVisible == InOther.bIsValuePinVisible && bIsOverridePinVisible == InOther.bIsOverridePinVisible;
	}
};

class SDefault_GraphNodeMakeStruct : public SDefault_GraphNodeK2Default
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeMakeStruct) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, UK2Node_MakeStruct* InNode);

	/** Callback for the pin for whether the pin should display as enabled */
	bool IsPinEnabled(FOptionalPinFromProperty* InPropertyEntry) const;

	// SGraphNode interface
	virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;
	virtual void CreatePinWidgets() override;
	// End of SGraphNode interface
};
