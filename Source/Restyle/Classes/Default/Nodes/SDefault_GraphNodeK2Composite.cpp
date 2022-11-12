// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeK2Composite.h"
#include "EdGraph/EdGraph.h"
#include "Widgets/SBoxPanel.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SToolTip.h"
#include "Styling/CoreStyle.h"
#include "GraphEditorSettings.h"
#include "SCommentBubble.h"
#include "K2Node_Composite.h"
#include "SGraphPreviewer.h"
#include "IDocumentationPage.h"
#include "IDocumentation.h"
#include "SDefault_CommentBubble.h"

#include "Widgets/Text/SInlineEditableTextBlock.h"

/////////////////////////////////////////////////////
// SDefault_GraphNodeK2Composite

void SDefault_GraphNodeK2Composite::Construct(const FArguments& InArgs, UK2Node_Composite* InNode)
{
	GraphNode = InNode;
	auto Style = UNodeRestyleSettings::Get();
	CachedState = IsInvalid() ? EDTGraphNodeState::Invalid : EDTGraphNodeState::Normal;
	CachedOutlineWidth = UDefaultThemeSettings::GetOutlineWidth(
		Style->CollapsedNode.GetTypeData(GetNodeType()).GetState(CachedState).Body.Get().OutlineWidth
	);
	EnabledStateWidgetAdditionalPadding = UDefaultThemeSettings::GetMargin(Style->StateWidget.Padding);
	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}

EDTCollapsedNodeType SDefault_GraphNodeK2Composite::GetNodeType() const
{
	return EDTCollapsedNodeType::Default;
}

void SDefault_GraphNodeK2Composite::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	SetupErrorReporting_New();
	const auto& CollapsedNode = UNodeRestyleSettings::Get()->CollapsedNode;
	EDTCollapsedNodeType NodeType = GetNodeType();
	const auto& State = CollapsedNode.GetTypeData(NodeType).GetState(CachedState);
	TSharedPtr<SDefault_NodeTitle> NodeTitle = SNew(SDefault_NodeTitle, GraphNode, State.Title.ExtraText.Get(),
	                                                FNodeRestyleStyles::CollapsedNode_Title_ExtraText);
	//  ______________________
	// |      TITLE AREA      |
	// +-------+------+-------+
	// | (>) L |      | R (>) |
	// | (>) E |      | I (>) |
	// | (>) F |      | G (>) |
	// | (>) T |      | H (>) |
	// |       |      | T (>) |
	// |_______|______|_______|
	//
	FMargin TitlePadding = UDefaultThemeSettings::Get()->GetMargin(CollapsedNode.Title.Padding);
	ContentScale.Bind(this, &SGraphNode::GetContentScale);
	GetOrAddSlot(ENodeZone::Center)
	    .HAlign(HAlign_Center)
	    .VAlign(VAlign_Center)
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SAssignNew(Body, SImage)
			.Image(FAppStyle::Get().GetBrush(FNodeRestyleStyles::CollapsedNode_Body(NodeType, CachedState)))
		]
		+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Top)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				  .HAlign(HAlign_Left)
				  .VAlign(VAlign_Center)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					  .AutoHeight()
					  .HAlign(HAlign_Fill)
					  .VAlign(VAlign_Top)
					  .Padding(TitlePadding)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SAssignNew(InlineEditableText, SInlineEditableTextBlock)
							.Style(FEditorStyle::Get(), FNodeRestyleStyles::CollapsedNode_Title_MainText)
							//.Text(NodeTitle.Get(), &sSDefault_NodeTitle::GetHeadTitle)
							.Text(NodeTitle->GetHeadTitle())
							.OnVerifyTextChanged(this, &SDefault_GraphNodeK2Composite::OnVerifyNameTextChanged)
							.OnTextCommitted(this, &SDefault_GraphNodeK2Composite::OnNameTextCommited)
							.IsReadOnly(this, &SDefault_GraphNodeK2Composite::IsNameReadOnly)
							.IsSelected(this, &SDefault_GraphNodeK2Composite::IsSelectedExclusively)
							.ColorAndOpacity(FLinearColor::White)
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							NodeTitle.ToSharedRef()
						]
					]
				]
			]
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Top)
			[
				CreateNodeBody()
			]
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .Padding(0)
			[
				ErrorReporting->AsWidget()
			]
		]

	];
	InlineEditableText->SetColorAndOpacity(State.Title.MainText.Get());
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
	.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)
		[
			CommentBubble.ToSharedRef()
		];

	CreatePinWidgets();
}

