// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/Reply.h"
#include "SDefault_AnimationGraphNode.h"

class SVerticalBox;
class UAnimGraphNode_LayeredBoneBlend;

class SDefault_GraphNodeLayeredBoneBlend : public SDefault_AnimationGraphNode
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeLayeredBoneBlend) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UAnimGraphNode_LayeredBoneBlend* InNode);

protected:
	// SGraphNode interface
	virtual void CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox) override;
	virtual FReply OnAddPin() override;
	// End of SGraphNode interface

private:

	// The node that we represent
	UAnimGraphNode_LayeredBoneBlend* Node;

};