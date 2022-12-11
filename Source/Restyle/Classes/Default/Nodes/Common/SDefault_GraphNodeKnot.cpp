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
#include "SDefault_CommentBubble.h"

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
		.Style(FAppStyle::Get(), "Graph.Node.NodeTitleInlineEditableText")
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
			.Image(FAppStyle::GetBrush("WhiteBrush"))
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
	return /*bSelected ? FAppStyle::GetBrush(TEXT("Graph.Node.ShadowSelected")) : */FAppStyle::GetNoBrush();
}

TSharedPtr<SGraphPin> SDefault_GraphNodeKnot::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SNew(SGraphPinKnot, Pin);
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
