// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_CommentBubble.h"
#include "Widgets/SOverlay.h"
#include "SCommentBubble.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "SGraphPanel.h"
#include "Styling/StyleColors.h"

#include "Themes/Default/NodeRestyleDefault.h"

#include "Widgets/Layout/SScaleBox.h"

namespace SCommentBubbleDefs
{
	/** Bubble fade up/down delay */
	static const float FadeDelay = -3.5f;

	/** Bubble Toggle Icon Fade Speed */
	static const float FadeDownSpeed = 5.f;

	/** Height of the arrow connecting the bubble to the node */
	static const float BubbleArrowHeight = 8.f;

	/** Offset from the left edge to comment bubbles arrow center */
	static const float ArrowCentreOffset = 12.f;

	/** Offset from the left edge to comment bubbles toggle button center */
	static const float ToggleButtonCentreOffset = 3.f;

	/** Luminance CoEficients */
	static const FLinearColor LuminanceCoEff(0.2126f, 0.7152f, 0.0722f, 1.f);

	/** Clear text box background color */
	static const FLinearColor TextClearBackground(0.f, 0.f, 0.f, 0.f);
};

void SDefault_CommentBubble::Construct(const FArguments& InArgs)
{
	check(InArgs._Text.IsBound());
	check(InArgs._GraphNode);

	GraphNode = InArgs._GraphNode;
	CommentAttribute = InArgs._Text;
	OnTextCommittedDelegate = InArgs._OnTextCommitted;
	OnToggledDelegate = InArgs._OnToggled;
	ColorAndOpacity = InArgs._ColorAndOpacity;
	bAllowPinning = InArgs._AllowPinning;
	bEnableTitleBarBubble = InArgs._EnableTitleBarBubble;
	bEnableBubbleCtrls = InArgs._EnableBubbleCtrls;
	bInvertLODCulling = InArgs._InvertLODCulling;
	GraphLOD = InArgs._GraphLOD;
	IsGraphNodeHovered = InArgs._IsGraphNodeHovered;
	HintText = InArgs._HintText.IsSet()
		           ? InArgs._HintText
		           : NSLOCTEXT("CommentBubble", "EditCommentHint", "Click to edit");
	OpacityValue = SCommentBubbleDefs::FadeDelay;
	// Create default delegate/attribute handlers if required
	ToggleButtonCheck = InArgs._ToggleButtonCheck.IsBound()
		                    ? InArgs._ToggleButtonCheck
		                    : TAttribute<ECheckBoxState>(this, &SDefault_CommentBubble::GetToggleButtonCheck);
	// Ensue this value is set to something sensible
	CalculatedForegroundColor = FStyleColors::Foreground;
	BubbleLuminance = 0.0f;

	// Cache the comment
	CachedComment = CommentAttribute.Get();
	CachedCommentText = FText::FromString(CachedComment);
	CachedBubbleControls = MakeShared<TSharedRef<SWidget>>(SNullWidget::NullWidget);
	// Create Widget
	CalculatedForegroundColor = FStyleColors::Foreground;
	UpdateBubble_New();
}

void SDefault_CommentBubble::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime,
                                  const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	// Check Editable and Hovered so we can prevent bubble toggling in read only graphs.
	const bool bNodeEditable = !IsReadOnly();
	const bool bEnableTitleHintBubble = bEnableTitleBarBubble && bNodeEditable;

	/*const bool bTitleBarBubbleVisible = bEnableTitleHintBubble && IsGraphNodeHovered.IsBound();
	if (bTitleBarBubbleVisible || IsBubbleVisible())
	{
		const FLinearColor BubbleColor = GetBubbleColor().GetSpecifiedColor() * SCommentBubbleDefs::LuminanceCoEff;
		BubbleLuminance = BubbleColor.R + BubbleColor.G + BubbleColor.B;
		CalculatedForegroundColor = BubbleLuminance < 0.5f ? FStyleColors::Foreground : FStyleColors::Background;
	}*/

	TickVisibility(InCurrentTime, InDeltaTime);

	if (CachedComment != CommentAttribute.Get())
	{
		CachedComment = CommentAttribute.Get();
		CachedCommentText = FText::FromString(CachedComment);

		// Toggle the comment on/off, provided it the parent isn't a comment node
		if (!bInvertLODCulling)
		{
			// If the comment visibility isn't correct, toggle it.
			if (CachedComment.IsEmpty() == GraphNode->bCommentBubbleVisible)
			{
				OnCommentBubbleToggle_New(CachedComment.IsEmpty()
					                          ? ECheckBoxState::Unchecked
					                          : ECheckBoxState::Checked);
			}
			else
			{
				// we just need to refresh the widget's visibility, not the graph node
				UpdateBubble_New();
			}
		}
	}
}

