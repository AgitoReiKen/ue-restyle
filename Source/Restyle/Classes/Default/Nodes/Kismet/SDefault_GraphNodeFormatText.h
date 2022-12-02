// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SDefault_GraphNodeK2Default.h"

class SVerticalBox;
class UK2Node_FormatText;

class SDefault_GraphNodeFormatText : public SDefault_GraphNodeK2Default
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeFormatText) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UK2Node_FormatText* InNode);

	// SGraphNode interface
	virtual void CreatePinWidgets() override;

protected:
	virtual void CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox) override;
	virtual EVisibility IsAddPinButtonVisible() const override;
	virtual FReply OnAddPin() override;
	// End of SGraphNode interface
};
