// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/Reply.h"
#include "SDefault_GraphNodeK2Default.h"
#include "KismetNodes/SGraphNodeK2Sequence.h"
class SDefault_GraphNodeK2Sequence : public SDefault_GraphNodeK2Default
{

public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeK2Sequence) {}
	SLATE_END_ARGS()

	SDefault_GraphNodeK2Sequence() = default;
	void Construct(const FArguments& InArgs, UK2Node* InNode);


protected:
	virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;
	virtual FReply OnAddPin() override;
	virtual EVisibility IsAddPinButtonVisible() const override;
};