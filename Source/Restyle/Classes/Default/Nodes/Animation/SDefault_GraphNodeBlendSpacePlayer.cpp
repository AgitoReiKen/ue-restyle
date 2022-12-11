// Alexander (AgitoReiKen) Moskalenko (C) 2022


#include "SDefault_GraphNodeBlendSpacePlayer.h"
#include "AnimGraphNode_Base.h"
#include "AnimGraphNode_BlendSpacePlayer.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "SLevelOfDetailBranchNode.h"
#include "Widgets/Layout/SSpacer.h" 

#include "Kismet2/KismetDebugUtilities.h"
 
void SDefault_GraphNodeBlendSpacePlayer::Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode)
{

	CachedSyncGroupName = NAME_None;

	SDefault_AnimationGraphNode::Construct(SDefault_AnimationGraphNode::FArguments(), InNode);
 
	RegisterActiveTimer(1.0f / 60.0f, FWidgetActiveTimerDelegate::CreateLambda([this](double InCurrentTime, float InDeltaTime)
		{
			UpdateGraphSyncLabel();
			return EActiveTimerReturnType::Continue;
		}
	));
}

void SDefault_GraphNodeBlendSpacePlayer::CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox)
{
	SDefault_AnimationGraphNode::CreateBelowPinControls(MainBox);

	// Insert above the error reporting bar (but above the tag/functions)
	MainBox->InsertSlot(FMath::Max(0, MainBox->NumSlots() - DebugGridSlotReverseIndex))
		.AutoHeight()
		.VAlign(VAlign_Fill)
		.Padding(0.0f)
		[
			SNew(SLevelOfDetailBranchNode)
			.UseLowDetailSlot(this, &SDefault_GraphNodeBlendSpacePlayer::UseLowDetailNodeTitles)
			.HighDetail()
			[
				SNew(SDefault_BlendSpacePreview, CastChecked<UAnimGraphNode_Base>(GraphNode))
			]
		];
}

void SDefault_GraphNodeBlendSpacePlayer::UpdateGraphSyncLabel()
{
	if (UAnimGraphNode_BlendSpacePlayer* VisualBlendSpacePlayer = Cast<UAnimGraphNode_BlendSpacePlayer>(GraphNode))
	{
		FName CurrentSyncGroupName = NAME_None;

		if (UAnimBlueprint* AnimBlueprint = Cast<UAnimBlueprint>(FBlueprintEditorUtils::FindBlueprintForNode(GraphNode)))
		{
			if (UAnimBlueprintGeneratedClass* GeneratedClass = AnimBlueprint->GetAnimBlueprintGeneratedClass())
			{
				if (UObject* ActiveObject = AnimBlueprint->GetObjectBeingDebugged())
				{
					if (VisualBlendSpacePlayer->Node.GetGroupMethod() == EAnimSyncMethod::Graph)
					{
						int32 NodeIndex = GeneratedClass->GetNodeIndexFromGuid(VisualBlendSpacePlayer->NodeGuid);
						if (NodeIndex != INDEX_NONE)
						{
							if (const FName* SyncGroupNamePtr = GeneratedClass->GetAnimBlueprintDebugData().NodeSyncsThisFrame.Find(NodeIndex))
							{
								CurrentSyncGroupName = *SyncGroupNamePtr;
							}
						}
					}
				}
			}
		}

		if (CachedSyncGroupName != CurrentSyncGroupName)
		{
			// Invalidate the node title so we can dynamically display the sync group gleaned from the graph
			VisualBlendSpacePlayer->OnNodeTitleChangedEvent().Broadcast();
			CachedSyncGroupName = CurrentSyncGroupName;
		}
	}
}
