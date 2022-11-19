// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "SDefault_PinTypeSelector.h"

#include "IDocumentation.h"
#include "PinTypeSelectorFilter.h"

#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Images/SLayeredImage.h"
#define LOCTEXT_NAMESPACE "PinTypeSelector"
namespace PinTypeSelectorStatics
{
	static const FString BigTooltipDocLink = TEXT("Shared/Editor/Blueprint/VariableTypes");
}	

/** Wraps a custom pin type filter provided at construction time. */
class FPinTypeSelectorCustomFilterProxy : public IPinTypeSelectorFilter
{
public:
	FPinTypeSelectorCustomFilterProxy(TSharedRef<IPinTypeSelectorFilter> InFilter, FSimpleDelegate InOnFilterChanged)
		:Filter(InFilter)
	{
		// Auto-register the given delegate to respond to any filter change event and refresh the filtered item list, etc.
		OnFilterChanged_DelegateHandle = Filter->RegisterOnFilterChanged(InOnFilterChanged);
	}

	virtual ~FPinTypeSelectorCustomFilterProxy()
	{
		// Auto-unregister the delegate that was previously registered at construction time.
		Filter->UnregisterOnFilterChanged(OnFilterChanged_DelegateHandle);
	}

	virtual FDelegateHandle RegisterOnFilterChanged(FSimpleDelegate InOnFilterChanged)
	{
		return Filter->RegisterOnFilterChanged(InOnFilterChanged);
	}

	virtual void UnregisterOnFilterChanged(FDelegateHandle InDelegateHandle)
	{
		Filter->UnregisterOnFilterChanged(InDelegateHandle);
	}

	virtual TSharedPtr<SWidget> GetFilterOptionsWidget()
	{
		return Filter->GetFilterOptionsWidget();
	}

	virtual bool ShouldShowPinTypeTreeItem(FPinTypeTreeItem InItem) const
	{
		return Filter->ShouldShowPinTypeTreeItem(InItem);
	}

private:
	/** The underlying filter for which we're acting as a proxy. */
	TSharedRef<IPinTypeSelectorFilter> Filter;

	/** A handle to a delegate that gets called whenever the custom filter changes. Will be unregistered automatically when the proxy is destroyed. */
	FDelegateHandle OnFilterChanged_DelegateHandle;
};

