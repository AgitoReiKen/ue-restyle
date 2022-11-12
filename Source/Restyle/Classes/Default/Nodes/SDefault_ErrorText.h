// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once
#include "Widgets/Notifications/SErrorText.h"
#include "Themes/Default/NodeRestyleDefault.h"
class SDefault_ErrorText : public SErrorText
{
public:
	void Construct(const FArguments& InArgs, EDTNodeReportType Type);
	TSharedPtr<class STextBlock> TextBlock_New;
	FCurveSequence ExpandAnimation_New;
	FVector2D GetDesiredSizeScale_New() const;

	TAttribute<EVisibility> CustomVisibility;
	EVisibility MyVisibility_New() const;
	virtual void SetError(const FText& InErrorText) override;
	virtual bool HasError() const override;
};