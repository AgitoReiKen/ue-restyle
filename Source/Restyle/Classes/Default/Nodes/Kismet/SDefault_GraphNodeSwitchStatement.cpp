// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeSwitchStatement.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "GraphEditorSettings.h"
#include "SGraphPin.h"
#include "K2Node_Switch.h"
#include "KismetPins/SGraphPinExec.h"
#include "NodeFactory.h"
#include "K2Node_SwitchEnum.h"

#include "ScopedTransaction.h"

#include "Default/Pins/SDefault_Pins.h"

#include "Kismet2/BlueprintEditorUtils.h"

//////////////////////////////////////////////////////////////////////////
// SGraphPinSwitchNodeDefaultCaseExec

class SGraphPinSwitchNodeDefaultCaseExec : public SDefault_GraphPinExec
{
public:
	SLATE_BEGIN_ARGS(SGraphPinSwitchNodeDefaultCaseExec) {}
	SLATE_END_ARGS()

	//	void Construct(const FArguments& InArgs, UEdGraphPin* InPin)
	//{
	//	SDefault_GraphPin::Construct(
	//		SDefault_GraphPin::FArguments().PinLabelStyle(FName("Graph.Node.DefaultPinName")), 
	//		InPin);

	//	CachePinIcons();
	//}
};

//////////////////////////////////////////////////////////////////////////
// SDefault_GraphNodeSwitchStatement

void SDefault_GraphNodeSwitchStatement::Construct(const FArguments& InArgs, UK2Node_Switch* InNode)
{
	SDefault_GraphNodeK2Default::Construct(SDefault_GraphNodeK2Default::FArguments(), InNode);
}

void SDefault_GraphNodeSwitchStatement::CreatePinWidgets()
{
	UK2Node_Switch* SwitchNode = CastChecked<UK2Node_Switch>(GraphNode);
	UEdGraphPin* DefaultPin = SwitchNode->GetDefaultPin();

	// Create Pin widgets for each of the pins, except for the default pin
	for (auto PinIt = GraphNode->Pins.CreateConstIterator(); PinIt; ++PinIt)
	{
		UEdGraphPin* CurrentPin = *PinIt;
		if ((!CurrentPin->bHidden) && (CurrentPin != DefaultPin))
		{
			TSharedPtr<SGraphPin> NewPin = FNodeFactory::CreatePinWidget(CurrentPin);
			check(NewPin.IsValid());

			this->AddPin(NewPin.ToSharedRef());
		}
	}

	// Handle the default pin
	if (DefaultPin != NULL)
	{
		// Create some padding
		RightNodeBox->AddSlot()
			.AutoHeight()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(1.0f)
			[
				SNew(SImage)
				.Image(FAppStyle::GetBrush("Graph.Pin.DefaultPinSeparator"))
			];

		// Create the pin itself
		TSharedPtr<SGraphPin> NewPin = SNew(SDefault_GraphPinExec, DefaultPin);

		this->AddPin(NewPin.ToSharedRef());
	}
}

void SDefault_GraphNodeSwitchStatement::CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox)
{
	TSharedRef<SWidget> AddPinButton = AddPinButtonContent_New(
		NSLOCTEXT("SwitchStatementNode", "SwitchStatementNodeAddPinButton", "Add pin"),
		NSLOCTEXT("SwitchStatementNode", "SwitchStatementNodeAddPinButton_Tooltip", "Add new pin"));

	FMargin AddPinPadding = Settings->GetOutputPinPadding();
	AddPinPadding.Top += 0.0f;

	OutputBox->AddSlot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.Padding(AddPinPadding)
		[
			AddPinButton
		];
}

EVisibility SDefault_GraphNodeSwitchStatement::IsAddPinButtonVisible() const
{
	if (!GraphNode->IsA<UK2Node_SwitchEnum>())
	{
		return SGraphNode::IsAddPinButtonVisible();
	}
	return EVisibility::Collapsed;
}

FReply SDefault_GraphNodeSwitchStatement::OnAddPin()
{
	UK2Node_Switch* SwitchNode = CastChecked<UK2Node_Switch>(GraphNode);

	const FScopedTransaction Transaction(NSLOCTEXT("Kismet", "AddExecutionPin", "Add Execution Pin"));
	SwitchNode->Modify();

	SwitchNode->AddPinToSwitchNode();
	FBlueprintEditorUtils::MarkBlueprintAsModified(SwitchNode->GetBlueprint());

	UpdateGraphNode();
	GraphNode->GetGraph()->NotifyGraphChanged();

	return FReply::Handled();
}
