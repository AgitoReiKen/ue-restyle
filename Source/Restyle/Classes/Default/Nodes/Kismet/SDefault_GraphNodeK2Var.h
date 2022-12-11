// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateColor.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SDefault_GraphNodeK2Base.h"

class SDefault_GraphNodeK2Var : public SDefault_GraphNodeK2Base
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeK2Var) {}
	SLATE_END_ARGS()
	 
	SDefault_GraphNodeK2Var() = default;
	void Construct(const FArguments& InArgs, UK2Node* InNode);
	EDTVarType GetVarNodeType() const;
	virtual void OnStateUpdated(EDTGraphNodeState NewState) override; 
	// SGraphNode interface
	virtual void UpdateGraphNode() override;
	// End of SGraphNode interface
	virtual bool IsInvalid() const override;
protected:
	FSlateColor GetVariableColor() const;

	// Allow derived classes to override title widget
	virtual TSharedRef<SWidget> UpdateTitleWidget(FText InTitleText, TSharedPtr<SWidget> InTitleWidget, EHorizontalAlignment& InOutTitleHAlign, FMargin& InOutTitleMargin) const;
	TSharedPtr<SImage> VarNodeBody;
	mutable TSharedPtr<SWidget> TitleTextBlock;
	FLinearColor CachedVariableColor;
	bool bVariableColorIsWhite;
};
