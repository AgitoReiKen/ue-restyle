// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#include "DefineSlateUtils.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
class SDefault_MultiLineEditableTextBox : public SMultiLineEditableTextBox
{
public:
#pragma region SlateArgs
	SLATE_BEGIN_ARGS(SDefault_MultiLineEditableTextBox)
		: _Style(&FCoreStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("NormalEditableTextBox"))
		, _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))
		, _Marshaller()
		, _Text()
		, _HintText()
		, _SearchText()
		, _Font()
		, _ForegroundColor()
		, _ReadOnlyForegroundColor()
		, _FocusedForegroundColor()
		, _Justification(ETextJustify::Left)
		, _LineHeightPercentage(1.0f)
		, _IsReadOnly(false)
		, _AllowMultiLine(true)
		, _IsCaretMovedWhenGainFocus(true)
		, _SelectAllTextWhenFocused(false)
		, _ClearTextSelectionOnFocusLoss(true)
		, _RevertTextOnEscape(false)
		, _ClearKeyboardFocusOnCommit(true)
		, _AllowContextMenu(true)
		, _AlwaysShowScrollbars(false)
		, _HScrollBar()
		, _VScrollBar()
		, _WrapTextAt(0.0f)
		, _AutoWrapText(false)
		, _WrappingPolicy(ETextWrappingPolicy::DefaultWrapping)
		, _SelectAllTextOnCommit(false)
		, _SelectWordOnMouseDoubleClick(true)
		, _BackgroundColor()
		, _Padding()
		, _Margin()
		//, _ErrorReporting()
		, _ModiferKeyForNewLine(EModifierKey::None)
		, _VirtualKeyboardOptions(FVirtualKeyboardOptions())
		, _VirtualKeyboardTrigger(EVirtualKeyboardTrigger::OnFocusByPointer)
		, _VirtualKeyboardDismissAction(EVirtualKeyboardDismissAction::TextChangeOnDismiss)
		, _TextShapingMethod()
		, _TextFlowDirection()
		, _OverflowPolicy()
		, _ErrorReportingSpacing(4)
		//, _bIsPassword(false)
		//, _DefaultScrollBarThickness(FVector2D(4))
	{
	}

	SLATE_STYLE_ARGUMENT(FEditableTextBoxStyle, Style)
		SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle)
		SLATE_ARGUMENT(TSharedPtr< ITextLayoutMarshaller >, Marshaller)
		//SLATE_ARGUMENT(bool, bIsPassword)
		SLATE_ATTRIBUTE(FText, Text)
		SLATE_ATTRIBUTE(FText, HintText)
		SLATE_ATTRIBUTE(FText, SearchText)
		SLATE_ATTRIBUTE(FSlateFontInfo, Font)
		SLATE_ATTRIBUTE(FSlateColor, ForegroundColor)
		SLATE_ATTRIBUTE(FSlateColor, ReadOnlyForegroundColor)
		SLATE_ATTRIBUTE(FSlateColor, FocusedForegroundColor)
		SLATE_ATTRIBUTE(ETextJustify::Type, Justification)
		SLATE_ATTRIBUTE(float, LineHeightPercentage)
		SLATE_ATTRIBUTE(bool, IsReadOnly)
		SLATE_ATTRIBUTE(bool, AllowMultiLine)
		SLATE_ATTRIBUTE(bool, IsCaretMovedWhenGainFocus)
		SLATE_ATTRIBUTE(bool, SelectAllTextWhenFocused)
		SLATE_ATTRIBUTE(bool, ClearTextSelectionOnFocusLoss)
		SLATE_ATTRIBUTE(bool, RevertTextOnEscape)
		SLATE_ATTRIBUTE(bool, ClearKeyboardFocusOnCommit)
		SLATE_ATTRIBUTE(bool, AllowContextMenu)
		SLATE_ARGUMENT(bool, AlwaysShowScrollbars)
		SLATE_ARGUMENT(TSharedPtr< SScrollBar >, HScrollBar)
		SLATE_ARGUMENT(TSharedPtr< SScrollBar >, VScrollBar)
		SLATE_ATTRIBUTE(FMargin, HScrollBarPadding)
		SLATE_ATTRIBUTE(FMargin, VScrollBarPadding)
		SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening)

		/**
		 * This is NOT for validating input!
		 *
		 * Called whenever a character is typed.
		 * Not called for copy, paste, or any other text changes!
		 */
		SLATE_EVENT(FOnIsTypedCharValid, OnIsTypedCharValid)

		SLATE_EVENT(FOnTextChanged, OnTextChanged)
		SLATE_EVENT(FOnTextCommitted, OnTextCommitted)
		SLATE_EVENT(FOnUserScrolled, OnHScrollBarUserScrolled)
		SLATE_EVENT(FOnUserScrolled, OnVScrollBarUserScrolled)
		SLATE_EVENT(SMultiLineEditableText::FOnCursorMoved, OnCursorMoved)
		SLATE_EVENT(FOnKeyChar, OnKeyCharHandler)
		SLATE_EVENT(FOnKeyDown, OnKeyDownHandler)
		SLATE_EVENT(FMenuExtensionDelegate, ContextMenuExtender)
		SLATE_EVENT(FCreateSlateTextLayout, CreateSlateTextLayout)
		SLATE_ATTRIBUTE(float, WrapTextAt)

		/** Whether to wrap text automatically based on the widget's computed horizontal space.
		 *  IMPORTANT: Using automatic wrapping can result
			in visual artifacts, as the the wrapped size will computed be at least one frame late!  Consider using WrapTextAt instead.  The initial
			desired size will not be clamped.  This works best in cases where the text block's size is not affecting other widget's layout. */
		SLATE_ATTRIBUTE(bool, AutoWrapText)
		SLATE_ATTRIBUTE(ETextWrappingPolicy, WrappingPolicy)
		SLATE_ATTRIBUTE(bool, SelectAllTextOnCommit)
		SLATE_ATTRIBUTE(bool, SelectWordOnMouseDoubleClick)
		SLATE_ATTRIBUTE(FSlateColor, BackgroundColor)
		SLATE_ATTRIBUTE(FMargin, Padding)
		SLATE_ATTRIBUTE(FMargin, Margin)
		//SLATE_ARGUMENT(TSharedPtr<class IErrorReportingWidget>, ErrorReporting)
		SLATE_ARGUMENT(EModifierKey::Type, ModiferKeyForNewLine)
		SLATE_ARGUMENT(FVirtualKeyboardOptions, VirtualKeyboardOptions)
		SLATE_ATTRIBUTE(EVirtualKeyboardTrigger, VirtualKeyboardTrigger)
		SLATE_ATTRIBUTE(EVirtualKeyboardDismissAction, VirtualKeyboardDismissAction)
		SLATE_ARGUMENT(TOptional<ETextShapingMethod>, TextShapingMethod)
		SLATE_ARGUMENT(TOptional<ETextFlowDirection>, TextFlowDirection)
		SLATE_ARGUMENT(TOptional<ETextOverflowPolicy>, OverflowPolicy)
		SLATE_ARGUMENT(float, ErrorReportingSpacing)
		//SLATE_ARGUMENT(FVector2D, DefaultScrollBarThickness)

		SLATE_END_ARGS()
