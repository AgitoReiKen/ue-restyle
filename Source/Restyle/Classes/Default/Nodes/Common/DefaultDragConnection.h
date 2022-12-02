// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Input/DragAndDrop.h"
#include "Input/Reply.h"
#include "Widgets/SWidget.h"
#include "SGraphPin.h"
#include "GraphEditorDragDropAction.h"

class SGraphPanel;
class UEdGraph;

class FDefaultDragConnection : public FGraphEditorDragDropAction
{
public:
	DRAG_DROP_OPERATOR_TYPE(FDragConnection, FGraphEditorDragDropAction)

		typedef TArray<FGraphPinHandle> FDraggedPinTable;
	static TSharedRef<FDefaultDragConnection> New(const TSharedRef<SGraphPanel>& InGraphPanel, const FDraggedPinTable& InStartingPins);

	// FDragDropOperation interface
	virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;
	// End of FDragDropOperation interface

	// FGraphEditorDragDropAction interface
	virtual void HoverTargetChanged() override;
	virtual FReply DroppedOnPin(FVector2D ScreenPosition, FVector2D GraphPosition) override;
	virtual FReply DroppedOnNode(FVector2D ScreenPosition, FVector2D GraphPosition) override;
	virtual FReply DroppedOnPanel(const TSharedRef< SWidget >& Panel, FVector2D ScreenPosition, FVector2D GraphPosition, UEdGraph& Graph) override;
	virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;
	// End of FGraphEditorDragDropAction interface

	/*
	 *	Function to check validity of graph pins in the StartPins list. This check helps to prevent processing graph pins which are outdated.
	 */
	virtual void ValidateGraphPinList(TArray<UEdGraphPin*>& OutValidPins);

protected:
	typedef FGraphEditorDragDropAction Super;

	// Constructor: Make sure to call Construct() after factorying one of these
	FDefaultDragConnection(const TSharedRef<SGraphPanel>& GraphPanel, const FDraggedPinTable& DraggedPins);

protected:
	TSharedPtr<SGraphPanel> GraphPanel;
	FDraggedPinTable DraggingPins;

	/** Offset information for the decorator widget */
	FVector2D DecoratorAdjust;
};
