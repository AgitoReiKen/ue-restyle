// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "Default/Nodes/Common/SDefault_NodeTitle.h"

#include "KismetNodes/SGraphNodeK2Default.h"

class UK2Node;
class UDefaultThemeSettings;
class UNodeRestyleSettings;
class SDefault_GraphNodeRestyleK2Base : public SGraphNodeK2Base
{

public:
	SDefault_GraphNodeRestyleK2Base();
	/* State */
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	virtual bool IsInvalid() const;
	virtual bool IsDisabled() const;
	void UpdateState(bool bSelected = false) const;
	virtual void OnStateUpdated(EDTGraphNodeState NewState);
	virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;
	virtual EDTGraphNodeTitleType GetNodeType() const;

	/* Custom Zoom */
	virtual void SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel) override;

	/* Disabled Opacity*/
	void SetupRenderOpacity();

	/* Widgets */
	void UpdateErrorInfo_New();
	void SetupErrorReporting_New();

	TSharedPtr<SWidget> CreateEnabledStateWidget();
	FMargin GetEnabledStateWidgetPadding() const;

	FReply OnAdvancedDisplayClicked();
	virtual void CreateAdvancedViewArrowNew(TSharedPtr<SVerticalBox> MainBox);

	virtual void UpdateGraphNode() override;

protected:
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
	virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle) override;

	const FSlateBrush* GetAdvancedViewArrowNew() const
	{
		const bool bAdvancedPinsHidden = GraphNode && (ENodeAdvancedPins::Hidden == GraphNode->AdvancedPinDisplay);
		return bAdvancedPinsHidden ? IChevronDown : IChevronUp;
	}
	TSharedRef<SWidget> AddPinButtonContent_New(FText PinText, FText PinTooltipText, bool bRightSide = true, FString DocumentationExcerpt = FString(), TSharedPtr<SToolTip> CustomTooltip = NULL);
	const FSlateBrush* CachedNoDrawBrush;
	FMargin EnabledStateWidgetAdditionalPadding;
	mutable float CachedOutlineWidth;
	/* Gets updated in GetShadowBrush*/
	mutable EDTGraphNodeState CachedState;
	/* Used to move from const context. Gets updated in tick*/
	EDTGraphNodeState LastUpdatedState;
	EDTNodeReportType ErrorInfoType;
	const FSlateBrush* IChevronDown;
	const FSlateBrush* IChevronUp;
	TSharedPtr<SImage> AdvancedViewArrow;
	TSharedPtr<SWidget> EnabledStateWidget;

	TSharedPtr<SImage> MainBackground;
	TSharedPtr<SImage> TitleIcon;
	TSharedPtr<SBorder> MainTitleBorder;
	TSharedPtr<SDefault_NodeTitle> TitleExtraText;
	TSharedPtr<SBorder> ContentBorder;

	TSharedPtr<SHorizontalBox> TitleContent;
	TSharedPtr<SBox> EnabledStateWidgetBox;
};
