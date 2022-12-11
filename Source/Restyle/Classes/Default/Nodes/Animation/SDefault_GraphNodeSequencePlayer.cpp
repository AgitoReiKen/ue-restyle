// Alexander (AgitoReiKen) Moskalenko (C) 2022
 
#include "SDefault_GraphNodeSequencePlayer.h"
#include "Widgets/Input/SSlider.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Kismet2/KismetDebugUtilities.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Animation/AnimNode_SequencePlayer.h"
#include "AnimGraphNode_SequencePlayer.h"
#include "Styling/StyleColors.h"
#include "SLevelOfDetailBranchNode.h"

#include "Themes/Default/DefaultTheme.h"

#include "Widgets/Layout/SSpacer.h"

/////////////////////////////////////////////////////
// SDefault_GraphNodeSequencePlayer

void SDefault_GraphNodeSequencePlayer::Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode)
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

void SDefault_GraphNodeSequencePlayer::GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const
{
}

FText SDefault_GraphNodeSequencePlayer::GetPositionTooltip() const
{
	float Position;
	float Length;
	int32 FrameCount;
	if (GetSequencePositionInfo(/*out*/ Position, /*out*/ Length, /*out*/ FrameCount))
	{
		const int32 Minutes = FMath::TruncToInt(Position / 60.0f);
		const int32 Seconds = FMath::TruncToInt(Position) % 60;
		const int32 Hundredths = FMath::TruncToInt(FMath::Fractional(Position) * 100);

		FString MinuteStr;
		if (Minutes > 0)
		{
			MinuteStr = FString::Printf(TEXT("%dm"), Minutes);
		}

		const FString SecondStr = FString::Printf(TEXT("%02ds"), Seconds);

		const FString HundredthsStr = FString::Printf(TEXT(".%02d"), Hundredths);

		const int32 CurrentFrame = FMath::TruncToInt((Position / Length) * FrameCount);

		const FString FramesStr = FString::Printf(TEXT("Frame %d"), CurrentFrame);

		return FText::FromString(FString::Printf(TEXT("%s (%s%s%s)"), *FramesStr, *MinuteStr, *SecondStr, *HundredthsStr));
	}

	return NSLOCTEXT("SDefault_GraphNodeSequencePlayer", "PositionToolTip_Default", "Position");
}

void SDefault_GraphNodeSequencePlayer::UpdateGraphNode()
{
	SDefault_AnimationGraphNode::UpdateGraphNode();
}

void SDefault_GraphNodeSequencePlayer::CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox)
{
	SDefault_AnimationGraphNode::CreateBelowPinControls(MainBox);

	auto UseLowDetailNode = [this]()
	{
		return GetCurrentLOD() <= EGraphRenderingLOD::LowDetail;
	};
	const FDTAnimationNode& AnimationNode = UNodeRestyleSettings::Get()->OtherNodes.Animation;
	auto& TimelineSlider = AnimationNode.TimelineSlider;
	auto SliderStyleId = FRestyleDefaultThemeStyles::ToStyleId(TimelineSlider.Subject, TimelineSlider.Id);
	auto Padding = UDefaultThemeSettings::GetMargin(AnimationNode.TimelineSliderPadding);
	// Insert above the error reporting bar (but above the tag/functions)
	MainBox->InsertSlot(FMath::Max(0, MainBox->NumSlots() - DebugSliderSlotReverseIndex))
		.AutoHeight()
		.VAlign(VAlign_Fill)
		.Padding(Padding)
		[
			SNew(SLevelOfDetailBranchNode)
			.UseLowDetailSlot_Lambda(UseLowDetailNode)
			.LowDetail()
			[
				SNew(SSpacer)
				.Size(FVector2D(16.0f, 16.f))
			]
			.HighDetail()
			[
				SNew(SSlider)
				.Style(FAppStyle::Get(), SliderStyleId)
				.ToolTipText(this, &SDefault_GraphNodeSequencePlayer::GetPositionTooltip)
				.Visibility(this, &SDefault_GraphNodeSequencePlayer::GetSliderVisibility)
				.Value(this, &SDefault_GraphNodeSequencePlayer::GetSequencePositionRatio)
				.OnValueChanged(this, &SDefault_GraphNodeSequencePlayer::SetSequencePositionRatio)
				.Locked(false)
				.SliderHandleColor(FStyleColors::White)
				.SliderBarColor(FStyleColors::Foreground)
			]
		];
}

