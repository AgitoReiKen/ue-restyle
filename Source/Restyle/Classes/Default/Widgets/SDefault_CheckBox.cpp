// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_CheckBox.h"

void SDefault_CheckBox::PreConstruct(const FArguments& InArgs)
{
	check(InArgs._Style != nullptr);
	Style = InArgs._Style;

	UncheckedImage = InArgs._UncheckedImage;
	UncheckedHoveredImage = InArgs._UncheckedHoveredImage;
	UncheckedPressedImage = InArgs._UncheckedPressedImage;

	CheckedImage = InArgs._CheckedImage;
	CheckedHoveredImage = InArgs._CheckedHoveredImage;
	CheckedPressedImage = InArgs._CheckedPressedImage;

	UndeterminedImage = InArgs._UndeterminedImage;
	UndeterminedHoveredImage = InArgs._UndeterminedHoveredImage;
	UndeterminedPressedImage = InArgs._UndeterminedPressedImage;

	BackgroundImage = InArgs._BackgroundImage;
	BackgroundHoveredImage = InArgs._BackgroundHoveredImage;
	BackgroundPressedImage = InArgs._BackgroundPressedImage;

	PaddingOverride = InArgs._Padding;
	ForegroundColorOverride = InArgs._ForegroundColor;
	BorderBackgroundColorOverride = InArgs._BorderBackgroundColor;
	CheckBoxTypeOverride = InArgs._Type;

	HorizontalAlignment = InArgs._HAlign;
	bCheckBoxContentUsesAutoWidth = InArgs._CheckBoxContentUsesAutoWidth;

	bIsPressed = false;
	bIsFocusable = InArgs._IsFocusable;
	 
	IsCheckboxChecked = InArgs._IsChecked;
	OnCheckStateChanged = InArgs._OnCheckStateChanged;

	ClickMethod = InArgs._ClickMethod;
	TouchMethod = InArgs._TouchMethod;
	PressMethod = InArgs._PressMethod;

	OnGetMenuContent = InArgs._OnGetMenuContent;

	HoveredSound = InArgs._HoveredSoundOverride.Get(InArgs._Style->HoveredSlateSound);
	CheckedSound = InArgs._CheckedSoundOverride.Get(InArgs._Style->CheckedSlateSound);
	UncheckedSound = InArgs._UncheckedSoundOverride.Get(InArgs._Style->UncheckedSlateSound);
}

void SDefault_CheckBox::InConstruct(const FArguments& InArgs)
{
	BuildCheckBox_New(InArgs._Content.Widget);
}

void SDefault_CheckBox::PostConstruct(const FArguments& InArgs)
{
}

void SDefault_CheckBox::BuildCheckBox_New(TSharedRef<SWidget> InContent)
{
	if (ContentContainer.IsValid())
	{
		ContentContainer->SetContent(SNullWidget::NullWidget);
	}

	ESlateCheckBoxType::Type CheckBoxType = OnGetCheckBoxType();
	/*
	 * padding is applied to content
	 * padding needs to be applied on icon
	 *  ___   _________
	 * | x | | content |
	 *  ---   ---------
	 */
	if (CheckBoxType == ESlateCheckBoxType::CheckBox)
	{
		// Check boxes use a separate check button to the side of the user's content (often, a text label or icon.)
		SHorizontalBox::FSlot* ContentSlot;
		this->ChildSlot
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew(SBorder)
				.BorderImage(this, &SDefault_CheckBox::OnGetBackgroundImage)
				.Padding(Style->Padding)
				[
					SNew(SImage)
					.Image(this, &SDefault_CheckBox::OnGetCheckImage)
					.ColorAndOpacity(FSlateColor::UseForeground())
				] 
			]
			+ SHorizontalBox::Slot()
			.Padding(0)
			//.Padding(TAttribute<FMargin>(this, &SCheckBox::OnGetPadding))
			.VAlign(VAlign_Center)
			.Expose(ContentSlot)
			[
				SAssignNew(ContentContainer, SBorder)
				.BorderImage(FStyleDefaults::GetNoBrush())
				.Padding(0.0f)
				[
					InContent
				]
			]
		];
		if (bCheckBoxContentUsesAutoWidth)
		{
			ContentSlot->SetAutoWidth();
		}
	}
	else if (ensure(CheckBoxType == ESlateCheckBoxType::ToggleButton))
	{
		// Toggle buttons have a visual appearance that is similar to a Slate button
		this->ChildSlot
		[
			SAssignNew(ContentContainer, SBorder)
			.BorderImage(this, &SDefault_CheckBox::OnGetCheckImage)
			.Padding(this, &SDefault_CheckBox::OnGetPadding)
			.BorderBackgroundColor(this, &SDefault_CheckBox::OnGetBorderBackgroundColor)
			.HAlign(HorizontalAlignment)
			[
				InContent
			]
		];
	}
}
