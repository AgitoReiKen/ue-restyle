// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "DefaultGraphPanelWireFactory.h"

#include "MaterialGraph/MaterialGraph.h"

#include "Wires/DefaultConnectionDrawingPolicy.h"
#include "MaterialGraph/MaterialGraphSchema.h"
#include "Utils/Privates.h"
FConnectionDrawingPolicy* FDefaultGraphPanelWireFactory::CreateConnectionPolicy(const UEdGraphSchema* Schema,
	int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect,
	FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const
{
	FConnectionDrawingPolicy* ConnectionDrawingPolicy = nullptr;
	const auto& VisualPinConnectionFactories = access_private_static::FEdGraphUtilities::VisualPinConnectionFactories();
	for (TSharedPtr<FGraphPanelPinConnectionFactory> FactoryPtr : VisualPinConnectionFactories)
	{
		if (FactoryPtr.IsValid() && FactoryPtr.Get() != this)
		{
			ConnectionDrawingPolicy = FactoryPtr->CreateConnectionPolicy(Schema, InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements, InGraphObj);

			if (ConnectionDrawingPolicy)
			{
				break;
			}
		}
	}

	if (!ConnectionDrawingPolicy)
	{
		ConnectionDrawingPolicy = new FDefaultConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements, InGraphObj);
	}
	return ConnectionDrawingPolicy;
}