UEdGraph* SDefault_GraphNodeK2Composite::GetInnerGraph() const
{
	UK2Node_Composite* CompositeNode = CastChecked<UK2Node_Composite>(GraphNode);
	return CompositeNode->BoundGraph;
}

TSharedPtr<SToolTip> SDefault_GraphNodeK2Composite::GetComplexTooltip()
{
	if (UEdGraph* BoundGraph = GetInnerGraph())
	{
		struct LocalUtils
		{
			static bool IsInteractive()
			{
				const FModifierKeysState ModifierKeys = FSlateApplication::Get().GetModifierKeys();
				return (ModifierKeys.IsAltDown() && ModifierKeys.IsControlDown());
			}
		};

		TSharedPtr<SToolTip> FinalToolTip = NULL;
		TSharedPtr<SVerticalBox> Container = NULL;
		SAssignNew(FinalToolTip, SToolTip)
			.IsInteractive_Static(&LocalUtils::IsInteractive)
			[
				SAssignNew(Container, SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
				.Text(this, &SDefault_GraphNodeK2Composite::GetTooltipTextForNode)
				.Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
				.WrapTextAt(160.0f)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					// Create preview for the tooltip, make sure to disable state overlays to prevent
					// PIE and read-only borders obscuring the graph
					SNew(SGraphPreviewer, BoundGraph)
					.CornerOverlayText(this, &SDefault_GraphNodeK2Composite::GetPreviewCornerText)
					.ShowGraphStateOverlay(false)
				]
			];

		// Check to see whether this node has a documentation excerpt. If it does, create a doc box for the tooltip
		TSharedRef<IDocumentationPage> DocPage = IDocumentation::Get()->
			GetPage(GraphNode->GetDocumentationLink(), NULL);
		if (DocPage->HasExcerpt(GraphNode->GetDocumentationExcerptName()))
		{
			Container->AddSlot()
			         .AutoHeight()
			         .Padding(FMargin(0.0f, 5.0f))
			[
				IDocumentation::Get()->CreateToolTip(FText::FromString("Documentation"), NULL,
				                                     GraphNode->GetDocumentationLink(),
				                                     GraphNode->GetDocumentationExcerptName())
			];
		}

		return FinalToolTip;
	}
	else
	{
		return SNew(SToolTip)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
					.Text(NSLOCTEXT("CompositeNode", "CompositeNodeInvalidGraphMessage", "ERROR: Invalid Graph"))
					.Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
					.WrapTextAt(160.0f)
			]
		];
	}
}

const FSlateBrush* SDefault_GraphNodeK2Composite::GetShadowBrush(bool bSelected) const
{
	if (UpdateState(bSelected))
	{
		auto NodeType = GetNodeType();
		const auto& State = UNodeRestyleSettings::Get()->CollapsedNode.GetTypeData(NodeType).GetState(CachedState);

		if (Body.IsValid())
		{
			FName Id = FNodeRestyleStyles::CollapsedNode_Body(NodeType, CachedState); 
			Body->SetImage(FAppStyle::Get().GetBrush(Id));
		}
		if (InlineEditableText.IsValid())
		{
			InlineEditableText->SetColorAndOpacity(State.Title.MainText.Get());
		}
		if (TitleExtraText.IsValid() && TitleExtraText->ExtraTextBlock.IsValid())
		{
			TitleExtraText->ExtraTextBlock->SetColorAndOpacity(State.Title.ExtraText.Get());
		}
	}
	return CachedNoDrawBrush;
}

FText SDefault_GraphNodeK2Composite::GetPreviewCornerText() const
{
	UEdGraph* BoundGraph = GetInnerGraph();
	return FText::FromString(BoundGraph->GetName());
}

FText SDefault_GraphNodeK2Composite::GetTooltipTextForNode() const
{
	return GraphNode->GetTooltipText();
}

TSharedRef<SWidget> SDefault_GraphNodeK2Composite::CreateNodeBody()
{
	if (GraphNode && GraphNode->Pins.Num() > 0)
	{
		const auto& CollapsedNode = UNodeRestyleSettings::Get()->CollapsedNode;
		float ContentSpacing = UDefaultThemeSettings::Get()->GetSpacing(CollapsedNode.ContentSpacing);
		// Create the input and output pin areas if there are pins
		return SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("NoBorder"))
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(0)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Left)
			  .FillWidth(1.0f)
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
	else
	{
		// Create a spacer so the node has some body to it
		return SNew(SSpacer)
			.Size(FVector2D(100.f, 50.f));
	}
}
