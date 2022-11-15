// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h" 
class UDefaultThemeSettings;
class UNodeRestyleSettings;
class FDefaultGraphPanelNodeFactory : public FGraphPanelNodeFactory
{
public:
	explicit FDefaultGraphPanelNodeFactory();
	virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* InNode) const override;
	TSharedPtr<SGraphNode> TryKismet(UEdGraphNode* InNode) const;
	TSharedPtr<SGraphNode> TryAnimation(UEdGraphNode* InNode) const;
	TSharedPtr<SGraphNode> TryMaterial(UEdGraphNode* InNode) const;
	TSharedPtr<SGraphNode> TryOther(UEdGraphNode* InNode) const;

};
