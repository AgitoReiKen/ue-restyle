// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "SDefault_GraphNodeMaterialResult.h"
#include "MaterialGraph/MaterialGraph.h"
#include "MaterialGraph/MaterialGraphNode_Root.h"
#include "MaterialGraph/MaterialGraphSchema.h"
#include "SGraphPanel.h"
#include "TutorialMetaData.h"
#include "Widgets/SToolTip.h"
#include "IDocumentation.h"

/////////////////////////////////////////////////////
// SDefault_GraphNodeMaterialResult

void SDefault_GraphNodeMaterialResult::Construct(const FArguments& InArgs, UMaterialGraphNode_Root* InNode)
{
	GraphNode = RootNode = InNode;

	auto Style = UNodeRestyleSettings::Get();
	CachedState = IsInvalid() ? EDTGraphNodeState::Invalid : EDTGraphNodeState::Normal;
	CachedOutlineWidth = UDefaultThemeSettings::GetOutlineWidth(
		Style->Node.GetTypeData(GetNodeType()).GetState(CachedState).Body.Get().OutlineWidth
	);
	EnabledStateWidgetAdditionalPadding = UDefaultThemeSettings::GetMargin(Style->StateWidget.Padding);
	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}

void SDefault_GraphNodeMaterialResult::CreatePinWidgets()
{
	// Create Pin widgets for each of the pins.
	UMaterialGraphNode_Base* MaterialGraphNode = Cast<UMaterialGraphNode_Base>(GraphNode);
	UMaterialGraph* MaterialGraph = CastChecked<UMaterialGraph>(GraphNode->GetGraph());

	bool bHideNoConnectionPins = false;
	if (OwnerGraphPanelPtr.IsValid())
	{
		bHideNoConnectionPins = OwnerGraphPanelPtr.Pin()->GetPinVisibility() == SGraphEditor::Pin_HideNoConnection;
	}

	for (UEdGraphPin* CurPin : MaterialGraphNode->Pins)
	{
		const bool bPinHasConections = CurPin->LinkedTo.Num() > 0;

		bool bPinDesiresToBeHidden = bHideNoConnectionPins && !bPinHasConections;
		if (CurPin->PinType.PinCategory != UMaterialGraphSchema::PC_Exec)
		{
			if (!MaterialGraph->MaterialInputs[CurPin->SourceIndex].IsVisiblePin(MaterialGraph->Material))
			{
				bPinDesiresToBeHidden = true;
			}
		}

		if (!bPinDesiresToBeHidden)
		{
			TSharedPtr<SGraphPin> NewPin = CreatePinWidget(CurPin);
			check(NewPin.IsValid());

			if (CurPin->PinType.PinCategory != UMaterialGraphSchema::PC_Exec)
			{
				TSharedPtr<SToolTip> ToolTipWidget = IDocumentation::Get()->CreateToolTip(MaterialGraph->MaterialInputs[CurPin->SourceIndex].GetToolTip(), nullptr, FString(TEXT("")), FString(TEXT("")));
				NewPin->SetToolTip(ToolTipWidget.ToSharedRef());
			}

			this->AddPin(NewPin.ToSharedRef());
		}
	}
}

void SDefault_GraphNodeMaterialResult::MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty)
{
	SGraphNode::MoveTo(NewPosition, NodeFilter, bMarkDirty);

	RootNode->Material->EditorX = RootNode->NodePosX;
	RootNode->Material->EditorY = RootNode->NodePosY;
	RootNode->Material->MarkPackageDirty();
	RootNode->Material->MaterialGraph->MaterialDirtyDelegate.ExecuteIfBound();
}


void SDefault_GraphNodeMaterialResult::PopulateMetaTag(FGraphNodeMetaData* TagMeta) const
{
	if ((GraphNode != nullptr) && (RootNode != nullptr))
	{
		UMaterialGraph* OuterGraph = RootNode->GetTypedOuter<UMaterialGraph>();
		if (OuterGraph != nullptr)
		{
			TagMeta->OuterName = OuterGraph->OriginalMaterialFullName;
			// There is only one root node - so we dont need a guid. 
			TagMeta->Tag = FName(*FString::Printf(TEXT("MaterialResNode_%s"), *TagMeta->OuterName));
			TagMeta->GUID.Invalidate();
			TagMeta->FriendlyName = FString::Printf(TEXT("Material Result node in %s"), *TagMeta->OuterName);
		}
	}
}
