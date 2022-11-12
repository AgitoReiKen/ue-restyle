// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_MultiLineEditableTextBox.h"

#include "Widgets/Notifications/SPopUpErrorText.h"


void SDefault_MultiLineEditableTextBox::PreConstruct(const FArguments& InArgs)
{
	check(InArgs._Style);
	Style = InArgs._Style;

	BorderImageNormal = &InArgs._Style->BackgroundImageNormal;
	BorderImageHovered = &InArgs._Style->BackgroundImageHovered;
	BorderImageFocused = &InArgs._Style->BackgroundImageFocused;
	BorderImageReadOnly = &InArgs._Style->BackgroundImageReadOnly;

	PaddingOverride = InArgs._Padding;
	HScrollBarPaddingOverride = InArgs._HScrollBarPadding;
	VScrollBarPaddingOverride = InArgs._VScrollBarPadding;
	FontOverride = InArgs._Font;
	ForegroundColorOverride = InArgs._ForegroundColor;
	BackgroundColorOverride = InArgs._BackgroundColor;
	ReadOnlyForegroundColorOverride = InArgs._ReadOnlyForegroundColor;
	FocusedForegroundColorOverride = InArgs._FocusedForegroundColor;
	bSelectWordOnMouseDoubleClick = InArgs._SelectWordOnMouseDoubleClick;

	bHasExternalHScrollBar = InArgs._HScrollBar.IsValid();
	bHasExternalVScrollBar = InArgs._VScrollBar.IsValid();
	HScrollBar = InArgs._HScrollBar;
	VScrollBar = InArgs._VScrollBar;
	ErrorReportingSpacing = InArgs._ErrorReportingSpacing;
	//DefaultScrollBarThickness = InArgs._DefaultScrollBarThickness;
	//ErrorReporting = InArgs._ErrorReporting;
}

