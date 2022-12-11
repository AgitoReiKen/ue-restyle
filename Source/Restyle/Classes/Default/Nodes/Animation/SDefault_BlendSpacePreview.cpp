// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "SDefault_BlendSpacePreview.h"

#include "SDefault_GraphNodeBlendSpacePlayer.h"
#include "AnimGraphNode_Base.h"
#include "AnimGraphNode_BlendSpacePlayer.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "SLevelOfDetailBranchNode.h"
#include "Widgets/Layout/SSpacer.h" 

#include "Kismet2/KismetDebugUtilities.h"
void SDefault_BlendSpacePreview::Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode)
{
	check(InNode);

	Node = InNode;

	FPersonaModule& PersonaModule = FModuleManager::LoadModuleChecked<FPersonaModule>("Persona");

	FBlendSpacePreviewArgs Args;

	Args.PreviewBlendSpace = MakeAttributeLambda([this]() { return CachedBlendSpace.Get(); });
	Args.PreviewPosition = MakeAttributeLambda([this]() { return CachedPosition; });
	Args.PreviewFilteredPosition = MakeAttributeLambda([this]() { return CachedFilteredPosition; });
	Args.OnGetBlendSpaceSampleName = InArgs._OnGetBlendSpaceSampleName;

	ChildSlot
	[
		SNew(SBox)
		.MinDesiredHeight_Lambda([this]()
			{
				return 100.0f;
			})
		.Visibility(this, &SDefault_BlendSpacePreview::GetBlendSpaceVisibility)
		[
			PersonaModule.CreateBlendSpacePreviewWidget(Args)
		]
	];

	RegisterActiveTimer(1.0f / 60.0f, FWidgetActiveTimerDelegate::CreateLambda([this](double InCurrentTime, float InDeltaTime)
		{
			GetBlendSpaceInfo(CachedBlendSpace, CachedPosition, CachedFilteredPosition);
			return EActiveTimerReturnType::Continue;
		}
	));
}

EVisibility SDefault_BlendSpacePreview::GetBlendSpaceVisibility() const
{
	if (Node.Get() != nullptr)
	{
		if (UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForNode(Node.Get()))
		{
			if (FProperty* Property = FKismetDebugUtilities::FindClassPropertyForNode(Blueprint, Node.Get()))
			{
				if (UObject* ActiveObject = Blueprint->GetObjectBeingDebugged())
				{
					return EVisibility::Visible;
				}
			}
		}
	}

	return EVisibility::Collapsed;
}

bool SDefault_BlendSpacePreview::GetBlendSpaceInfo(TWeakObjectPtr<const UBlendSpace>& OutBlendSpace, FVector& OutPosition, FVector& OutFilteredPosition) const
{
	if (Node.Get() != nullptr)
	{
		if (UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForNode(Node.Get()))
		{
			if (UObject* ActiveObject = Blueprint->GetObjectBeingDebugged())
			{
				if (UAnimBlueprintGeneratedClass* Class = Cast<UAnimBlueprintGeneratedClass>(ActiveObject->GetClass()))
				{
					if (int32* NodeIndexPtr = Class->GetAnimBlueprintDebugData().NodePropertyToIndexMap.Find(Node))
					{
						int32 AnimNodeIndex = *NodeIndexPtr;
						// reverse node index temporarily because of a bug in NodeGuidToIndexMap
						AnimNodeIndex = Class->GetAnimNodeProperties().Num() - AnimNodeIndex - 1;

						if (FAnimBlueprintDebugData::FBlendSpacePlayerRecord* DebugInfo = Class->GetAnimBlueprintDebugData().BlendSpacePlayerRecordsThisFrame.FindByPredicate(
							[AnimNodeIndex](const FAnimBlueprintDebugData::FBlendSpacePlayerRecord& InRecord) { return InRecord.NodeID == AnimNodeIndex; }))
						{
							OutBlendSpace = DebugInfo->BlendSpace.Get();
							OutPosition = DebugInfo->Position;
							OutFilteredPosition = DebugInfo->FilteredPosition;
							return true;
						}
					}
				}
			}
		}
	}

	OutBlendSpace = nullptr;
	OutPosition = FVector::ZeroVector;
	OutFilteredPosition = FVector::ZeroVector;
	return false;
}
