// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "PersonaDelegates.h"
#include "PersonaModule.h"
class UAnimGraphNode_Base;
class SDefault_BlendSpacePreview : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDefault_BlendSpacePreview) {}

	SLATE_ARGUMENT(FOnGetBlendSpaceSampleName, OnGetBlendSpaceSampleName)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode);

protected:
	EVisibility GetBlendSpaceVisibility() const;
	bool GetBlendSpaceInfo(TWeakObjectPtr<const UBlendSpace>& OutBlendSpace, FVector& OutPosition, FVector& OutFilteredPosition) const;

	TWeakObjectPtr<const UAnimGraphNode_Base> Node;
	TWeakObjectPtr<const UBlendSpace> CachedBlendSpace;
	FVector CachedPosition;
	FVector CachedFilteredPosition;
};