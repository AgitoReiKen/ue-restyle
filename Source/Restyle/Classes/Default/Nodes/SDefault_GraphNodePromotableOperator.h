// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once 

#include "SGraphNodePromotableOperator.h"
#include "SDefault_GraphNodeK2Sequence.h"

class SDefault_GraphNodePromotableOperator : public SDefault_GraphNodeK2Sequence
{
public:

	SLATE_BEGIN_ARGS(SDefault_GraphNodePromotableOperator) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UK2Node_PromotableOperator* InNode);

	// SGraphNode interface
	virtual void CreatePinWidgets() override;
	// End of SGraphNode interface

protected:

	void LoadCachedIcons();

	const FSlateBrush* CachedOuterIcon;
	const FSlateBrush* CachedInnerIcon;
};