void SDefault_CommentBubble::UpdateBubble_New()
{
	const auto& CommentBubble = UNodeRestyleSettings::Get()->CommentBubble;
	const auto& TextSettings = CommentBubble.Text.Get();
	//const FLinearColor BubbleColor = 
	//	ColorAndOpacity.IsBound() ? ColorAndOpacity.GetBinding().Execute().GetSpecifiedColor()
	//		: ColorAndOpacity.IsSet() ? ColorAndOpacity.Get().GetSpecifiedColor() * SCommentBubbleDefs::LuminanceCoEff
	//			: FLinearColor::Black;

	//BubbleLuminance =(BubbleColor.R + BubbleColor.G + BubbleColor.B) * BubbleColor.A;
	//bool bWhiteForeground = BubbleLuminance <= .5f;
	bool bWhiteForeground = true;
	FLinearColor ForegroundCorrected = bWhiteForeground ? FLinearColor::White : FLinearColor::Black;
	FLinearColor NormalForegroundColor = ColorAndOpacity.IsSet() ? ForegroundCorrected : TextSettings.ForegroundNormal.Get();
	FLinearColor FocusedForegroundColor = ColorAndOpacity.IsSet() ? ForegroundCorrected : TextSettings.ForegroundFocused.Get();
	FLinearColor ReadOnlyForegroundColor = ColorAndOpacity.IsSet()  ? ForegroundCorrected : TextSettings.ForegroundReadOnly.Get();
	if (GraphNode->bCommentBubbleVisible)
	{
		const FSlateBrush* CommentCalloutArrowBrush = FAppStyle::GetBrush(FNodeRestyleStyles::CommentBubble_CommentArrow);
		const FSlateBrush* DynamicArrow = ColorAndOpacity.IsSet() ? FAppStyle::GetNoBrush() : CommentCalloutArrowBrush;

		// Create the comment bubble widget

		ChildSlot
		[
			SNew(SVerticalBox)
			.Visibility(this, &SDefault_CommentBubble::GetBubbleVisibility)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					[
						SNew(SImage)
						.Image(FAppStyle::GetBrush(ColorAndOpacity.IsSet()
							? FNodeRestyleStyles::CommentBubble_Body_White
							: FNodeRestyleStyles::CommentBubble_Body))
						.ColorAndOpacity(ColorAndOpacity.IsSet() || ColorAndOpacity.IsBound() ? ColorAndOpacity : FSlateColor(FLinearColor::White))
					]
					+ SOverlay::Slot()
					  .Padding(UDefaultThemeSettings::GetMargin(CommentBubble.InnerPadding))
					  .HAlign(HAlign_Left)
					  .VAlign(VAlign_Center)
					[
						SAssignNew(MainHorizontalBox, SHorizontalBox)
						+ SHorizontalBox::Slot()
						  .AutoWidth()
						  .Padding(0, 0)
						[
							SAssignNew(TextBlock, SMultiLineEditableTextBox)
							.ForegroundColor(NormalForegroundColor)
							.FocusedForegroundColor(FocusedForegroundColor)
							.ReadOnlyForegroundColor(ReadOnlyForegroundColor)
							.Padding(0)
							.Text(MakeAttributeLambda([this] { return CachedCommentText; }))
							.Style(FAppStyle::Get(), FNodeRestyleStyles::CommentBubble_EditableText)
							.HintText(NSLOCTEXT("CommentBubble", "EditCommentHint", "Click to edit"))
							.IsReadOnly(this, &SDefault_CommentBubble::IsReadOnly)
							.SelectAllTextWhenFocused(true)
							.RevertTextOnEscape(true)
							.ClearKeyboardFocusOnCommit(true)
							.ModiferKeyForNewLine(EModifierKey::Shift)
							.OnTextChanged(this, &SDefault_CommentBubble::OnCommentTextChanged)
							.OnTextCommitted(this, &SDefault_CommentBubble::OnCommentTextCommitted)
						]
					]
				]
			]
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .Padding(4, 0, -2, 0)
			[
				SNew(SBox)
				.MinDesiredHeight(CommentCalloutArrowBrush->ImageSize.Y)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.MaxWidth(CommentCalloutArrowBrush->ImageSize.X)
					[
						SNew(SImage)
						.Image(DynamicArrow)
					]
				]
			]
		];
		UpdateBubbleControls(ShouldDrawHorizontalControls());
	}
	else
	{
		TSharedPtr<SWidget> TitleBarBubble = SNullWidget::NullWidget;

		if (bEnableTitleBarBubble)
		{
			// Create Title bar bubble toggle widget
			SAssignNew(TitleBarBubble, SHorizontalBox)
				.Visibility(this, &SDefault_CommentBubble::GetToggleButtonVisibility)
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .HAlign(HAlign_Center)
				  .VAlign(VAlign_Top)
				  .Padding(CommentBubble.Buttons.ToggleOffset)
				[
					SNew(SCheckBox)
					.Style(&FAppStyle::Get().GetWidgetStyle<FCheckBoxStyle>(
						               FNodeRestyleStyles::CommentBubble_Checkbox_TitleButton))
					.IsChecked(ToggleButtonCheck)
					.OnCheckStateChanged(this, &SDefault_CommentBubble::OnCommentBubbleToggle_New)
					.ToolTipText(NSLOCTEXT("CommentBubble", "ToggleCommentTooltip", "Toggle Comment Bubble"))
					.Cursor(EMouseCursor::Default)
				];
		}
		ChildSlot
		[
			TitleBarBubble.ToSharedRef()
		];
	}
}

