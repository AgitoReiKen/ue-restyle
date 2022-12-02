// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeRestyleBase.h"

#include "IDocumentation.h"
#include "Default/Nodes/Common/SDefault_CommentBubble.h"
#include "Default/Nodes/Common/SDefault_NodeTitle.h"
#include "SGraphPanel.h"
#include "TutorialMetaData.h"

#include "Themes/Default/NodeRestyleDefault.h"

#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "Restyle/Classes/Default/Nodes/Common/SDefault_ErrorText.h"
SDefault_GraphNodeRestyleBase::SDefault_GraphNodeRestyleBase()
{
	CachedNoDrawBrush = FAppStyle::Get().GetBrush(FNodeRestyleStyles::NoDrawBrush);
	CachedOutlineWidth = .0f;
	CachedState = EDTGraphNodeState::Num;
	ErrorInfoType = EDTNodeReportType::Num;

	IChevronDown = FAppStyle::GetBrush("Icons.ChevronDown");
	IChevronUp = FAppStyle::GetBrush("Icons.ChevronUp");
}

void SDefault_GraphNodeRestyleBase::SetupRenderOpacity()
{
	if (IsDisabled()) SetRenderOpacity(UNodeRestyleSettings::Get()->DisabledOpacity);
}

bool SDefault_GraphNodeRestyleBase::IsInvalid() const
{
	return GraphNode->IsDeprecated() || GraphNode->IsNodeUnrelated();
}

bool SDefault_GraphNodeRestyleBase::IsDisabled() const
{
	return !GraphNode->IsNodeEnabled() || GraphNode->IsDisplayAsDisabledForced();
}

bool SDefault_GraphNodeRestyleBase::UpdateState(bool bSelected) const
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

const FSlateBrush* SDefault_GraphNodeRestyleBase::GetShadowBrush(bool bSelected) const
{
	if (UpdateState(bSelected))
	{
		EDTGraphNodeTitleType TitleType = GetNodeType();
		auto* Style = UNodeRestyleSettings::Get();
		const auto& State = Style->Node.GetTypeData(TitleType).GetState(CachedState);
		if (MainBackground.IsValid())
		{
			auto Body = FAppStyle::Get().GetBrush(FNodeRestyleStyles::GraphNode_Body(TitleType, CachedState));
			CachedOutlineWidth = Body->OutlineSettings.Width;
			MainBackground->SetImage(Body);
		}

		if (TitleIcon.IsValid())
		{
			TitleIcon->SetColorAndOpacity(State.Title.Icon.Get());
		}
		if (MainTitleBorder.IsValid())
		{
			auto Body = FAppStyle::Get().
				GetBrush(FNodeRestyleStyles::GraphNode_Title_Body(TitleType, CachedState));
			MainTitleBorder->SetBorderImage(Body);
			MainTitleBorder->SetBorderBackgroundColor(State.Title.Background.Get());
		}
		if (InlineEditableText.IsValid())
		{
			InlineEditableText->SetColorAndOpacity(State.Title.MainText.Get());
		}
		if (TitleExtraText.IsValid() && TitleExtraText->ExtraTextBlock.IsValid())
		{
			TitleExtraText->ExtraTextBlock->SetColorAndOpacity(State.Title.ExtraText.Get());
		}
		if (EnabledStateWidgetBox.IsValid())
		{
			EnabledStateWidgetBox->SetPadding(GetEnabledStateWidgetPadding());
		}
	}
	return CachedNoDrawBrush;
}

void SDefault_GraphNodeRestyleBase::SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel)
{
	SGraphNode::SetOwner(OwnerPanel);
	if (UNodeRestyleSettings::Get()->bNewZoom)
	{
		OwnerPanel->SetZoomLevelsContainer<FRestyleZoomLevelsContainer>();
	}
}

