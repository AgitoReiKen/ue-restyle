// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_KeySelector.h"
#include "Widgets/Layout/SScaleBox.h"
class FKeyTreeInfo
{
public:
	/** This data item's children */
	TArray< TSharedPtr<FKeyTreeInfo> > Children;

private:
	/** This data item's name */
	FText Name;

	/** The actual key associated with this item */
	TSharedPtr<FKey> Key;

public:
	FKeyTreeInfo(FText InName, TSharedPtr<FKey> InKey)
		: Name(InName)
		, Key(InKey)
	{
	}

	FKeyTreeInfo(TSharedPtr<FKeyTreeInfo> InInfo)
		: Name(InInfo->Name)
		, Key(InInfo->Key)
	{
	}

	FText GetDescription() const
	{
		if (Key.IsValid())
		{
			return Key->GetDisplayName();
		}
		else
		{
			return Name;
		}
	}

	TSharedPtr<FKey> GetKey() const
	{
		return Key;
	}

	bool MatchesSearchTokens(const TArray<FString>& SearchTokens)
	{
		FString Description = GetDescription().ToString();

		for (auto Token : SearchTokens)
		{
			if (!Description.Contains(Token))
			{
				return false;
			}
		}

		return true;
	}
};

void SDefault_KeySelector::PreConstruct(const FArguments& InArgs)
{
	SearchText = FText::GetEmpty();

	OnKeyChanged = InArgs._OnKeyChanged;
	CurrentKey = InArgs._CurrentKey;

	TMap<FName, FKeyTreeItem> TreeRootsForCategories;
	// Ensure that Gamepad, Keyboard, and Mouse will appear at the top of the list, other categories will dynamically get added as the keys are encountered
	TreeRootsForCategories.Add(EKeys::NAME_GamepadCategory, *new (KeyTreeRoot) FKeyTreeItem(MakeShareable(new FKeyTreeInfo(EKeys::GetMenuCategoryDisplayName(EKeys::NAME_GamepadCategory), nullptr))));
	TreeRootsForCategories.Add(EKeys::NAME_KeyboardCategory, *new (KeyTreeRoot) FKeyTreeItem(MakeShareable(new FKeyTreeInfo(EKeys::GetMenuCategoryDisplayName(EKeys::NAME_KeyboardCategory), nullptr))));
	TreeRootsForCategories.Add(EKeys::NAME_MouseCategory, *new (KeyTreeRoot) FKeyTreeItem(MakeShareable(new FKeyTreeInfo(EKeys::GetMenuCategoryDisplayName(EKeys::NAME_MouseCategory), nullptr))));

	TArray<FKey> AllKeys;
	EKeys::GetAllKeys(AllKeys);

	for (FKey Key : AllKeys)
	{
		if (Key.IsBindableToActions() && (!InArgs._FilterBlueprintBindable || Key.IsBindableInBlueprints()))
		{
			const FName KeyMenuCategory = Key.GetMenuCategory();
			FKeyTreeItem* KeyCategory = TreeRootsForCategories.Find(KeyMenuCategory);
			if (KeyCategory == nullptr)
			{
				KeyCategory = new (KeyTreeRoot) FKeyTreeItem(MakeShareable(new FKeyTreeInfo(EKeys::GetMenuCategoryDisplayName(KeyMenuCategory), nullptr)));
				TreeRootsForCategories.Add(KeyMenuCategory, *KeyCategory);
			}
			(*KeyCategory)->Children.Add(MakeShareable(new FKeyTreeInfo(FText(), MakeShareable(new FKey(Key)))));
		}
	}

	// if we allow NoClear, add a "None" option to be able to clear out a binding
	if (InArgs._AllowClear)
	{
		new (KeyTreeRoot) FKeyTreeItem(MakeShareable(new FKeyTreeInfo(FText(), MakeShareable(new FKey(EKeys::Invalid)))));
	}

	TreeViewWidth = InArgs._TreeViewWidth;
	TreeViewHeight = InArgs._TreeViewHeight;
	CategoryFont = FCoreStyle::GetDefaultFontStyle("Bold", 9);
	KeyFont = FCoreStyle::GetDefaultFontStyle("Regular", 10);

	FilteredKeyTreeRoot = KeyTreeRoot;

}

void SDefault_KeySelector::InConstruct(const FArguments& InArgs)
{
	this->ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Fill)
		[
			SAssignNew(KeyComboButton, SComboButton)
			.ComboButtonStyle(InArgs._ComboButtonStyle)
			.OnGetMenuContent(this, &SDefault_KeySelector::GetMenuContent)
			// Longer key descriptions can overrun the visible space in the combo button
			// if the parent width is constrained, so we reflect them in the tooltip too.
			.ToolTipText(this, &SDefault_KeySelector::GetKeyDescription)
			.HasDownArrow(InArgs._bHasDownArrow) 
			.ButtonContent()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Left)
				[
					SNew(STextBlock)
					.Text(this, &SDefault_KeySelector::GetKeyDescription)
					.Font(InArgs._Font)
				] 
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SSpacer).Size(InArgs._bHasDownArrow ? FVector2D(InArgs._SpacingBetweenTextAndArrow, 0) : FVector2D(0))
				]
			]
		]
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SSpacer).Size(FVector2D(InArgs._Spacing, 0))
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SButton)
			.ButtonStyle(InArgs._ButtonStyle)
			.PressMethod(EButtonPressMethod::DownAndUp)
			.ToolTipText(this, &SDefault_KeySelector::GetKeyTooltip)
			.OnClicked(this, &SDefault_KeySelector::ListenForInput)
			.ContentPadding(InArgs._ButtonContentPadding)
			[
				SNew(SBox)
				.MaxDesiredHeight(InArgs._ButtonIconSize)
				.MaxDesiredWidth(InArgs._ButtonIconSize)
				[
					SNew(SScaleBox)
					.Stretch(EStretch::ScaleToFit)
					[	
						SNew(SImage)
						.Image(this, &SDefault_KeySelector::GetKeyIconImage_New)
						.ColorAndOpacity(FSlateColor::UseStyle())
						.DesiredSizeOverride(FVector2D(InArgs._ButtonIconSize))
					]
				]
			]
		]
	];
}

void SDefault_KeySelector::PostConstruct(const FArguments& InArgs)
{
}

const FSlateBrush* SDefault_KeySelector::GetKeyIconImage_New() const
{
	if (bListenForNextInput)
	{
		return FAppStyle::GetBrush("Icons.Restyle.Edit");
	}

	TOptional<FKey> CurrentKeyValue = CurrentKey.Get();
	if (CurrentKeyValue.IsSet())
	{
		const FKey& Key = CurrentKeyValue.GetValue();
		if (Key.IsValid() && (Key.IsDeprecated() || !Key.IsBindableToActions()))
		{
			return FAppStyle::GetBrush("Icons.Warning");
		}
		return GetIconFromKey(CurrentKeyValue.GetValue());
	}
	return nullptr;
}
