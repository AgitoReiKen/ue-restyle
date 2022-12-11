// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#include "SDefault_GraphNodeK2Base.h"

class SDefault_GraphNodeK2Default : public SDefault_GraphNodeK2Base
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeK2Default)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UK2Node* InNode);
	void UpdateCompactNode_New();
	virtual void UpdateGraphNode() override;
	virtual void OnStateUpdated(EDTGraphNodeState NewState) override;

protected:
	TSharedPtr<STextBlock> CompactTitleTextBlock;
	TSharedPtr<SImage> CompactBody;
	TSharedPtr<SBox> EnabledStateWidgetBox;
};
