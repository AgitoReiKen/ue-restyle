// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

class FDefaultGraphPanelPinFactory : public FGraphPanelPinFactory
{
public:
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* InPin) const override;

	TSharedPtr<SGraphPin> TryKismet(UEdGraphPin* InPin) const;
	TSharedPtr<SGraphPin> TryMaterial(UEdGraphPin* InPin) const;
	TSharedPtr<SGraphPin> TryAnimation(UEdGraphPin* InPin) const;

}; 