// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeComment.h"
#include "Widgets/SBoxPanel.h"
#include "Framework/Application/SlateApplication.h"
#include "EdGraphNode_Comment.h"
#include "GraphEditorSettings.h"
#include "SGraphPanel.h"
#include "SDefault_CommentBubble.h"
//#include "TextWrapperHelpers.h"
#include "TutorialMetaData.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "Themes/Default/NodeRestyleDefault.h"
namespace SCommentNodeDefs
{

	/** Size of the hit result border for the window borders */
	/* L, T, R, B */
	static const FSlateRect HitResultBorderSize(10, 10, 10, 10);

	/** Minimum resize width for comment */
	static const float MinWidth = 30.0;

	/** Minimum resize height for comment */
	static const float MinHeight = 30.0;

	/** TitleBarColor = CommentColor * TitleBarColorMultiplier */
	static const float TitleBarColorMultiplier = 0.6f;

	/** Titlebar Offset - taken from the widget borders in UpdateGraphNode */
	static const FSlateRect TitleBarOffset(13, 8, -3, 0);
}


void SDefault_GraphNodeComment::Construct(const FArguments& InArgs, UEdGraphNode_Comment* InNode)
{
	this->GraphNode = InNode;
	this->bIsSelected = false;

	// Set up animation
	{
		ZoomCurve = SpawnAnim.AddCurve(0, 0.1f);
		FadeCurve = SpawnAnim.AddCurve(0.15f, 0.15f);
	}
 
	// Cache these values so they do not force a re-build of the node next tick.
	CachedCommentTitle = GetNodeComment();
	CachedWidth = InNode->NodeWidth;

	this->UpdateGraphNode();

	// Pull out sizes
	UserSize.X = InNode->NodeWidth;
	UserSize.Y = InNode->NodeHeight;

	// Cache desired size so we cull correctly. We can do this as our ComputeDesiredSize ignores the layout scale.
	CacheDesiredSize(1.0f);

	MouseZone = CRWZ_NotInWindow;
	bUserIsDragging = false;
	CachedMouseMoveScreenSpace = FVector2D::ZeroVector;

	const auto& CommentNode = UNodeRestyleSettings::Get()->CommentNode;
	CachedNormalOpacity = CommentNode.NormalOpacity;
	CachedSelectedOpacity = CommentNode.SelectedOpacity;
	bNewResizingMethod = CommentNode.bNewResizingMethod;
}

void SDefault_GraphNodeComment::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SGraphNode::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	const FString CurrentCommentTitle = GetNodeComment();
	if (CurrentCommentTitle != CachedCommentTitle)
	{
		CachedCommentTitle = CurrentCommentTitle;
	}

	const int32 CurrentWidth = static_cast<int32>(UserSize.X);
	if (CurrentWidth != CachedWidth)
	{
		CachedWidth = CurrentWidth;
	}

	UEdGraphNode_Comment* CommentNode = CastChecked<UEdGraphNode_Comment>(GraphNode);
	if (bCachedBubbleVisibility != CommentNode->bCommentBubbleVisible_InDetailsPanel)
	{
		CommentBubble->UpdateBubble_New();
		bCachedBubbleVisibility = CommentNode->bCommentBubbleVisible_InDetailsPanel;
	}

	if (CachedFontSize != CommentNode->GetFontSize())
	{
		UpdateGraphNode();
	}
}

FReply SDefault_GraphNodeComment::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	return FReply::Unhandled();
}

void SDefault_GraphNodeComment::OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{

}

float SDefault_GraphNodeComment::GetWrapAt() const
{
	return (float)(CachedWidth - 32.0f);
}

bool SDefault_GraphNodeComment::IsNameReadOnly() const
{
	return !IsEditable.Get() || SGraphNode::IsNameReadOnly();
}

