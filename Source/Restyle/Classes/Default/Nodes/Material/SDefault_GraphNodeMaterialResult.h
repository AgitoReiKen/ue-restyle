// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SDefault_GraphNodeMaterialBase.h"

class FGraphNodeMetaData;
class UMaterialGraphNode_Root;

class SDefault_GraphNodeMaterialResult : public SDefault_GraphNodeRestyleBase
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeMaterialResult) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UMaterialGraphNode_Root* InNode);

	// SGraphNode interface
	virtual void CreatePinWidgets() override;
	virtual void PopulateMetaTag(FGraphNodeMetaData* TagMeta) const override;
	// End of SGraphNode interface

	// SNodePanel::SNode interface
	virtual void MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;
	// End of SNodePanel::SNode interface

private:
	UMaterialGraphNode_Root* RootNode;
}; 