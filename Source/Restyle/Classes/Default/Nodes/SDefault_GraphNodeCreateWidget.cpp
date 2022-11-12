// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeCreateWidget.h"
#include "UMGEditor/Private/Nodes/K2Node_CreateWidget.h"
#include "Restyle/Classes/Default/Pins/SDefault_Pins.h"
TSharedPtr<SGraphPin> SDefault_GraphNodeCreateWidget::CreatePinWidget(UEdGraphPin* Pin) const
{
	UK2Node_CreateWidget* CreateWidgetNode = CastChecked<UK2Node_CreateWidget>(GraphNode);
	UEdGraphPin* ClassPin = CreateWidgetNode->GetClassPin();
	if ((ClassPin == Pin) && (!ClassPin->bHidden || (ClassPin->LinkedTo.Num() > 0)))
	{
		TSharedPtr<SDefault_GraphPinClass> NewPin = SNew(SDefault_GraphPinClass, ClassPin);
		check(NewPin.IsValid());
		NewPin->SetAllowAbstractClasses(false);
		return NewPin;
	}
	return SDefault_GraphNodeK2Default::CreatePinWidget(Pin);
}
