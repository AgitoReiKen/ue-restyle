// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_EditableTextBox.h"

#include "Widgets/Notifications/SPopUpErrorText.h"

void SDefault_EditableTextBox::PreConstruct(const FArguments& InArgs)
{
	check(InArgs._Style);
	SetStyle(InArgs._Style);

	PaddingOverride = InArgs._Padding;
	FontOverride = InArgs._Font;
	ForegroundColorOverride = InArgs._ForegroundColor;
	BackgroundColorOverride = InArgs._BackgroundColor;
	ReadOnlyForegroundColorOverride = InArgs._ReadOnlyForegroundColor;
	FocusedForegroundColorOverride = InArgs._FocusedForegroundColor;
	OnTextChanged = InArgs._OnTextChanged;
	OnVerifyTextChanged = InArgs._OnVerifyTextChanged;
	OnTextCommitted = InArgs._OnTextCommitted;
	ErrorReportingSpacing = InArgs._ErrorReportingSpacing;
}

void SDefault_EditableTextBox::InConstruct(const FArguments& InArgs)
{
	SBorder::Construct(SBorder::FArguments()
	                   .BorderImage(this, &SDefault_EditableTextBox::GetBorderImage)
	                   .BorderBackgroundColor(this, &SDefault_EditableTextBox::DetermineBackgroundColor)
	                   .ForegroundColor(this, &SDefault_EditableTextBox::DetermineForegroundColor)
	                   .Padding(0.f)
		[
			SAssignNew(Box, SHorizontalBox)

			+ SHorizontalBox::Slot()
			  .VAlign(VAlign_Fill)
			  .HAlign(HAlign_Fill)
			  .FillWidth(1)
			[
				SAssignNew(PaddingBox, SBox)
				.Padding(this, &SDefault_EditableTextBox::DeterminePadding)
				.VAlign(VAlign_Center)
				[
					SAssignNew(EditableText, SEditableText)
					.Text(InArgs._Text)
					.HintText(InArgs._HintText)
					.SearchText(InArgs._SearchText)
					.Font(this, &SDefault_EditableTextBox::DetermineFont)
					.IsReadOnly(InArgs._IsReadOnly)
					.IsPassword(InArgs._IsPassword)
					.IsCaretMovedWhenGainFocus(InArgs._IsCaretMovedWhenGainFocus)
					.SelectAllTextWhenFocused(InArgs._SelectAllTextWhenFocused)
					.RevertTextOnEscape(InArgs._RevertTextOnEscape)
					.ClearKeyboardFocusOnCommit(InArgs._ClearKeyboardFocusOnCommit)
					.Justification(InArgs._Justification)
					.AllowContextMenu(InArgs._AllowContextMenu)
					.OnContextMenuOpening(InArgs._OnContextMenuOpening)
					.ContextMenuExtender(InArgs._ContextMenuExtender)
					.OnTextChanged(this, &SDefault_EditableTextBox::OnEditableTextChanged)
					.OnTextCommitted(this, &SDefault_EditableTextBox::OnEditableTextCommitted)
					.MinDesiredWidth(InArgs._MinDesiredWidth)
					.SelectAllTextOnCommit(InArgs._SelectAllTextOnCommit)
					.SelectWordOnMouseDoubleClick(InArgs._SelectWordOnMouseDoubleClick)
					.OnKeyCharHandler(InArgs._OnKeyCharHandler)
					.OnKeyDownHandler(InArgs._OnKeyDownHandler)
					.VirtualKeyboardType(InArgs._VirtualKeyboardType)
					.VirtualKeyboardOptions(InArgs._VirtualKeyboardOptions)
					.VirtualKeyboardTrigger(InArgs._VirtualKeyboardTrigger)
					.VirtualKeyboardDismissAction(InArgs._VirtualKeyboardDismissAction)
					.TextShapingMethod(InArgs._TextShapingMethod)
					.TextFlowDirection(InArgs._TextFlowDirection)
					.OverflowPolicy(InArgs._OverflowPolicy)
				]
			]
		]
	);
}

void SDefault_EditableTextBox::PostConstruct(const FArguments& InArgs)
{
}

void SDefault_EditableTextBox::OnEditableTextChanged(const FText& InText)
{
	OnTextChanged.ExecuteIfBound(InText);

	if (OnVerifyTextChanged.IsBound())
	{
		FText OutErrorMessage;
		if (!OnVerifyTextChanged.Execute(InText, OutErrorMessage))
		{
			// Display as an error.
			SetErrorMessage(OutErrorMessage);
		}
		else
		{
			SetErrorMessage(FText::GetEmpty());
		}
	}
}

void SDefault_EditableTextBox::OnEditableTextCommitted(const FText& InText, ETextCommit::Type InCommitType)
{
	if (OnVerifyTextChanged.IsBound())
	{
		FText OutErrorMessage;
		if (!OnVerifyTextChanged.Execute(InText, OutErrorMessage))
		{
			// Display as an error.
			if (InCommitType == ETextCommit::OnEnter)
			{
				SetErrorMessage(OutErrorMessage);
			}
			return;
		}
	}

	// Text commited without errors, so clear error text
	SetErrorMessage(FText::GetEmpty());

	OnTextCommitted.ExecuteIfBound(InText, InCommitType);
}

void SDefault_EditableTextBox::SetErrorMessage(const FText& InError)
{
	SetErrorMessage(InError.ToString());
}

void SDefault_EditableTextBox::SetErrorMessage(const FString& InError)
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

void SDefault_EditableTextBox::SetStyle(const FEditableTextBoxStyle* InStyle)
{
	Style = InStyle;

	if (Style == nullptr)
	{
		FArguments Defaults;
		Style = Defaults._Style;
	}

	check(Style);

	BorderImageNormal = &Style->BackgroundImageNormal;
	BorderImageHovered = &Style->BackgroundImageHovered;
	BorderImageFocused = &Style->BackgroundImageFocused;
	BorderImageReadOnly = &Style->BackgroundImageReadOnly;
}

FSlateColor SDefault_EditableTextBox::DetermineForegroundColor() const
{
	check(Style);

	if (EditableText->IsTextReadOnly())
	{
		if (ReadOnlyForegroundColorOverride.IsSet())
		{
			return ReadOnlyForegroundColorOverride.Get();
		}
		if (ForegroundColorOverride.IsSet())
		{
			return ForegroundColorOverride.Get();
		}

		return Style->ReadOnlyForegroundColor;
	}
	else if (HasKeyboardFocus())
	{
		return FocusedForegroundColorOverride.IsSet()
			       ? FocusedForegroundColorOverride.Get()
			       : Style->FocusedForegroundColor;
	}
	else
	{
		return ForegroundColorOverride.IsSet() ? ForegroundColorOverride.Get() : Style->ForegroundColor;
	}
}

const FSlateBrush* SDefault_EditableTextBox::GetBorderImage() const
{
	if (EditableText->IsTextReadOnly())
	{
		return BorderImageReadOnly;
	}
	else if (EditableText->HasKeyboardFocus())
	{
		return BorderImageFocused;
	}
	else
	{
		if (EditableText->IsHovered())
		{
			return BorderImageHovered;
		}
		else
		{
			return BorderImageNormal;
		}
	}
}