void SDefault_GraphNodeComment::UpdateGraphNode()
{
	// No pins in a comment box
	InputPins.Empty();
	OutputPins.Empty();

	// Avoid standard box model too
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	// Remember if we should be showing the bubble
	UEdGraphNode_Comment* CommentNode = CastChecked<UEdGraphNode_Comment>(GraphNode);
	bCachedBubbleVisibility = CommentNode->bCommentBubbleVisible_InDetailsPanel;

	// Setup a tag for this node
	FString TagName;

	// We want the name of the blueprint as our name - we can find the node from the GUID
	UObject* Package = GraphNode->GetOutermost();
	UObject* LastOuter = GraphNode->GetOuter();
	while (LastOuter->GetOuter() != Package)
	{
		LastOuter = LastOuter->GetOuter();
	}
	TagName = FString::Printf(TEXT("GraphNode,%s,%s"), *LastOuter->GetFullName(), *GraphNode->NodeGuid.ToString());

	SetupErrorReporting();

	// Setup a meta tag for this node
	FGraphNodeMetaData TagMeta(TEXT("Graphnode"));
	PopulateMetaTag(&TagMeta);

	CachedFontSize = CommentNode->GetFontSize();

	CommentStyle = FAppStyle::Get().GetWidgetStyle<FInlineEditableTextBlockStyle>(FNodeRestyleStyles::CommentNode_Title_Text);
	CommentStyle.EditableTextBoxStyle.TextStyle.Font.Size = CachedFontSize;
	CommentStyle.TextStyle.Font.Size = CachedFontSize;
	ContentScale.Bind(this, &SGraphNode::GetContentScale);

	const auto& Style = UNodeRestyleSettings::Get()->CommentNode;
	FMargin TitlePadding = UDefaultThemeSettings::Get()->GetMargin(Style.TitlePadding);
	GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
			.ColorAndOpacity(FLinearColor::White)
			.BorderBackgroundColor(this, &SDefault_GraphNodeComment::GetCommentBodyColor)
			.Padding(0)
			.AddMetaData<FGraphNodeMetaData>(TagMeta)
			[
				SNew(SVerticalBox)
				.ToolTipText(this, &SGraphNode::GetNodeTooltip)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Top)
				[
					SAssignNew(TitleBar, SBorder)
					.BorderImage(FAppStyle::GetBrush("NoBorder"))
					.BorderBackgroundColor(this, &SDefault_GraphNodeComment::GetCommentTitleBarColor)
					.Padding(TitlePadding)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					[
						SAssignNew(InlineEditableText, SInlineEditableTextBlock)
						.Style(&CommentStyle)
						.Text(this, &SDefault_GraphNodeComment::GetEditableNodeTitleAsText)
						.OnVerifyTextChanged(this, &SDefault_GraphNodeComment::OnVerifyNameTextChanged)
						.OnTextCommitted(this, &SDefault_GraphNodeComment::OnNameTextCommited)
						.IsReadOnly(this, &SDefault_GraphNodeComment::IsNameReadOnly)
						.IsSelected(this, &SDefault_GraphNodeComment::IsSelectedExclusively)
						.WrapTextAt(this, &SDefault_GraphNodeComment::GetWrapAt)
						.MultiLine(true)
						.ModiferKeyForNewLine(EModifierKey::Shift)
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0)
				[
					ErrorReporting->AsWidget()
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					// NODE CONTENT AREA
					SNew(SBorder)
					.BorderImage(FAppStyle::GetBrush("NoBorder"))
				]
			]
		];

	// Create comment bubble
	CommentBubble = SNew(SDefault_CommentBubble)
		.GraphNode(GraphNode)
		.Text(this, &SDefault_GraphNodeComment::GetNodeComment)
		.OnTextCommitted(this, &SDefault_GraphNodeComment::OnNameTextCommited)
		.ColorAndOpacity(this, &SDefault_GraphNodeComment::GetCommentBubbleColor)
		.AllowPinning(true)
		.EnableTitleBarBubble(false)
		.EnableBubbleCtrls(false)
		.GraphLOD(this, &SGraphNode::GetCurrentLOD)
		.InvertLODCulling(true)
		.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)
		[
			CommentBubble.ToSharedRef()
		];
}

FVector2D SDefault_GraphNodeComment::ComputeDesiredSize(float) const
{
	return UserSize;
}

FString SDefault_GraphNodeComment::GetNodeComment() const
{
	const FString Title = GetEditableNodeTitle();;
	return Title;
}

