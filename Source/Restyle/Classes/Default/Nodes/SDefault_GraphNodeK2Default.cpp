// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeK2Default.h"
#include "SDefault_GraphNodeK2Base.h"
#include "K2Node.h"
#include "KismetNodes/SGraphNodeK2Base.h"
#include "Internationalization/Culture.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SToolTip.h"
#include "SCommentBubble.h"
#include "SGraphPin.h"
#include "K2Node_Timeline.h"
#include "Kismet2/Breakpoint.h"
#include "IDocumentation.h"
#include "TutorialMetaData.h"
#include "Widgets/Layout/SBox.h"
#include "SDefault_CommentBubble.h"
#include "SDefault_NodeTitle.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "SDefault_ErrorText.h"
#include "Components/ScaleBox.h"
#include "Slate/SObjectWidget.h"
#include "Themes/Default/NodeRestyleDefault.h"
#include "Themes/Default/PinRestyleDefault.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"

void SDefault_GraphNodeK2Default::Construct(const FArguments& InArgs, UK2Node* InNode)
{
	GraphNode = InNode;
	auto Style = UNodeRestyleSettings::Get();
	CachedState = IsInvalid() ? EDTGraphNodeState::Invalid : EDTGraphNodeState::Normal;
	CachedOutlineWidth = UDefaultThemeSettings::GetOutlineWidth(
		Style->Node.GetTypeData(GetNodeType()).GetState(CachedState).Body.Get().OutlineWidth
	);
	EnabledStateWidgetAdditionalPadding = UDefaultThemeSettings::GetMargin(Style->StateWidget.Padding);
	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}

EDTGraphNodeTitleType SDefault_GraphNodeK2Default::GetNodeType()
{
	FLinearColor RawTitleColor = GetNodeObj()->GetNodeTitleColor();

	return UNodeRestyleSettings::DetermineTitleTypeByColor(RawTitleColor);
}


void SDefault_GraphNodeK2Default::UpdateStandardNode_New()
{
	{
		InputPins.Empty();
		OutputPins.Empty();

		RightNodeBox.Reset();
		LeftNodeBox.Reset();
	}
	SetupRenderOpacity();
	ContentScale.Bind(this, &SGraphNode::GetContentScale);

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

		FString ExtraTextIgnore = Node.Title.bRemoveTargetIsTitle ? "Target Is" : "";
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

	auto MakeInnerVerticalBox = [this, &DefaultTitleAreaWidget, &Node]()-> TSharedPtr<SVerticalBox>
	{
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
				]
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
			//@TODO
			// Create comment bubble
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

	// @WARN <Do Not Touch> zone
	{
		CreateBelowWidgetControls(MainVerticalBox);
		CreatePinWidgets();
		CreateInputSideAddButton(LeftNodeBox);
		CreateOutputSideAddButton(RightNodeBox);
		CreateBelowPinControls(InnerVerticalBox);
		CreateAdvancedViewArrowNew(InnerVerticalBox);
		SetToolTip(nullptr);
	}
}