void SDefault_MultiLineEditableTextBox::InConstruct(const FArguments& InArgs)
{
	if (!bHasExternalHScrollBar && !HScrollBar.IsValid())
	{
		// Create and use our own scrollbar
		HScrollBar = SNew(SScrollBar)
			.Style(&InArgs._Style->ScrollBarStyle)
			.Orientation(Orient_Horizontal)
			.AlwaysShowScrollbar(InArgs._AlwaysShowScrollbars);
			//.Thickness(DefaultScrollBarThickness);
	}

	if (!bHasExternalVScrollBar && !VScrollBar.IsValid())
	{
		// Create and use our own scrollbar
		VScrollBar = SNew(SScrollBar)
			.Style(&InArgs._Style->ScrollBarStyle)
			.Orientation(Orient_Vertical)
			.AlwaysShowScrollbar(InArgs._AlwaysShowScrollbars);
			//.Thickness(DefaultScrollBarThickness);
	}

	SBorder::Construct(SBorder::FArguments()
	                   .BorderImage(this, &SDefault_MultiLineEditableTextBox::GetBorderImage)
	                   .BorderBackgroundColor(this, &SDefault_MultiLineEditableTextBox::DetermineBackgroundColor)
	                   .ForegroundColor(this, &SDefault_MultiLineEditableTextBox::DetermineForegroundColor)
	                   .Padding(this, &SDefault_MultiLineEditableTextBox::DeterminePadding)
		[
			SAssignNew(Box, SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .VAlign(VAlign_Fill)
			  .HAlign(HAlign_Fill)
			  .FillWidth(1)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				  .VAlign(VAlign_Fill)
				  .HAlign(HAlign_Fill)
				  .FillHeight(1)
				[
					SAssignNew(EditableText, SMultiLineEditableText)
					.Text(InArgs._Text)
					.HintText(InArgs._HintText)
					.SearchText(InArgs._SearchText)
					.TextStyle(InArgs._TextStyle)
					.Marshaller(InArgs._Marshaller)
					.Font(this, &SDefault_MultiLineEditableTextBox::DetermineFont)
					.IsReadOnly(InArgs._IsReadOnly)
					.AllowMultiLine(InArgs._AllowMultiLine)
					.OnContextMenuOpening(InArgs._OnContextMenuOpening)
					.OnIsTypedCharValid(InArgs._OnIsTypedCharValid)
					.OnTextChanged(InArgs._OnTextChanged)
					.OnTextCommitted(InArgs._OnTextCommitted)
					.OnCursorMoved(InArgs._OnCursorMoved)
					.ContextMenuExtender(InArgs._ContextMenuExtender)
					.CreateSlateTextLayout(InArgs._CreateSlateTextLayout)
					.Justification(InArgs._Justification)
					.RevertTextOnEscape(InArgs._RevertTextOnEscape)
					.SelectAllTextWhenFocused(InArgs._SelectAllTextWhenFocused)
					.SelectWordOnMouseDoubleClick(InArgs._SelectWordOnMouseDoubleClick)
					.ClearTextSelectionOnFocusLoss(InArgs._ClearTextSelectionOnFocusLoss)
					.ClearKeyboardFocusOnCommit(InArgs._ClearKeyboardFocusOnCommit)
					.LineHeightPercentage(InArgs._LineHeightPercentage)
					.Margin(InArgs._Margin)
					.WrapTextAt(InArgs._WrapTextAt)
					.AutoWrapText(InArgs._AutoWrapText)
					.WrappingPolicy(InArgs._WrappingPolicy)
					.HScrollBar(HScrollBar)
					.VScrollBar(VScrollBar)
					.OnHScrollBarUserScrolled(InArgs._OnHScrollBarUserScrolled)
					.OnVScrollBarUserScrolled(InArgs._OnVScrollBarUserScrolled)
					.OnKeyCharHandler(InArgs._OnKeyCharHandler)
					.OnKeyDownHandler(InArgs._OnKeyDownHandler)
					.ModiferKeyForNewLine(InArgs._ModiferKeyForNewLine)
					.VirtualKeyboardOptions(InArgs._VirtualKeyboardOptions)
					.VirtualKeyboardTrigger(InArgs._VirtualKeyboardTrigger)
					.VirtualKeyboardDismissAction(InArgs._VirtualKeyboardDismissAction)
					.TextShapingMethod(InArgs._TextShapingMethod)
					.TextFlowDirection(InArgs._TextFlowDirection)
					.AllowContextMenu(InArgs._AllowContextMenu)
					.OverflowPolicy(InArgs._OverflowPolicy)
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(HScrollBarPaddingBox, SBox)
					.Padding(this, &SDefault_MultiLineEditableTextBox::DetermineHScrollBarPadding)
					[
						HScrollBar.ToSharedRef()
					]
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SAssignNew(VScrollBarPaddingBox, SBox)
				.Padding(this, &SDefault_MultiLineEditableTextBox::DetermineVScrollBarPadding)
				[
					VScrollBar.ToSharedRef()
				]
			]
		]
	);
}

void SDefault_MultiLineEditableTextBox::PostConstruct(const FArguments& InArgs)
{
}

void SDefault_MultiLineEditableTextBox::SetErrorMessage(const FText& InError)
{
	SetErrorMessage(InError.ToString());
}

void SDefault_MultiLineEditableTextBox::SetErrorMessage(const FString& InError)
{
	const bool bHaveError = !InError.IsEmpty();

	if (!bHaveError && ErrorReporting.IsValid())
	{
		Box->RemoveSlot(ErrorReporting->AsWidget());
		ErrorReporting = nullptr;
	}

	if (bHaveError && !ErrorReporting.IsValid())
	{
		// No error reporting was specified; make a default one
		TSharedPtr<SPopupErrorText> ErrorTextWidget;
		Box->AddSlot()
		   .AutoWidth()
		   .Padding(ErrorReportingSpacing, 0, 0, 0)
		[
			SAssignNew(ErrorTextWidget, SPopupErrorText)
		];
		ErrorReporting = ErrorTextWidget;
		ErrorReporting->SetError(InError);
	}
}

const FSlateBrush* SDefault_MultiLineEditableTextBox::GetBorderImage() const
{
	if (EditableText->IsTextReadOnly())
	{
		return BorderImageReadOnly;
	}
	if (EditableText->HasKeyboardFocus())
	{
		return BorderImageFocused;
	}
	if (EditableText->IsHovered())
	{
		return BorderImageHovered;
	}
	return BorderImageNormal;
}

FSlateColor SDefault_MultiLineEditableTextBox::DetermineForegroundColor() const
{
	check(Style);

	FSlateColor Result = FSlateColor::UseStyle();

	if (EditableText->IsTextReadOnly())
	{
		if (ReadOnlyForegroundColorOverride.IsSet())
		{
			Result = ReadOnlyForegroundColorOverride.Get();
		}
		else if (ForegroundColorOverride.IsSet())
		{
			Result = ForegroundColorOverride.Get();
		}

		if (Result == FSlateColor::UseStyle())
		{
			return Style->ReadOnlyForegroundColor;
		}
		return Result;
	}
	if (HasKeyboardFocus())
	{
		if (FocusedForegroundColorOverride.IsSet())
		{
			Result = FocusedForegroundColorOverride.Get();
		}
		else if (ForegroundColorOverride.IsSet())
		{
			Result = ForegroundColorOverride.Get();
		}

		if (Result == FSlateColor::UseStyle())
		{
			return Style->FocusedForegroundColor;
		}
		return Result;
	}
	if (ForegroundColorOverride.IsSet())
	{
		Result = ForegroundColorOverride.Get();
	}

	if (Result == FSlateColor::UseStyle())
	{
		return Style->ForegroundColor;
	}
	return Result;
}
