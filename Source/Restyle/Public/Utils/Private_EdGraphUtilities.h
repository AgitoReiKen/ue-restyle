// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once
#include "Restyle/ThirdParty/AccessPrivate/AccessPrivate.h"
#include "EdGraphUtilities.h"
ACCESS_PRIVATE_STATIC_FIELD(FEdGraphUtilities, TArray< TSharedPtr<FGraphPanelNodeFactory> >, VisualNodeFactories);
ACCESS_PRIVATE_STATIC_FIELD(FEdGraphUtilities, TArray< TSharedPtr<FGraphPanelPinFactory> >, VisualPinFactories);
ACCESS_PRIVATE_STATIC_FIELD(FEdGraphUtilities, TArray<TSharedPtr<FGraphPanelPinConnectionFactory>>, VisualPinConnectionFactories);
 