// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeRestyleK2Base.h"
#include "KismetNodes/SGraphNodeK2Base.h"
#include "Internationalization/Culture.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SToolTip.h"
#include "SCommentBubble.h"
#include "SGraphPin.h"
#include "Kismet2/KismetDebugUtilities.h"
#include "IDocumentation.h"
#include "Restyle.h"
#include "Default/Nodes/Common/SDefault_ErrorText.h"
#include "SGraphPanel.h"
#include "Slate/SObjectWidget.h"

#include "Themes/Default/NodeRestyleDefault.h"
#include "Themes/Default/PinRestyleDefault.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "K2Node_Timeline.h"
#include "TutorialMetaData.h"
#include "Widgets/Layout/SBox.h"
#include "Default/Nodes/Common/SDefault_CommentBubble.h"
#include "Default/Nodes/Common/SDefault_NodeTitle.h"
#include "Components/ScaleBox.h"

TSharedPtr<SWidget> SDefault_GraphNodeRestyleK2Base::CreateEnabledStateWidget()
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

		/*FEditorStyle::GetBrush(bDevelopmentOnly
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


FMargin SDefault_GraphNodeRestyleK2Base::GetEnabledStateWidgetPadding() const
{
	return FMargin(CachedOutlineWidth, 0) + EnabledStateWidgetAdditionalPadding;
}

FReply SDefault_GraphNodeRestyleK2Base::OnAdvancedDisplayClicked()
{
	OnAdvancedViewChanged(IsAdvancedViewChecked() == ECheckBoxState::Checked
		? ECheckBoxState::Unchecked : ECheckBoxState::Checked);
	if (AdvancedViewArrow.IsValid()) AdvancedViewArrow->SetImage(GetAdvancedViewArrowNew());
	return FReply::Handled();
}

void SDefault_GraphNodeRestyleK2Base::CreateAdvancedViewArrowNew(TSharedPtr<SVerticalBox> MainBox)
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
				.Visibility(this, &SDefault_GraphNodeRestyleK2Base::AdvancedViewArrowVisibility)
				.ButtonStyle(FEditorStyle::Get(), FNodeRestyleStyles::AdvancedDisplay)
				.OnClicked(this, &SDefault_GraphNodeRestyleK2Base::OnAdvancedDisplayClicked)
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

void SDefault_GraphNodeRestyleK2Base::UpdateGraphNode()
{
	UpdateState();
	LastUpdatedState = CachedState;
	auto CurrentState = LastUpdatedState;
	auto Style = UNodeRestyleSettings::Get();
	const auto& Node = Style->Node;
	EDTGraphNodeTitleType TitleType = GetNodeType();
	const auto& State = Node.GetTypeData(TitleType).GetState(CurrentState);
	{
		InputPins.Empty();
		OutputPins.Empty();

		RightNodeBox.Reset();
		LeftNodeBox.Reset();
	}
	SetupRenderOpacity();
	ContentScale.Bind(this, &SDefault_GraphNodeRestyleK2Base::GetContentScale);

	FGraphNodeMetaData TagMeta(TEXT("Graphnode"));
	PopulateMetaTag(&TagMeta);

	TSharedPtr<SVerticalBox> MainVerticalBox;
	 
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

		TArray<FString> ExtraTextIgnore = Node.Title.bRemoveTargetIsTitle ?
			TArray{
				FString(TEXT("Target Is")),
				FString(TEXT("目标是")),
				FString(TEXT("ターゲットは")),
				FString(TEXT("타깃은"))
		}
		: TArray<FString>{};
		TSharedPtr<SDefault_NodeTitle> NodeTitle = SAssignNew(TitleExtraText, SDefault_NodeTitle, GraphNode,
		                                                      State.Title.ExtraText.Get(),
		                                                      FNodeRestyleStyles::GraphNode_Title_ExtraText,
		                                                      ExtraTextIgnore);
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
							CreateTitleWidget(NodeTitle)
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
						CreateTitleWidget(NodeTitle)
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
				TAttribute<FText>(this, &SDefault_GraphNodeRestyleK2Base::GetNodeTooltip), NULL, GraphNode->GetDocumentationLink(),
				GraphNode->GetDocumentationExcerptName());
			SetToolTip(DefaultToolTip);
		}
	};
	UpdateTooltip();

	auto MakeInnerVerticalBox = [this, &DefaultTitleAreaWidget, &Node]()-> TSharedPtr<SVerticalBox>
	{
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
				CreateNodeContentArea()
			];
		return InnerVerticalBox;
	};
	auto InnerVerticalBox = MakeInnerVerticalBox();

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
						.BorderImage(FEditorStyle::GetBrush("NoBorder"))
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
				.Text(this, &SDefault_GraphNodeRestyleK2Base::GetNodeComment)
				.OnTextCommitted(this, &SDefault_GraphNodeRestyleK2Base::OnCommentTextCommitted)
				.OnToggled(this, &SDefault_GraphNodeRestyleK2Base::OnCommentBubbleToggled)
				.AllowPinning(true)
				.EnableTitleBarBubble(true)
				.EnableBubbleCtrls(true)
				.GraphLOD(this, &SDefault_GraphNodeRestyleK2Base::GetCurrentLOD)
				.IsGraphNodeHovered(this, &SDefault_GraphNodeRestyleK2Base::IsHovered);

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
	SetToolTip(nullptr);
}

TSharedRef<SWidget> SDefault_GraphNodeRestyleK2Base::CreateNodeContentArea()
{
	auto Style = UNodeRestyleSettings::Get();
	float ContentSpacing = UDefaultThemeSettings::GetSpacing(Style->Node.ContentSpacing);
	return SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("NoBorder"))
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(0)
			//.Padding(PaddingBelowPin)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Left)
				  .FillWidth(1.0f)
				  .Padding(0)
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
			];
}

TSharedRef<SWidget> SDefault_GraphNodeRestyleK2Base::CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle)
{
	const auto& Node = UNodeRestyleSettings::Get()->Node;
	const auto& State = Node.GetTypeData(GetNodeType()).GetState(LastUpdatedState);

	SAssignNew(InlineEditableText, SInlineEditableTextBlock)
		.Style(FAppStyle::Get(), FNodeRestyleStyles::GraphNode_Title_MainText)
		//@note seems not necessary
		//.Text(NodeTitle.Get(), &SDefault_NodeTitle::GetNodeTitle_New)
		.Text(NodeTitle->GetHeadTitle())
		.OnVerifyTextChanged(this, &SDefault_GraphNodeRestyleK2Base::OnVerifyNameTextChanged)
		.OnTextCommitted(this, &SDefault_GraphNodeRestyleK2Base::OnNameTextCommited)
		.IsReadOnly(this, &SDefault_GraphNodeRestyleK2Base::IsNameReadOnly)
		.IsSelected(this, &SDefault_GraphNodeRestyleK2Base::IsSelectedExclusively)
		.ColorAndOpacity(FLinearColor::White);
	InlineEditableText->SetColorAndOpacity(State.Title.MainText.Get());

	return InlineEditableText.ToSharedRef();
}

void SDefault_GraphNodeRestyleK2Base::SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel)
{
	SGraphNodeK2Base::SetOwner(OwnerPanel);
	if (UNodeRestyleSettings::Get()->bNewZoom)
	{
		OwnerPanel->SetZoomLevelsContainer<FRestyleZoomLevelsContainer>();
	}
}

void SDefault_GraphNodeRestyleK2Base::SetupRenderOpacity()
{
	if (IsDisabled()) SetRenderOpacity(UNodeRestyleSettings::Get()->DisabledOpacity);
}

SDefault_GraphNodeRestyleK2Base::SDefault_GraphNodeRestyleK2Base()
{
	CachedNoDrawBrush = FAppStyle::Get().GetBrush(FNodeRestyleStyles::NoDrawBrush);
	CachedOutlineWidth = .0f;
	CachedState = LastUpdatedState = EDTGraphNodeState::Num;
	ErrorInfoType = EDTNodeReportType::Num;
	IChevronDown = FEditorStyle::GetBrush("Icons.ChevronDown");
	IChevronUp = FEditorStyle::GetBrush("Icons.ChevronUp");
}

void SDefault_GraphNodeRestyleK2Base::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime,
                                           const float InDeltaTime)
{
	SGraphNodeK2Base::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	if (LastUpdatedState != CachedState)
	{
		LastUpdatedState = CachedState;
		OnStateUpdated(LastUpdatedState);
	}
}

TSharedRef<SWidget> SDefault_GraphNodeRestyleK2Base::AddPinButtonContent_New(FText PinText, FText PinTooltipText,
                                                                             bool bRightSide, FString DocumentationExcerpt,
                                                                             TSharedPtr<SToolTip> CustomTooltip)
{
	bool bPinsLoaded = FRestyleModule::Get()->IsSubjectProviderRegistered("Default", ERestyleSubject::Pin);
	if (!bPinsLoaded)
	{
		return AddPinButtonContent(PinText, PinTooltipText, bRightSide, DocumentationExcerpt, CustomTooltip);
	}

	auto Style = UPinRestyleSettings::Get();
	const auto& Seq = Style->Inputs.Sequence;
	FVector2D IconSize = UDefaultThemeSettings::GetIconSize(Seq.IconSize);
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
				.Image(FEditorStyle::GetBrush(FPinRestyleStyles::Icon_AddPin))
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
				.Image(FEditorStyle::GetBrush(FPinRestyleStyles::Icon_AddPin))
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
		.OnClicked(this, &SDefault_GraphNodeRestyleK2Base::OnAddPin)
		.IsEnabled(this, &SDefault_GraphNodeRestyleK2Base::IsNodeEditable)
		.ToolTipText(PinTooltipText)
		.ToolTip(Tooltip)
		.Visibility(this, &SDefault_GraphNodeRestyleK2Base::IsAddPinButtonVisible)
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


void SDefault_GraphNodeRestyleK2Base::UpdateErrorInfo_New()
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

void SDefault_GraphNodeRestyleK2Base::SetupErrorReporting_New()
{
	UpdateErrorInfo_New();

	if (!ErrorReporting.IsValid())
	{
		// generate widget
		SAssignNew(ErrorReporting, SDefault_ErrorText, ErrorInfoType)
			.ToolTipText(this, &SDefault_GraphNodeRestyleK2Base::GetErrorMsgToolTip);
	}
	ErrorReporting->SetError(ErrorMsg);
}


bool SDefault_GraphNodeRestyleK2Base::IsInvalid() const
{
	return GraphNode->IsDeprecated() || GraphNode->IsNodeUnrelated();
}

bool SDefault_GraphNodeRestyleK2Base::IsDisabled() const
{
	return !GraphNode->IsNodeEnabled() || GraphNode->IsDisplayAsDisabledForced();
}

void SDefault_GraphNodeRestyleK2Base::UpdateState(bool bSelected) const
{
	CachedState = bSelected
		? EDTGraphNodeState::Selected
		: IsInvalid()
		? EDTGraphNodeState::Invalid
		: EDTGraphNodeState::Normal;
}

void SDefault_GraphNodeRestyleK2Base::OnStateUpdated(EDTGraphNodeState NewState)
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

const FSlateBrush* SDefault_GraphNodeRestyleK2Base::GetShadowBrush(bool bSelected) const
{
	UpdateState(bSelected);
	return CachedNoDrawBrush;
}

EDTGraphNodeTitleType SDefault_GraphNodeRestyleK2Base::GetNodeType() const
{
	FLinearColor RawTitleColor = GetNodeObj()->GetNodeTitleColor();

	return UNodeRestyleSettings::DetermineTitleTypeByColor(RawTitleColor);
}
