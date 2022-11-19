// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeK2Base.h"
#include "KismetNodes/SGraphNodeK2Base.h"
#include "Internationalization/Culture.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SToolTip.h"
#include "SCommentBubble.h"
#include "SGraphPin.h"
#include "Kismet2/Breakpoint.h"
#include "Kismet2/KismetDebugUtilities.h"
#include "IDocumentation.h"
#include "SDefault_ErrorText.h"
#include "SGraphPanel.h"
#include "Slate/SObjectWidget.h"

#include "Themes/Default/DefaultTheme.h"
#include "Themes/Default/NodeRestyleDefault.h"
#include "Themes/Default/PinRestyleDefault.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
 
TSharedPtr<SWidget> SDefault_GraphNodeK2Base::CreateEnabledStateWidget()
{
	if ((GraphNode->GetDesiredEnabledState() != ENodeEnabledState::Enabled) && !GraphNode->
		IsAutomaticallyPlacedGhostNode())
	{
		const bool bDevelopmentOnly = GraphNode->GetDesiredEnabledState() == ENodeEnabledState::DevelopmentOnly;
		const FText StatusMessage = bDevelopmentOnly
			                            ? NSLOCTEXT("SGraphNode", "DevelopmentOnly", "Development Only")
			                            : NSLOCTEXT("SGraphNode", "DisabledNode", "Disabled");
		const FText StatusMessageTooltip = bDevelopmentOnly
			                                   ? NSLOCTEXT("SGraphNode", "DevelopmentOnlyTooltip",
			                                               "This node will only be executed in the editor and in Development builds in a packaged game (it will be treated as disabled in Shipping or Test builds cooked from a commandlet)")
			                                   : NSLOCTEXT("SGraphNode", "DisabledNodeTooltip",
			                                               "This node is currently disabled and will not be executed");

		/*FAppStyle::GetBrush(bDevelopmentOnly
			? "Graph.Node.DevelopmentBanner"
			: "Graph.Node.DisabledBanner"*/
		auto Type = bDevelopmentOnly ? EDTEnabledStateType::Development : EDTEnabledStateType::Disabled;
		const auto& Style = UNodeRestyleSettings::Get()->StateWidget.Types[(int)Type];
		return
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush(FNodeRestyleStyles::EnabledState_Body(Type)))
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Style.Title))
				.TextStyle(FAppStyle::Get(), FNodeRestyleStyles::EnabledState_Text(Type))
				.ToolTipText(StatusMessageTooltip)
				.Justification(ETextJustify::Center)
				.Visibility(EVisibility::Visible)
			];
	}
	return TSharedPtr<SWidget>();
}

 
FMargin SDefault_GraphNodeK2Base::GetEnabledStateWidgetPadding() const
{
	return FMargin(CachedOutlineWidth, 0) + EnabledStateWidgetAdditionalPadding;
}

FReply SDefault_GraphNodeK2Base::OnAdvancedDisplayClicked()
{
	OnAdvancedViewChanged(IsAdvancedViewChecked() == ECheckBoxState::Checked 
		? ECheckBoxState::Unchecked : ECheckBoxState::Checked);
	if (AdvancedViewArrow.IsValid()) AdvancedViewArrow->SetImage(GetAdvancedViewArrowNew());
	return FReply::Handled();
}

