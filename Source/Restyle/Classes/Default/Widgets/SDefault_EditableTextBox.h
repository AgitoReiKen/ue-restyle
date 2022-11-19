// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#include "DefineSlateUtils.h"
class SDefault_EditableTextBox : public SEditableTextBox
{
public:
#pragma region SlateArgs
	SLATE_BEGIN_ARGS(SDefault_EditableTextBox)
		: _Style(&FCoreStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("NormalEditableTextBox"))
		, _Text()
		, _HintText()
		, _SearchText()
		, _Font()
		, _ForegroundColor()
		, _ReadOnlyForegroundColor()
		, _FocusedForegroundColor()
		, _IsReadOnly(false)
		, _IsPassword(false)
		, _IsCaretMovedWhenGainFocus(true)
		, _SelectAllTextWhenFocused(false)
		, _RevertTextOnEscape(false)
		, _ClearKeyboardFocusOnCommit(true)
		, _Justification(ETextJustify::Left)
		, _AllowContextMenu(true)
		, _MinDesiredWidth(0.0f)
		, _SelectAllTextOnCommit(false)
		, _SelectWordOnMouseDoubleClick(true)
		, _BackgroundColor()
		, _Padding()
		//, _ErrorReporting()
		, _VirtualKeyboardOptions(FVirtualKeyboardOptions())
		, _VirtualKeyboardTrigger(EVirtualKeyboardTrigger::OnFocusByPointer)
		, _VirtualKeyboardDismissAction(EVirtualKeyboardDismissAction::TextChangeOnDismiss)
		, _OverflowPolicy()
		, _ErrorReportingSpacing(4)
		//, _DefaultScrollBarThickness(FVector2D(4))
	{
	}

	SLATE_STYLE_ARGUMENT(FEditableTextBoxStyle, Style)
		SLATE_ATTRIBUTE(FText, Text)
		SLATE_ATTRIBUTE(FText, HintText)
		SLATE_ATTRIBUTE(FText, SearchText)
		SLATE_ATTRIBUTE(FSlateFontInfo, Font)
		SLATE_ATTRIBUTE(FSlateColor, ForegroundColor)
		SLATE_ATTRIBUTE(FSlateColor, ReadOnlyForegroundColor)
		SLATE_ATTRIBUTE(FSlateColor, FocusedForegroundColor)
		SLATE_ATTRIBUTE(bool, IsReadOnly)
		SLATE_ATTRIBUTE(bool, IsPassword)
		SLATE_ATTRIBUTE(bool, IsCaretMovedWhenGainFocus)
		SLATE_ATTRIBUTE(bool, SelectAllTextWhenFocused)
		SLATE_ATTRIBUTE(bool, RevertTextOnEscape)
		SLATE_ATTRIBUTE(bool, ClearKeyboardFocusOnCommit)
		SLATE_ATTRIBUTE(ETextJustify::Type, Justification)
		SLATE_ATTRIBUTE(bool, AllowContextMenu)
		SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening)
		SLATE_EVENT(FMenuExtensionDelegate, ContextMenuExtender)
		SLATE_EVENT(FOnTextChanged, OnTextChanged)
		SLATE_EVENT(FOnTextCommitted, OnTextCommitted)
		SLATE_EVENT(FOnVerifyTextChanged, OnVerifyTextChanged)
		SLATE_ATTRIBUTE(float, MinDesiredWidth)
		SLATE_ATTRIBUTE(bool, SelectAllTextOnCommit)
		SLATE_ATTRIBUTE(bool, SelectWordOnMouseDoubleClick)
		SLATE_EVENT(FOnKeyChar, OnKeyCharHandler)
		SLATE_EVENT(FOnKeyDown, OnKeyDownHandler)
		SLATE_ATTRIBUTE(FSlateColor, BackgroundColor)
		SLATE_ATTRIBUTE(FMargin, Padding)
		//SLATE_ARGUMENT(TSharedPtr<class IErrorReportingWidget>, ErrorReporting)
		SLATE_ATTRIBUTE(EKeyboardType, VirtualKeyboardType)
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

	SLATE_CONSTRUCT(
		SLATE_CONSTRUCT_IMP(InArgs),
		const FArguments& InArgs)

	virtual void SetErrorMessage(const FText& InError);
	virtual void SetErrorMessage(const FString& InError);
protected:
	virtual void OnEditableTextChanged(const FText& InText);
	virtual void OnEditableTextCommitted(const FText& InText, ETextCommit::Type InCommitType);
 

	virtual void SetStyle(const FEditableTextBoxStyle* InStyle);

	virtual FMargin FORCEINLINE DeterminePadding() const
	{
		check(Style);
		return PaddingOverride.IsSet() ? PaddingOverride.Get() : Style->Padding;
	}

	virtual FSlateFontInfo FORCEINLINE DetermineFont() const
	{
		check(Style);
		return FontOverride.IsSet() ? FontOverride.Get() : Style->TextStyle.Font;
	}

	virtual FSlateColor FORCEINLINE DetermineBackgroundColor() const
	{
		check(Style);
		return BackgroundColorOverride.IsSet() ? BackgroundColorOverride.Get() : Style->BackgroundColor;
	}

	virtual FSlateColor DetermineForegroundColor() const;

	/** Styling: border image to draw when not hovered or focused */
	const FSlateBrush* BorderImageNormal;
	/** Styling: border image to draw when hovered */
	const FSlateBrush* BorderImageHovered;
	/** Styling: border image to draw when focused */
	const FSlateBrush* BorderImageFocused;
	/** Styling: border image to draw when read only */
	const FSlateBrush* BorderImageReadOnly;
	float ErrorReportingSpacing;
	const FSlateBrush* GetBorderImage() const;
};