#pragma endregion

	SLATE_CONSTRUCT(SLATE_CONSTRUCT_IMP(InArgs), const FArguments& InArgs)

	virtual void SetErrorMessage(const FText& InError);
	virtual void SetErrorMessage(const FString& InError);

protected:
	virtual const FSlateBrush* GetBorderImage() const;

	virtual FMargin DeterminePadding() const
	{
		check(Style);
		return PaddingOverride.IsSet() ? PaddingOverride.Get() : Style->Padding;
	}

	virtual FMargin DetermineHScrollBarPadding() const
	{
		check(Style);
		return HScrollBarPaddingOverride.IsSet() ? HScrollBarPaddingOverride.Get() : Style->HScrollBarPadding;
	}

	virtual FMargin DetermineVScrollBarPadding() const
	{
		check(Style);
		return VScrollBarPaddingOverride.IsSet() ? VScrollBarPaddingOverride.Get() : Style->VScrollBarPadding;
	}

	virtual FSlateFontInfo DetermineFont() const
	{
		check(Style);
		return FontOverride.IsSet() ? FontOverride.Get() : Style->Font;
	}

	virtual FSlateColor DetermineBackgroundColor() const
	{
		check(Style);
		return BackgroundColorOverride.IsSet() ? BackgroundColorOverride.Get() : Style->BackgroundColor;
	}

	virtual FSlateColor DetermineForegroundColor() const;

	const FSlateBrush* BorderImageNormal;
	const FSlateBrush* BorderImageHovered;
	const FSlateBrush* BorderImageFocused;
	const FSlateBrush* BorderImageReadOnly;
	float ErrorReportingSpacing;
	FVector2D DefaultScrollBarThickness;
};