void SDefault_GraphNodeRestyleBase::UpdateGraphNode()
{
	UpdateState();
	{
		InputPins.Empty();
		OutputPins.Empty();

		// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
		RightNodeBox.Reset();
		LeftNodeBox.Reset();
	}
	SetupRenderOpacity();
	ContentScale.Bind(this, &SGraphNode::GetContentScale);

	// Setup a meta tag for this node
	FGraphNodeMetaData TagMeta(TEXT("Graphnode"));
	PopulateMetaTag(&TagMeta);

	TSharedPtr<SVerticalBox> MainVerticalBox;
	auto Style = UNodeRestyleSettings::Get();
	const auto& Node = Style->Node;
	EDTGraphNodeTitleType TitleType = GetNodeType();
	EDTGraphNodeState CurrentState = IsInvalid() ? EDTGraphNodeState::Invalid : EDTGraphNodeState::Normal;

	const auto& State = Node.GetTypeData(TitleType).GetState(CurrentState);

	auto MakeDefaultTitleAreaWidget = [this, &Node, &State, CurrentState, TitleType]()-> TSharedRef<SOverlay>
	{
		auto GetIcon = [this]() -> const FSlateBrush*
		{
			IconColor = FLinearColor::White;
			if (GraphNode != NULL && GraphNode->ShowPaletteIconOnNode())
			{
				return GraphNode->GetIconAndTint(IconColor).GetOptionalIcon();
			}
			return nullptr;
		};
		const FSlateBrush* IconBrush = GetIcon();

		TSharedPtr<SDefault_NodeTitle> NodeTitle = SAssignNew(TitleExtraText, SDefault_NodeTitle, GraphNode,
		                                                      State.Title.ExtraText.Get(),
		                                                      FNodeRestyleStyles::GraphNode_Title_ExtraText);
		auto RightWidget = CreateTitleRightWidget();
		auto Body = FAppStyle::Get().GetBrush(FNodeRestyleStyles::GraphNode_Title_Body(TitleType, CurrentState));
		if (Node.Title.bAlternativeStyle && TitleType != EDTGraphNodeTitleType::Event)
		{
			float Spacing = UDefaultThemeSettings::GetSpacing(Node.Title.AltItemSpacing);
			SAssignNew(TitleContent, SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						[
							SAssignNew(InlineEditableText, SInlineEditableTextBlock)
							.Style(FAppStyle::Get(), FNodeRestyleStyles::GraphNode_Title_MainText)
							//@note seems not necessary
							//.Text(NodeTitle.Get(), &SDefault_NodeTitle::GetNodeTitle_New)
							.Text(NodeTitle->GetHeadTitle())
							.OnVerifyTextChanged(this, &SGraphNode::OnVerifyNameTextChanged)
							.OnTextCommitted(this, &SGraphNode::OnNameTextCommited)
							.IsReadOnly(this, &SGraphNode::IsNameReadOnly)
							.IsSelected(this, &SGraphNode::IsSelectedExclusively)
							.ColorAndOpacity(FLinearColor::White)
						]
						+ SHorizontalBox::Slot()
						  .VAlign(VAlign_Center)
						  .HAlign(HAlign_Right)
						  .AutoWidth()
						  .Padding(Spacing, 0, 0, 0)
						[
							SAssignNew(TitleIcon, SImage)
							.Image(IconBrush)
							.ColorAndOpacity(State.Title.Icon.Get())
						]
						+ SHorizontalBox::Slot()
						  .VAlign(VAlign_Center)
						  .HAlign(HAlign_Right)
						  .Padding(RightWidget != SNullWidget::NullWidget ? Spacing : 0, 0, 0, 0)
						  .AutoWidth()
						[
							RightWidget
						]
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						NodeTitle.ToSharedRef()
					]
				];
		}
		else
		{
			bool bHasSubText = NodeTitle.Get()->ExtraTextBlock.IsValid()
				                   ? !NodeTitle.Get()->ExtraTextBlock->GetText().IsEmpty()
				                   : false;
			float Spacing = UDefaultThemeSettings::GetSpacing(Node.Title.ItemSpacing);
			SAssignNew(TitleContent, SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .VAlign(bHasSubText ? VAlign_Top : VAlign_Center)
				  .HAlign(HAlign_Left)
				  .AutoWidth()
				[
					SAssignNew(TitleIcon, SImage)
					.Image(IconBrush)
					.ColorAndOpacity(FSlateColor(State.Title.Icon.Get()))
				]
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Fill)
				  .Padding(Spacing, 0, 0, 0)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					[
						SAssignNew(InlineEditableText, SInlineEditableTextBlock)
						.Style(FAppStyle::Get(), FNodeRestyleStyles::GraphNode_Title_MainText)
						//.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
						.Text(NodeTitle->GetHeadTitle())
						.OnVerifyTextChanged(this, &SGraphNode::OnVerifyNameTextChanged)
						.OnTextCommitted(this, &SGraphNode::OnNameTextCommited)
						.IsReadOnly(this, &SGraphNode::IsNameReadOnly)
						.IsSelected(this, &SGraphNode::IsSelectedExclusively)
						.ColorAndOpacity(FLinearColor::White)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						NodeTitle.ToSharedRef()
					]
				]
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Right)
				  .VAlign(VAlign_Center)
				  .Padding(
					  RightWidget != SNullWidget::NullWidget ? Spacing : 0, 0,
					  0, 0)
				  .AutoWidth()
				[
					RightWidget
				];
		}
		 
		InlineEditableText->SetColorAndOpacity(State.Title.MainText.Get());
		return SNew(SOverlay)
			+ SOverlay::Slot()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Center)
			[
				SAssignNew(MainTitleBorder, SBorder)
				.BorderImage(Body)
				//.Visibility(EVisibility::HitTestInvisible)
				// Allowing interaction on title
				.Visibility(EVisibility::SelfHitTestInvisible)
				.BorderBackgroundColor(FSlateColor(State.Title.Background.Get()))
				.Padding(UDefaultThemeSettings::GetMargin(Node.Title.Padding))
				[
					TitleContent.ToSharedRef()
				]
			];
	};

	auto DefaultTitleAreaWidget = MakeDefaultTitleAreaWidget();
	SetDefaultTitleAreaWidget(DefaultTitleAreaWidget);

	auto UpdateTooltip = [this]()
	{
		if (!SWidget::GetToolTip().IsValid())
		{
			TSharedRef<SToolTip> DefaultToolTip = IDocumentation::Get()->CreateToolTip(
				TAttribute<FText>(this, &SGraphNode::GetNodeTooltip), NULL, GraphNode->GetDocumentationLink(),
				GraphNode->GetDocumentationExcerptName());
			SetToolTip(DefaultToolTip);
		}
	};
	UpdateTooltip();
	
	auto InnerVerticalBox = MakeInnerVerticalBox(DefaultTitleAreaWidget);
	auto AddEnabledStateWidget = [this, &InnerVerticalBox, Style]
	{
		EnabledStateWidget = CreateEnabledStateWidget();
		if (EnabledStateWidget.IsValid())
		{
			InnerVerticalBox->AddSlot()
			                .AutoHeight()
			                .HAlign(HAlign_Fill)
			                .VAlign(VAlign_Top)
			[
				SAssignNew(EnabledStateWidgetBox, SBox)
				.Padding(GetEnabledStateWidgetPadding())
				[
					EnabledStateWidget.ToSharedRef()
				]
			];
		}
	};
	auto AddErrorReporting = [this, &InnerVerticalBox]
	{
		SetupErrorReporting_New();
		InnerVerticalBox->AddSlot()
		                .AutoHeight()
		                .Padding(0)
		[
			ErrorReporting->AsWidget()
		];
	};
	AddEnabledStateWidget();
	AddErrorReporting();
	
	auto AddVerticalBox = [this, &MainVerticalBox, &TagMeta, &InnerVerticalBox, &Style, &State, &TitleType,
			&CurrentState]
	{
		auto Body = FAppStyle::Get().GetBrush(FNodeRestyleStyles::GraphNode_Body(TitleType, CurrentState));
		
		GetOrAddSlot(ENodeZone::Center)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(MainVerticalBox, SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SOverlay)
					.AddMetaData<FGraphNodeMetaData>(TagMeta)
					+ SOverlay::Slot()
					.Padding(0)
					[
						SAssignNew(MainBackground, SImage)
						.Image(Body)
					]
					+ SOverlay::Slot()
					.Padding(0)
					[
						SAssignNew(ContentBorder, SBorder)
						.BorderImage(FAppStyle::GetBrush("NoBorder"))
						.Padding(0)
						[
							InnerVerticalBox.ToSharedRef()
						]
					]
				]
			];
	};
	AddVerticalBox();

	auto AddCommentIfNeeded = [this, Style]()
	{
		bool SupportsBubble = true;
		if (GraphNode != nullptr)
		{
			SupportsBubble = GraphNode->SupportsCommentBubble();
		}

		if (SupportsBubble)
		{
			TSharedPtr<SDefault_CommentBubble> CommentBubble;
			//GetDefault<UGraphEditorSettings>()->DefaultCommentNodeTitleColor;
			SAssignNew(CommentBubble, SDefault_CommentBubble)
				.GraphNode(GraphNode)
				.Text(this, &SGraphNode::GetNodeComment)
				.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
				.OnToggled(this, &SGraphNode::OnCommentBubbleToggled)
				.AllowPinning(true)
				.EnableTitleBarBubble(true)
				.EnableBubbleCtrls(true)
				.GraphLOD(this, &SGraphNode::GetCurrentLOD)
				.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

			GetOrAddSlot(ENodeZone::TopCenter)
				.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
				.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
				.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
				.VAlign(VAlign_Top)
				[
					CommentBubble.ToSharedRef()
				];
		}
	};
	AddCommentIfNeeded();

	CreateBelowWidgetControls(MainVerticalBox);
	CreatePinWidgets();
	CreateInputSideAddButton(LeftNodeBox);
	CreateOutputSideAddButton(RightNodeBox);
	CreateBelowPinControls(InnerVerticalBox);
	CreateAdvancedViewArrowNew(InnerVerticalBox);
}

