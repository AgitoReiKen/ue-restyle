// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#include "CoreMinimal.h"
#include "SDefault_GraphNodeK2Default.h"

class SDefault_GraphNodeCreateWidget : public SDefault_GraphNodeK2Default
{
protected:
	virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;
};
 