void SDefault_CommentBubble::OnCommentBubbleToggle_New(ECheckBoxState State)
{
	const bool bNewVisibilityState = (State == ECheckBoxState::Checked);
	if (!IsReadOnly() && bNewVisibilityState != GraphNode->bCommentBubbleVisible)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("CommentBubble", "BubbleVisibility", "Comment Bubble Visibility"));
		GraphNode->Modify();
		SetCommentBubbleVisibility_New(bNewVisibilityState);
		OnToggledDelegate.ExecuteIfBound(GraphNode->bCommentBubbleVisible);
	}
}

void SDefault_CommentBubble::SetCommentBubbleVisibility_New(bool bVisible)
{
	if (!IsReadOnly() && bVisible != GraphNode->bCommentBubbleVisible)
	{
		GraphNode->bCommentBubbleVisible = bVisible;
		OpacityValue = 0.f;
		UpdateBubble_New();
	}
}

bool SDefault_CommentBubble::ShouldDrawHorizontalControls()
{
	if (TextBlock.IsValid()) return ShouldDrawHorizontalControls(TextBlock->GetText());
	return true;
}

TSharedPtr<SWidget> SDefault_CommentBubble::UpdateBubbleControls(bool bHorizontal)
{
	const auto& CommentBubble = UNodeRestyleSettings::Get()->CommentBubble;
	if (bEnableBubbleCtrls)
	{
		if (bAllowPinning)
		{
			if (bHorizontal)
			{
				auto AddToHorizontalBox = [this, &CommentBubble]()
				{
					SAssignNew(BubbleControls, SHorizontalBox)
						.Visibility(this, &SDefault_CommentBubble::GetButtonControlsVisibility)
						+ SHorizontalBox::Slot()
						  .Padding(0)
						  .AutoWidth()
						  .VAlign(VAlign_Center)
						[
							SNew(SCheckBox)
							.Style(&FAppStyle::Get().GetWidgetStyle<FCheckBoxStyle>(
								               FNodeRestyleStyles::CommentBubble_Checkbox_Pin))
							.IsChecked(this, &SDefault_CommentBubble::GetPinnedButtonCheck)
							.OnCheckStateChanged(this, &SDefault_CommentBubble::OnPinStateToggle)
							.ToolTipText(this, &SDefault_CommentBubble::GetScaleButtonTooltip)
							.Cursor(EMouseCursor::Default)

						]
						+ SHorizontalBox::Slot()
						  .Padding(0)
						  .AutoWidth()
						[
							SNew(SSpacer)
							.Size(FVector2D(CommentBubble.Buttons.SpaceBetweenButtons.X, 0))
						]
						+ SHorizontalBox::Slot()
						  .Padding(0)
						  .AutoWidth()
						  .VAlign(VAlign_Center)
						[

							SNew(SCheckBox)
							.Style(&FAppStyle::Get().GetWidgetStyle<FCheckBoxStyle>(
								               FNodeRestyleStyles::CommentBubble_Checkbox_Button))
							.IsChecked(ToggleButtonCheck)
							.OnCheckStateChanged(this, &SDefault_CommentBubble::OnCommentBubbleToggle_New)
							.ToolTipText(
								               NSLOCTEXT("CommentBubble", "ToggleCommentTooltip",
								                         "Toggle Comment Bubble"))
							.Cursor(EMouseCursor::Default)
						];
				};
				AddToHorizontalBox();
			}
			else
			{
				auto AddToVerticalBox = [this, &CommentBubble]()
				{
					SAssignNew(BubbleControls, SVerticalBox)
						.Visibility(this, &SDefault_CommentBubble::GetButtonControlsVisibility)
						+ SVerticalBox::Slot()
						  .Padding(0)
						  .AutoHeight()
						  .VAlign(VAlign_Top)
						[

							SNew(SCheckBox)
							.Style(&FAppStyle::Get().GetWidgetStyle<FCheckBoxStyle>(
								               FNodeRestyleStyles::CommentBubble_Checkbox_Pin))
							.IsChecked(this, &SDefault_CommentBubble::GetPinnedButtonCheck)
							.OnCheckStateChanged(this, &SDefault_CommentBubble::OnPinStateToggle)
							.ToolTipText(this, &SDefault_CommentBubble::GetScaleButtonTooltip)
							.Cursor(EMouseCursor::Default)
						]
						+ SVerticalBox::Slot()
						  .VAlign(VAlign_Top)
						  .AutoHeight()
						  .Padding(0)
						[
							SNew(SSpacer)
							.Size(FVector2D(0, CommentBubble.Buttons.SpaceBetweenButtons.Y))
						]
						+ SVerticalBox::Slot()
						  .Padding(0)
						  .AutoHeight()
						  .VAlign(VAlign_Top)
						[
							SNew(SCheckBox)
							.Style(&FAppStyle::Get().GetWidgetStyle<FCheckBoxStyle>(
								               FNodeRestyleStyles::CommentBubble_Checkbox_Button))
							.IsChecked(ToggleButtonCheck)
							.OnCheckStateChanged(this, &SDefault_CommentBubble::OnCommentBubbleToggle_New)
							.ToolTipText(NSLOCTEXT("CommentBubble", "ToggleCommentTooltip", "Toggle Comment Bubble"))
							.Cursor(EMouseCursor::Default)
						];
				};
				AddToVerticalBox();
			}
		}
		else
		{
			SAssignNew(BubbleControls, SVerticalBox)
				.Visibility(this, &SDefault_CommentBubble::GetButtonControlsVisibility)
				+ SVerticalBox::Slot()
				  .AutoHeight()
				  .Padding(0)
				  .VAlign(VAlign_Top)
				[
					SNew(SCheckBox)
					.Style(&FAppStyle::Get().GetWidgetStyle<FCheckBoxStyle>(
						               FNodeRestyleStyles::CommentBubble_Checkbox_Button))
					.IsChecked(ToggleButtonCheck)
					.OnCheckStateChanged(this, &SDefault_CommentBubble::OnCommentBubbleToggle_New)
					.ToolTipText(
						               NSLOCTEXT("CommentBubble", "ToggleCommentTooltip",
						                         "Toggle Comment Bubble"))
					.Cursor(EMouseCursor::Default)
				];
		}
	}
	else
	{
		BubbleControls = SNullWidget::NullWidget;
	}

	if (MainHorizontalBox.IsValid())
	{
		MainHorizontalBox->RemoveSlot(*CachedBubbleControls);
		*CachedBubbleControls = BubbleControls.ToSharedRef();
		MainHorizontalBox->AddSlot()
		                 .AutoWidth()
		                 .HAlign(HAlign_Right)
		                 .VAlign(VAlign_Fill)
		                 .Padding(UDefaultThemeSettings::GetMargin(CommentBubble.Buttons.ButtonsBoxOffset))
			[*CachedBubbleControls];
	}
	return BubbleControls;
}

EVisibility SDefault_CommentBubble::GetButtonControlsVisibility() const
{
	if (GetBubbleVisibility() == EVisibility::Hidden) return EVisibility::Hidden;
	if (IsHovered()) return EVisibility::Visible;
	return EVisibility::Collapsed;
}
