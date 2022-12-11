// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "KismetNodes/SGraphNodeK2Composite.h"
#include "Default/Nodes/Kismet/SDefault_GraphNodeK2Composite.h"

class UEdGraph;
class SDefault_PoseWatchOverlay;

class SDefault_GraphNodeStateMachineInstance : public SDefault_GraphNodeK2Composite
{
public: 

	void Construct(const FArguments& InArgs, class UAnimGraphNode_StateMachineBase* InNode);

protected:
	// SGraphNodeK2Composite interface
	virtual UEdGraph* GetInnerGraph() const override;
	virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2D& WidgetSize) const override;
	// End of SGraphNodeK2Composite interface

private:
	TSharedPtr<SDefault_PoseWatchOverlay> PoseWatchWidget;
};
