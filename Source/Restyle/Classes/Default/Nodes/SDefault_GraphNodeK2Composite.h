// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "SDefault_GraphNodeK2Base.h"
class SToolTip;
class UEdGraph;
class UK2Node_Composite;

class SDefault_GraphNodeK2Composite : public SDefault_GraphNodeK2Base
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeK2Composite)
		{
		}

	SLATE_END_ARGS()

	SDefault_GraphNodeK2Composite() = default;
	void Construct(const FArguments& InArgs, UK2Node_Composite* InNode);

	virtual EDTCollapsedNodeType GetNodeType() const;
	virtual void UpdateGraphNode() override;
	virtual TSharedPtr<SToolTip> GetComplexTooltip() override;
	virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;
protected:
	virtual UEdGraph* GetInnerGraph() const;

	FText GetPreviewCornerText() const;
	FText GetTooltipTextForNode() const;

	virtual TSharedRef<SWidget> CreateNodeBody();
	TSharedPtr<SDefault_NodeTitle> TitleExtraText;
	TSharedPtr<SImage> Body;
};
