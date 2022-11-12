// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "DefaultGraphPanelNodeFactory.h"
#include "SCommentBubble.h"
#include "SGraphNode.h" 
#include "Editor/BlueprintGraph/Public/BlueprintGraphDefinitions.h"
#include "SGraphPin.h"
#include "K2Node.h"
#include "K2Node_Event.h"
#include "K2Node_AddPinInterface.h"
#include "K2Node_CallMaterialParameterCollectionFunction.h"
#include "K2Node_Composite.h"
#include "K2Node_Copy.h"
#include "K2Node_CreateDelegate.h"
#include "K2Node_FormatText.h"
#include "K2Node_Knot.h"
#include "K2Node_MakeStruct.h"
#include "K2Node_SpawnActor.h"
#include "K2Node_SpawnActorFromClass.h"
#include "K2Node_Switch.h"
#include "K2Node_Timeline.h"  
#include "KismetPins/SGraphPinNum.h" 
#include "K2Node_PromotableOperator.h"
#include "MaterialNodes/SGraphNodeMaterialBase.h"
#include "Themes/Default/NodeRestyleDefault.h"
#include "KismetNodes/SGraphNodeK2Var.h"
#include "KismetNodes/SGraphNodeK2Composite.h" 

#include "MaterialGraph/MaterialGraphNode_Comment.h"

#include "Nodes/SDefault_GraphNodeK2Event.h"
#include "Nodes/SDefault_GraphNodeK2Default.h"
#include "Nodes/SDefault_GraphNodeK2Sequence.h"
#include "Nodes/SDefault_GraphNodePromotableOperator.h"
#include "Nodes/SDefault_GraphNodeK2Var.h"
#include "Nodes/SDefault_GraphNodeK2Composite.h"
#include "Nodes/SDefault_GraphNodeKnot.h"
#include "Nodes/SDefault_GraphNodeK2Timeline.h"
#include "Nodes/SDefault_GraphNodeSpawnActor.h"
#include "Nodes/SDefault_GraphNodeSpawnActorFromClass.h"
#include "Nodes/SDefault_GraphNodeFormatText.h"
#include "Nodes/SDefault_GraphNodeK2CreateDelegate.h"
#include "Nodes/SDefault_GraphNodeSwitchStatement.h"
#include "Nodes/SDefault_GraphNodeMakeStruct.h"
#include "Nodes/SDefault_GraphNodeComment.h"
#include "Nodes/SDefault_GraphNodeCreateWidget.h"
#include "UMGEditor/Private/Nodes/K2Node_CreateWidget.h"
FDefaultGraphPanelNodeFactory::FDefaultGraphPanelNodeFactory()
{
}

TSharedPtr<SGraphNode> FDefaultGraphPanelNodeFactory::CreateNode(UEdGraphNode* InNode) const
{
	if (!InNode) return nullptr;
	if (UK2Node* K2Node = Cast<UK2Node>(InNode))
	{
		if (UK2Node_CreateWidget* CreateWidgetNode = Cast<UK2Node_CreateWidget>(InNode))
		{
			return SNew(SDefault_GraphNodeCreateWidget, CreateWidgetNode);
		}
		if (UK2Node_Composite* CompositeNode = Cast<UK2Node_Composite>(InNode))
		{
			return SNew(SDefault_GraphNodeK2Composite, CompositeNode);
		}
		if (K2Node->DrawNodeAsVariable())
		{
			return SNew(SDefault_GraphNodeK2Var, K2Node);
		}
		if (UK2Node_Switch* SwitchNode = Cast<UK2Node_Switch>(InNode))
		{
			return SNew(SDefault_GraphNodeSwitchStatement, SwitchNode);
		}
		if (UK2Node_PromotableOperator* PromotableOperator = Cast<UK2Node_PromotableOperator>(InNode))
		{
			return SNew(SDefault_GraphNodePromotableOperator, PromotableOperator);
		}
		if (InNode->GetClass()->ImplementsInterface(UK2Node_AddPinInterface::StaticClass()))
		{
			return SNew(SDefault_GraphNodeK2Sequence, CastChecked<UK2Node>(InNode));
		}
		if (UK2Node_Timeline* TimelineNode = Cast<UK2Node_Timeline>(InNode))
		{
			return SNew(SDefault_GraphNodeK2Timeline, TimelineNode);
		}
		if (UK2Node_SpawnActor* SpawnActorNode = Cast<UK2Node_SpawnActor>(InNode))
		{
			return SNew(SDefault_GraphNodeSpawnActor, SpawnActorNode);
		}
		if (UK2Node_SpawnActorFromClass* SpawnActorNodeFromClass = Cast<UK2Node_SpawnActorFromClass>(InNode))
		{
			return SNew(SDefault_GraphNodeSpawnActorFromClass, SpawnActorNodeFromClass);
		}
		if (UK2Node_CreateDelegate* CreateDelegateNode = Cast<UK2Node_CreateDelegate>(InNode))
		{
			return SNew(SDefault_GraphNodeK2CreateDelegate, CreateDelegateNode);
		}
		if (UK2Node_CallMaterialParameterCollectionFunction* CallFunctionNode = Cast<UK2Node_CallMaterialParameterCollectionFunction>(InNode))
		{
			return nullptr;
			//return SNew(SGraphNodeCallParameterCollectionFunction, CallFunctionNode);
		}
		if (UK2Node_Event* EventNode = Cast<UK2Node_Event>(InNode))
		{
			return SNew(SDefault_GraphNodeK2Event, EventNode);
		}
		if (UK2Node_FormatText* FormatTextNode = Cast<UK2Node_FormatText>(InNode))
		{
			return SNew(SDefault_GraphNodeFormatText, FormatTextNode);
		}
		if (UK2Node_Knot* Knot = Cast<UK2Node_Knot>(InNode))
		{
			return SNew(SDefault_GraphNodeKnot, Knot);
		}
		if (UK2Node_MakeStruct* MakeStruct = Cast<UK2Node_MakeStruct>(InNode))
		{
			return SNew(SDefault_GraphNodeMakeStruct, MakeStruct);
		}
		if (UK2Node_Copy* CopyNode = Cast<UK2Node_Copy>(InNode))
		{
			return nullptr;
			//return SNew(SGraphNodeK2Copy, CopyNode);
		}
		 
		/* Functions, PureFunctions, Macros*/
		return SNew(SDefault_GraphNodeK2Default, K2Node);
	}
	else if (UEdGraphNode_Comment* CommentNode = Cast<UEdGraphNode_Comment>(InNode))
	{
		if (UMaterialGraphNode_Comment* MaterialCommentNode = Cast<UMaterialGraphNode_Comment>(InNode))
		{
			return nullptr;
			//return SNew(SGraphNodeMaterialComment, MaterialCommentNode);
		}
		else
		{
			return SNew(SDefault_GraphNodeComment, CommentNode);
		}
	}
	return nullptr;
}
