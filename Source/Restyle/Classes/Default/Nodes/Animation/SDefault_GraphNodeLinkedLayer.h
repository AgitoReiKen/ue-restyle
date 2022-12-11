// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "SDefault_AnimationGraphNode.h"
#include "UObject/NameTypes.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class UAnimGraphNode_Base;

class SDefault_GraphNodeLinkedLayer : public SDefault_AnimationGraphNode
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeLinkedLayer) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode);

protected:
	void UpdateNodeLabel();

	FName CachedTargetName;
};
