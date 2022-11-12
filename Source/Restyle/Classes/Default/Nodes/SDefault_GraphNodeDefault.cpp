// Alexander (AgitoReiKen) Moskalenko (C) 2022


#include "SDefault_GraphNodeDefault.h"
#include "SGraphPanel.h"

#include "Themes/Default/NodeRestyleDefault.h"


void SDefault_GraphNodeDefault::Construct(const FArguments& InArgs)
{
	this->GraphNode = InArgs._GraphNodeObj;

	this->SetCursor(EMouseCursor::CardinalCross);

	this->UpdateGraphNode();
} 

bool SDefault_GraphNodeDefault::IsNodeSelected() const
{
	TSharedPtr<SGraphPanel> OwnerPanel = OwnerGraphPanelPtr.Pin();
	if (!OwnerPanel.IsValid() || !GraphNode)
	{
		return false;
	}

	return OwnerPanel->SelectionManager.IsNodeSelected(GraphNode);
}
 
