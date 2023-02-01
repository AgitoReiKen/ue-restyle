// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_NodeTitle.h"

void SDefault_NodeTitle::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	CachedSize = AllottedGeometry.GetLocalSize();

	// Checks to see if the cached string is valid, and if not, updates it.
	if (NodeTitleCache.IsOutOfDate(GraphNode.Get()))
	{
		NodeTitleCache.SetCachedText(TitleText.Get(), GraphNode.Get());
		RebuildWidget_New();
	}
}

FText SDefault_NodeTitle::GetNodeTitle_New() const
{
	return GetNodeTitle();
}


 
void SDefault_NodeTitle::Construct(const FArguments& InArgs, UEdGraphNode* Node, const FLinearColor& TextColor,
	const FName& InTextBlockStyle, const TArray<FString>& InIgnoreLineStartsWith)
{
	GraphNode = Node;
	TitleText = InArgs._Text.IsSet() ? InArgs._Text : TAttribute<FText>(this, &SDefault_NodeTitle::GetNodeTitle_New);
	Color = TextColor;
	TextBlockStyle = InTextBlockStyle;
	NodeTitleCache.SetCachedText(TitleText.Get(), GraphNode.Get());
	IgnoreLineStartsWith = InIgnoreLineStartsWith;
	RebuildWidget_New();
}
 
void SDefault_NodeTitle::RebuildWidget_New()
{
	// Create the box to contain the lines
	TSharedPtr<SVerticalBox> VerticalBox;
	this->ChildSlot
	[
		SAssignNew(VerticalBox, SVerticalBox)
	];

	FString CachedTitleString = NodeTitleCache.GetCachedText().ToString().Replace(TEXT("\r"), TEXT(""));
	int NewlineCharIndex = 0;
	if (CachedTitleString.FindChar('\n', NewlineCharIndex))
	{
		CachedHeadTitle = FText::FromString(CachedTitleString.Mid(0, NewlineCharIndex));

		// if string not ends after \n
		if ((CachedTitleString.Len() - 1) > NewlineCharIndex)
		{
			FString ExtraTextStr = CachedTitleString.Mid(NewlineCharIndex + 1);
			bool bIsIgnored = IgnoreLineStartsWith.ContainsByPredicate([&ExtraTextStr](const FString& str)->bool
				{
					return ExtraTextStr.StartsWith(str);
				});
			if (bIsIgnored)
			{
				if (int32 Id = 0; ExtraTextStr.FindChar('\n', Id)) {

					ExtraTextStr.RemoveAt(0, Id + 1);
				}
				else
				{
					ExtraTextStr.Empty();
				}
			}
			if (!ExtraTextStr.IsEmpty()) {
				FText ExtraText = FText::FromString(ExtraTextStr);
				VerticalBox->AddSlot()
				           .AutoHeight()
				[
					SAssignNew(ExtraTextBlock, STextBlock)
					.TextStyle(FAppStyle::Get(), TextBlockStyle)
					.ColorAndOpacity(FSlateColor(Color))
					.Text(ExtraText)
				];
			}
		}
	}
	else
	{
		CachedHeadTitle = FText::FromString(CachedTitleString);
	}
}
