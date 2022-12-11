// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "SDefault_GraphNodeAnimationResult.h"

TSharedRef<SWidget> SDefault_GraphNodeAnimationResult::CreateNodeContentArea()
{
	auto Style = UNodeRestyleSettings::Get();
	float ContentSpacing = UDefaultThemeSettings::GetSpacing(Style->Node.ContentSpacing);
	auto GESettings = GetDefault<UGraphEditorSettings>();
	return SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("NoBorder"))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(0)
		//.Padding(PaddingBelowPin)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.FillWidth(1.0f)
			.Padding(0)
			[
				// LEFT
				SAssignNew(LeftNodeBox, SVerticalBox)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(ContentSpacing)
			[
				SNew(SImage)
				.Image(FAppStyle::GetBrush("Graph.AnimationResultNode.Body"))
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			.Padding(0, 0, 0, 0)
			[
				// RIGHT
				SAssignNew(RightNodeBox, SVerticalBox)
			]
		];

}