void SDefault_GraphNodeK2Base::CreateAdvancedViewArrowNew(TSharedPtr<SVerticalBox> MainBox)
{
	const bool bHidePins = OwnerGraphPanelPtr.IsValid() && (OwnerGraphPanelPtr.Pin()->GetPinVisibility() != SGraphEditor::Pin_Show);
	//const bool bAnyAdvancedPin = GraphNode && (ENodeAdvancedPins::NoPins != GraphNode->AdvancedPinDisplay);
	FMargin Padding = UDefaultThemeSettings::GetMargin(UNodeRestyleSettings::Get()->AdvancedDisplay.Padding);
	if (!bHidePins && GraphNode && MainBox.IsValid())
	{
		MainBox->AddSlot()
			.AutoHeight()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Top)
			.Padding(Padding)
			[
				SNew(SButton)
				.Visibility(this, &SDefault_GraphNodeK2Base::AdvancedViewArrowVisibility)
				.ButtonStyle(FAppStyle::Get(), FNodeRestyleStyles::AdvancedDisplay)
				.OnClicked(this, &SDefault_GraphNodeK2Base::OnAdvancedDisplayClicked)
				.Cursor(EMouseCursor::Default)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Center)
					[
						SAssignNew(AdvancedViewArrow, SImage)
						.ColorAndOpacity(FSlateColor::UseForeground())
						.Image(GetAdvancedViewArrowNew())
					]
				]
			];
	}
}

void SDefault_GraphNodeK2Base::SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel)
{
	SGraphNodeK2Base::SetOwner(OwnerPanel);
	if (UNodeRestyleSettings::Get()->bNewZoom)
	{
		OwnerPanel->SetZoomLevelsContainer<FRestyleZoomLevelsContainer>();
	}
}

void SDefault_GraphNodeK2Base::SetupRenderOpacity()
{
	if (IsDisabled()) SetRenderOpacity(UNodeRestyleSettings::Get()->DisabledOpacity);
}

