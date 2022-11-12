// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeK2Event.h"
#include "SGraphPin.h"
#include "K2Node_Event.h"

void SDefault_GraphNodeK2Event::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	const bool bDelegateOutput = (PinObj != nullptr) && (UK2Node_Event::DelegateOutputName == PinObj->PinName);
	if (bDelegateOutput && TitleAreaWidget.IsValid())
	{
		PinToAdd->SetOwner(SharedThis(this));
		const auto& Title = UNodeRestyleSettings::Get()->Node.Title;
		float PinSpacing = UDefaultThemeSettings::GetSpacing(Title.DelegatePinSpacing);
		bHasDelegateOutputPin = true;
		PinToAdd->SetShowLabel(false);

	/*	TitleAreaWidget->AddSlot()
		               .HAlign(HAlign_Right)
		               .VAlign(VAlign_Center)
		               .Padding(FMargin(Padding))
		[
			PinToAdd
		];*/

		if (TitleContent.IsValid())
		{
			TitleContent->AddSlot()
			            .HAlign(HAlign_Right)
			            .VAlign(VAlign_Center)
						.AutoWidth()
						.Padding(PinSpacing,0,0,0)
						
			[
				PinToAdd
			];
			//PinToAdd->SetVisibility(EVisibility::Visible);
		}
		/*RightNodeBox->AddSlot()
		            .HAlign(HAlign_Right)
		            .VAlign(VAlign_Top)
		            .Padding(PinPadding)
		[
			PinToAdd
		];*/
		OutputPins.Add(PinToAdd);
	}
	else
	{
		SDefault_GraphNodeK2Default::AddPin(PinToAdd);
	}
}

bool SDefault_GraphNodeK2Event::UseLowDetailNodeTitles() const
{
	return (!bHasDelegateOutputPin) && ParentUseLowDetailNodeTitles();
}

EVisibility SDefault_GraphNodeK2Event::GetTitleVisibility() const
{
	return ParentUseLowDetailNodeTitles() ? EVisibility::Hidden : EVisibility::Visible;
}

TSharedRef<SWidget> SDefault_GraphNodeK2Event::CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle)
{
	TSharedRef<SWidget> WidgetRef = SDefault_GraphNodeK2Default::CreateTitleWidget(NodeTitle);
	WidgetRef->SetVisibility(MakeAttributeSP(this, &SDefault_GraphNodeK2Event::GetTitleVisibility));
	if (NodeTitle.IsValid())
	{
		NodeTitle->SetVisibility(MakeAttributeSP(this, &SDefault_GraphNodeK2Event::GetTitleVisibility));
	}

	return WidgetRef;
}
