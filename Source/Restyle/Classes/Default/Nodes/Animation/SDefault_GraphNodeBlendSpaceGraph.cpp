// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeBlendSpaceGraph.h"
#include "BlendSpaceGraph.h"
#include "AnimGraphNode_BlendSpaceGraphBase.h"
#include "Widgets/SToolTip.h"
#include "PersonaModule.h"
#include "IDocumentationPage.h"
#include "IDocumentation.h"
#include "SDefault_AnimationGraphNode.h"
#include "SLevelOfDetailBranchNode.h"
#include "Widgets/Layout/SSpacer.h"

#define LOCTEXT_NAMESPACE "SDefault_GraphNodeBlendSpaceGraph"

void SDefault_GraphNodeBlendSpaceGraph::Construct(const FArguments& InArgs, UAnimGraphNode_BlendSpaceGraphBase* InNode)
{

	PoseWatchWidget = SNew(SDefault_PoseWatchOverlay, InNode);
	GraphNode = InNode;
	auto Style = UNodeRestyleSettings::Get();
	CachedState = IsInvalid() ? EDTGraphNodeState::Invalid : EDTGraphNodeState::Normal;
	CachedOutlineWidth = UDefaultThemeSettings::GetOutlineWidth(
		Style->CollapsedNode.GetTypeData(GetCollapsedNodeType()).GetState(CachedState).Body.Get().OutlineWidth
	);
	EnabledStateWidgetAdditionalPadding = UDefaultThemeSettings::GetMargin(Style->StateWidget.Padding);
	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
	SDefault_AnimationGraphNode::ReconfigurePinWidgetsForPropertyBindings(
		CastChecked<UAnimGraphNode_Base>(GraphNode), 
		SharedThis(this), 
		[this](UEdGraphPin* InPin) { return FindWidgetForPin(InPin); });
}

UEdGraph* SDefault_GraphNodeBlendSpaceGraph::GetInnerGraph() const
{
	UAnimGraphNode_BlendSpaceGraphBase* BlendSpaceNode = CastChecked<UAnimGraphNode_BlendSpaceGraphBase>(GraphNode);

	return BlendSpaceNode->GetBlendSpaceGraph();
}

TArray<FOverlayWidgetInfo> SDefault_GraphNodeBlendSpaceGraph::GetOverlayWidgets(bool bSelected, const FVector2D& WidgetSize) const
{
	TArray<FOverlayWidgetInfo> Widgets;

	if (UAnimGraphNode_Base* AnimNode = CastChecked<UAnimGraphNode_Base>(GraphNode, ECastCheckedType::NullAllowed))
	{
		if (PoseWatchWidget->IsPoseWatchValid())
		{
			FOverlayWidgetInfo Info;
			Info.OverlayOffset = PoseWatchWidget->GetOverlayOffset();
			Info.Widget = PoseWatchWidget;
			Widgets.Add(Info);
		}
	}

	return Widgets;
}

TSharedPtr<SToolTip> SDefault_GraphNodeBlendSpaceGraph::GetComplexTooltip()
{
	if (UBlendSpaceGraph* BlendSpaceGraph = CastChecked<UBlendSpaceGraph>(GetInnerGraph()))
	{
		struct LocalUtils
		{
			static bool IsInteractive()
			{
				const FModifierKeysState ModifierKeys = FSlateApplication::Get().GetModifierKeys();
				return ( ModifierKeys.IsAltDown() && ModifierKeys.IsControlDown() );
			}
		};

		FPersonaModule& PersonaModule = FModuleManager::LoadModuleChecked<FPersonaModule>("Persona");

		FBlendSpacePreviewArgs Args;
		Args.PreviewBlendSpace = BlendSpaceGraph->BlendSpace;

		TSharedPtr<SToolTip> FinalToolTip = nullptr;
		TSharedPtr<SVerticalBox> Container = nullptr;
		SAssignNew(FinalToolTip, SToolTip)
		.IsInteractive_Static(&LocalUtils::IsInteractive)
		[
			SAssignNew(Container, SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew( STextBlock )
				.Text(this, &SDefault_GraphNodeBlendSpaceGraph::GetTooltipTextForNode)
				.Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
				.WrapTextAt(160.0f)
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBox)
				.WidthOverride(200.0f)
				.HeightOverride(150.0f)
				[
					PersonaModule.CreateBlendSpacePreviewWidget(Args)
				]
			]
		];

		// Check to see whether this node has a documentation excerpt. If it does, create a doc box for the tooltip
		TSharedRef<IDocumentationPage> DocPage = IDocumentation::Get()->GetPage(GraphNode->GetDocumentationLink(), nullptr);
		if(DocPage->HasExcerpt(GraphNode->GetDocumentationExcerptName()))
		{
			Container->AddSlot()
			.AutoHeight()
			.Padding(FMargin( 0.0f, 5.0f ))
			[
				IDocumentation::Get()->CreateToolTip(FText::FromString("Documentation"), nullptr, GraphNode->GetDocumentationLink(), GraphNode->GetDocumentationExcerptName())
			];
		}

		return FinalToolTip;
	}
	else
	{
		return SNew(SToolTip)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew( STextBlock )
					.Text(LOCTEXT("InvalidBlendspaceMessage", "ERROR: Invalid Blendspace"))
					.Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
					.WrapTextAt(160.0f)
				]
			];
	}

}

TSharedRef<SWidget> SDefault_GraphNodeBlendSpaceGraph::CreateNodeBody()
{
	TSharedRef<SWidget> NodeBody = SDefault_GraphNodeK2Composite::CreateNodeBody();
	
	UAnimGraphNode_BlendSpaceGraphBase* BlendSpaceNode = CastChecked<UAnimGraphNode_BlendSpaceGraphBase>(GraphNode);

	auto UseLowDetailNode = [this]()
	{
		return GetCurrentLOD() <= EGraphRenderingLOD::LowDetail;
	};
	
	return SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			NodeBody
		]
	+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.0f, 2.0f, 4.0f, 2.0f)
		[
			SDefault_AnimationGraphNode::CreateNodeFunctionsWidget(BlendSpaceNode, MakeAttributeLambda(UseLowDetailNode))
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SLevelOfDetailBranchNode)
			.UseLowDetailSlot_Lambda(UseLowDetailNode)
			.HighDetail()
			[
				SNew(SDefault_BlendSpacePreview, CastChecked<UAnimGraphNode_Base>(GraphNode))
				.OnGetBlendSpaceSampleName(FOnGetBlendSpaceSampleName::CreateLambda([this, WeakBlendSpaceNode = TWeakObjectPtr<UAnimGraphNode_BlendSpaceGraphBase>(BlendSpaceNode)](int32 InSampleIndex) -> FName
				{
					if(WeakBlendSpaceNode.Get())
					{
						UAnimGraphNode_BlendSpaceGraphBase* BlendSpaceNode = WeakBlendSpaceNode.Get();
						return BlendSpaceNode->GetGraphs()[InSampleIndex]->GetFName();
					}

					return NAME_None;
				}))
			]
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Right)
		.Padding(4.0f, 2.0f, 4.0f, 2.0f)
		[
			SDefault_AnimationGraphNode::CreateNodeTagWidget(BlendSpaceNode, MakeAttributeLambda(UseLowDetailNode))
		];
}

#undef LOCTEXT_NAMESPACE