void SDefault_GraphNodeK2Default::UpdateCompactNode_New()
{
	{
		InputPins.Empty();
		OutputPins.Empty();

		RightNodeBox.Reset();
		LeftNodeBox.Reset();
	}
	SetupRenderOpacity();
	ContentScale.Bind(this, &SGraphNode::GetContentScale);

	FGraphNodeMetaData TagMeta(TEXT("Graphnode"));
	PopulateMetaTag(&TagMeta);
	 
	TSharedRef<SOverlay> NodeOverlay = SNew(SOverlay);

	TSharedRef<SOverlay> PinOverlay = SNew(SOverlay);
	const auto& State = UNodeRestyleSettings::Get()->CompactNode.States.GetState(CachedState);
	EDTGraphNodeTitleType TitleType = GetNodeType();
	const auto& CompactNode = UNodeRestyleSettings::Get()->CompactNode;
	TSharedRef<SWidget> AlternativeTitleWidget = SNullWidget::NullWidget;

	auto AddIdentificationContent = [this, &NodeOverlay, &State, &TitleType, &CompactNode, &AlternativeTitleWidget]()
	{
		TSharedPtr<SDefault_NodeTitle> NodeTitle = SNew(SDefault_NodeTitle, GraphNode, FLinearColor::Black,
		                                                FNodeRestyleStyles::GraphNode_Title_ExtraText)
			.Text(this, &SDefault_GraphNodeK2Base::GetNodeCompactTitle);
		TSharedPtr<SWidget> Image = GraphNode->CreateNodeImage();
		//CastNode
		//FText CastSymbol = NSLOCTEXT("K2Node", "CastSymbol", "\x2022");
		bool bIsMacro = false;
		bool bIsFunc = false;
		switch (TitleType)
		{
		case EDTGraphNodeTitleType::Function:
		case EDTGraphNodeTitleType::PureFunction:
			bIsFunc = true;
			break;
		case EDTGraphNodeTitleType::ExecBranch:
			bIsMacro = true;
			break;
		default: break;
		}
		float LenValue = bIsFunc ? CompactNode.AltFuncIfGreater : CompactNode.AltMacroIfGreater;
		FString NodeTitleStr = NodeTitle->GetHeadTitle().ToString();
		bool bAlternative = /*LenValue != -1 && */ NodeTitleStr.Len() > LenValue;
		bool bIsOneSymbolText = NodeTitleStr.Len() == 1;
		//Map, Set, Array Nodes Check
		if (!Image.IsValid())
		{
			FName Id = "";
			FLinearColor IdColor = FLinearColor::Transparent;
			if (bIsFunc)
			{
				Id = "Kismet.AllClasses.FunctionIcon";
				IdColor = bAlternative
					          ? CompactNode.AlternativeTitle.FunctionIconColor.Get()
					          : CompactNode.Title.FunctionIconColor.Get();
			}
			else if (bIsMacro)
			{
				Id = "GraphEditor.Macro_16x";
				IdColor = bAlternative
					          ? CompactNode.AlternativeTitle.MacroIconColor.Get()
					          : CompactNode.Title.MacroIconColor.Get();
			}

			Image = SNew(SImage).Image(FAppStyle::Get().GetBrush(Id)).ColorAndOpacity(IdColor);
		}

		if (bAlternative)
		{
			//@formatter:off
			auto Padding = UDefaultThemeSettings::GetMargin(CompactNode.AlternativeTitle.Padding);
			float ItemSpacing = UDefaultThemeSettings::GetSpacing(CompactNode.AlternativeTitle.ItemSpacing);
			AlternativeTitleWidget = SNew(SBox).Padding(Padding)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .HAlign(HAlign_Fill)
				  .VAlign(VAlign_Top)
				[
					// MIDDLE
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					  .HAlign(HAlign_Center)
					  .AutoHeight()
					[
						SAssignNew(CompactTitleTextBlock, STextBlock)
						.TextStyle(FEditorStyle::Get(), FNodeRestyleStyles::GraphNode_Compact_AlternativeTitle)
						.ColorAndOpacity(State.TitleColor.Get())
						//.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
						.Text(NodeTitle->GetHeadTitle())
						.WrapTextAt(CompactNode.AlternativeTitle.WrapAt)
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
				  .Padding(ItemSpacing, 0, 0, 0)
				[
					SNew(SScaleBox)
					.RenderTransform(FSlateRenderTransform(FScale2D(1.0f)))
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.Stretch(EStretch::ScaleToFit)
					.StretchDirection(EStretchDirection::Both)
					[
						Image.ToSharedRef()
					]
				]
			];
			//@formatter:on
		}
		else
		{
			NodeOverlay->AddSlot()
			           .HAlign(HAlign_Fill)
			           .VAlign(VAlign_Fill)
			           .Padding(0.f)
			[
				SNew(SScaleBox)
				.RenderTransform(FSlateRenderTransform(FScale2D(.5f)))
				.RenderTransformPivot(.5f)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Stretch(EStretch::ScaleToFit)
				.StretchDirection(EStretchDirection::Both)
				[
					Image.ToSharedRef()
				]
			];
			//@formatter:off 
			auto Padding = UDefaultThemeSettings::GetMargin(CompactNode.Title.Padding);
			NodeOverlay->AddSlot()
			           .HAlign(HAlign_Center)
			           .VAlign(VAlign_Center)
			           .Padding(Padding)
			[
				// MIDDLE
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				  .HAlign(HAlign_Center)
				  .AutoHeight()
				[
					SAssignNew(CompactTitleTextBlock, STextBlock)
					.TextStyle(FEditorStyle::Get(),
					           bIsOneSymbolText
						           ? FNodeRestyleStyles::GraphNode_Compact_Title_OneSymbol
						           : FNodeRestyleStyles::GraphNode_Compact_Title)
				.ColorAndOpacity(State.TitleColor.Get())
				//.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
				.Text(NodeTitle->GetHeadTitle())
				.WrapTextAt(CompactNode.Title.WrapAt)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					NodeTitle.ToSharedRef()
				]
			];
			//@formatter:on
		}
	};
	AddIdentificationContent();

	float ContentSpacing = UDefaultThemeSettings::GetSpacing(CompactNode.ContentSpacing);
	PinOverlay->AddSlot()
	          .HAlign(HAlign_Fill)
	          .VAlign(VAlign_Top)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SAssignNew(LeftNodeBox, SVerticalBox)
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SNew(SSpacer)
			.Size(ContentSpacing)

		] + SHorizontalBox::Slot()
		.AutoWidth()
		[
			SAssignNew(RightNodeBox, SVerticalBox)
		]
	];
	NodeOverlay->AddSlot()
	[
		SNew(SBox)
			.Padding(0)
		.MinDesiredWidth(CompactNode.MinWidth)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			  .Padding(0)
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			[
				AlternativeTitleWidget
			]
			+ SVerticalBox::Slot()
			  .Padding(0)
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			[
				PinOverlay
			]
		]
	];
	auto MakeInnerVerticalBox = [this, &NodeOverlay, &State]()-> TSharedRef<SVerticalBox>
	{
		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				// NODE CONTENT AREA
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SAssignNew(CompactBody, SImage)
					.Image(FEditorStyle::GetBrush(FNodeRestyleStyles::GraphNode_Compact_Body(CachedState)))
				]
				+ SOverlay::Slot()
				.Padding(0.f)
				[
					NodeOverlay
				]
			];
	};

	TSharedRef<SVerticalBox> InnerVerticalBox = MakeInnerVerticalBox();

	auto AddEnabledStateWidget = [this, &InnerVerticalBox]()
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
	AddEnabledStateWidget();

	auto AddErrorReporting = [this, &InnerVerticalBox]()
	{
		SetupErrorReporting_New();
		InnerVerticalBox->AddSlot()
		                .AutoHeight()
		                .Padding(0)
		[
			ErrorReporting->AsWidget()
		];
	};
	AddErrorReporting();


	auto Style = UNodeRestyleSettings::Get();
	auto AddComment = [this, Style]()
	{
		// Create comment bubble
		TSharedPtr<SDefault_CommentBubble> CommentBubble;

		SAssignNew(CommentBubble, SDefault_CommentBubble)
			.GraphNode(GraphNode)
			.Text(this, &SGraphNode::GetNodeComment)
			.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
			.AllowPinning(true)
			.EnableTitleBarBubble(true)
			.EnableBubbleCtrls(true)
			.GraphLOD(this, &SGraphNode::GetCurrentLOD)
			.IsGraphNodeHovered(this, &SGraphNodeK2Base::IsHovered);

		GetOrAddSlot(ENodeZone::TopCenter)
			.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
			.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
			.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
			.VAlign(VAlign_Top)
			[
				CommentBubble.ToSharedRef()
			];
	};
	AddComment();
	this->GetOrAddSlot(ENodeZone::Center)
	    .HAlign(HAlign_Center)
	    .VAlign(VAlign_Center)
	[
		InnerVerticalBox
	];

	CreatePinWidgets();

	// Hide pin labels
	for (auto InputPin : this->InputPins)
	{
		if (InputPin->GetPinObj()->ParentPin == nullptr)
		{
			InputPin->SetShowLabel(false);
		}
	}

	for (auto OutputPin : this->OutputPins)
	{
		if (OutputPin->GetPinObj()->ParentPin == nullptr)
		{
			OutputPin->SetShowLabel(false);
		}
	}

	CreateInputSideAddButton(LeftNodeBox);
	CreateOutputSideAddButton(RightNodeBox);
}

