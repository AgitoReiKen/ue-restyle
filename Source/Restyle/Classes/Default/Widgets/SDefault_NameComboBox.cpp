// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_NameComboBox.h"

void SDefault_NameComboBox::PreConstruct(const FArguments& InArgs)
{

	SelectionChanged = InArgs._OnSelectionChanged;
	GetTextLabelForItem = InArgs._OnGetNameLabelForItem;
	Font = InArgs._Font;
}

void SDefault_NameComboBox::InConstruct(const FArguments& InArgs)
{
	this->ChildSlot
	[
		SAssignNew(NameCombo, SComboBox< TSharedPtr<FName> >)
		.ComboBoxStyle(InArgs._ComboBoxStyle)
		.ItemStyle(InArgs._ItemStyle)
		.OptionsSource(InArgs._OptionsSource)
		.OnGenerateWidget(this, &SDefault_NameComboBox::MakeItemWidget)
		.OnSelectionChanged(this, &SDefault_NameComboBox::OnSelectionChanged)
		.OnComboBoxOpening(InArgs._OnComboBoxOpening)
		.InitiallySelectedItem(InArgs._InitiallySelectedItem)
		.ContentPadding(InArgs._ContentPadding)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1)
			[
				SNew(STextBlock)
				.ColorAndOpacity(InArgs._ColorAndOpacity)
				.Text(this, &SDefault_NameComboBox::GetSelectedNameLabel)
				.Font(InArgs._Font)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SSpacer)
				.Size(FVector2D(InArgs._SpacingBetweenTextAndArrow, 0))
			]
		]
	];
}

void SDefault_NameComboBox::PostConstruct(const FArguments& InArgs)
{
	SelectedItem = NameCombo->GetSelectedItem();
} 
FText SDefault_NameComboBox::GetItemNameLabel(TSharedPtr<FName> NameItem) const
{
	if (!NameItem.IsValid())
	{
		return FText::GetEmpty();
	}

	return (GetTextLabelForItem.IsBound())
		       ? FText::FromString(GetTextLabelForItem.Execute(NameItem))
		       : FText::FromName(*NameItem);
}

FText SDefault_NameComboBox::GetSelectedNameLabel() const
{
	TSharedPtr<FName> StringItem = NameCombo->GetSelectedItem();
	return GetItemNameLabel(StringItem);
}
 

TSharedRef<SWidget> SDefault_NameComboBox::MakeItemWidget(TSharedPtr<FName> NameItem)
{
	check(NameItem.IsValid());

	return SNew(STextBlock)
		.Text(this, &SDefault_NameComboBox::GetItemNameLabel, NameItem)
		.Font(Font);
}

void SDefault_NameComboBox::OnSelectionChanged(TSharedPtr<FName> Selection, ESelectInfo::Type SelectInfo)
{
	if (Selection.IsValid())
	{
		SelectedItem = Selection;
	}
	SelectionChanged.ExecuteIfBound(Selection, SelectInfo);
}

void SDefault_NameComboBox::SetSelectedItem(TSharedPtr<FName> NewSelection)
{
	NameCombo->SetSelectedItem(NewSelection);
}

TSharedPtr<FName> SDefault_NameComboBox::GetSelectedItem()
{
	return SelectedItem;
}

void SDefault_NameComboBox::RefreshOptions()
{
	NameCombo->RefreshOptions();
}

void SDefault_NameComboBox::ClearSelection()
{
	NameCombo->ClearSelection();
}
