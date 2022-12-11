// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SNodePanel.h"
#include "SDefault_AnimationGraphNode.h"
#include "Animation/BlendSpace.h"
#include "SDefault_BlendSpacePreview.h"
class SVerticalBox;
class UAnimGraphNode_Base;

class SDefault_GraphNodeBlendSpacePlayer : public SDefault_AnimationGraphNode
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeBlendSpacePlayer) {}
	SLATE_END_ARGS()

	// Reverse index of the debug grid widget
	static const int32 DebugGridSlotReverseIndex = 2;

	void Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode);

	// SGraphNode interface
	virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;
	// End of SGraphNode interface

protected:
	// Invalidates the node's label if we are syncing based on graph context
	void UpdateGraphSyncLabel();

	// Cached name to display when sync groups are dynamic
	FName CachedSyncGroupName;
};