void SDefault_PinTypeSelector::PreConstruct(const FArguments& InArgs, FGetPinTypeTree GetPinTypeTreeFunc)
{
	
	SearchText = FText::GetEmpty();

	ReadOnly = InArgs._ReadOnly;

	OnTypeChanged = InArgs._OnPinTypeChanged;
	OnTypePreChanged = InArgs._OnPinTypePreChanged;

	check(GetPinTypeTreeFunc.IsBound());
	GetPinTypeTree = GetPinTypeTreeFunc;

	Schema = InArgs._Schema;
	SchemaAction = InArgs._SchemaAction;
	TypeTreeFilter = InArgs._TypeTreeFilter;
	TreeViewWidth = InArgs._TreeViewWidth;
	TreeViewHeight = InArgs._TreeViewHeight;

	TargetPinType = InArgs._TargetPinType;
	SelectorType = InArgs._SelectorType;

	NumFilteredPinTypeItems = 0;

	if (InArgs._CustomFilters.Num() > 0)
	{
		for (const TSharedPtr<IPinTypeSelectorFilter>& Filter : InArgs._CustomFilters)
		{
			CustomFilters.Add(MakeShared<FPinTypeSelectorCustomFilterProxy>(Filter.ToSharedRef(), FSimpleDelegate::CreateSP(this, &SDefault_PinTypeSelector::OnCustomFilterChanged)));
		}
	}
	else if (InArgs._CustomFilter.IsValid())
	{
		CustomFilters.Add(MakeShared<FPinTypeSelectorCustomFilterProxy>(InArgs._CustomFilter.ToSharedRef(), FSimpleDelegate::CreateSP(this, &SDefault_PinTypeSelector::OnCustomFilterChanged)));
	}
	else if (UClass* PinTypeSelectorFilterClass = GetDefault<UPinTypeSelectorFilter>()->FilterClass.LoadSynchronous())
	{
		TSharedPtr<IPinTypeSelectorFilter> SelectorFilter = GetDefault<UPinTypeSelectorFilter>(PinTypeSelectorFilterClass)->GetPinTypeSelectorFilter();
		CustomFilters.Add(MakeShared<FPinTypeSelectorCustomFilterProxy>(SelectorFilter.ToSharedRef(), FSimpleDelegate::CreateSP(this, &SDefault_PinTypeSelector::OnCustomFilterChanged)));
	}

	bIsRightMousePressed = false;


	TypeComboButtonStyle = InArgs._TypeComboButtonStyle;
	if (!TypeComboButtonStyle)
	{
		TypeComboButtonStyle = &FAppStyle::Get().GetWidgetStyle<FComboButtonStyle>("ComboButton");
	}
	 
} 
void SDefault_PinTypeSelector::InConstruct(const FArguments& InArgs, FGetPinTypeTree GetPinTypeTreeFunc)
{
	// Depending on whether this is a full selector or not, we generate a different primary type image widget
	TSharedPtr<SWidget> PrimaryTypeImage;
	if (SelectorType == ESelectorType::Full)
	{
		// Full selector displays container and secondary type separately, so the main combo button should just have the primary icon
		PrimaryTypeImage =
			SNew(SImage)
			.Image(this, &SDefault_PinTypeSelector::GetTypeIconImage)
			.ColorAndOpacity(this, &SDefault_PinTypeSelector::GetTypeIconColor);
	}
	else
	{
		// Partial/compact selectors do not display container or secondary type separately, so we need to jam it all in the one image
		PrimaryTypeImage =
			SNew(
				SLayeredImage,
				TAttribute<const FSlateBrush*>(this, &SDefault_PinTypeSelector::GetSecondaryTypeIconImage),
				TAttribute<FSlateColor>(this, &SDefault_PinTypeSelector::GetSecondaryTypeIconColor)
			)
			.Image(this, &SDefault_PinTypeSelector::GetTypeIconImage)
			.ColorAndOpacity(this, &SDefault_PinTypeSelector::GetTypeIconColor);
	}

	// Depending on if this is a compact selector or not, we generate a different compound widget
	TSharedPtr<SWidget> Widget;
	const TSharedPtr<SWidget> ReadOnlyWidget = SNew(SHorizontalBox)
			.Clipping(EWidgetClipping::OnDemand)
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			.Padding(FMargin(2.0f, 3.0f, 2.0f, 3.0f))
			.AutoWidth()
			[
				// Read-only version does not display container or secondary type separately, so we need to jam it all in the one image
				SNew(SLayeredImage, TAttribute<const FSlateBrush*>(this, &SDefault_PinTypeSelector::GetSecondaryTypeIconImage), TAttribute<FSlateColor>(this, &SDefault_PinTypeSelector::GetSecondaryTypeIconColor))
				.Image(this, &SDefault_PinTypeSelector::GetTypeIconImage)
				.ColorAndOpacity(this, &SDefault_PinTypeSelector::GetTypeIconColor)
			]
			+ SHorizontalBox::Slot()
			.Padding(2.0f, 2.0f)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			.AutoWidth()
			[
				SNew(STextBlock)
				.Text(this, &SDefault_PinTypeSelector::GetTypeDescription, false)
				.Font(InArgs._Font)
				.ColorAndOpacity(FSlateColor::UseForeground())
			];

	if (SelectorType == ESelectorType::Compact)
	{
		// Only have a combo button with an icon
		Widget = SAssignNew( TypeComboButton, SComboButton )
			.OnGetMenuContent(this, &SDefault_PinTypeSelector::GetMenuContent, false)
			.ContentPadding(0.0f)
			.ToolTipText(this, &SDefault_PinTypeSelector::GetToolTipForComboBoxType)
			.HasDownArrow(false)
			.ButtonStyle(FAppStyle::Get(),  "BlueprintEditor.CompactPinTypeSelector")
			.ButtonContent()
			[
				PrimaryTypeImage.ToSharedRef()
			];
	}
	else if (SelectorType == ESelectorType::None)
	{
		Widget = ReadOnlyWidget;
	}
	else if (SelectorType == ESelectorType::Full || SelectorType == ESelectorType::Partial)
	{
		TSharedPtr<SWidget> ContainerControl;

		if(SelectorType == ESelectorType::Full)
		{
			// Traditional Pin Type Selector with a combo button, the icon, the current type name, and a toggle button for being an array
			ContainerControl = SNew(SComboButton)
				.ComboButtonStyle(FAppStyle::Get(),"BlueprintEditor.CompactVariableTypeSelector")
				.MenuPlacement(EMenuPlacement::MenuPlacement_ComboBoxRight)
				.OnGetMenuContent(this, &SDefault_PinTypeSelector::GetPinContainerTypeMenuContent)
				.ContentPadding(0.0f)
				.ToolTip(IDocumentation::Get()->CreateToolTip(TAttribute<FText>(this, &SDefault_PinTypeSelector::GetToolTipForContainerWidget), NULL, *PinTypeSelectorStatics::BigTooltipDocLink, TEXT("Containers")))
				.IsEnabled(TargetPinType.Get().PinCategory != UEdGraphSchema_K2::PC_Exec)
				.Visibility(InArgs._bAllowArrays ? EVisibility::Visible : EVisibility::Collapsed)
				.ButtonContent()
				[
					SNew(SLayeredImage, TAttribute<const FSlateBrush*>(this, &SDefault_PinTypeSelector::GetSecondaryTypeIconImage), TAttribute<FSlateColor>(this, &SDefault_PinTypeSelector::GetSecondaryTypeIconColor))
					.Image(this, &SDefault_PinTypeSelector::GetTypeIconImage)
					.ColorAndOpacity(this, &SDefault_PinTypeSelector::GetTypeIconColor)
				];
		}

		TSharedRef<SHorizontalBox> HBox = SNew(SHorizontalBox).Clipping(EWidgetClipping::ClipToBoundsAlways);
		Widget = HBox;

		const float FullComboButtonWidth = 125.f;

		HBox->AddSlot()
		.HAlign(HAlign_Left)
		[
			SNew(SBox)
			.WidthOverride(SelectorType == ESelectorType::Full ? FullComboButtonWidth : FOptionalSize())
			[
				SAssignNew(TypeComboButton, SComboButton)
				.ComboButtonStyle(TypeComboButtonStyle)
				.OnGetMenuContent(this, &SDefault_PinTypeSelector::GetMenuContent, false)
				.ContentPadding(InArgs._TypeComboButtonPadding)
				.ComboButtonStyle(FAppStyle::Get(), "ComboButton")
				.OnGetMenuContent(this, &SDefault_PinTypeSelector::GetMenuContent, false)
				.ContentPadding(0.0f)
				.ToolTipText(this, &SDefault_PinTypeSelector::GetToolTipForComboBoxType)
				.ForegroundColor(FSlateColor::UseForeground())
				.ButtonContent()
				[
					SNew(SHorizontalBox)
					.Clipping(EWidgetClipping::ClipToBoundsAlways)
					+ SHorizontalBox::Slot()
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Left)
					.Padding(0.0f, 0.0f, 0.0f, 0.0f)
					.AutoWidth()
					[
						PrimaryTypeImage.ToSharedRef()
					]
					+ SHorizontalBox::Slot()
					.Padding(InArgs._TypeComboButtonContentSpacing, 0.0f, 0.0f, 0.0f)
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Left)
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text(this, &SDefault_PinTypeSelector::GetTypeDescription, false)
						.Font(InArgs._Font)
						.ColorAndOpacity(FSlateColor::UseForeground())
					]
				]
			]
		];

		if(SelectorType == ESelectorType::Full)
		{
			HBox->AddSlot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Center)
				.Padding(2.0f)
				[
					ContainerControl.ToSharedRef()
				];
	
			HBox->AddSlot()
			[
				SNew(SBox)
				.WidthOverride(FullComboButtonWidth)
				.Visibility_Lambda([this]() {return this->TargetPinType.Get().IsMap() == true ? EVisibility::Visible : EVisibility::Collapsed; })
				[
					SAssignNew( SecondaryTypeComboButton, SComboButton )
					.OnGetMenuContent(this, &SDefault_PinTypeSelector::GetMenuContent, true )
					.ContentPadding(0.0f)
					.ToolTipText(this, &SDefault_PinTypeSelector::GetToolTipForComboBoxSecondaryType)
					.ButtonContent()
					[
						SNew(SHorizontalBox)
						.Clipping(EWidgetClipping::OnDemand)
						+SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Left)
						.Padding(0.0f, 0.0f, 2.0f, 0.0f)
						[
							SNew(SImage)
							.Image( this, &SDefault_PinTypeSelector::GetSecondaryTypeIconImage )
							.ColorAndOpacity( this, &SDefault_PinTypeSelector::GetSecondaryTypeIconColor )
						]
						+SHorizontalBox::Slot()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Left)
						.Padding(2.0f, 0.0f, 0.0f, 0.0f)
						[
							SNew(STextBlock)
							.Text(this, &SDefault_PinTypeSelector::GetSecondaryTypeDescription, false)
							.Font(InArgs._Font)
						]
					]
				]
			];
		}
	}


	this->ChildSlot
	[
		SNew(SWidgetSwitcher)
		.WidgetIndex_Lambda([this](){return ReadOnly.Get() ? 1 : 0; })
		+ SWidgetSwitcher::Slot() // editable version
		.Padding(SelectorType == ESelectorType::Partial ? FMargin(-6.0f, 0.0f,0.0f,0.0f) : FMargin(0))
		[
			Widget.ToSharedRef()
		]
		+ SWidgetSwitcher::Slot() // read-only version
		[
			ReadOnlyWidget.ToSharedRef()
		]	
	];
} 
void SDefault_PinTypeSelector::PostConstruct(const FArguments& InArgs, FGetPinTypeTree GetPinTypeTreeFunc)
{
}
#undef LOCTEXT_NAMESPACE