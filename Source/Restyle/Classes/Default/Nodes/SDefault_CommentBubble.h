// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "SCommentBubble.h"

class SDefault_CommentBubble : public SCommentBubble
{
	SLATE_BEGIN_ARGS(SDefault_CommentBubble)
			: _GraphNode(NULL)
			  , _AllowPinning(false)
			  , _EnableTitleBarBubble(false)
			  , _EnableBubbleCtrls(false)
			  , _InvertLODCulling(false)
			  , _GraphLOD(EGraphRenderingLOD::DefaultDetail)
		{
		}

		/** the GraphNode this bubble should interact with */
		SLATE_ARGUMENT(UEdGraphNode*, GraphNode)

		/** Attribute to determine the visibility buttons check state */
		SLATE_ATTRIBUTE(ECheckBoxState, ToggleButtonCheck)

		/** The comment text for the bubble */
		SLATE_ATTRIBUTE(FString, Text)

		/** Called when the comment text is committed */
		SLATE_EVENT(FOnTextCommitted, OnTextCommitted)

		/** Called when the comment bubble is toggled */
		SLATE_EVENT(FOnCommentBubbleToggled, OnToggled)

		/** The comment hint text for the bubble */
		SLATE_ATTRIBUTE(FText, HintText)

		/** Color and opacity for the comment bubble */
		SLATE_ATTRIBUTE(FSlateColor, ColorAndOpacity)

		/** Allow bubble to be pinned */
		SLATE_ARGUMENT(bool, AllowPinning)

		/** Enable the title bar bubble to toggle */
		SLATE_ARGUMENT(bool, EnableTitleBarBubble)

		/** Enable the controls within the bubble */
		SLATE_ARGUMENT(bool, EnableBubbleCtrls)

		/** Invert LOD culling */
		SLATE_ARGUMENT(bool, InvertLODCulling)

		/** The current level of detail */
		SLATE_ATTRIBUTE(EGraphRenderingLOD::Type, GraphLOD)

		/** Delegate to determine if the parent node is in the hovered state. */
		SLATE_EVENT(FIsGraphNodeHovered, IsGraphNodeHovered)

	SLATE_END_ARGS()
	 
	/*Can't override previous construct, so new parameter is needed*/
	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	void UpdateBubble_New();
	void OnCommentBubbleToggle_New(ECheckBoxState State);
	void SetCommentBubbleVisibility_New(bool bVisible);
	void OnCommentTextChanged(const FText& Text);
	TSharedPtr<SWidget> BubbleControls;
	TSharedPtr<SWidget> HorizontalBubbleControls;
	TSharedPtr<SWidget> VerticalBubbleControls;
	bool ShouldDrawHorizontalControls();
	bool ShouldDrawHorizontalControls(const FText& Text);
	TSharedPtr<SWidget> UpdateBubbleControls(bool bHorizontal);
	TSharedPtr<SHorizontalBox> MainHorizontalBox;

	TSharedPtr<TSharedRef<SWidget>> CachedBubbleControls;
	EVisibility GetButtonControlsVisibility() const;
};

inline void SDefault_CommentBubble::OnCommentTextChanged(const FText& Text)
{
	UpdateBubbleControls(ShouldDrawHorizontalControls(Text));
}
inline bool SDefault_CommentBubble::ShouldDrawHorizontalControls(const FText& Text)
{
	int SearchIndex = 0;
	FString String = Text.ToString().Replace(TEXT("\r"), TEXT(""));
	bool bFound = String.FindChar(TEXT('\n'), SearchIndex);
	return !bFound;
}