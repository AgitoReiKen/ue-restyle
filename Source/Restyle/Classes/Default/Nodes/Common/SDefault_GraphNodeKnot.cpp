// Alexander (AgitoReiKen) Moskalenko (C) 2022


#include "SDefault_GraphNodeKnot.h"
#include "SCommentBubble.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SSpacer.h"
#include "GraphEditorSettings.h"
#include "SGraphPanel.h"
#include "DragConnection.h"
#include "K2Node_Knot.h"
#include "ScopedTransaction.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Framework/Commands/GenericCommands.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "DefaultDragConnection.h"
#include "Default/Nodes/Common/SDefault_CommentBubble.h"

#include "Default/Pins/SDefault_Pins.h"

#include "Themes/Default/NodeRestyleDefault.h"

namespace SKnotNodeDefinitions
{
	/** Offset from the left edge to display comment toggle button at */
	static const float KnotCenterButtonAdjust = 3.f;

	/** Offset from the left edge to display comment bubbles at */
	static const float KnotCenterBubbleAdjust = 20.f;

	/** Knot node spacer sizes */
	static const FVector2D NodeSpacerSize(42.0f, 24.0f);
}

class FAmbivalentDirectionDragConnection : public FDefaultDragConnection
{
public:
	// FDragDropOperation interface
	virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;
	// End of FDragDropOperation interface

	UEdGraphPin* GetBestPin() const;

	// FDefaultDragConnection interface
	virtual void ValidateGraphPinList(TArray<UEdGraphPin*>& OutValidPins) override;
	// End of FDefaultDragConnection interface


	static TSharedRef<FAmbivalentDirectionDragConnection> New(UEdGraphNode* InKnot, const TSharedRef<SGraphPanel>& InGraphPanel, const FDraggedPinTable& InStartingPins)
	{
		TSharedRef<FAmbivalentDirectionDragConnection> Operation = MakeShareable(new FAmbivalentDirectionDragConnection(InKnot, InGraphPanel, InStartingPins));
		Operation->Construct();

		return Operation;
	}

protected:
	FAmbivalentDirectionDragConnection(UEdGraphNode* InKnot, const TSharedRef<SGraphPanel>& InGraphPanel, const FDraggedPinTable& InStartingPins)
		: FDefaultDragConnection(InGraphPanel, InStartingPins)
		, KnotPtr(InKnot)
		, StartScreenPos(FVector2D::ZeroVector)
		, MostRecentScreenPos(FVector2D::ZeroVector)
		, bLatchedStartScreenPos(false)
	{
	}

protected:
	TWeakObjectPtr<UEdGraphNode> KnotPtr;

	FVector2D StartScreenPos;
	FVector2D MostRecentScreenPos;
	bool bLatchedStartScreenPos;
};

UEdGraphPin* FAmbivalentDirectionDragConnection::GetBestPin() const
{
	if (bLatchedStartScreenPos)
	{
		int32 InputPinIndex = -1;
		int32 OutputPinIndex = -1;

		if (KnotPtr.Get() && KnotPtr->ShouldDrawNodeAsControlPointOnly(InputPinIndex, OutputPinIndex))
		{
			const bool bIsRight = MostRecentScreenPos.X >= StartScreenPos.X;
			return bIsRight ? KnotPtr->GetPinAt(OutputPinIndex) : KnotPtr->GetPinAt(InputPinIndex);
		}
	}

	return nullptr;
}

void FAmbivalentDirectionDragConnection::OnDragged(const class FDragDropEvent& DragDropEvent)
{
	if (bLatchedStartScreenPos)
	{
		const FVector2D LastScreenPos = MostRecentScreenPos;
		MostRecentScreenPos = DragDropEvent.GetScreenSpacePosition();

		// Switch directions on the preview connector as we cross from left to right of the starting drag point (or vis versa)
		const bool bWasRight = LastScreenPos.X >= StartScreenPos.X;
		const bool bIsRight = MostRecentScreenPos.X >= StartScreenPos.X;

		if (bWasRight ^ bIsRight)
		{
			GraphPanel->OnStopMakingConnection(/*bForceStop=*/ true);
			GraphPanel->OnBeginMakingConnection(GetBestPin());
		}
	}
	else
	{
		StartScreenPos = DragDropEvent.GetScreenSpacePosition();
		MostRecentScreenPos = StartScreenPos;
		bLatchedStartScreenPos = true;
	}

	FDefaultDragConnection::OnDragged(DragDropEvent);
}