FReply SDefault_GraphNodeComment::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
	// If user double-clicked in the title bar area
	if (FindMouseZone(InMyGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition())) == CRWZ_TitleBar && IsEditable.Get())
	{
		// Request a rename
		RequestRename();

		// Set the keyboard focus
		if (!HasKeyboardFocus())
		{
			FSlateApplication::Get().SetKeyboardFocus(SharedThis(this), EFocusCause::SetDirectly);
		}

		return FReply::Handled();
	}
	else
	{
		// Otherwise let the graph handle it, to allow spline interactions to work when they overlap with a comment node
		return FReply::Unhandled();
	}
}

FReply SDefault_GraphNodeComment::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{

	if ((MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) && bUserIsDragging)
	{
		bUserIsDragging = false;

		// Resize the node
		//UserSize.X = FMath::RoundToFloat(UserSize.X);
		//UserSize.Y = FMath::RoundToFloat(UserSize.Y);

		//GetNodeObj()->ResizeNode(UserSize);

		// End resize transaction
		ResizeTransactionPtr.Reset();

		// Update contained child Nodes
		HandleSelection(bIsSelected, true);

		return FReply::Handled().ReleaseMouseCapture();
	}
	return FReply::Unhandled();
}

int32 SDefault_GraphNodeComment::GetSortDepth() const
{
	UEdGraphNode_Comment* CommentNode = Cast<UEdGraphNode_Comment>(GraphNode);
	return CommentNode ? CommentNode->CommentDepth : -1;
}

void SDefault_GraphNodeComment::HandleSelection(bool bSelected, bool bUpdateNodesUnderComment) const
{
	const FVector2D NodeSize = GetDesiredSize();
	// we only want to do this after the comment has a valid desired size
	if (!NodeSize.IsZero())
	{
		if ((!this->bIsSelected && bSelected) || bUpdateNodesUnderComment)
		{
			SDefault_GraphNodeComment* Comment = const_cast<SDefault_GraphNodeComment*> (this);
			UEdGraphNode_Comment* CommentNode = Cast<UEdGraphNode_Comment>(GraphNode);
			if (CommentNode)
			{
				TSharedPtr<SGraphPanel> Panel = Comment->GetOwnerPanel();
				FChildren* PanelChildren = Panel->GetAllChildren();
				int32 NumChildren = PanelChildren->Num();
				CommentNode->ClearNodesUnderComment();

				for (int32 NodeIndex = 0; NodeIndex < NumChildren; ++NodeIndex)
				{
					const TSharedRef<SGraphNode> SomeNodeWidget = StaticCastSharedRef<SGraphNode>(PanelChildren->GetChildAt(NodeIndex));
					UObject* GraphObject = SomeNodeWidget->GetObjectBeingDisplayed();
					if (GraphObject != CommentNode)
					{
						if (IsNodeUnderComment(CommentNode, SomeNodeWidget))
						{
							CommentNode->AddNodeUnderComment(GraphObject);
						}
					}
				}
			}
		}
		bIsSelected = bSelected;
	}
}

bool SDefault_GraphNodeComment::IsNodeUnderComment(UEdGraphNode_Comment* InCommentNode, const TSharedRef<SGraphNode> InNodeWidget) const
{
	const FVector2D NodePosition = GetPosition();
	const FVector2D NodeSize = GetDesiredSize();
	const FSlateRect CommentRect(NodePosition.X, NodePosition.Y, NodePosition.X + NodeSize.X, NodePosition.Y + NodeSize.Y);

	const FVector2D InNodePosition = InNodeWidget->GetPosition();
	const FVector2D InNodeSize = InNodeWidget->GetDesiredSize();

	const FSlateRect NodeGeometryGraphSpace(InNodePosition.X, InNodePosition.Y, InNodePosition.X + InNodeSize.X, InNodePosition.Y + InNodeSize.Y);
	return FSlateRect::IsRectangleContained(CommentRect, NodeGeometryGraphSpace);
}

const FSlateBrush* SDefault_GraphNodeComment::GetShadowBrush(bool bSelected) const
{
	HandleSelection(bSelected);
	return FAppStyle::GetNoBrush();
}

