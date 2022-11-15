// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "DefaultGraphPanelWireFactory.h"

#include "MaterialGraph/MaterialGraph.h"

#include "Wires/DefaultConnectionDrawingPolicy.h"
#include "MaterialGraph/MaterialGraphSchema.h"
FConnectionDrawingPolicy* FDefaultGraphPanelWireFactory::CreateConnectionPolicy(const UEdGraphSchema* Schema,
	int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect,
	FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const
{
	if (Schema->IsA(UEdGraphSchema_K2::StaticClass()) || Schema->IsA(UMaterialGraphSchema::StaticClass()) || Schema->IsA(UEdGraphSchema::StaticClass()))
		return new FDefaultConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements, InGraphObj);
	return nullptr;
}