void FAmbivalentDirectionDragConnection::ValidateGraphPinList(TArray<UEdGraphPin*>& OutValidPins)
{
	OutValidPins.Empty(DraggingPins.Num());

	if (KnotPtr.Get() != nullptr)
	{
		bool bUseOutput = true;

		// Pick output or input based on if the drag op is currently to the left or to the right of the starting drag point
		if (bLatchedStartScreenPos)
		{
			bUseOutput = (StartScreenPos.X < MostRecentScreenPos.X);
		}

		if (UEdGraphPin* TargetPinObj = GetHoveredPin())
		{
			// Dragging to another pin, pick the opposite direction as a source to maximize connection chances
			if (TargetPinObj->Direction == EGPD_Input)
			{
				bUseOutput = true;
			}
			else
			{
				bUseOutput = false;
			}
		}

		int32 InputPinIndex = -1;
		int32 OutputPinIndex = -1;

		if (KnotPtr->ShouldDrawNodeAsControlPointOnly(InputPinIndex, OutputPinIndex))
		{
			// Switch the effective valid pin so it makes sense for the current drag context
			if (bUseOutput)
			{
				OutValidPins.Add(KnotPtr->GetPinAt(OutputPinIndex));
			}
			else
			{
				OutValidPins.Add(KnotPtr->GetPinAt(InputPinIndex));
			}
		}
	}
	else
	{
		// Fall back to the default behavior
		FDefaultDragConnection::ValidateGraphPinList(OutValidPins);
	}
}

/////////////////////////////////////////////////////
// SDefault_GraphPinKnot

class SDefault_GraphPinKnot : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinKnot) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, UEdGraphPin* InPin);

	// SWidget interface
	virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
	// End of SWidget interface

protected:
	// Begin SGraphPin interface
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
	virtual TSharedRef<FDragDropOperation> SpawnPinDragEvent(const TSharedRef<SGraphPanel>& InGraphPanel, const TArray< TSharedRef<SGraphPin> >& InStartingPins) override;
	virtual FReply OnPinMouseDown(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent) override;
	virtual FSlateColor GetPinColor() const override;
	// End SGraphPin interface
};

void SDefault_GraphPinKnot::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	SGraphPin::Construct(SGraphPin::FArguments().SideToSideMargin(0.0f), InPin);
}

void SDefault_GraphPinKnot::OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	TSharedPtr<FDragDropOperation> Operation = DragDropEvent.GetOperation();
	if (Operation.IsValid() && Operation->IsOfType<FDefaultDragConnection>())
	{
		TSharedPtr<FDefaultDragConnection> DragConnectionOp = StaticCastSharedPtr<FDefaultDragConnection>(Operation);

		TArray<UEdGraphPin*> ValidPins;
		DragConnectionOp->ValidateGraphPinList(/*out*/ ValidPins);

		if (ValidPins.Num() > 0)
		{
			UEdGraphPin* PinToHoverOver = nullptr;
			UEdGraphNode* Knot = GraphPinObj->GetOwningNode();
			int32 InputPinIndex = -1;
			int32 OutputPinIndex = -1;

			if (Knot != nullptr && Knot->ShouldDrawNodeAsControlPointOnly(InputPinIndex, OutputPinIndex))
			{
				// Dragging to another pin, pick the opposite direction as a source to maximize connection chances
				PinToHoverOver = (ValidPins[0]->Direction == EGPD_Input) ? Knot->GetPinAt(OutputPinIndex) : Knot->GetPinAt(InputPinIndex);
				check(PinToHoverOver);
			}

			if (PinToHoverOver != nullptr)
			{
				DragConnectionOp->SetHoveredPin(PinToHoverOver);

				// Pins treat being dragged over the same as being hovered outside of drag and drop if they know how to respond to the drag action.
				SBorder::OnMouseEnter(MyGeometry, DragDropEvent);

				return;
			}
		}
	}

	SGraphPin::OnDragEnter(MyGeometry, DragDropEvent);
}

FSlateColor SDefault_GraphPinKnot::GetPinColor() const
{
	// Make ourselves transparent if we're the input, since we are underneath the output pin and would double-blend looking ugly
	return (GetPinObj()->Direction == EEdGraphPinDirection::EGPD_Input) ? FLinearColor::Transparent : SGraphPin::GetPinColor();
}