void SDefault_GraphNodeComment::GetOverlayBrushes(bool bSelected, const FVector2D WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const
{
	const float Fudge = 3.0f;

	HandleSelection(bSelected);

	FOverlayBrushInfo HandleBrush = FAppStyle::GetBrush(TEXT("Graph.Node.Comment.Handle"));

	HandleBrush.OverlayOffset.X = WidgetSize.X - HandleBrush.Brush->ImageSize.X - Fudge;
	HandleBrush.OverlayOffset.Y = WidgetSize.Y - HandleBrush.Brush->ImageSize.Y - Fudge;

	Brushes.Add(HandleBrush);
	return SGraphNode::GetOverlayBrushes(bSelected, WidgetSize, Brushes);
}

void SDefault_GraphNodeComment::MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty)
{
	FVector2D PositionDelta = NewPosition - GetPosition();
	SGraphNode::MoveTo(NewPosition, NodeFilter, bMarkDirty);
	// Don't drag note content if either of the shift keys are down.
	FModifierKeysState KeysState = FSlateApplication::Get().GetModifierKeys();
	if (!KeysState.IsShiftDown())
	{
		UEdGraphNode_Comment* CommentNode = Cast<UEdGraphNode_Comment>(GraphNode);
		if (CommentNode && CommentNode->MoveMode == ECommentBoxMode::GroupMovement)
		{
			// Now update any nodes which are touching the comment but *not* selected
			// Selected nodes will be moved as part of the normal selection code
			TSharedPtr< SGraphPanel > Panel = GetOwnerPanel();

			for (FCommentNodeSet::TConstIterator NodeIt(CommentNode->GetNodesUnderComment()); NodeIt; ++NodeIt)
			{
				if (UEdGraphNode* Node = Cast<UEdGraphNode>(*NodeIt))
				{
					if (!Panel->SelectionManager.IsNodeSelected(Node) && !NodeFilter.Find(Node->DEPRECATED_NodeWidget.Pin()))
					{
						NodeFilter.Add(Node->DEPRECATED_NodeWidget.Pin());
						Node->Modify(bMarkDirty);
						Node->NodePosX += PositionDelta.X;
						Node->NodePosY += PositionDelta.Y;
					}
				}
			}
		}
	}
}

void SDefault_GraphNodeComment::EndUserInteraction() const
{
	// Find any parent comments and their list of child nodes
	const FVector2D NodeSize = GetDesiredSize();
	if (!NodeSize.IsZero())
	{
		const FVector2D NodePosition = GetPosition();
		const FSlateRect CommentRect(NodePosition.X, NodePosition.Y, NodePosition.X + NodeSize.X, NodePosition.Y + NodeSize.Y);

		TSharedPtr<SGraphPanel> Panel = GetOwnerPanel();
		FChildren* PanelChildren = Panel->GetAllChildren();
		int32 NumChildren = PanelChildren->Num();
		static FString SDefault_GraphNodeCommentType = "SDefault_GraphNodeComment";

		for (int32 NodeIndex = 0; NodeIndex < NumChildren; ++NodeIndex)
		{
			const TSharedPtr<SGraphNode> SomeNodeWidget = StaticCastSharedRef<SGraphNode>(PanelChildren->GetChildAt(NodeIndex));

			UObject* GraphObject = SomeNodeWidget->GetObjectBeingDisplayed();
			if (!GraphObject->IsA<UEdGraphNode_Comment>())
			{
				continue;
			}

			const FVector2D SomeNodePosition = SomeNodeWidget->GetPosition();
			const FVector2D SomeNodeSize = SomeNodeWidget->GetDesiredSize();

			const FSlateRect NodeGeometryGraphSpace(SomeNodePosition.X, SomeNodePosition.Y, SomeNodePosition.X + SomeNodeSize.X, SomeNodePosition.Y + SomeNodeSize.Y);
			if (FSlateRect::DoRectanglesIntersect(CommentRect, NodeGeometryGraphSpace))
			{
				// This downcast *should* be valid at this point, since we verified the GraphObject is a comment node
				TSharedPtr<SDefault_GraphNodeComment> CommentWidget = StaticCastSharedPtr<SDefault_GraphNodeComment>(SomeNodeWidget);
				CommentWidget->HandleSelection(CommentWidget->bIsSelected, true);
			}
		}
	}
}

