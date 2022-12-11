// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "SDefault_GraphNodeStateMachineInstance.h"

#include "AnimGraphNode_StateMachineBase.h"
#include "AnimationStateMachineGraph.h"
#include "SDefault_AnimationGraphNode.h"

#define LOCTEXT_NAMESPACE "SGraphNodeStateMachineInstance"

/////////////////////////////////////////////////////
// SGraphNodeStateMachineInstance

void SDefault_GraphNodeStateMachineInstance::Construct(const FArguments& InArgs, UAnimGraphNode_StateMachineBase* InNode)
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
}

UEdGraph* SDefault_GraphNodeStateMachineInstance::GetInnerGraph() const
{
	UAnimGraphNode_StateMachineBase* StateMachineInstance = CastChecked<UAnimGraphNode_StateMachineBase>(GraphNode);

	return StateMachineInstance->EditorStateMachineGraph;
}

TArray<FOverlayWidgetInfo> SDefault_GraphNodeStateMachineInstance::GetOverlayWidgets(bool bSelected, const FVector2D& WidgetSize) const
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

#undef LOCTEXT_NAMESPACE