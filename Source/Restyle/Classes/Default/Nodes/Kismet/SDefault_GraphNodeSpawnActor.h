// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "KismetNodes/SGraphNodeK2Default.h"
#include "SDefault_GraphNodeK2Default.h"

class SDefault_GraphNodeSpawnActor : public SDefault_GraphNodeK2Default
{
public:

	// SGraphNode interface
	virtual void CreatePinWidgets() override;
	// End of SGraphNode interface
};
