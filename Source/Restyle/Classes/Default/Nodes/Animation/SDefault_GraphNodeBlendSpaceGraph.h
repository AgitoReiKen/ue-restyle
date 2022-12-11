// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Default/Nodes/Kismet/SDefault_GraphNodeK2Composite.h"
#include "SDefault_BlendSpacePreview.h"
class UEdGraph;
class UAnimGraphNode_BlendSpaceGraphBase;

class SDefault_GraphNodeBlendSpaceGraph : public SDefault_GraphNodeK2Composite
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeBlendSpaceGraph) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UAnimGraphNode_BlendSpaceGraphBase* InNode);

protected:
	// SGraphNodeK2Composite interface
	virtual UEdGraph* GetInnerGraph() const override;
	virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2D& WidgetSize) const override;
	virtual TSharedRef<SWidget> CreateNodeBody() override;

	// SGraphNode interface
	TSharedPtr<SToolTip> GetComplexTooltip() override;

private:
	TSharedPtr<SDefault_PoseWatchOverlay> PoseWatchWidget;
};
