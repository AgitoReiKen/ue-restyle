// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_ErrorText.h"
#include "Brushes/SlateRoundedBoxBrush.h"

void SDefault_ErrorText::Construct(const FArguments& InArgs, EDTNodeReportType Type)
{
	auto& Config = UNodeRestyleSettings::Get()->NodeReports[(int)Type];
	
	ExpandAnimation_New = FCurveSequence(0.0f, 0.15f);

	CustomVisibility = GetVisibilityAttribute().ToAttribute();
	SetVisibility(MakeAttributeSP(this, &SDefault_ErrorText::MyVisibility_New));

	SBorder::Construct(SBorder::FArguments()
		.BorderImage(FAppStyle::GetBrush(FNodeRestyleStyles::NodeReport_Body(Type)))
		.ContentScale(this, &SDefault_ErrorText::GetDesiredSizeScale_New)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Padding(UDefaultThemeSettings::GetMargin(Config.InnerPadding))
		[
			SAssignNew(TextBlock_New, STextBlock)
			.TextStyle(FAppStyle::Get(), FNodeRestyleStyles::NodeReport_Text(Type))
			.AutoWrapText(InArgs._AutoWrapText)
		]
	);

	SetError(InArgs._ErrorText);
}

FVector2D SDefault_ErrorText::GetDesiredSizeScale_New() const
{
	const float AnimAmount = ExpandAnimation_New.GetLerp();
	return FVector2D(1.0f, AnimAmount);
}

EVisibility SDefault_ErrorText::MyVisibility_New() const
{
	return (!TextBlock_New->GetText().IsEmpty())
		? CustomVisibility.Get()
		: EVisibility::Collapsed;
}

void SDefault_ErrorText::SetError(const FText& InErrorText)
{
	if (TextBlock_New->GetText().IsEmpty() && !InErrorText.IsEmpty())
	{
		ExpandAnimation_New.Play(this->AsShared());
	}

	TextBlock_New->SetText(InErrorText);
}
 

bool SDefault_ErrorText::HasError() const
{
	return !TextBlock_New->GetText().IsEmpty();
} 