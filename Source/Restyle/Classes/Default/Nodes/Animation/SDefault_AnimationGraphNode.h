// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "SDefault_AnimationGraphNodeRestyleBase.h"

#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/Reply.h"
#include "Styling/SlateColor.h"
#include "SNodePanel.h"

#include "Default/Nodes/Kismet/SDefault_GraphNodeK2Base.h"

#include "KismetNodes/SGraphNodeK2Base.h"
#include "Engine/PoseWatch.h"

class UAnimGraphNode_Base;
class IDetailTreeNode;
class IPropertyRowGenerator;
class UAnimBlueprint;
class SPoseWatchOverlay;

class SDefault_PoseWatchOverlay : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDefault_PoseWatchOverlay) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphNode* InNode);
	FVector2D GetOverlayOffset() const;
	bool IsPoseWatchValid() const;

private:
	void HandlePoseWatchesChanged(UAnimBlueprint* InAnimBlueprint, UEdGraphNode* InNode);

	FSlateColor GetPoseViewColor() const;
	const FSlateBrush* GetPoseViewIcon() const;
	FReply TogglePoseWatchVisibility();

	TWeakObjectPtr<UEdGraphNode> GraphNode;
	TWeakObjectPtr<class UPoseWatch> PoseWatch;

	static const FSlateBrush* IconVisible;
	static const FSlateBrush* IconNotVisible;
};

class SDefault_AnimationGraphNode : public SDefault_AnimationGraphNodeRestyleBase
{
public:
	SLATE_BEGIN_ARGS(SDefault_AnimationGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode);

	virtual void HandleNodeTitleChangedNew();

	// Create below-widget controls for editing anim node functions
	static TSharedRef<SWidget> CreateNodeFunctionsWidgetNew(UAnimGraphNode_Base* InAnimNode, TAttribute<bool> InUseLowDetail);

protected:
	virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;
	virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle) override;
	virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2D& WidgetSize) const override;
	TSharedPtr<SDefault_PoseWatchOverlay> PoseViewWidget;
	bool UseLowDetailNodeContent() const;
	FVector2D GetLowDetailDesiredSize() const;
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
};
