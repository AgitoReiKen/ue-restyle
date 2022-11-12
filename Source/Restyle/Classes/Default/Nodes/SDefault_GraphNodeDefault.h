// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SGraphNode.h"

class SDefault_GraphNodeDefault : public SGraphNode
{
public:

	SLATE_BEGIN_ARGS(SDefault_GraphNodeDefault)
		: _GraphNodeObj(static_cast<UEdGraphNode*>(NULL))
	{}

	SLATE_ARGUMENT(UEdGraphNode*, GraphNodeObj)
		SLATE_END_ARGS()

	bool IsNodeSelected() const;
	void Construct(const FArguments& InArgs);
	 
};
