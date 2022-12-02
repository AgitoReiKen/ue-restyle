// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SOverlay.h"
#include "SGraphNode.h"
#include "SGraphPin.h"
#include "Rendering/RenderingCommon.h"
enum class EDTGraphNodeTitleType;
enum class EDTGraphNodeState;
enum class EDTNodeReportType;
class SDefault_NodeTitle;
class SDefault_GraphNodeRestyleBase : public SGraphNode
{
	// Restyle
public:
	SDefault_GraphNodeRestyleBase();

	virtual void SetupRenderOpacity();
	virtual bool IsInvalid() const;
	virtual bool IsDisabled() const;
	/** @return True if state changed*/
	virtual bool UpdateState(bool bSelected = false) const;
	virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;
	virtual void SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel) override;
	virtual void UpdateGraphNode() override;
	virtual EDTGraphNodeTitleType GetNodeType() const;
	virtual TSharedPtr<SWidget> CreateEnabledStateWidget();
	virtual FMargin GetEnabledStateWidgetPadding() const;

	virtual void UpdateErrorInfo_New();
	virtual void SetupErrorReporting_New();
	/** Create widget to show/hide advanced pins */
	virtual void CreateAdvancedViewArrowNew(TSharedPtr<SVerticalBox> MainBox);
	virtual FReply OnAdvancedDisplayClicked();

	virtual TSharedPtr<SVerticalBox> MakeInnerVerticalBox(TSharedRef<SOverlay> DefaultTitleAreaWidget);
protected:
	const FSlateBrush* GetAdvancedViewArrowNew() const
	{
		const bool bAdvancedPinsHidden = GraphNode && (ENodeAdvancedPins::Hidden == GraphNode->AdvancedPinDisplay);
		return bAdvancedPinsHidden ? IChevronDown : IChevronUp;
	}

	EDTNodeReportType ErrorInfoType;

	const FSlateBrush* CachedNoDrawBrush;
	mutable float CachedOutlineWidth;
	mutable EDTGraphNodeState CachedState;

	TSharedPtr<SImage> MainBackground;
	TSharedPtr<SImage> TitleIcon;
	TSharedPtr<SBorder> MainTitleBorder;
	TSharedPtr<SDefault_NodeTitle> TitleExtraText;
	TSharedPtr<SBorder> ContentBorder;
	TSharedPtr<SHorizontalBox> TitleContent; 

	TSharedPtr<SWidget> EnabledStateWidget;
	TSharedPtr<SBox> EnabledStateWidgetBox;
	FMargin EnabledStateWidgetAdditionalPadding;

	const FSlateBrush* IChevronDown;
	const FSlateBrush* IChevronUp;
	TSharedPtr<SImage> AdvancedViewArrow;

};
