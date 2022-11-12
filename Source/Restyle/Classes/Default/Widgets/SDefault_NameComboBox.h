// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once
#include "DefineSlateUtils.h"
class SDefault_NameComboBox : public SCompoundWidget
{
public:
	DECLARE_DELEGATE_RetVal_OneParam(FString, FGetNameComboLabel, TSharedPtr<FName>);
	typedef TSlateDelegates<TSharedPtr<FName>>::FOnSelectionChanged FOnNameSelectionChanged;
#pragma region SlateArgs


	SLATE_BEGIN_ARGS(SDefault_NameComboBox)
		:
		_ItemStyle(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("ComboBox.Row"))
		,	_ComboBoxStyle(&FCoreStyle::Get().GetWidgetStyle<FComboBoxStyle>("ComboBox"))
		, _ColorAndOpacity(FSlateColor::UseForeground())
		, _ButtonTextPadding(FMargin(0))
		, _SpacingBetweenTextAndArrow(4.f)
	{
	}

	SLATE_STYLE_ARGUMENT(FTableRowStyle, ItemStyle)
		SLATE_STYLE_ARGUMENT(FComboBoxStyle, ComboBoxStyle)
		SLATE_ARGUMENT(TArray< TSharedPtr<FName> >*, OptionsSource)
		SLATE_ATTRIBUTE(FSlateFontInfo, Font)
		SLATE_ATTRIBUTE(FSlateColor, ColorAndOpacity)
		SLATE_ATTRIBUTE(FMargin, ContentPadding)
		SLATE_ATTRIBUTE(FMargin, ButtonTextPadding)
		SLATE_EVENT(FOnNameSelectionChanged, OnSelectionChanged)
		SLATE_EVENT(FOnComboBoxOpening, OnComboBoxOpening)
		SLATE_ARGUMENT(TSharedPtr<FName>, InitiallySelectedItem)
		SLATE_EVENT(FGetNameComboLabel, OnGetNameLabelForItem)
		SLATE_ARGUMENT(float, SpacingBetweenTextAndArrow)
		SLATE_END_ARGS()
#pragma endregion

	SLATE_CONSTRUCT(SLATE_CONSTRUCT_IMP(InArgs), const FArguments& InArgs)

public:
	virtual TSharedRef<SWidget> MakeItemWidget(TSharedPtr<FName> StringItem);
	virtual void SetSelectedItem(TSharedPtr<FName> NewSelection);
	virtual TSharedPtr<FName> GetSelectedItem();
	virtual void RefreshOptions();
	virtual void ClearSelection();
protected:
	virtual TSharedPtr<FName> OnGetSelection() const { return SelectedItem; }
	virtual void OnSelectionChanged(TSharedPtr<FName> Selection, ESelectInfo::Type SelectInfo);
	virtual FText GetSelectedNameLabel() const;
	virtual FText GetItemNameLabel(TSharedPtr<FName> StringItem) const;
	FGetNameComboLabel GetTextLabelForItem;
	TSharedPtr<FName> SelectedItem;
	TArray<TSharedPtr<FName>> Names;
	TSharedPtr<SComboBox<TSharedPtr<FName>>> NameCombo;
	FOnNameSelectionChanged SelectionChanged;
	TAttribute<FSlateFontInfo> Font;
};