EDTGraphNodeTitleType SDefault_GraphNodeRestyleBase::GetNodeType() const
{
	FLinearColor RawTitleColor = GetNodeObj()->GetNodeTitleColor();

	return UNodeRestyleSettings::DetermineTitleTypeByColor(RawTitleColor);
}

TSharedPtr<SWidget> SDefault_GraphNodeRestyleBase::CreateEnabledStateWidget()
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

FMargin SDefault_GraphNodeRestyleBase::GetEnabledStateWidgetPadding() const
{
	return FMargin(CachedOutlineWidth, 0) + EnabledStateWidgetAdditionalPadding;
}

void SDefault_GraphNodeRestyleBase::UpdateErrorInfo_New()
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

void SDefault_GraphNodeRestyleBase::SetupErrorReporting_New()
{
	UpdateErrorInfo_New();

	if (!ErrorReporting.IsValid())
	{
		// generate widget
		SAssignNew(ErrorReporting, SDefault_ErrorText, ErrorInfoType)
			.ToolTipText(this, &SDefault_GraphNodeRestyleBase::GetErrorMsgToolTip);
	}
	ErrorReporting->SetError(ErrorMsg);
}

void SDefault_GraphNodeRestyleBase::CreateAdvancedViewArrowNew(TSharedPtr<SVerticalBox> MainBox)
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
				.Visibility(this, &SDefault_GraphNodeRestyleBase::AdvancedViewArrowVisibility)
				.ButtonStyle(FAppStyle::Get(), FNodeRestyleStyles::AdvancedDisplay)
				.OnClicked(this, &SDefault_GraphNodeRestyleBase::OnAdvancedDisplayClicked)
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