void SDefault_GraphNodeK2Default::UpdateGraphNode()
{
	UpdateState();
	UK2Node* K2Node = CastChecked<UK2Node>(GraphNode);
	if (K2Node->ShouldDrawCompact())
	{
		UpdateCompactNode_New();
	}
	else
	{
		UpdateStandardNode_New();
	}
}

const FSlateBrush* SDefault_GraphNodeK2Default::GetShadowBrush(bool bSelected) const
{
	if (UpdateState(bSelected))
	{
		UK2Node* K2Node = CastChecked<UK2Node>(GraphNode);
		const bool bCompactMode = K2Node->ShouldDrawCompact();
		if (bCompactMode)
		{
			auto* Style = UNodeRestyleSettings::Get();
			const auto& State = Style->CompactNode.States.GetState(CachedState);
			if (CompactTitleTextBlock.IsValid())
			{
				CompactTitleTextBlock->SetColorAndOpacity(State.TitleColor.Get());
			}
			if (CompactBody.IsValid())
			{
				auto Body = FEditorStyle::GetBrush(FNodeRestyleStyles::GraphNode_Compact_Body(CachedState));
				CachedOutlineWidth = Body->OutlineSettings.Width;
				CompactBody->SetImage(Body);
			}
		}
		else
		{
			FLinearColor RawTitleColor = GetNodeObj()->GetNodeTitleColor();
			EDTGraphNodeTitleType TitleType = UNodeRestyleSettings::DetermineTitleTypeByColor(RawTitleColor);
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
	}
	return CachedNoDrawBrush;
}