float SDefault_GraphNodeComment::GetTitleBarHeight() const
{
	return TitleBar.IsValid() ? TitleBar->GetDesiredSize().Y : 0.0f;
}

FSlateRect SDefault_GraphNodeComment::GetHitTestingBorder() const
{
	return SCommentNodeDefs::HitResultBorderSize;
}

FVector2D SDefault_GraphNodeComment::GetNodeMaximumSize() const
{
	return FVector2D(UserSize.X + 100, UserSize.Y + 100);
}

FSlateColor SDefault_GraphNodeComment::GetCommentBodyColor() const
{
	UEdGraphNode_Comment* CommentNode = Cast<UEdGraphNode_Comment>(GraphNode);
	float Opacity = bIsSelected ? CachedSelectedOpacity : CachedNormalOpacity;
	if (CommentNode)
	{
		const FLinearColor Color = CommentNode->CommentColor * SCommentNodeDefs::TitleBarColorMultiplier;
		return FLinearColor(Color.R, Color.G, Color.B, Opacity);
	}
	else
	{
		const FLinearColor Color = FLinearColor::White * SCommentNodeDefs::TitleBarColorMultiplier;
		return FLinearColor(Color.R, Color.G, Color.B, Opacity);
	}
}

FSlateColor SDefault_GraphNodeComment::GetCommentTitleBarColor() const
{
	return GetCommentBodyColor();
}

FSlateColor SDefault_GraphNodeComment::GetCommentBubbleColor() const
{
	return GetCommentBodyColor();
}

bool SDefault_GraphNodeComment::CanBeSelected(const FVector2D& MousePositionInNode) const
{
	const EResizableWindowZone InMouseZone = FindMouseZone(MousePositionInNode);
	return CRWZ_TitleBar == InMouseZone;
}

FVector2D SDefault_GraphNodeComment::GetDesiredSizeForMarquee() const
{
	const float TitleBarHeight = TitleBar.IsValid() ? TitleBar->GetDesiredSize().Y : 0.0f;
	return FVector2D(UserSize.X, TitleBarHeight);
}

FSlateRect SDefault_GraphNodeComment::GetTitleRect() const
{
	const FVector2D NodePosition = GetPosition();
	FVector2D NodeSize = TitleBar.IsValid() ? TitleBar->GetDesiredSize() : GetDesiredSize();
	return FSlateRect(NodePosition.X, NodePosition.Y, NodePosition.X + NodeSize.X, NodePosition.Y + NodeSize.Y) + SCommentNodeDefs::TitleBarOffset;
}

