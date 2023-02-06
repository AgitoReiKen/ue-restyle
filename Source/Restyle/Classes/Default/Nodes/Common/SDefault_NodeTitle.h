// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#include "SGraphNode.h"
#include "Themes/Default/NodeRestyleDefault.h"

class SDefault_NodeTitle : public SNodeTitle
{
public:
	SLATE_BEGIN_ARGS(SDefault_NodeTitle)
		{
		}

		// Title text to display, auto-binds to get the title if not set externally
		SLATE_ATTRIBUTE(FText, Text)

	SLATE_END_ARGS() 
	void Construct(const FArguments& InArgs, UEdGraphNode* Node, const FLinearColor& TextColor,
		const FName& InTextBlockStyle, const TArray<FString>& InIgnoreLineStartsWith = {});
	void RebuildWidget_New();
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	FText GetNodeTitle_New() const;
	TSharedPtr<STextBlock> ExtraTextBlock;
private:
	TArray<FString> IgnoreLineStartsWith;
	FLinearColor Color;
	FName TextBlockStyle;
};
