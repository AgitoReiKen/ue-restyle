// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeLayeredBoneBlend.h"
#include "AnimGraphNode_LayeredBoneBlend.h"
#include "GraphEditorSettings.h"

/////////////////////////////////////////////////////
// SDefault_GraphNodeLayeredBoneBlend

void SDefault_GraphNodeLayeredBoneBlend::Construct(const FArguments& InArgs, UAnimGraphNode_LayeredBoneBlend* InNode)
{
	Node = InNode;
	SDefault_AnimationGraphNode::Construct(SDefault_AnimationGraphNode::FArguments(), InNode);
}

void SDefault_GraphNodeLayeredBoneBlend::CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox)
{
	TSharedRef<SWidget> AddPinButton = AddPinButtonContent_New(
		NSLOCTEXT("LayeredBoneBlendNode", "LayeredBoneBlendNodeAddPinButton", "Add pin"),
		NSLOCTEXT("LayeredBoneBlendNode", "LayeredBoneBlendNodeAddPinButton_Tooltip", "Adds a input pose to the node"),
		false);

	FMargin AddPinPadding = Settings->GetInputPinPadding();
	AddPinPadding.Top += 0.0f;

	InputBox->AddSlot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.Padding(AddPinPadding)
		[
			AddPinButton
		];
}

FReply SDefault_GraphNodeLayeredBoneBlend::OnAddPin()
{
	Node->AddPinToBlendByFilter();

	return FReply::Handled();
}
