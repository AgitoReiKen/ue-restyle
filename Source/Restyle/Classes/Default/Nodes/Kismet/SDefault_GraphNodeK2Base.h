// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "Default/Nodes/Common/SDefault_NodeTitle.h"

#include "KismetNodes/SGraphNodeK2Default.h"
 
class UK2Node;
class UDefaultThemeSettings;
class UNodeRestyleSettings;
class SDefault_GraphNodeK2Base : public SGraphNodeK2Base
{

public:
	SDefault_GraphNodeK2Base()
	{
		CachedNoDrawBrush = FAppStyle::Get().GetBrush(FNodeRestyleStyles::NoDrawBrush);
		CachedOutlineWidth = .0f;
		CachedState = EDTGraphNodeState::Num;
		ErrorInfoType = EDTNodeReportType::Num;
		IChevronDown = FAppStyle::GetBrush("Icons.ChevronDown");
		IChevronUp = FAppStyle::GetBrush("Icons.ChevronUp");
	}

	virtual bool IsInvalid() const;
	virtual bool IsDisabled() const;
	/** @return True if state changed*/
	bool UpdateState(bool bSelected = false) const;
	 

	void UpdateErrorInfo_New();
	void SetupErrorReporting_New();
	TSharedPtr<SWidget> CreateEnabledStateWidget();
	FMargin GetEnabledStateWidgetPadding() const;
	FReply OnAdvancedDisplayClicked();
	/** Create widget to show/hide advanced pins */
	virtual void CreateAdvancedViewArrowNew(TSharedPtr<SVerticalBox> MainBox);
 
	virtual void SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel) override;
	void SetupRenderOpacity();
protected:
	const FSlateBrush* GetAdvancedViewArrowNew() const
	{
		const bool bAdvancedPinsHidden = GraphNode && (ENodeAdvancedPins::Hidden == GraphNode->AdvancedPinDisplay);
		return bAdvancedPinsHidden ? IChevronDown : IChevronUp;
	}
	const FSlateBrush* CachedNoDrawBrush;
	TSharedRef<SWidget> AddPinButtonContent_New(FText PinText, FText PinTooltipText, bool bRightSide = true, FString DocumentationExcerpt = FString(), TSharedPtr<SToolTip> CustomTooltip = NULL);
	FMargin EnabledStateWidgetAdditionalPadding;
	mutable float CachedOutlineWidth;
	mutable EDTGraphNodeState CachedState;
	EDTNodeReportType ErrorInfoType;
	const FSlateBrush* IChevronDown;
	const FSlateBrush* IChevronUp;
	TSharedPtr<SImage> AdvancedViewArrow;
	TSharedPtr<SWidget> EnabledStateWidget;
	//InlineEditableText -> MainText
};