TSharedRef<SWidget>	SDefault_GraphPinKnot::GetDefaultValueWidget()
{
	return SNullWidget::NullWidget;
}

TSharedRef<FDragDropOperation> SDefault_GraphPinKnot::SpawnPinDragEvent(const TSharedRef<SGraphPanel>& InGraphPanel, const TArray< TSharedRef<SGraphPin> >& InStartingPins)
{
	FAmbivalentDirectionDragConnection::FDraggedPinTable PinHandles;
	PinHandles.Reserve(InStartingPins.Num());
	// since the graph can be refreshed and pins can be reconstructed/replaced 
	// behind the scenes, the DragDropOperation holds onto FGraphPinHandles 
	// instead of direct widgets/graph-pins
	for (const TSharedRef<SGraphPin>& PinWidget : InStartingPins)
	{
		PinHandles.Add(PinWidget->GetPinObj());
	}

	TSharedRef<FAmbivalentDirectionDragConnection> Operation = FAmbivalentDirectionDragConnection::New(GetPinObj()->GetOwningNode(), InGraphPanel, PinHandles);
	return Operation;
}

FReply SDefault_GraphPinKnot::OnPinMouseDown(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if (!GraphPinObj->bNotConnectable && IsEditingEnabled())
		{
			if (MouseEvent.IsAltDown())
			{
				// Normally break connections, but overloaded here to delete the node entirely
				const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());

				UEdGraphNode* NodeToDelete = GetPinObj()->GetOwningNode();
				if (NodeToDelete != nullptr)
				{
					UEdGraph* Graph = NodeToDelete->GetGraph();
					if (Graph != nullptr)
					{
						const UEdGraphSchema* Schema = Graph->GetSchema();
						if (Schema != nullptr && Schema->SafeDeleteNodeFromGraph(Graph, NodeToDelete))
						{
							return FReply::Handled();
						}
					}
				}

				return FReply::Unhandled();
			}
			else if (MouseEvent.IsControlDown())
			{
				// Normally moves the connections from one pin to another, but moves the node instead since it's really representing a set of connections
				// Returning unhandled will cause the node behind us to catch it and move us
				return FReply::Unhandled();
			}
		}
	}

	return SGraphPin::OnPinMouseDown(SenderGeometry, MouseEvent);
}
//////////////////////////////////////////////////////////////////////////
// SDefault_GraphNodeKnot

void SDefault_GraphNodeKnot::Construct(const FArguments& InArgs, UEdGraphNode* InKnot)
{
	int32 InputPinIndex = -1;
	int32 OutputPinIndex = -1;
	verify(InKnot->ShouldDrawNodeAsControlPointOnly(InputPinIndex, OutputPinIndex) == true &&
		InputPinIndex >= 0 && OutputPinIndex >= 0);
	SDefault_GraphNodeDefault::Construct(SDefault_GraphNodeDefault::FArguments().GraphNodeObj(InKnot));
}


void SDefault_GraphNodeKnot::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	//@TODO: Keyboard focus on edit doesn't work unless the node is visible, but the text is just the comment and it's already shown in a bubble, so Transparent black it is...
	InlineEditableText = SNew(SInlineEditableTextBlock)
		.ColorAndOpacity(FLinearColor::Transparent)
		.Style(FEditorStyle::Get(), "Graph.Node.NodeTitleInlineEditableText")
		.Text(this, &SDefault_GraphNodeKnot::GetEditableNodeTitleAsText)
		.OnVerifyTextChanged(this, &SDefault_GraphNodeKnot::OnVerifyNameTextChanged)
		.OnTextCommitted(this, &SDefault_GraphNodeKnot::OnNameTextCommited)
		.IsReadOnly(this, &SDefault_GraphNodeKnot::IsNameReadOnly)
		.IsSelected(this, &SDefault_GraphNodeKnot::IsSelectedExclusively);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	const auto& Reroute = UNodeRestyleSettings::Get()->OtherNodes.Reroute;

	this->GetOrAddSlot(ENodeZone::Center)
	    .HAlign(HAlign_Center)
	    .VAlign(VAlign_Center)
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			//// Grab handle to be able to move the node
			SNew( SImage)
			.Image(FAppStyle::Get().GetBrush("WhiteBrush"))
			.ColorAndOpacity(Reroute.BodyColor.Get())
			.DesiredSizeOverride(Reroute.BodySize)
			.Visibility(this, &SDefault_GraphNodeKnot::GetDragVisibility)
			.Cursor(EMouseCursor::CardinalCross)
			/*SNew(SSpacer)
			.Size(SKnotNodeDefinitions::NodeSpacerSize)
			.Visibility(EVisibility::Visible)
			.Cursor(EMouseCursor::CardinalCross)*/

		]

		+ SOverlay::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			  .VAlign(VAlign_Top)
			  .HAlign(HAlign_Center)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					[
						// LEFT
						SAssignNew(LeftNodeBox, SVerticalBox)
					]
					+ SOverlay::Slot()
					[
						// RIGHT
						SAssignNew(RightNodeBox, SVerticalBox)
					]
				]

			]
		]
	];

	SAssignNew(CommentBubble, SDefault_CommentBubble)
		.GraphNode(GraphNode)
		.Text(this, &SGraphNode::GetNodeComment)
		.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
		.EnableTitleBarBubble(true)
		.EnableBubbleCtrls(true)
		.AllowPinning(true)
		.GraphLOD(this, &SGraphNode::GetCurrentLOD)
		.IsGraphNodeHovered(this, &SGraphNode::IsHovered)
		.OnToggled(this, &SGraphNode::OnCommentBubbleToggled);

	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(this, &SDefault_GraphNodeKnot::GetCommentOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)
		[
			CommentBubble.ToSharedRef()
		];
	CreatePinWidgets();
}

