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

	SDefault_GraphNodeK2Default() = default;
	void Construct(const FArguments& InArgs, UK2Node* InNode);
	void UpdateStandardNode_New();
	void UpdateCompactNode_New();
	virtual void UpdateGraphNode() override;
	virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;
	EDTGraphNodeTitleType GetNodeType();
	 
protected:
	TSharedPtr<SImage> MainBackground;
	TSharedPtr<SImage> TitleIcon;
	TSharedPtr<SBorder> MainTitleBorder;
	TSharedPtr<SDefault_NodeTitle> TitleExtraText;
	TSharedPtr<SBorder> ContentBorder;

	TSharedPtr<SHorizontalBox> TitleContent;
	TSharedPtr<STextBlock> CompactTitleTextBlock;
	TSharedPtr<SImage> CompactBody;
	TSharedPtr<SBox> EnabledStateWidgetBox;
};
