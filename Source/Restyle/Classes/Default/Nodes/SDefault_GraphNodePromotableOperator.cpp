// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodePromotableOperator.h"

#include "SGraphPin.h"

#include "Widgets/Images/SLayeredImage.h"

void SDefault_GraphNodePromotableOperator::Construct(const FArguments& InArgs, UK2Node_PromotableOperator* InNode)
{
	SDefault_GraphNodeK2Sequence::Construct(SDefault_GraphNodeK2Sequence::FArguments(), InNode);

	LoadCachedIcons();
}

void SDefault_GraphNodePromotableOperator::CreatePinWidgets()
{

	SDefault_GraphNodeK2Sequence::CreatePinWidgets();

	TSet<TSharedRef<SWidget>> AllPins;
	GetPins(AllPins);

	LoadCachedIcons();

	for (TSharedRef<SWidget>& Widget : AllPins)
	{

		if (TSharedPtr<SGraphPin> Pin = StaticCastSharedRef<SGraphPin>(Widget))
		{
			UEdGraphPin* SourcePin = Pin->GetPinObj();

			// Split pins should be drawn as normal pins, the inner properties are not promotable
			if (!SourcePin || SourcePin->ParentPin)
			{
				continue;
			}

			//if (TSharedPtr<SLayeredImage> PinImage = StaticCastSharedPtr<SLayeredImage>(Pin->GetPinImageWidget()))
			//{
			//	// Set the image to use the outer icon, which will be the connect pin type color
			//	PinImage->SetLayerBrush(0, CachedOuterIcon);

			//	// Set the inner image to be wildcard color, which is grey by default
			//	PinImage->AddLayer(CachedInnerIcon, GetDefault<UGraphEditorSettings>()->WildcardPinTypeColor);
			//}
		}
	}
}

void SDefault_GraphNodePromotableOperator::LoadCachedIcons()
{
	static const FName PromotableTypeOuterName("Kismet.VariableList.PromotableTypeOuterIcon");
	static const FName PromotableTypeInnerName("Kismet.VariableList.PromotableTypeInnerIcon");

	// Outer ring icons
	if (!CachedOuterIcon)
	{
		CachedOuterIcon = FAppStyle::GetBrush(PromotableTypeOuterName);
	}

	if (!CachedInnerIcon)
	{
		CachedInnerIcon = FAppStyle::GetBrush(PromotableTypeInnerName);
	}
}