FAnimNode_SequencePlayer* SDefault_GraphNodeSequencePlayer::GetSequencePlayer() const
{
	if (UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForNode(GraphNode))
	{
		if (UObject* ActiveObject = Blueprint->GetObjectBeingDebugged())
		{
			if (UAnimGraphNode_SequencePlayer* VisualSequencePlayer = Cast<UAnimGraphNode_SequencePlayer>(GraphNode))
			{
				if (UAnimBlueprintGeneratedClass* Class = Cast<UAnimBlueprintGeneratedClass>((UObject*)ActiveObject->GetClass()))
				{
					return Class->GetPropertyInstance<FAnimNode_SequencePlayer>(ActiveObject, VisualSequencePlayer);
				}
			}
		}
	}
	return NULL;
}

EVisibility SDefault_GraphNodeSequencePlayer::GetSliderVisibility() const
{
	if (UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForNode(GraphNode))
	{
		if (FProperty* Property = FKismetDebugUtilities::FindClassPropertyForNode(Blueprint, GraphNode))
		{
			if (UObject* ActiveObject = Blueprint->GetObjectBeingDebugged())
			{
				return EVisibility::Visible;
			}
		}
	}

	return EVisibility::Collapsed;
}

bool SDefault_GraphNodeSequencePlayer::GetSequencePositionInfo(float& Out_Position, float& Out_Length, int32& Out_FrameCount) const
{
	if (UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForNode(GraphNode))
	{
		if (UObject* ActiveObject = Blueprint->GetObjectBeingDebugged())
		{
			if (UAnimGraphNode_SequencePlayer* VisualSequencePlayer = Cast<UAnimGraphNode_SequencePlayer>(GraphNode))
			{
				if (UAnimBlueprintGeneratedClass* Class = Cast<UAnimBlueprintGeneratedClass>((UObject*)ActiveObject->GetClass()))
				{
					if (int32* NodeIndexPtr = Class->GetAnimBlueprintDebugData().NodePropertyToIndexMap.Find(TWeakObjectPtr<UAnimGraphNode_Base>(Cast<UAnimGraphNode_Base>(GraphNode))))
					{
						int32 AnimNodeIndex = *NodeIndexPtr;
						// reverse node index temporarily because of a bug in NodeGuidToIndexMap
						AnimNodeIndex = Class->GetAnimNodeProperties().Num() - AnimNodeIndex - 1;

						if (FAnimBlueprintDebugData::FSequencePlayerRecord* DebugInfo = Class->GetAnimBlueprintDebugData().SequencePlayerRecordsThisFrame.FindByPredicate([AnimNodeIndex](const FAnimBlueprintDebugData::FSequencePlayerRecord& InRecord) { return InRecord.NodeID == AnimNodeIndex; }))
						{
							Out_Position = DebugInfo->Position;
							Out_Length = DebugInfo->Length;
							Out_FrameCount = DebugInfo->FrameCount;

							return true;
						}
					}
				}
			}
		}
	}

	Out_Position = 0.0f;
	Out_Length = 0.0f;
	Out_FrameCount = 0;
	return false;
}

float SDefault_GraphNodeSequencePlayer::GetSequencePositionRatio() const
{
	float Position;
	float Length;
	int32 FrameCount;
	if (GetSequencePositionInfo(/*out*/ Position, /*out*/ Length, /*out*/ FrameCount))
	{
		return Position / Length;
	}
	return 0.0f;
}

void SDefault_GraphNodeSequencePlayer::SetSequencePositionRatio(float NewRatio)
{
	if (FAnimNode_SequencePlayer* SequencePlayer = GetSequencePlayer())
	{
		UAnimSequenceBase* Sequence = SequencePlayer->GetSequence();
		if (Sequence != NULL)
		{
			const float NewTime = NewRatio * Sequence->GetPlayLength();
			SequencePlayer->SetAccumulatedTime(NewTime);
		}
	}
}

void SDefault_GraphNodeSequencePlayer::UpdateGraphSyncLabel()
{
	if (UAnimGraphNode_SequencePlayer* VisualSequencePlayer = Cast<UAnimGraphNode_SequencePlayer>(GraphNode))
	{
		FName CurrentSyncGroupName = NAME_None;

		if (UAnimBlueprint* AnimBlueprint = Cast<UAnimBlueprint>(FBlueprintEditorUtils::FindBlueprintForNode(GraphNode)))
		{
			if (UAnimBlueprintGeneratedClass* GeneratedClass = AnimBlueprint->GetAnimBlueprintGeneratedClass())
			{
				if (UObject* ActiveObject = AnimBlueprint->GetObjectBeingDebugged())
				{
					if (VisualSequencePlayer->Node.GetGroupMethod() == EAnimSyncMethod::Graph)
					{
						int32 NodeIndex = GeneratedClass->GetNodeIndexFromGuid(VisualSequencePlayer->NodeGuid);
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
			VisualSequencePlayer->OnNodeTitleChangedEvent().Broadcast();
			CachedSyncGroupName = CurrentSyncGroupName;
		}
	}
}