FReply SDefault_GraphNodeRestyleBase::OnAdvancedDisplayClicked()
{
	OnAdvancedViewChanged(IsAdvancedViewChecked() == ECheckBoxState::Checked
		? ECheckBoxState::Unchecked : ECheckBoxState::Checked);
	if (AdvancedViewArrow.IsValid()) AdvancedViewArrow->SetImage(GetAdvancedViewArrowNew());
	return FReply::Handled();
}

TSharedPtr<SVerticalBox> SDefault_GraphNodeRestyleBase::MakeInnerVerticalBox(TSharedRef<SOverlay> DefaultTitleAreaWidget)
{
	auto Style = UNodeRestyleSettings::Get();
	const auto& Node = Style->Node;
	float ContentSpacing = UDefaultThemeSettings::GetSpacing(Node.ContentSpacing);
	TSharedPtr<SVerticalBox> InnerVerticalBox =
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Top)
			  .Padding(0)
			[
				DefaultTitleAreaWidget
			]
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Top)
			  .Padding(0)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("NoBorder"))
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(0)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					  .HAlign(HAlign_Left)
					  .FillWidth(1.0f)
					  .Padding(0 )
					[
						// LEFT
						SAssignNew(LeftNodeBox, SVerticalBox)
					]
					+ SHorizontalBox::Slot()
					  .AutoWidth()
					  .HAlign(HAlign_Right)
					  .Padding(ContentSpacing, 0, 0, 0)
					[
						// RIGHT
						SAssignNew(RightNodeBox, SVerticalBox)
					]
				]
			];
		return InnerVerticalBox;
}
