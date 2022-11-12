// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#include "DefineSlateUtils.h"
#include "SKeySelector.h"

class SDefault_KeySelector : public SKeySelector
{
public:
	SLATE_BEGIN_ARGS(SDefault_KeySelector)
		: _CurrentKey(FKey())
		, _TreeViewWidth(300.f)
		, _TreeViewHeight(400.f)
		, _Font(FEditorStyle::GetFontStyle(TEXT("NormalFont")))
		, _FilterBlueprintBindable(true)
		, _AllowClear(true)
		, _ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("Button"))
		, _ComboButtonStyle(&FAppStyle::Get().GetWidgetStyle<FComboButtonStyle>("ComboButton"))
		, _Spacing(4.f)
		, _SpacingBetweenTextAndArrow(4.f)
		, _bHasDownArrow(false)
		, _ButtonIconSize(12)
		, _ButtonContentPadding(FMargin(0))
	
	{}
	SLATE_ATTRIBUTE(TOptional<FKey>, CurrentKey)
		SLATE_ATTRIBUTE(FOptionalSize, TreeViewWidth)
		SLATE_ATTRIBUTE(FOptionalSize, TreeViewHeight)
		SLATE_EVENT(FOnKeyChanged, OnKeyChanged)
		SLATE_ATTRIBUTE(FSlateFontInfo, Font)
		SLATE_ARGUMENT(bool, FilterBlueprintBindable)
		SLATE_ARGUMENT(bool, AllowClear)
		SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle)
		SLATE_STYLE_ARGUMENT(FComboButtonStyle, ComboButtonStyle)
		SLATE_ARGUMENT(float, Spacing)
		SLATE_ARGUMENT(float, SpacingBetweenTextAndArrow)
		SLATE_ARGUMENT(bool, bHasDownArrow)
		SLATE_ARGUMENT(uint16, ButtonIconSize)
		SLATE_ARGUMENT(FMargin, ButtonContentPadding)
	SLATE_END_ARGS()

	SLATE_CONSTRUCT(SLATE_CONSTRUCT_IMP(InArgs), const FArguments& InArgs);

	const FSlateBrush* GetKeyIconImage_New() const;

};