const FSlateBrush* SDefault_GraphNodeKnot::GetShadowBrush(bool bSelected) const
{
	bCachedSelected = bSelected;
	return /*bSelected ? FEditorStyle::GetBrush(TEXT("Graph.Node.ShadowSelected")) : */FEditorStyle::GetNoBrush();
}

TSharedPtr<SGraphPin> SDefault_GraphNodeKnot::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SNew(SDefault_GraphPinKnot, Pin);
}

void SDefault_GraphNodeKnot::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));

	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	PinToAdd->SetShowLabel(false);

	if (PinToAdd->GetDirection() == EEdGraphPinDirection::EGPD_Input)
	{
		LeftNodeBox->AddSlot()
		           .AutoHeight()
		           .HAlign(HAlign_Left)
		           .VAlign(VAlign_Center)
			//.Padding(10, 4)
			[
				PinToAdd
			];
		InputPins.Add(PinToAdd);
	}
	else
	{
		RightNodeBox->AddSlot()
		            .AutoHeight()
		            .HAlign(HAlign_Right)
		            .VAlign(VAlign_Center)
			//.Padding(10, 4)
			[
				PinToAdd
			];
		OutputPins.Add(PinToAdd);
	}
}

EVisibility SDefault_GraphNodeKnot::GetDragVisibility() const
{
	return IsHovered() || bCachedSelected? EVisibility::Visible : EVisibility::Hidden;
}

FVector2D SDefault_GraphNodeKnot::GetCommentOffset() const
{
	const bool bBubbleVisible = GraphNode->bCommentBubbleVisible || bAlwaysShowCommentBubble;
	const float ZoomAmount = GraphNode->bCommentBubblePinned && OwnerGraphPanelPtr.IsValid()
		                         ? OwnerGraphPanelPtr.Pin()->GetZoomAmount()
		                         : 1.f;
	const float NodeWidthOffset = bBubbleVisible
		                              ? SKnotNodeDefinitions::KnotCenterBubbleAdjust * ZoomAmount
		                              : SKnotNodeDefinitions::KnotCenterButtonAdjust * ZoomAmount;

	return FVector2D(NodeWidthOffset - CommentBubble->GetArrowCenterOffset(), -CommentBubble->GetDesiredSize().Y);
}

void SDefault_GraphNodeKnot::OnCommentBubbleToggled(bool bInCommentBubbleVisible)
{
	SGraphNode::OnCommentBubbleToggled(bInCommentBubbleVisible);
	bAlwaysShowCommentBubble = bInCommentBubbleVisible;
}

void SDefault_GraphNodeKnot::OnCommentTextCommitted(const FText& NewComment, ETextCommit::Type CommitInfo)
{
	SGraphNode::OnCommentTextCommitted(NewComment, CommitInfo);
	if (!bAlwaysShowCommentBubble && !CommentBubble->TextBlockHasKeyboardFocus() && !CommentBubble->IsHovered())
	{
		// Hide the comment bubble if visibility hasn't changed
		CommentBubble->SetCommentBubbleVisibility(/*bVisible =*/false);
	}
}
