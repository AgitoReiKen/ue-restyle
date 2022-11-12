// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once
#include "DefineSlateUtils.h"

class SDefault_IndexComboBox : public SCompoundWidget
{
public:
	typedef SListView<TSharedPtr<int32>> SComboList;
	typedef TSlateDelegates<TSharedPtr<int32>>::FOnSelectionChanged FIndexOnSelectionChanged;
	DECLARE_DELEGATE_RetVal_OneParam(FText, FGetIntComboLabel, int32);
#pragma region SlateArgs
	SLATE_BEGIN_ARGS(SDefault_IndexComboBox)
		: _ItemStyle(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("ComboBox.Row"))
		  , _ComboBoxStyle(&FCoreStyle::Get().GetWidgetStyle<FComboBoxStyle>("ComboBox"))
		  , _ColorAndOpacity(FSlateColor::UseForeground())
		  , _SpacingBetweenTextAndArrow(4.f)
		{
		}

		SLATE_STYLE_ARGUMENT(FTableRowStyle, ItemStyle)
		SLATE_STYLE_ARGUMENT(FComboBoxStyle, ComboBoxStyle)
		SLATE_ARGUMENT(TArray<TSharedPtr<int32>>, OptionsSource)
		SLATE_EVENT(FIndexOnSelectionChanged, OnSelectionChanged)
		SLATE_EVENT(FGetIntComboLabel, OnGetDisplayNameForItem)
		SLATE_EVENT(FGetIntComboLabel, OnGetTooltipForItem)
		SLATE_ATTRIBUTE(FSlateFontInfo, Font)
		SLATE_ATTRIBUTE(FSlateColor, ColorAndOpacity)
		SLATE_ATTRIBUTE(FMargin, ContentPadding)
		SLATE_EVENT(FOnComboBoxOpening, OnComboBoxOpening)
		SLATE_ARGUMENT(int32, InitiallySelectedItem)
		SLATE_ARGUMENT(float, SpacingBetweenTextAndArrow)
	SLATE_END_ARGS()
#pragma endregion

	SLATE_CONSTRUCT(SLATE_CONSTRUCT_IMP(InArgs), const FArguments& InArgs)

	virtual TSharedRef<SWidget> MakeItemWidget(TSharedPtr<int32> NameItem);
	virtual TSharedPtr<int32> GetSelectedItem();
protected:
	virtual void OnSelectionChangedInternal(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo);
	virtual FText GetItemDisplayName(int32 RowIndex) const;
	virtual FText GetItemTooltip(int32 RowIndex) const;
	virtual FText GetSelectedIntLabel() const;


	TArray<TSharedPtr<int32>> OptionsSource;
	TSharedPtr<SComboBox<TSharedPtr<int32>>> ComboBox;
	FIndexOnSelectionChanged OnSelectionChanged;
	TWeakPtr<int32> CurrentSelection;
	TAttribute<FSlateFontInfo> Font;

	TSharedPtr<int32> SelectedItem;
	FGetIntComboLabel OnGetDisplayName;
	FGetIntComboLabel OnGetTooltip;
};
