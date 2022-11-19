// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#include "DefineSlateUtils.h"
#include "STextPropertyEditableTextBox.h"
#include "SDefault_MultiLineEditableTextBox.h"
#include "SDefault_EditableTextBox.h"
class SDefault_TextPropertyEditableTextBox : public SCompoundWidget
{
public:
#pragma region SlateArgs
	SLATE_BEGIN_ARGS(SDefault_TextPropertyEditableTextBox)
		: _Style(&FCoreStyle::Get().GetWidgetStyle<FEditableTextBoxStyle>("NormalEditableTextBox"))
		, _ComboButtonStyle(&FCoreStyle::Get().GetWidgetStyle<FComboButtonStyle>("ComboButton"))
		, _Font()
		, _ForegroundColor()
		, _WrapTextAt(0.0f)
		, _AutoWrapText(false)
		, _MinDesiredWidth()
		//, _MaxDesiredHeight(300.0f)
		, _Spacing(4.f)
		, _AdvancedTextIconSize(12)
		, _bHasDownArrow(false)
		, _SpacingBetweenIconAndArrow(4.f)
	{
	}

	SLATE_STYLE_ARGUMENT(FEditableTextBoxStyle, Style)
		SLATE_STYLE_ARGUMENT(FComboButtonStyle, ComboButtonStyle)
		SLATE_ATTRIBUTE(FSlateFontInfo, Font)
		SLATE_ATTRIBUTE(FSlateColor, ForegroundColor)
		SLATE_ATTRIBUTE(float, WrapTextAt)
		SLATE_ATTRIBUTE(bool, AutoWrapText)
		SLATE_ATTRIBUTE(FOptionalSize, MinDesiredWidth)
		//SLATE_ATTRIBUTE(FOptionalSize, MaxDesiredHeight)
		SLATE_ARGUMENT(float, Spacing)
		SLATE_ARGUMENT(uint16, AdvancedTextIconSize)
		SLATE_ARGUMENT(bool, bHasDownArrow)
		SLATE_ARGUMENT(float, SpacingBetweenIconAndArrow)
	SLATE_END_ARGS()
#pragma endregion

	SLATE_CONSTRUCT(
		SLATE_CONSTRUCT_IMP(InArgs, InEditableTextProperty), 
		const FArguments& InArgs, const TSharedRef<IEditableTextProperty>& InEditableTextProperty)

	virtual bool SupportsKeyboardFocus() const override;
	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;
protected:
	virtual void GetDesiredWidth(float& OutMinDesiredWidth, float& OutMaxDesiredWidth);
	virtual bool CanEdit() const;
	virtual bool IsCultureInvariantFlagEnabled() const;
	virtual bool IsSourceTextReadOnly() const;
	virtual bool IsIdentityReadOnly() const;
	virtual FText GetToolTipText() const;
	virtual bool IsTextLocalizable() const;

	virtual FText GetTextValue() const;
	virtual void OnTextChanged(const FText& NewText);
	virtual void OnTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);
	virtual void SetTextError(const FText& InErrorMsg);

	virtual FText GetNamespaceValue() const;
	virtual void OnNamespaceChanged(const FText& NewText);
	virtual void OnNamespaceCommitted(const FText& NewText, ETextCommit::Type CommitInfo);

	virtual FText GetKeyValue() const;
#if USE_STABLE_LOCALIZATION_KEYS
	virtual void OnKeyChanged(const FText& NewText);
	virtual void OnKeyCommitted(const FText& NewText, ETextCommit::Type CommitInfo);

	virtual FText GetPackageValue() const;
#endif // USE_STABLE_LOCALIZATION_KEYS

	virtual ECheckBoxState GetLocalizableCheckState() const;

	virtual void HandleLocalizableCheckStateChanged(ECheckBoxState InCheckboxState);

	virtual FText GetAdvancedTextSettingsComboToolTip() const;
	virtual const FSlateBrush* GetAdvancedTextSettingsComboImage() const;

	virtual bool IsValidIdentity(const FText& InIdentity, FText* OutReason = nullptr,
		const FText* InErrorCtx = nullptr) const;

	TSharedPtr<IEditableTextProperty> EditableTextProperty;

	TSharedPtr<class SWidget> PrimaryWidget;

	TSharedPtr<SDefault_MultiLineEditableTextBox> MultiLineWidget;

	TSharedPtr<SDefault_EditableTextBox> SingleLineWidget;

	TSharedPtr<SDefault_EditableTextBox> NamespaceEditableTextBox;

	TSharedPtr<SDefault_EditableTextBox> KeyEditableTextBox;

	TOptional<float> PreviousHeight;

	bool bIsMultiLine;

	static FText MultipleValuesText;
};
