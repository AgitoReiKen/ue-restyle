// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SNodePanel.h"
#include "KismetNodes/SGraphNodeK2Default.h"
#include "SDefault_GraphNodeK2Default.h"
class UK2Node_Timeline;

class SDefault_GraphNodeK2Timeline : public SDefault_GraphNodeK2Default
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphNodeK2Timeline) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UK2Node_Timeline* InNode);

	// SNodePanel::SNode interface
	void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;
	// End of SNodePanel::SNode interface
};
