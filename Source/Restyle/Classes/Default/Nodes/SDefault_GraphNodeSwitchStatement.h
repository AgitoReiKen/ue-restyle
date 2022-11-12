// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/Reply.h"
#include "SDefault_GraphNodeK2Default.h"

class SVerticalBox;
class UK2Node_Switch;

class SDefault_GraphNodeSwitchStatement : public SDefault_GraphNodeK2Default
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeSwitchStatement) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, UK2Node_Switch* InNode);

	// SGraphNode interface
	virtual void CreatePinWidgets() override;

protected:
	virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;
	virtual EVisibility IsAddPinButtonVisible() const override;
	virtual FReply OnAddPin() override;
	// End of SGraphNode interface
};