TSharedRef<SWidget> SDefault_GraphNodeK2Base::AddPinButtonContent_New(FText PinText, FText PinTooltipText,
                                                                      bool bRightSide, FString DocumentationExcerpt,
                                                                      TSharedPtr<SToolTip> CustomTooltip)
{
	//Restyle Pins aren't loaded then..
	if (!FAppStyle::Get().HasWidgetStyle<FTextBlockStyle>(FPinRestyleStyles::Sequence_Button_Text))
	{
		return AddPinButtonContent(PinText, PinTooltipText, bRightSide, DocumentationExcerpt, CustomTooltip);
	}

	auto Style = UPinRestyleSettings::Get();
	const auto& Seq = Style->Inputs.Sequence;

	FVector2D IconSize(UDefaultThemeSettings::GetIconSize(Seq.IconSize));
	FText Text = !Seq.OverrideText.IsEmpty() ? Seq.OverrideText : PinText;
	FMargin ButtonContentPadding = UDefaultThemeSettings::GetMargin(Seq.ButtonStyle.Get().Padding);
	float Spacing = UDefaultThemeSettings::GetSpacing(Seq.Spacing);
	 
	TSharedPtr<SWidget> ButtonContent;
	if (bRightSide)
	{
		SAssignNew(ButtonContent, SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .AutoWidth()
			  .HAlign(HAlign_Left)
			[
				SNew(STextBlock)
				.Text(Text)
				.TextStyle(FAppStyle::Get(), FPinRestyleStyles::Sequence_Button_Text)
				.ColorAndOpacity(FSlateColor::UseStyle())
			]
			+ SHorizontalBox::Slot()
			  .AutoWidth()
			  .VAlign(VAlign_Center)
			  .Padding(Spacing, 0, 0, 0)
			[
				SNew(SImage)
				.Image(FAppStyle::GetBrush(FPinRestyleStyles::Icon_AddPin))
				.DesiredSizeOverride(IconSize)
				.ColorAndOpacity(FSlateColor::UseStyle())
			];
	}
	else
	{
		SAssignNew(ButtonContent, SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .AutoWidth()
			  .VAlign(VAlign_Center)
			  .Padding(0, 0, Spacing, 0)
			[
				SNew(SImage)
				.Image(FAppStyle::GetBrush(FPinRestyleStyles::Icon_AddPin))
				.DesiredSizeOverride(IconSize)
				.ColorAndOpacity(FSlateColor::UseStyle())
			]
			+ SHorizontalBox::Slot()
			  .AutoWidth()
			  .HAlign(HAlign_Left)
			[
				SNew(STextBlock)
				.Text(Text)
				.TextStyle(FAppStyle::Get(), FPinRestyleStyles::Sequence_Button_Text)
				.ColorAndOpacity(FSlateColor::UseStyle())
			];
	}

	TSharedPtr<SToolTip> Tooltip;

	if (CustomTooltip.IsValid())
	{
		Tooltip = CustomTooltip;
	}
	else if (!DocumentationExcerpt.IsEmpty())
	{
		Tooltip = IDocumentation::Get()->CreateToolTip(PinTooltipText, NULL, GraphNode->GetDocumentationLink(),
		                                               DocumentationExcerpt);
	}
	TSharedRef<SButton> AddPinButton = SNew(SButton)
	.ContentPadding(ButtonContentPadding)
	.ButtonStyle(FAppStyle::Get(), FPinRestyleStyles::Sequence_Button)
	.OnClicked(this, &SDefault_GraphNodeK2Base::OnAddPin)
	.IsEnabled(this, &SGraphNode::IsNodeEditable)
	.ToolTipText(PinTooltipText)
	.ToolTip(Tooltip)
	.Visibility(this, &SDefault_GraphNodeK2Base::IsAddPinButtonVisible)
	[
		SNew(SBox)
		.MinDesiredHeight(Style->Base.MinDesiredHeight)
		.VAlign(VAlign_Center)
		[
			ButtonContent.ToSharedRef()
		]
	];

	AddPinButton->SetCursor(EMouseCursor::Hand);

	return AddPinButton;
}

 
void SDefault_GraphNodeK2Base::UpdateErrorInfo_New()
{
	ErrorInfoType = EDTNodeReportType::Num;
	if (GraphNode->bHasCompilerMessage)
	{
		if (GraphNode->ErrorType <= EMessageSeverity::Error)
		{
			ErrorInfoType = EDTNodeReportType::Error;
		}
		else if (GraphNode->ErrorType <= EMessageSeverity::Warning)
		{
			ErrorInfoType = EDTNodeReportType::Warning;
		}
		else
		{
			ErrorInfoType = EDTNodeReportType::Info;
		}
	}
	else if (!GraphNode->NodeUpgradeMessage.IsEmpty())
	{
		ErrorInfoType = EDTNodeReportType::Upgrade;
	}

	if (ErrorInfoType != EDTNodeReportType::Num)
	{
		ErrorMsg = UNodeRestyleSettings::Get()->NodeReports[(int)ErrorInfoType].Title;
	}
	else
	{
		ErrorMsg.Empty();
		ErrorInfoType = EDTNodeReportType::Info;
	}
}

void SDefault_GraphNodeK2Base::SetupErrorReporting_New()
{
	UpdateErrorInfo_New();

	if (!ErrorReporting.IsValid())
	{
		// generate widget
		SAssignNew(ErrorReporting, SDefault_ErrorText, ErrorInfoType)
			.ToolTipText(this, &SDefault_GraphNodeK2Base::GetErrorMsgToolTip);
	}
	ErrorReporting->SetError(ErrorMsg);
}

 
bool SDefault_GraphNodeK2Base::IsInvalid() const
{
	return GraphNode->IsDeprecated() || GraphNode->IsNodeUnrelated();
}

bool SDefault_GraphNodeK2Base::IsDisabled() const
{
	return !GraphNode->IsNodeEnabled() || GraphNode->IsDisplayAsDisabledForced();
}

bool SDefault_GraphNodeK2Base::UpdateState(bool bSelected) const
{
	auto CurrentState = bSelected
		                    ? EDTGraphNodeState::Selected
		                    : IsInvalid()
		                    ? EDTGraphNodeState::Invalid
		                    : EDTGraphNodeState::Normal;
	bool bUpdated = CurrentState != CachedState;
	if (bUpdated) CachedState = CurrentState;
	return bUpdated;
}
