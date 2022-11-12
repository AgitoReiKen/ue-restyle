// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_IndexComboBox.h"


void SDefault_IndexComboBox::PreConstruct(const FArguments& InArgs)
{
	OnGetTooltip = InArgs._OnGetTooltipForItem;
	OnGetDisplayName = InArgs._OnGetDisplayNameForItem;
	OnSelectionChanged = InArgs._OnSelectionChanged;
	Font = InArgs._Font;
	OptionsSource = InArgs._OptionsSource;
}

void SDefault_IndexComboBox::InConstruct(const FArguments& InArgs)
{
	TSharedPtr<int32>* _SelectedItem =
		OptionsSource.FindByPredicate([&InArgs](const TSharedPtr<int32>& ptr)
		{
			return (*ptr) == InArgs._InitiallySelectedItem;
		});
	check(_SelectedItem)
	this->ChildSlot
	[
		SAssignNew(ComboBox, SComboBox< TSharedPtr<int32> >)
		.ComboBoxStyle(InArgs._ComboBoxStyle)
		.ItemStyle(InArgs._ItemStyle)
		.OptionsSource(&OptionsSource)
		.OnGenerateWidget(this, &SDefault_IndexComboBox::MakeItemWidget)
		.OnSelectionChanged(this, &SDefault_IndexComboBox::OnSelectionChangedInternal)
		.OnComboBoxOpening(InArgs._OnComboBoxOpening)
		.InitiallySelectedItem(*_SelectedItem)
		.ContentPadding(InArgs._ContentPadding)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1)
			[
				SNew(STextBlock)
				.ColorAndOpacity(InArgs._ColorAndOpacity)
				.Text(this, &SDefault_IndexComboBox::GetSelectedIntLabel)
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

void SDefault_IndexComboBox::PostConstruct(const FArguments& InArgs)
{
	SelectedItem = ComboBox->GetSelectedItem();
}

TSharedRef<SWidget> SDefault_IndexComboBox::MakeItemWidget(TSharedPtr<int32> NameItem)
{
	check(NameItem.IsValid());

	return SNew(STextBlock)
		.Text(this, &SDefault_IndexComboBox::GetItemDisplayName, *NameItem)
		.ToolTipText(this, &SDefault_IndexComboBox::GetItemTooltip, *NameItem)
		.Font(Font);
}

TSharedPtr<int32> SDefault_IndexComboBox::GetSelectedItem()
{
	return SelectedItem;
}

FText SDefault_IndexComboBox::GetItemDisplayName(int32 RowIndex) const
{
	return OnGetDisplayName.Execute(RowIndex);
}

FText SDefault_IndexComboBox::GetItemTooltip(int32 RowIndex) const
{
	return OnGetTooltip.Execute(RowIndex);
}

FText SDefault_IndexComboBox::GetSelectedIntLabel() const
{
	return GetItemDisplayName(*ComboBox->GetSelectedItem());
}

void SDefault_IndexComboBox::OnSelectionChangedInternal(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	if (CurrentSelection.Pin() != NewSelection)
	{
		CurrentSelection = NewSelection;
		// Close the popup as soon as the selection changes
		ComboBox->SetIsOpen(false);

		OnSelectionChanged.ExecuteIfBound(NewSelection, SelectInfo);
	}
}