FReply SDefault_GraphNodeComment::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (bNewResizingMethod) {
		if (bUserIsDragging)
		{
			FVector2D OldGraphSpaceCoordinates = NodeCoordToGraphCoord(MouseEvent.GetLastScreenSpacePosition());
			FVector2D GraphSpaceCoordinates = NodeCoordToGraphCoord(MouseEvent.GetScreenSpacePosition());
			TSharedPtr<SWindow> OwnerWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());

			if (!ResizeTransactionPtr.IsValid())
			{
				CachedMouseMoveScreenSpace = OldGraphSpaceCoordinates;
			}

			FVector2D Delta = (GraphSpaceCoordinates - CachedMouseMoveScreenSpace) /

				(OwnerWindow.IsValid() ? OwnerWindow->GetDPIScaleFactor() : 1.0f);
			CachedMouseMoveScreenSpace = GraphSpaceCoordinates;

			//Clamp delta value based on resizing direction

			if (MouseZone == CRWZ_LeftBorder || MouseZone == CRWZ_RightBorder)
			{
				Delta.Y = 0.0f;
			}
			else if (MouseZone == CRWZ_TopBorder || MouseZone == CRWZ_BottomBorder)
			{
				Delta.X = 0.0f;
			}

			//Resize node delta value
			FVector2D DeltaNodeSize = Delta;

			//Modify node size delta value based on resizing direction
			if ((MouseZone == CRWZ_LeftBorder) || (MouseZone == CRWZ_TopBorder) || (MouseZone == CRWZ_TopLeftBorder))
			{
				DeltaNodeSize = -DeltaNodeSize;
			}
			else if (MouseZone == CRWZ_TopRightBorder)
			{
				DeltaNodeSize.Y = -DeltaNodeSize.Y;
			}
			else if (MouseZone == CRWZ_BottomLeftBorder)
			{
				DeltaNodeSize.X = -DeltaNodeSize.X;
			}
			// Apply delta unfiltered to DragSize
			DragSize.X += DeltaNodeSize.X;
			DragSize.Y += DeltaNodeSize.Y;

			// apply snap
			//const float SnapSize = SNodePanel::GetSnapGridSize();
			const float SnapSize = static_cast<float>(SNodePanel::GetSnapGridSize());
			FVector2D SnappedSize;
			SnappedSize.X = SnapSize * FMath::RoundToFloat(DragSize.X / SnapSize);
			SnappedSize.Y = SnapSize * FMath::RoundToFloat(DragSize.Y / SnapSize);
			//SnappedSize.X = SnapSize * FMath::RoundToFloat(DragSize.X / SnapSize);
			//SnappedSize.Y = SnapSize * FMath::RoundToFloat(DragSize.Y / SnapSize);

			 //Enforce min/max sizing
			const FVector2D MinSize = GetNodeMinimumSize();
			SnappedSize.X = FMath::Max(SnappedSize.X, MinSize.X);
			SnappedSize.Y = FMath::Max(SnappedSize.Y, MinSize.Y);

			const FVector2D MaxSize = GetNodeMaximumSize();
			SnappedSize.X = FMath::Min(SnappedSize.X, MaxSize.X);
			SnappedSize.Y = FMath::Min(SnappedSize.Y, MaxSize.Y);

			FVector2D DeltaNodePos(0, 0);
			 if (UserSize != SnappedSize)
			{
				UserSize = SnappedSize;
				GraphNode->ResizeNode(UserSize);
				DeltaNodePos = GetCorrectedNodePosition() - GetPosition();
			}

			if (!ResizeTransactionPtr.IsValid() && UserSize != StoredUserSize)
			{
				// Start resize transaction.  The transaction is started here so all MoveTo actions are captured while empty
				//	transactions are not created
				ResizeTransactionPtr = MakeShareable(new FScopedTransaction(NSLOCTEXT("GraphEditor", "ResizeNodeAction", "Resize Node")));
			}

			FNodeSet NodeFilter;
			SGraphNode::MoveTo(GetPosition() + DeltaNodePos, NodeFilter);
		}
		else
		{
			const FVector2D LocalMouseCoordinates = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
			MouseZone = FindMouseZone(LocalMouseCoordinates);
		}
		return SGraphNode::OnMouseMove(MyGeometry, MouseEvent);
	}
	return SGraphNodeResizable::OnMouseMove(MyGeometry, MouseEvent);
}

void SDefault_GraphNodeComment::PopulateMetaTag(FGraphNodeMetaData* TagMeta) const
{
	if (GraphNode != nullptr)
	{
		// We want the name of the blueprint as our name - we can find the node from the GUID
		UObject* Package = GraphNode->GetOutermost();
		UObject* LastOuter = GraphNode->GetOuter();
		while (LastOuter->GetOuter() != Package)
		{
			LastOuter = LastOuter->GetOuter();
		}
		TagMeta->Tag = FName(*FString::Printf(TEXT("GraphNode_%s_%s"), *LastOuter->GetFullName(), *GraphNode->NodeGuid.ToString()));
		TagMeta->OuterName = LastOuter->GetFullName();
		TagMeta->GUID = GraphNode->NodeGuid;
		TagMeta->FriendlyName = FString::Printf(TEXT("%s in %s"), *GraphNode->GetNodeTitle(ENodeTitleType::FullTitle).ToString(), *TagMeta->OuterName);
	}
}
