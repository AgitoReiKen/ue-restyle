// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "DefineSlateUtils.h"
#include "SPinTypeSelector.h"

class SDefault_PinTypeSelector : public SPinTypeSelector
{
	SLATE_BEGIN_ARGS(SDefault_PinTypeSelector)
		: _TargetPinType()
		, _Schema(nullptr)
		, _SchemaAction(nullptr)
		, _TypeTreeFilter(ETypeTreeFilter::None)
		, _bAllowArrays(true)
		, _TreeViewWidth(300.f)
		, _TreeViewHeight(400.f)
		, _Font(FAppStyle::GetFontStyle(TEXT("NormalFont")))
		, _SelectorType(ESelectorType::Full)
		, _TypeComboButtonStyle(nullptr)
		, _TypeComboButtonPadding(FMargin(0))
		, _TypeComboButtonContentSpacing(0.f)
		, _ReadOnly(false)

		{
		}
		SLATE_STYLE_ARGUMENT(FComboButtonStyle, TypeComboButtonStyle)
		SLATE_ARGUMENT(FMargin, TypeComboButtonPadding)
		SLATE_ARGUMENT(float, TypeComboButtonContentSpacing)
		SLATE_ATTRIBUTE(FEdGraphPinType, TargetPinType)
		SLATE_ARGUMENT(const UEdGraphSchema*, Schema)
		SLATE_ARGUMENT(TWeakPtr<const FEdGraphSchemaAction>, SchemaAction)
		SLATE_ARGUMENT(ETypeTreeFilter, TypeTreeFilter)
		SLATE_ARGUMENT(bool, bAllowArrays)
		SLATE_ATTRIBUTE(FOptionalSize, TreeViewWidth)
		SLATE_ATTRIBUTE(FOptionalSize, TreeViewHeight)
		SLATE_EVENT(FOnPinTypeChanged, OnPinTypePreChanged)
		SLATE_EVENT(FOnPinTypeChanged, OnPinTypeChanged)
		SLATE_ATTRIBUTE(FSlateFontInfo, Font)
		SLATE_ARGUMENT(ESelectorType, SelectorType)
		SLATE_ATTRIBUTE(bool, ReadOnly)
		SLATE_ARGUMENT_DEPRECATED(TSharedPtr<class IPinTypeSelectorFilter>, CustomFilter, 5.1, "Please use CustomFilters instead")
		SLATE_ARGUMENT(TArray<TSharedPtr<class IPinTypeSelectorFilter>>, CustomFilters)
	SLATE_END_ARGS()

public:
	SLATE_CONSTRUCT(
		SLATE_CONSTRUCT_IMP(InArgs, GetPinTypeTreeFunc),
		const FArguments& InArgs,
		FGetPinTypeTree GetPinTypeTreeFunc
	)
	const FComboButtonStyle* TypeComboButtonStyle;
};
