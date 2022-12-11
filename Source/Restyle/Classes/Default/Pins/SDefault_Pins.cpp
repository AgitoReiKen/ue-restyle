// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_Pins.h"

#include "ClassViewerFilter.h"
#include "ClassViewerModule.h"
#include "ContentBrowserModule.h"

#include "Themes/Default/PinRestyleDefault.h"

#include "Widgets/Input/SNumericEntryBox.h"

#include "EdGraphSchema_K2.h"
#include "IContentBrowserSingleton.h"

#include "Restyle/Classes/Default/Widgets/SDefault_PinTypeSelector.h"
#include "SKeySelector.h"
#include "SNameComboBox.h"
#include "Selection.h"
#include "StructViewerFilter.h"
#include "StructViewerModule.h"

#include "AssetRegistry/AssetRegistryModule.h"

#include "Engine/UserDefinedStruct.h"

#include "MaterialGraph/MaterialGraph.h"
#include "MaterialGraph/MaterialGraphSchema.h"

#include "Misc/OutputDeviceNull.h"

#include "Styling/StyleColors.h"

#include "Widgets/Colors/SColorPicker.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Notifications/SPopUpErrorText.h"
#include "SSimpleComboButton.h"
#include "Internationalization/TextNamespaceUtil.h"
#include "GraphEditorSettings.h"

#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetDebugUtilities.h"
//
//void SDefault_ControlRigGraphPinCurveFloat::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_ControlRigGraphPinNameList::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_ControlRigGraphPinParameterName::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_ControlRigGraphPinVariableBinding::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_ControlRigGraphPinVariableName::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_LiveLinkSubjectNameGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_LiveLinkSubjectRepresentationGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_PrimaryAssetIdGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_PrimaryAssetTypeGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_GameplayTagQueryGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_NiagaraGraphPinNumeric::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_NiagaraGraphPinAdd::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_DataRegistryTypeGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_GameplayAttributeGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_DMXEntityReferenceGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_DynamicNameListGraphPin<TStructType>::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_NullGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_DMXPixelMappingComponentPin<TComponentClass>::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_DMXInputPortReferenceGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_DMXOutputPortReferenceGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_GraphPinAI::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_GraphPinPose::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_StateMachineOutputPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_MotionControllerSourceGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_CopyNodeGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
#include "AnimGraphNode_Base.h"
#include "SGraphPanel.h"
#include "SLevelOfDetailBranchNode.h"

#pragma region GraphPin
void SDefault_GraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	check(InGraphPinObj != NULL);

	const UGraphEditorSettings* GraphSettings = GetDefault<UGraphEditorSettings>();
	const auto& Style = UPinRestyleSettings::Get()->Base;
	const float Spacing = UDefaultThemeSettings::GetSpacing(Style.Spacing);

	bUsePinColorForText = InArgs._UsePinColorForText;
	GraphPinObj = InGraphPinObj;
	SetCursor(EMouseCursor::Default);
	SetVisibility(MakeAttributeSP(this, &SDefault_GraphPin::GetPinVisiblity));

	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	checkf(
		Schema,
		TEXT("Missing schema for pin: %s with outer: %s of type %s" ),
		*(GraphPinObj->GetName()),
		GraphPinObj->GetOuter() ? *(GraphPinObj->GetOuter()->GetName()) : TEXT("NULL OUTER"),
		GraphPinObj->GetOuter() ? *(GraphPinObj->GetOuter()->GetClass()->GetName()) : TEXT("NULL OUTER")
	);

	// Colors
	{
		FLinearColor NonEditableMod = FLinearColor(1, 1, 1, Style.NonEditableOpacity);

		NormalColor = Style.NormalColor.Get();
		DiffingColor = Style.DiffingColor.Get();
		OrphanedColor = Style.OrphanedColor.Get();

		NonEditableNormalColor = NormalColor.GetSpecifiedColor() * NonEditableMod;
		NonEditableDiffingColor = DiffingColor.GetSpecifiedColor() * NonEditableMod;
		NonEditableOrphanedColor = OrphanedColor.GetSpecifiedColor() * NonEditableMod;

		PinTypeColor = Schema->GetPinTypeColor(GraphPinObj->PinType);
		NonEditablePinTypeColor = PinTypeColor * NonEditableMod;
		SecPinTypeColor = Schema->GetSecondaryPinTypeColor(GraphPinObj->PinType);
		NonEditableSecPinTypeColor = SecPinTypeColor * NonEditableMod;
	}

	// Create the pin icon widget
	TSharedRef<SWidget> PinWidgetRef = SPinTypeSelector::ConstructPinTypeImage(
		MakeAttributeSP(this, &SDefault_GraphPin::GetPinIcon),
		MakeAttributeSP(this, &SDefault_GraphPin::GetPinColor),
		MakeAttributeSP(this, &SDefault_GraphPin::GetSecondaryPinIcon_New),
		MakeAttributeSP(this, &SDefault_GraphPin::GetSecondaryPinColor_New));
	PinImage = PinWidgetRef;

	PinWidgetRef->SetCursor(
		TAttribute<TOptional<EMouseCursor::Type>>::Create(
			TAttribute<TOptional<EMouseCursor::Type>>::FGetter::CreateRaw(this, &SDefault_GraphPin::GetPinCursor)
		)
	);

	// Create the pin indicator widget (used for watched values)
	TSharedRef<SWidget> PinStatusIndicator =
		SNew(SButton)
		.ButtonStyle(FAppStyle::Get(), "NoBorder")
		.Visibility(this, &SDefault_GraphPin::GetPinStatusIconVisibility)
		.ContentPadding(0)
		.OnClicked(this, &SDefault_GraphPin::ClickedOnPinStatusIcon)
		[
			SNew(SImage)
			.Image(this, &SDefault_GraphPin::GetPinStatusIcon)
		];
	TSharedRef<SWidget> LabelWidget = GetLabelWidget(InArgs._PinLabelStyle);

	// Create the widget used for the pin body (status indicator, label, and value)
	LabelAndValue = SNew(SWrapBox).PreferredSize(Style.PreferredWrapSize);
	TSharedPtr<SWrapBox> LowLodContent = SNew(SWrapBox).PreferredSize(Style.PreferredWrapSize);
	TSharedPtr<SHorizontalBox> LowLodBox = SNew(SHorizontalBox);
	TSharedPtr<SHorizontalBox> HighLodBox = SNew(SHorizontalBox);
	if (GetDirection() == EGPD_Input)
	{
		/* Low LOD*/
		{
			LowLodContent->AddSlot()
			             .VAlign(VAlign_Center)
			             .Padding(0, 0, Spacing, 0)
			[
				LabelWidget
			];
			LowLodContent->AddSlot()
			             .VAlign(VAlign_Center)
			[
				PinStatusIndicator
			];
			// Input pin
			LowLodBox->AddSlot()
			         .AutoWidth()
			         .VAlign(VAlign_Center)
			         .Padding(0, 0, Spacing, 0)
			[
				PinWidgetRef
			];
			LowLodBox->AddSlot()
			         .AutoWidth()
			         .VAlign(VAlign_Center)
			[
				LowLodContent.ToSharedRef()
			];
		}
		/* High LOD */
		{
			LabelAndValue->AddSlot()
			             .VAlign(VAlign_Center)
			             .Padding(0, 0, Spacing, 0)
			[
				LabelWidget
			];

			ValueWidget = GetDefaultValueWidget();

			if (ValueWidget != SNullWidget::NullWidget)
			{
				TSharedPtr<SBox> ValueBox;
				LabelAndValue->AddSlot()
				             .Padding(0)
				             .VAlign(VAlign_Center)
				[
					SAssignNew(ValueBox, SBox)
					.Padding(0.0f)
					[
						ValueWidget.ToSharedRef()
					]
				];

				if (!DoesWidgetHandleSettingEditingEnabled())
				{
					ValueBox->SetEnabled(TAttribute<bool>(this, &SGraphPin::IsEditingEnabled));
				}
			}

			LabelAndValue->AddSlot()
			             .VAlign(VAlign_Center)
			[
				PinStatusIndicator
			];

			FullPinHorizontalRowWidget = HighLodBox =
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				  .Padding(0, 0, Spacing, 0)
				[
					PinWidgetRef
				]
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				[
					LabelAndValue.ToSharedRef()
				];
		}
	}
	else
	{
		/* Low LOD*/
		{
			LowLodContent->AddSlot()
			             .VAlign(VAlign_Center)
			[
				PinStatusIndicator
			];
			LowLodContent->AddSlot()
			             .VAlign(VAlign_Center)
			             .Padding(0, 0, Spacing, 0)
			[
				LabelWidget
			];
			LowLodBox->AddSlot()
			         .AutoWidth()
			         .VAlign(VAlign_Center)
			[
				LowLodContent.ToSharedRef()
			];
			LowLodBox->AddSlot()
			         .AutoWidth()
			         .VAlign(VAlign_Center)
			         .Padding(Spacing, 0, 0, 0)
			[
				PinWidgetRef
			];
		}
		/* High LOD */
		{
			LabelAndValue->AddSlot()
			             .VAlign(VAlign_Center)
			[
				PinStatusIndicator
			];

			LabelAndValue->AddSlot()
			             .VAlign(VAlign_Center)
			[
				LabelWidget
			];
			// Output pin
			FullPinHorizontalRowWidget = HighLodBox = SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				[
					LabelAndValue.ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				  .Padding(Spacing, 0, 0, 0)
				[
					PinWidgetRef
				];
		}
	}
	// Set up a hover for pins that is tinted the color of the pin.
	SBorder::Construct(SBorder::FArguments()
		//.BorderImage(this, &SGraphPin::GetPinBorder)
	                   .BorderImage(FAppStyle::GetBrush("NoBorder"))
	                   .Padding(0)
	                   .OnMouseButtonDown(this, &SDefault_GraphPin::OnPinNameMouseDown)
		[
			SNew(SBorder)
			.BorderImage(CachedImg_Pin_DiffOutline)
			.BorderBackgroundColor(this, &SDefault_GraphPin::GetPinDiffColor)
			.Padding(0)
			[
				SNew(SLevelOfDetailBranchNode)
				.UseLowDetailSlot(this, &SDefault_GraphPin::UseLowDetailPinNames)
				.LowDetail()
				[
					LowLodBox.ToSharedRef()
				]
				.HighDetail()
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					.Padding(FMargin(-GraphSettings->PaddingTowardsNodeEdge, 0))
					[
						SNew(SBorder)
					.BorderImage(this, &SDefault_GraphPin::GetPinBorder)
					.BorderBackgroundColor(this, &SDefault_GraphPin::GetPinColor)

					]
					+ SOverlay::Slot()
					.Padding(0)
					[
						SNew(SBox)
						.MinDesiredHeight(Style.MinDesiredHeight)
						[
							HighLodBox.ToSharedRef()
						]
					]
				]
			]
		]);

	TSharedPtr<IToolTip> TooltipWidget = SNew(SToolTip)
		.Text(this, &SDefault_GraphPin::GetTooltipText);

	SetToolTip(TooltipWidget);
}

SDefault_GraphPin::SDefault_GraphPin() : SGraphPin()
{
	CachedImg_SetPin_Connected = FAppStyle::GetBrush(
		FPinRestyleStyles::Kismet_VariableList_SetTypeIcon_Connected);
	CachedImg_SetPin_Disconnected = FAppStyle::GetBrush(
		FPinRestyleStyles::Kismet_VariableList_SetTypeIcon_Disconnected);
	CachedImg_MapPin_Value_Connected = FAppStyle::GetBrush(
		FPinRestyleStyles::Kismet_VariableList_MapValueTypeIcon_Connected);
	CachedImg_MapPin_Value_Disconnected = FAppStyle::GetBrush(
		FPinRestyleStyles::Kismet_VariableList_MapValueTypeIcon_Disconnected);
	CachedImg_WatchedPinIcon = FAppStyle::GetBrush(TEXT("Graph.WatchedPinIcon_Pinned"));

}

FSlateColor SDefault_GraphPin::GetPinTextColor() const
{
	UEdGraphPin* GraphPin = GetPinObj();
	// If there is no schema there is no owning node (or basically this is a deleted node)
	if (UEdGraphNode* GraphNode = GraphPin ? GraphPin->GetOwningNodeUnchecked() : nullptr)
	{
		const bool bDisabled = (!GraphNode->IsNodeEnabled() || GraphNode->IsDisplayAsDisabledForced() || !IsEditingEnabled() || GraphNode->IsNodeUnrelated());
		if (GraphPin->bOrphanedPin)
		{ 
			return bDisabled ? NonEditableOrphanedColor : OrphanedColor;
		}
		if (bDisabled)
		{
			return NonEditableNormalColor;
		}
		if (bUsePinColorForText)
		{
			return GetPinColor();
		}
	}
	return NormalColor;
}

const FSlateBrush* SDefault_GraphPin::GetPinIcon() const
{
	UEdGraphPin* GraphPin = GetPinObj();
	if (!GraphPin || GraphPin->IsPendingKill() || !GraphPin->GetOwningNodeUnchecked())
	{
		return CachedImg_Pin_Disconnected;
	}
	if (IsSet())
	{
		return IsConnected() ? CachedImg_SetPin_Connected : CachedImg_SetPin_Disconnected;
	}
	return SGraphPin::GetPinIcon();
}

FSlateColor SDefault_GraphPin::GetPinColor() const
{
	UEdGraphPin* GraphPin = GetPinObj();
	if (GraphPin && !GraphPin->IsPendingKill())
	{
		if (GraphPin->bOrphanedPin)
		{
			return IsEditingEnabled() ? OrphanedColor : NonEditableOrphanedColor;
		}
		if (bIsDiffHighlighted)
		{
			return IsEditingEnabled() ? DiffingColor : NonEditableDiffingColor;
		}
		if (const UEdGraphSchema* Schema = GraphPin->GetSchema())
		{
			const bool bDisabled = !GetPinObj()->GetOwningNode()->IsNodeEnabled() || GetPinObj()->GetOwningNode()->IsDisplayAsDisabledForced() || !IsEditingEnabled() || GetPinObj()->GetOwningNode()->IsNodeUnrelated();

			return (!bDisabled ? PinTypeColor : NonEditablePinTypeColor) * PinColorModifier;
		}
	}

	return IsEditingEnabled() ? NormalColor : NonEditableNormalColor;
}

const FSlateBrush* SDefault_GraphPin::GetSecondaryPinIcon_New() const
{
	UEdGraphPin* GraphPin = GetPinObj();
	if (GraphPin && !GraphPin->IsPendingKill())
	{
		if (IsMap())
		{
			return IsConnected() ? CachedImg_MapPin_Value_Connected : CachedImg_MapPin_Value_Disconnected;
		}
	}
	return nullptr;
}

FSlateColor SDefault_GraphPin::GetSecondaryPinColor_New() const
{
	UEdGraphPin* GraphPin = GetPinObj();
	if (GraphPin && !GraphPin->IsPendingKill())
	{
		return (IsEditingEnabled() ? SecPinTypeColor : NonEditableSecPinTypeColor) * PinColorModifier;
	}
	// use same color if invalid
	return GetPinColor();
}

TSharedRef<SWidget> SDefault_GraphPin::GetLabelWidget(const FName& InPinLabelStyle)
{
	return SNew(STextBlock)
		//.Text(this, &SDefault_GraphPin::GetPinLabel)
		.Text(GetPinLabel())
		.TextStyle(FAppStyle::Get(), InPinLabelStyle)
		.Visibility(this, &SDefault_GraphPin::GetPinLabelVisibility)
		.ColorAndOpacity(this, &SDefault_GraphPin::GetPinTextColor);
}

const FSlateBrush* SDefault_GraphPin::GetPinStatusIcon() const
{
	UEdGraphPin* GraphPin = GetPinObj();
	if (GraphPin && !GraphPin->IsPendingKill())
	{
		UEdGraphPin* WatchedPin = ((GraphPin->Direction == EGPD_Input) && (GraphPin->LinkedTo.Num() > 0))
			                          ? GraphPin->LinkedTo[0]
			                          : GraphPin;

		if (UEdGraphNode* GraphNode = WatchedPin->GetOwningNodeUnchecked())
		{
			UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForNodeChecked(GraphNode);

			if (FKismetDebugUtilities::DoesPinHaveWatches(Blueprint, WatchedPin))
			{
				return CachedImg_WatchedPinIcon;
			}
		}
	}

	return nullptr;
}
#pragma endregion

#pragma region ComboBox

#pragma endregion

#pragma region CollisionProfile

void SDefault_GraphPinCollisionProfile::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}


TSharedRef<SWidget> SDefault_GraphPinCollisionProfile::GetDefaultValueWidget()
{
	UCollisionProfile::GetProfileNames(NameList);

	TSharedPtr<FName> InitialSelectedName = GetSelectedName();
	if (InitialSelectedName.IsValid())
	{
		SetPropertyWithName(*InitialSelectedName.Get());
	}
	const auto& Select = UPinRestyleSettings::Get()->Inputs.Select;
	const auto& ComboButton = Select.Get().ComboButton.Get();
	const auto& Button = ComboButton.Button.Get();
	FMargin ButtonTextPadding = UDefaultThemeSettings::GetMargin(Button.Padding);
	//FLinearColor Color = Button.NormalForeground.Get();
	float SpacingBetweenTextAndArrow = UDefaultThemeSettings::GetSpacing(ComboButton.DownArrowSpacing);
	return SAssignNew(NameComboBox, SDefault_NameComboBox)
		.ItemStyle(FAppStyle::Get(), FPinRestyleStyles::ComboBox_Row)
		.Font(FAppStyle::Get().GetFontStyle(FPinRestyleStyles::ComboBox_Button_FontInfo))
		//.ColorAndOpacity(Color)
		.ButtonTextPadding(ButtonTextPadding)
		.ComboBoxStyle(FAppStyle::Get(), FPinRestyleStyles::ComboBox)
		.OptionsSource(&NameList)
		.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
		.InitiallySelectedItem(InitialSelectedName)
		.OnSelectionChanged(this, &SDefault_GraphPinCollisionProfile::OnSelectionChanged)
		.OnComboBoxOpening(this, &SDefault_GraphPinCollisionProfile::OnComboBoxOpening)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		.SpacingBetweenTextAndArrow(SpacingBetweenTextAndArrow);
}


void SDefault_GraphPinCollisionProfile::OnSelectionChanged(TSharedPtr<FName> NameItem, ESelectInfo::Type SelectInfo)
{
	if (NameItem.IsValid())
	{
		SetPropertyWithName(*NameItem);
	}
}


void SDefault_GraphPinCollisionProfile::OnComboBoxOpening()
{
	TSharedPtr<FName> SelectedName = GetSelectedName();
	if (SelectedName.IsValid())
	{
		check(NameComboBox.IsValid());
		NameComboBox->SetSelectedItem(SelectedName);
	}
}


TSharedPtr<FName> SDefault_GraphPinCollisionProfile::GetSelectedName() const
{
	int32 NameCount = NameList.Num();
	if (NameCount <= 0)
	{
		return NULL;
	}

	FName Name;
	GetPropertyAsName(Name);

	for (int32 NameIndex = 0; NameIndex < NameCount; ++NameIndex)
	{
		if (Name == *NameList[NameIndex].Get())
		{
			return NameList[NameIndex];
		}
	}

	return NameList[0];
}


void SDefault_GraphPinCollisionProfile::SetPropertyWithName(const FName& Name)
{
	check(GraphPinObj);
	check(GraphPinObj->PinType.PinSubCategoryObject == FCollisionProfileName::StaticStruct());

	FString PinString = TEXT("(Name=\"");
	PinString += *Name.ToString();
	PinString += TEXT("\")");

	if (GraphPinObj->GetDefaultAsString() != PinString)
	{
		const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeCollisionProfilePinValue",
		                                               "Change Collision Profile Pin Value"));
		GraphPinObj->Modify();

		if (PinString != GraphPinObj->GetDefaultAsString())
		{
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, PinString);
		}
	}
}


void SDefault_GraphPinCollisionProfile::GetPropertyAsName(FName& OutName) const
{
	check(GraphPinObj);
	check(GraphPinObj->PinType.PinSubCategoryObject == FCollisionProfileName::StaticStruct());

	FString PinString = GraphPinObj->GetDefaultAsString();

	if (PinString.StartsWith(TEXT("("), ESearchCase::CaseSensitive) && PinString.EndsWith(
		TEXT(")"), ESearchCase::CaseSensitive))
	{
		PinString.LeftChopInline(1, false);
		PinString.RightChopInline(1, false);
		PinString.Split(TEXT("="), nullptr, &PinString, ESearchCase::CaseSensitive);

		if (PinString.StartsWith(TEXT("\""), ESearchCase::CaseSensitive) && PinString.EndsWith(
			TEXT("\""), ESearchCase::CaseSensitive))
		{
			PinString.LeftChopInline(1, false);
			PinString.RightChopInline(1, false);
		}
	}

	if (!PinString.IsEmpty())
	{
		OutName = *PinString;

		UCollisionProfile* CollisionProfile = UCollisionProfile::Get();
		check(CollisionProfile);

		const FName* RedirectName = CollisionProfile->LookForProfileRedirect(OutName);
		if (RedirectName)
		{
			OutName = *RedirectName;
		}
	}
}

#pragma endregion

#pragma region Integer

void SDefault_GraphPinInteger::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPinNum<int32>::Construct(SDefault_GraphPinNum<int32>::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SDefault_GraphPinInteger::GetDefaultValueWidget()
{
	check(GraphPinObj);

	const FName PinSubCategory = GraphPinObj->PinType.PinSubCategory;
	const UEnum* BitmaskEnum = Cast<UEnum>(GraphPinObj->PinType.PinSubCategoryObject.Get());

	if (PinSubCategory == UEdGraphSchema_K2::PSC_Bitmask)
	{
		struct BitmaskFlagInfo
		{
			int32 Value;
			FText DisplayName;
			FText ToolTipText;
		};

		const int32 BitmaskBitCount = sizeof(int32) << 3;

		TArray<BitmaskFlagInfo> BitmaskFlags;
		BitmaskFlags.Reserve(BitmaskBitCount);

		if (BitmaskEnum)
		{
			const bool bUseEnumValuesAsMaskValues = BitmaskEnum->GetBoolMetaData(
				FBlueprintMetadata::MD_UseEnumValuesAsMaskValuesInEditor);
			auto AddNewBitmaskFlagLambda = [BitmaskEnum, &BitmaskFlags](int32 InEnumIndex, int32 InFlagValue)
			{
				BitmaskFlagInfo* BitmaskFlag = new(BitmaskFlags) BitmaskFlagInfo();

				BitmaskFlag->Value = InFlagValue;
				BitmaskFlag->DisplayName = BitmaskEnum->GetDisplayNameTextByIndex(InEnumIndex);
				BitmaskFlag->ToolTipText = BitmaskEnum->GetToolTipTextByIndex(InEnumIndex);
				if (BitmaskFlag->ToolTipText.IsEmpty())
				{
					BitmaskFlag->ToolTipText = FText::Format(
						NSLOCTEXT("GraphEditor", "BitmaskDefaultFlagToolTipText", "Toggle {0} on/off"),
						BitmaskFlag->DisplayName);
				}
			};

			// Note: This loop doesn't include (BitflagsEnum->NumEnums() - 1) in order to skip the implicit "MAX" value that gets added to the enum type at compile time.
			for (int32 BitmaskEnumIndex = 0; BitmaskEnumIndex < BitmaskEnum->NumEnums() - 1; ++BitmaskEnumIndex)
			{
				const int64 EnumValue = BitmaskEnum->GetValueByIndex(BitmaskEnumIndex);
				const bool bIsHidden = BitmaskEnum->HasMetaData(TEXT("Hidden"), BitmaskEnumIndex);
				if (EnumValue >= 0 && !bIsHidden)
				{
					if (bUseEnumValuesAsMaskValues)
					{
						if (EnumValue < MAX_int32 && FMath::IsPowerOfTwo(EnumValue))
						{
							AddNewBitmaskFlagLambda(BitmaskEnumIndex, static_cast<int32>(EnumValue));
						}
					}
					else if (EnumValue < BitmaskBitCount)
					{
						AddNewBitmaskFlagLambda(BitmaskEnumIndex, 1 << static_cast<int32>(EnumValue));
					}
				}
			}
		}
		else
		{
			for (int BitmaskFlagIndex = 0; BitmaskFlagIndex < BitmaskBitCount; ++BitmaskFlagIndex)
			{
				BitmaskFlagInfo* BitmaskFlag = new(BitmaskFlags) BitmaskFlagInfo();

				BitmaskFlag->Value = static_cast<int32>(1 << BitmaskFlagIndex);
				BitmaskFlag->DisplayName = FText::Format(
					NSLOCTEXT("GraphEditor", "BitmaskDefaultFlagDisplayName", "Flag {0}"),
					FText::AsNumber(BitmaskFlagIndex + 1));
				BitmaskFlag->ToolTipText = FText::Format(
					NSLOCTEXT("GraphEditor", "BitmaskDefaultFlagToolTipText", "Toggle {0} on/off"),
					BitmaskFlag->DisplayName);
			}
		}

		const auto& GetComboButtonText = [this, BitmaskFlags]() -> FText
		{
			int32 BitmaskValue = FCString::Atoi(*GraphPinObj->GetDefaultAsString());
			if (BitmaskValue != 0)
			{
				if (BitmaskValue & (BitmaskValue - 1))
				{
					return NSLOCTEXT("GraphEditor", "BitmaskButtonContentMultipleBitsSet", "(Multiple)");
				}
				else
				{
					for (int i = 0; i < BitmaskFlags.Num(); ++i)
					{
						if (BitmaskValue & BitmaskFlags[i].Value)
						{
							return BitmaskFlags[i].DisplayName;
						}
					}
				}
			}

			return NSLOCTEXT("GraphEditor", "BitmaskButtonContentNoFlagsSet", "(No Flags)");
		};

		const auto& Style = UPinRestyleSettings::Get()->Inputs.Select.Get();
		const auto& ComboButton = Style.ComboButton.Get();
		const auto& Button = ComboButton.Button.Get();
		FMargin ContentPadding = UDefaultThemeSettings::GetMargin(Button.Padding);

		return SNew(SComboButton)
			.ContentPadding(ContentPadding)
			.ComboButtonStyle(FAppStyle::Get(), FPinRestyleStyles::ComboButton)
			.MenuPlacement(MenuPlacement_BelowAnchor)
			.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
			.ForegroundColor(FSlateColor::UseStyle())
			.HasDownArrow(ComboButton.bHasDownArrow)
			.ButtonContent()
			[
				// Wrap in configurable box to restrain height/width of menu
				SNew(SBox)
				.MinDesiredWidth(84.0f)
				[
					SNew(STextBlock)
					.TextStyle(FAppStyle::Get(), FPinRestyleStyles::ComboButton_Text)
					.ColorAndOpacity(FSlateColor::UseStyle())
					.Text_Lambda(GetComboButtonText)
					.Font(FAppStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")))
				]
			]
			.OnGetMenuContent_Lambda([this, BitmaskFlags]()
			{
				FMenuBuilder MenuBuilder(false, nullptr);

				for (int i = 0; i < BitmaskFlags.Num(); ++i)
				{
					MenuBuilder.AddMenuEntry(
						BitmaskFlags[i].DisplayName,
						BitmaskFlags[i].ToolTipText,
						FSlateIcon(),
						FUIAction
						(
							FExecuteAction::CreateLambda([=]()
							{
								const FScopedTransaction Transaction(
									NSLOCTEXT("GraphEditor", "ChangePinValue", "Change Pin Value"));
								const int32 CurValue = FCString::Atoi(*GraphPinObj->GetDefaultAsString());
								GraphPinObj->Modify();
								GraphPinObj->GetSchema()->TrySetDefaultValue(
									*GraphPinObj, FString::FromInt(CurValue ^ BitmaskFlags[i].Value));
							}),
							FCanExecuteAction(),
							FIsActionChecked::CreateLambda([=]() -> bool
							{
								const int32 CurValue = FCString::Atoi(*GraphPinObj->GetDefaultAsString());
								return (CurValue & BitmaskFlags[i].Value) != 0;
							})
						),
						NAME_None,
						EUserInterfaceActionType::Check);
				}

				return MenuBuilder.MakeWidget();
			});
	}

	return SDefault_GraphPinNum<int32>::GetDefaultValueWidget();
}
#pragma endregion

#pragma region Class

void SDefault_GraphPinClass::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
	bAllowAbstractClasses = true;
}

#define LOCTEXT_NAMESPACE "SGraphPinClass"

FReply SDefault_GraphPinClass::OnClickUse()
{
	FEditorDelegates::LoadSelectedAssetsIfNeeded.Broadcast();

	if (GraphPinObj && GraphPinObj->GetSchema())
	{
		const UClass* PinRequiredParentClass = Cast<const UClass>(GraphPinObj->PinType.PinSubCategoryObject.Get());
		ensure(PinRequiredParentClass);

		const UClass* SelectedClass = GEditor->GetFirstSelectedClass(PinRequiredParentClass);
		if (SelectedClass)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeClassPinValue",
			                                               "Change Class Pin Value"));
			GraphPinObj->Modify();

			GraphPinObj->GetSchema()->TrySetDefaultObject(*GraphPinObj, const_cast<UClass*>(SelectedClass));
		}
	}

	return FReply::Handled();
}

class FGraphPinFilter : public IClassViewerFilter
{
public:
	/** Package containing the graph pin */
	const UPackage* GraphPinOutermostPackage;

	/** All children of these classes will be included unless filtered out by another setting. */
	TSet<const UClass*> AllowedChildrenOfClasses;

	const UClass* RequiredInterface = nullptr;

	bool bAllowAbstractClasses = true;

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass,
	                            TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		// If it appears on the allowed child-of classes list (or there is nothing on that list)
		bool Result = (InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) !=
			EFilterReturn::Failed);
		if (Result)
		{
			check(InClass != nullptr);
			const UPackage* ClassPackage = InClass->GetOutermost();
			check(ClassPackage != nullptr);

			// Don't allow classes from a loaded map (e.g. LSBPs) unless we're already working inside that package context. Otherwise, choosing the class would lead to a GLEO at save time.
			Result &= !ClassPackage->ContainsMap() || ClassPackage == GraphPinOutermostPackage;
			Result &= !InClass->HasAnyClassFlags(CLASS_Hidden | CLASS_HideDropDown);
			Result &= bAllowAbstractClasses || !InClass->HasAnyClassFlags(CLASS_Abstract);
			// either there is not a required interface, or our target class DOES implement that interface
			Result &= (RequiredInterface == nullptr || InClass->ImplementsInterface(RequiredInterface));
		}

		return Result;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions,
	                                    const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData,
	                                    TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		return (InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) !=
				EFilterReturn::Failed)
			&& (!InUnloadedClassData->HasAnyClassFlags(CLASS_Hidden | CLASS_HideDropDown))
			&& (bAllowAbstractClasses || !InUnloadedClassData->HasAnyClassFlags(CLASS_Abstract))
			// either there is not a required interface, or our target class DOES implement that interface
			&& (RequiredInterface == nullptr || InUnloadedClassData->ImplementsInterface(RequiredInterface));
	}
};

TSharedRef<SWidget> SDefault_GraphPinClass::GenerateAssetPicker()
{
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	// Fill in options
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.bShowNoneOption = true;

	// Get the min. spec for the classes allowed
	const UClass* PinRequiredParentClass = Cast<const UClass>(GraphPinObj->PinType.PinSubCategoryObject.Get());
	ensure(PinRequiredParentClass);
	if (PinRequiredParentClass == NULL)
	{
		PinRequiredParentClass = UObject::StaticClass();
	}

	TSharedPtr<FGraphPinFilter> Filter = MakeShareable(new FGraphPinFilter);
	Filter->bAllowAbstractClasses = bAllowAbstractClasses;

	// Check with the node to see if there is any "AllowAbstract" metadata for the pin
	FString AllowAbstractString = GraphPinObj->GetOwningNode()->GetPinMetaData(
		GraphPinObj->PinName, FBlueprintMetadata::MD_AllowAbstractClasses);

	// Override bAllowAbstractClasses is the AllowAbstract metadata was set
	if (!AllowAbstractString.IsEmpty())
	{
		Filter->bAllowAbstractClasses = AllowAbstractString.ToBool();
	}

	Options.ClassFilters.Add(Filter.ToSharedRef());

	Filter->AllowedChildrenOfClasses.Add(PinRequiredParentClass);
	Filter->GraphPinOutermostPackage = GraphPinObj->GetOuter()->GetOutermost();

	if (UEdGraphNode* ParentNode = GraphPinObj->GetOwningNode())
	{
		FString PossibleInterface = ParentNode->GetPinMetaData(GraphPinObj->PinName, TEXT("MustImplement"));
		if (!PossibleInterface.IsEmpty())
		{
			Filter->RequiredInterface = UClass::TryFindTypeSlow<UClass>(PossibleInterface);
		}
	}

	return
		SNew(SBox)
		.WidthOverride(280)
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			  .FillHeight(1.0f)
			  .MaxHeight(500)
			[
				SNew(SBorder)
			.Padding(4)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
				[
					ClassViewerModule.CreateClassViewer(
						Options, FOnClassPicked::CreateSP(this, &SDefault_GraphPinClass::OnPickedNewClass))
				]
			]
		];
}

FOnClicked SDefault_GraphPinClass::GetOnUseButtonDelegate()
{
	return FOnClicked::CreateSP(this, &SDefault_GraphPinClass::OnClickUse);
}

void SDefault_GraphPinClass::OnPickedNewClass(UClass* ChosenClass)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	FString NewPath;
	if (ChosenClass)
	{
		NewPath = ChosenClass->GetPathName();
	}

	if (GraphPinObj->GetDefaultAsString() != NewPath)
	{
		const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeClassPinValue", "Change Class Pin Value"));
		GraphPinObj->Modify();

		AssetPickerAnchor->SetIsOpen(false);
		GraphPinObj->GetSchema()->TrySetDefaultObject(*GraphPinObj, ChosenClass);
	}
}

FText SDefault_GraphPinClass::GetDefaultComboText() const
{
	return LOCTEXT("DefaultComboText", "Select Class");
}

const FAssetData& SDefault_GraphPinClass::GetAssetData(bool bRuntimePath) const
{
	if (bRuntimePath)
	{
		// For runtime use the default path
		return SDefault_GraphPinObject::GetAssetData(bRuntimePath);
	}

	FString CachedRuntimePath = CachedEditorAssetData.GetObjectPathString() + TEXT("_C");

	if (GraphPinObj->DefaultObject)
	{
		if (!GraphPinObj->DefaultObject->GetPathName().Equals(CachedRuntimePath, ESearchCase::CaseSensitive))
		{
			// This will cause it to use the UBlueprint
			CachedEditorAssetData = FAssetData(GraphPinObj->DefaultObject, false);
		}
	}
	else if (!GraphPinObj->DefaultValue.IsEmpty())
	{
		if (!GraphPinObj->DefaultValue.Equals(CachedRuntimePath, ESearchCase::CaseSensitive))
		{
			FString EditorPath = GraphPinObj->DefaultValue;
			EditorPath.RemoveFromEnd(TEXT("_C"));
			const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

			CachedEditorAssetData = AssetRegistryModule.Get().GetAssetByObjectPath(FSoftObjectPath(EditorPath));

			if (!CachedEditorAssetData.IsValid())
			{
				FString PackageName = FPackageName::ObjectPathToPackageName(EditorPath);
				FString PackagePath = FPackageName::GetLongPackagePath(PackageName);
				FString ObjectName = FPackageName::ObjectPathToObjectName(EditorPath);

				// Fake one
				CachedEditorAssetData = FAssetData(FName(*PackageName), FName(*PackagePath), FName(*ObjectName), UObject::StaticClass()->GetClassPathName());
			}
		}
	}
	else
	{
		if (CachedEditorAssetData.IsValid())
		{
			CachedEditorAssetData = FAssetData();
		}
	}

	return CachedEditorAssetData;
}

#undef LOCTEXT_NAMESPACE

#pragma endregion

#pragma region Struct

#define LOCTEXT_NAMESPACE "SGraphPinStruct"


void SDefault_GraphPinStruct::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

FReply SDefault_GraphPinStruct::OnClickUse()
{
	FEditorDelegates::LoadSelectedAssetsIfNeeded.Broadcast();

	UObject* SelectedObject = GEditor->GetSelectedObjects()->GetTop(UScriptStruct::StaticClass());
	if (SelectedObject)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("GraphEditor", "ChangeStructPinValue", "Change Struct Pin Value"));
		GraphPinObj->Modify();

		GraphPinObj->GetSchema()->TrySetDefaultObject(*GraphPinObj, SelectedObject);
	}

	return FReply::Handled();
}

class FGraphPinStructFilter : public IStructViewerFilter
{
public:
	/** The meta struct for the property that classes must be a child-of. */
	const UScriptStruct* MetaStruct = nullptr;

	// TODO: Have a flag controlling whether we allow UserDefinedStructs, even when a MetaClass is set (as they cannot support inheritance, but may still be allowed (eg, data tables))?

	virtual bool IsStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const UScriptStruct* InStruct,
	                             TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override
	{
		if (InStruct->IsA<UUserDefinedStruct>())
		{
			// User Defined Structs don't support inheritance, so only include them if we have don't a MetaStruct set
			return MetaStruct == nullptr;
		}

		// Query the native struct to see if it has the correct parent type (if any)
		return !MetaStruct || InStruct->IsChildOf(MetaStruct);
	}

	virtual bool IsUnloadedStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const FSoftObjectPath& InStructPath, TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override
	{
		// User Defined Structs don't support inheritance, so only include them if we have don't a MetaStruct set
		return MetaStruct == nullptr;
	}
};

TSharedRef<SWidget> SDefault_GraphPinStruct::GenerateAssetPicker()
{
	FStructViewerModule& StructViewerModule = FModuleManager::LoadModuleChecked<FStructViewerModule>("StructViewer");

	// Fill in options
	FStructViewerInitializationOptions Options;
	Options.Mode = EStructViewerMode::StructPicker;
	Options.bShowNoneOption = true;

	// TODO: We would need our own PC_ type to be able to get the meta-struct here
	const UScriptStruct* MetaStruct = nullptr;

	TSharedRef<FGraphPinStructFilter> StructFilter = MakeShared<FGraphPinStructFilter>();
	Options.StructFilter = StructFilter;
	StructFilter->MetaStruct = MetaStruct;

	return
		SNew(SBox)
		.WidthOverride(280)
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			  .FillHeight(1.0f)
			  .MaxHeight(500)
			[
				SNew(SBorder)
			.Padding(4)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
				[
					StructViewerModule.CreateStructViewer(
						Options, FOnStructPicked::CreateSP(this, &SDefault_GraphPinStruct::OnPickedNewStruct))
				]
			]
		];
}

FOnClicked SDefault_GraphPinStruct::GetOnUseButtonDelegate()
{
	return FOnClicked::CreateSP(this, &SDefault_GraphPinStruct::OnClickUse);
}

void SDefault_GraphPinStruct::OnPickedNewStruct(const UScriptStruct* ChosenStruct)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	FString NewPath;
	if (ChosenStruct)
	{
		NewPath = ChosenStruct->GetPathName();
	}

	if (GraphPinObj->GetDefaultAsString() != NewPath)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("GraphEditor", "ChangeStructPinValue", "Change Struct Pin Value"));
		GraphPinObj->Modify();

		AssetPickerAnchor->SetIsOpen(false);
		GraphPinObj->GetSchema()->TrySetDefaultObject(*GraphPinObj, const_cast<UScriptStruct*>(ChosenStruct));
	}
}

FText SDefault_GraphPinStruct::GetDefaultComboText() const
{
	return LOCTEXT("DefaultComboText", "Select Struct");
}

#undef LOCTEXT_NAMESPACE

#pragma endregion

#pragma region Enum
void SDefault_GraphPinEnum::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SDefault_GraphPinEnum::GetDefaultValueWidget()
{
	//Get list of enum indexes
	TArray<TSharedPtr<int32>> ComboItems;
	GenerateComboBoxIndexes(ComboItems);
	const auto& Select = UPinRestyleSettings::Get()->Inputs.Select;
	const auto& ComboButton = Select.Get().ComboButton.Get();
	FLinearColor Color = ComboButton.Button.Get().NormalForeground.Get();
	float SpacingBetweenTextAndArrow = UDefaultThemeSettings::GetSpacing(ComboButton.DownArrowSpacing);
	//Create widget
	return SAssignNew(ComboBox, SDefault_IndexComboBox)
		.ItemStyle(FAppStyle::Get(), FPinRestyleStyles::ComboBox_Row)
		.Font(FAppStyle::Get().GetFontStyle(FPinRestyleStyles::ComboBox_Button_FontInfo))
		.ColorAndOpacity(Color)
		.ComboBoxStyle(FAppStyle::Get(), FPinRestyleStyles::ComboBox)
		.InitiallySelectedItem(GetSelectedEnum())
		.OptionsSource(ComboItems)
		.OnSelectionChanged(this, &SDefault_GraphPinEnum::ComboBoxSelectionChanged)
		.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		.OnGetDisplayNameForItem(this, &SDefault_GraphPinEnum::OnGetFriendlyName)
		.OnGetTooltipForItem(this, &SDefault_GraphPinEnum::OnGetTooltip)
		.SpacingBetweenTextAndArrow(SpacingBetweenTextAndArrow);
}

int32 SDefault_GraphPinEnum::GetSelectedEnum() const
{
	FString SelectedString = GraphPinObj->GetDefaultAsString();

	UEnum* EnumPtr = Cast<UEnum>(GraphPinObj->PinType.PinSubCategoryObject.Get());
	if (EnumPtr && EnumPtr->NumEnums())
	{
		const int32 MaxIndex = EnumPtr->NumEnums();
		for (int32 EnumIdx = 0; EnumIdx < MaxIndex; ++EnumIdx)
		{
			// Ignore hidden enum values
			if (!EnumPtr->HasMetaData(TEXT("Hidden"), EnumIdx))
			{
				if (SelectedString == EnumPtr->GetNameStringByIndex(EnumIdx))
				{
					return EnumIdx;
				}
			}
		}
	}
	return 0;
}

FText SDefault_GraphPinEnum::OnGetFriendlyName(int32 EnumIndex)
{
	if (GraphPinObj->IsPendingKill())
	{
		return FText();
	}

	UEnum* EnumPtr = Cast<UEnum>(GraphPinObj->PinType.PinSubCategoryObject.Get());

	check(EnumPtr);
	if (EnumIndex >= EnumPtr->NumEnums())
	{
		return FText::FromString(TEXT("(INVALID)"));
	}
	//check(EnumIndex < EnumPtr->NumEnums());

	FText EnumValueName = EnumPtr->GetDisplayNameTextByIndex(EnumIndex);
	return EnumValueName;
}

FText SDefault_GraphPinEnum::OnGetTooltip(int32 EnumIndex)
{
	UEnum* EnumPtr = Cast<UEnum>(GraphPinObj->PinType.PinSubCategoryObject.Get());

	check(EnumPtr);
	if (EnumIndex >= EnumPtr->NumEnums())
	{
		return FText::FromString(TEXT("(INVALID)"));
	}
	//check(EnumIndex < EnumPtr->NumEnums());

	FText EnumValueTooltip = EnumPtr->GetToolTipTextByIndex(EnumIndex);
	return EnumValueTooltip;
}

void SDefault_GraphPinEnum::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type /*SelectInfo*/)
{
	UEnum* EnumPtr = Cast<UEnum>(GraphPinObj->PinType.PinSubCategoryObject.Get());
	check(EnumPtr);

	FString EnumSelectionString;
	if (NewSelection.IsValid())
	{
		check(*NewSelection < EnumPtr->NumEnums() - 1);
		EnumSelectionString = EnumPtr->GetNameStringByIndex(*NewSelection);
	}
	else
	{
		EnumSelectionString = FName(NAME_None).ToString();
	}


	if (GraphPinObj->GetDefaultAsString() != EnumSelectionString)
	{
		const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeEnumPinValue", "Change Enum Pin Value"));
		GraphPinObj->Modify();

		//Set new selection
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, EnumSelectionString);
	}
}

FString SDefault_GraphPinEnum::OnGetText() const
{
	FString SelectedString = GraphPinObj->GetDefaultAsString();

	UEnum* EnumPtr = Cast<UEnum>(GraphPinObj->PinType.PinSubCategoryObject.Get());
	if (EnumPtr && EnumPtr->NumEnums())
	{
		const int32 MaxIndex = EnumPtr->NumEnums() - 1;
		for (int32 EnumIdx = 0; EnumIdx < MaxIndex; ++EnumIdx)
		{
			// Ignore hidden enum values
			if (!EnumPtr->HasMetaData(TEXT("Hidden"), EnumIdx))
			{
				if (SelectedString == EnumPtr->GetNameStringByIndex(EnumIdx))
				{
					FString EnumDisplayName = EnumPtr->GetDisplayNameTextByIndex(EnumIdx).ToString();
					if (EnumDisplayName.Len() == 0)
					{
						return SelectedString;
					}
					else
					{
						return EnumDisplayName;
					}
				}
			}
		}

		if (SelectedString == EnumPtr->GetNameStringByIndex(MaxIndex))
		{
			return TEXT("(INVALID)");
		}
	}
	return SelectedString;
}

void SDefault_GraphPinEnum::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	UEnum* EnumPtr = Cast<UEnum>(GraphPinObj->PinType.PinSubCategoryObject.Get());
	if (EnumPtr)
	{
		//NumEnums() - 1, because the last item in an enum is the _MAX item
		for (int32 EnumIndex = 0; EnumIndex < EnumPtr->NumEnums() - 1; ++EnumIndex)
		{
			// Ignore hidden enum values
			if (!EnumPtr->HasMetaData(TEXT("Hidden"), EnumIndex))
			{
				TSharedPtr<int32> EnumIdxPtr(new int32(EnumIndex));
				OutComboBoxIndexes.Add(EnumIdxPtr);
			}
		}
	}
}
#pragma endregion

#pragma region Index

void SDefault_GraphPinIndex::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SDefault_GraphPinIndex::GetDefaultValueWidget()
{
	const UEdGraphSchema_K2* Schema = GetDefault<UEdGraphSchema_K2>();
	auto* ComboButtonStyle = &FAppStyle::Get().GetWidgetStyle<FComboBoxStyle>(FPinRestyleStyles::ComboBox).
	                                           ComboButtonStyle;
	const auto& Select = UPinRestyleSettings::Get()->Inputs.Select;
	const auto& ComboButton = Select.Get().ComboButton.Get();
	const auto& Button = ComboButton.Button.Get();

	FMargin ButtonTextPadding = UDefaultThemeSettings::GetMargin(Button.Padding);
	float ContentSpacing = UDefaultThemeSettings::GetSpacing(
		UPinRestyleSettings::Get()->Inputs.PinSelectorContentSpacing);;
	return SNew(SDefault_PinTypeSelector,
	            FGetPinTypeTree::CreateUObject(Schema, &UEdGraphSchema_K2::GetVariableTypeTree))
		.TargetPinType(this, &SDefault_GraphPinIndex::OnGetPinType)
		.OnPinTypeChanged(this, &SDefault_GraphPinIndex::OnTypeChanged)
		.Schema(Schema)
		.TypeTreeFilter(ETypeTreeFilter::IndexTypesOnly)
		.IsEnabled(true)
		.bAllowArrays(false)
		.TypeComboButtonStyle(ComboButtonStyle)
		.TypeComboButtonPadding(ButtonTextPadding)
		.TypeComboButtonContentSpacing(ContentSpacing)
		.Font(FAppStyle::Get().GetFontStyle(FPinRestyleStyles::ComboBox_Button_FontInfo))
		.SelectorType(SDefault_PinTypeSelector::ESelectorType::Full);
}

FEdGraphPinType SDefault_GraphPinIndex::OnGetPinType() const
{
	return GraphPinObj->PinType;
}

void SDefault_GraphPinIndex::OnTypeChanged(const FEdGraphPinType& PinType)
{
	if (GraphPinObj)
	{
		GraphPinObj->Modify();
		GraphPinObj->PinType = PinType;
		// Let the node know that one of its' pins had their pin type changed
		if (UEdGraphNode* OwningNode = GraphPinObj->GetOwningNode())
		{
			OwningNode->PinTypeChanged(GraphPinObj);
			OwningNode->ReconstructNode();
		}
	}
}


#pragma endregion

#pragma region Key

void SDefault_GraphPinKey::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	if (InGraphPinObj->bOrphanedPin)
	{
		SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
		return;
	}

	SelectedKey = FKey(*InGraphPinObj->GetDefaultAsString());

	InGraphPinObj->AutogeneratedDefaultValue = "None";
	if (SelectedKey.GetFName() == NAME_None)
	{
		InGraphPinObj->GetSchema()->ResetPinToAutogeneratedDefaultValue(InGraphPinObj, false);
		SelectedKey = FKey(*InGraphPinObj->GetDefaultAsString());
	}

	if (InGraphPinObj->Direction == EEdGraphPinDirection::EGPD_Input)
	{
		// None is a valid key
		if (SelectedKey.GetFName() == NAME_None)
		{
			SelectedKey = EKeys::Invalid;
		}
		else if (!SelectedKey.IsValid())
		{
			// Ensure first valid key is always set by default
			TArray<FKey> KeyList;
			EKeys::GetAllKeys(KeyList);
			SelectedKey = KeyList[0];
			InGraphPinObj->GetSchema()->TrySetDefaultValue(*InGraphPinObj, SelectedKey.ToString());
		}
	}

	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SDefault_GraphPinKey::GetDefaultValueWidget()
{
	const auto& Key = UPinRestyleSettings::Get()->Inputs.Key;
	const auto& ComboButton = Key.ComboButton.Get();
	float Spacing = UDefaultThemeSettings::GetSpacing(Key.Spacing);
	float SpacingBetweenIconAndArrow = UDefaultThemeSettings::GetSpacing(ComboButton.DownArrowSpacing);
	bool bHasDownArrow = ComboButton.bHasDownArrow;
	const auto& CaptureButton = Key.Button.Get();
	uint16 IconSize = UDefaultThemeSettings::GetIconSize(CaptureButton.IconSize);
	FMargin ButtonContentPadding = UDefaultThemeSettings::GetMargin(CaptureButton.Padding);
	return SNew(SDefault_KeySelector)
	.ComboButtonStyle(FAppStyle::Get(), FPinRestyleStyles::KeyInput_ComboButton)
	.ButtonStyle(FAppStyle::Get(), FPinRestyleStyles::KeyInput_Button)
	.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
	.CurrentKey(this, &SDefault_GraphPinKey::GetCurrentKey)
	.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
	.OnKeyChanged(this, &SDefault_GraphPinKey::OnKeyChanged)
	.Spacing(Spacing)
	.SpacingBetweenTextAndArrow(SpacingBetweenIconAndArrow)
	.bHasDownArrow(bHasDownArrow)
	.ButtonIconSize(IconSize)
	.ButtonContentPadding(ButtonContentPadding);
}

TOptional<FKey> SDefault_GraphPinKey::GetCurrentKey() const
{
	return SelectedKey;
}

void SDefault_GraphPinKey::OnKeyChanged(TSharedPtr<FKey> InSelectedKey)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	if (SelectedKey != *InSelectedKey.Get())
	{
		const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeKeyPinValue", "Change Key Pin Value"));
		GraphPinObj->Modify();

		SelectedKey = *InSelectedKey.Get();
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, SelectedKey.ToString());
	}
}

#pragma endregion

#pragma region Text
namespace
{
	/** Allows SDefault_TextPropertyEditableTextBox to edit a graph pin */
	class FEditableTextGraphPin : public IEditableTextProperty
	{
	public:
		FEditableTextGraphPin(UEdGraphPin* InGraphPinObj)
			: GraphPinObjRef(InGraphPinObj)
		{
		}

		virtual bool IsMultiLineText() const override
		{
			return true;
		}

		virtual bool IsPassword() const override
		{
			return false;
		}

		virtual bool IsReadOnly() const override
		{
			if (const UEdGraphPin* GraphPinObj = GraphPinObjRef.Get())
			{
				return GraphPinObj->bDefaultValueIsReadOnly;
			}

			return false;
		}

		virtual bool IsDefaultValue() const override
		{
			if (const UEdGraphPin* GraphPinObj = GraphPinObjRef.Get())
			{
				FString TextAsString;
				FTextStringHelper::WriteToBuffer(TextAsString, GraphPinObj->DefaultTextValue);
				return TextAsString.Equals(GraphPinObj->AutogeneratedDefaultValue, ESearchCase::CaseSensitive);
			}

			return false;
		}

		virtual FText GetToolTipText() const override
		{
			return FText::GetEmpty();
		}

		virtual int32 GetNumTexts() const override
		{
			return 1;
		}

		virtual FText GetText(const int32 InIndex) const override
		{
			check(InIndex == 0);
			if (const UEdGraphPin* GraphPinObj = GraphPinObjRef.Get())
			{
				return GraphPinObj->DefaultTextValue;
			}

			return FText::GetEmpty();
		}

		virtual void SetText(const int32 InIndex, const FText& InText) override
		{
			check(InIndex == 0);
			if (UEdGraphPin* GraphPinObj = GraphPinObjRef.Get())
			{
				const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeTxtPinValue",
				                                               "Change Text Pin Value"));
				GraphPinObj->Modify();
				GraphPinObj->GetSchema()->TrySetDefaultText(*GraphPinObj, InText);
			}
		}

		virtual bool IsValidText(const FText& InText, FText& OutErrorMsg) const override
		{
			return true;
		}

#if USE_STABLE_LOCALIZATION_KEYS
		virtual void GetStableTextId(const int32 InIndex, const ETextPropertyEditAction InEditAction,
		                             const FString& InTextSource, const FString& InProposedNamespace,
		                             const FString& InProposedKey, FString& OutStableNamespace,
		                             FString& OutStableKey) const override
		{
			check(InIndex == 0);
			if (const UEdGraphPin* GraphPinObj = GraphPinObjRef.Get())
			{
				StaticStableTextId(GraphPinObj->GetOwningNodeUnchecked(), InEditAction, InTextSource,
				                   InProposedNamespace, InProposedKey, OutStableNamespace, OutStableKey);
			}
		}
#endif // USE_STABLE_LOCALIZATION_KEYS

	private:
		FEdGraphPinReference GraphPinObjRef;
	};
}

void SDefault_GraphPinText::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SDefault_GraphPinText::GetDefaultValueWidget()
{
	const auto& Text = UPinRestyleSettings::Get()->Inputs.Text;
	float Spacing = UDefaultThemeSettings::GetSpacing(Text.Spacing);
	const auto& ComboButton = Text.AdvancedTextButton.Get();
	float SpacingBetweenIconAndArrow = UDefaultThemeSettings::GetSpacing(ComboButton.DownArrowSpacing);
	bool bHasDownArrow = ComboButton.bHasDownArrow;
	uint16 IconSize = UDefaultThemeSettings::GetIconSize(ComboButton.Button.Get().IconSize);
	return SNew(SDefault_TextPropertyEditableTextBox, MakeShareable(new FEditableTextGraphPin(GraphPinObj)))
		.Style(FAppStyle::Get(), FPinRestyleStyles::Graph_EditableTextBox)
		.ComboButtonStyle(FAppStyle::Get(), FPinRestyleStyles::Graph_TextInput_AdvancedText_ComboButton)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		.ForegroundColor(FSlateColor::UseForeground())
		.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
		.WrapTextAt(400)
		.MinDesiredWidth(18.0f)
		//.MaxDesiredHeight(200)
		.Spacing(Spacing)
		.SpacingBetweenIconAndArrow(SpacingBetweenIconAndArrow)
		.bHasDownArrow(bHasDownArrow)
		.AdvancedTextIconSize(IconSize);
}
#pragma endregion

#pragma region MaterialInput
void SDefault_GraphPinMaterialInput::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

FSlateColor SDefault_GraphPinMaterialInput::GetPinColor() const
{
	check(GraphPinObj);
	UMaterialGraph* MaterialGraph = CastChecked<UMaterialGraph>(GraphPinObj->GetOwningNode()->GetGraph());
	const UMaterialGraphSchema* Schema = CastChecked<UMaterialGraphSchema>(MaterialGraph->GetSchema());

	if (MaterialGraph->IsInputActive(GraphPinObj))
	{
		return Schema->ActivePinColor;
	}
	else
	{
		return Schema->InactivePinColor;
	}
}
#pragma endregion

//void SDefault_GraphPinKnot::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}

#pragma region Bool

void SDefault_GraphPinBool::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SDefault_GraphPinBool::GetDefaultValueWidget()
{
	return SNew(SCheckBox)
		.Style(&FAppStyle::Get().GetWidgetStyle<FCheckBoxStyle>(FPinRestyleStyles::Graph_Checkbox))
		.IsChecked(this, &SDefault_GraphPinBool::IsDefaultValueChecked)
		.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
		.OnCheckStateChanged(this, &SDefault_GraphPinBool::OnDefaultValueCheckBoxChanged)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility);
}

ECheckBoxState SDefault_GraphPinBool::IsDefaultValueChecked() const
{
	FString CurrentValue = GraphPinObj->GetDefaultAsString();
	return CurrentValue.ToBool() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SDefault_GraphPinBool::OnDefaultValueCheckBoxChanged(ECheckBoxState InIsChecked)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	const FString BoolString = (InIsChecked == ECheckBoxState::Checked) ? TEXT("true") : TEXT("false");
	if (GraphPinObj->GetDefaultAsString() != BoolString)
	{
		const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeBoolPinValue", "Change Bool Pin Value"));
		GraphPinObj->Modify();

		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, BoolString);
	}
}


#pragma endregion

#pragma region Color

void SDefault_GraphPinColor::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}


TSharedRef<SWidget> SDefault_GraphPinColor::GetDefaultValueWidget()
{
	const auto& Color = UPinRestyleSettings::Get()->Inputs.Color;
	auto Padding = UDefaultThemeSettings::GetMargin(Color.Padding);
	auto Size = UDefaultThemeSettings::GetIconSize(Color.Size);
	return SAssignNew(DefaultValueWidget, SBorder)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
		.BorderBackgroundColor(Color.Border.Get())
		.Padding(Padding)
	[
		SNew(SBox)
		.WidthOverride(Size)
		.HeightOverride(Size)
		[
			SNew(SColorBlock)
			.Color(this, &SDefault_GraphPinColor::GetColor)
			.ShowBackgroundForAlpha(true)
			.OnMouseButtonDown(this, &SDefault_GraphPinColor::OnColorBoxClicked)
		]
	];
}

FReply SDefault_GraphPinColor::OnColorBoxClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		SelectedColor = GetColor();
		TArray<FLinearColor*> LinearColorArray;
		LinearColorArray.Add(&SelectedColor);

		FColorPickerArgs PickerArgs;
		PickerArgs.bIsModal = true;
		PickerArgs.ParentWidget = DefaultValueWidget;
		PickerArgs.DisplayGamma = TAttribute<float>::Create(
			TAttribute<float>::FGetter::CreateUObject(GEngine, &UEngine::GetDisplayGamma));
		PickerArgs.LinearColorArray = &LinearColorArray;
		PickerArgs.OnColorCommitted = FOnLinearColorValueChanged::CreateSP(
			this, &SDefault_GraphPinColor::OnColorCommitted);
		PickerArgs.bUseAlpha = true;

		OpenColorPicker(PickerArgs);

		return FReply::Handled();
	}
	else
	{
		return FReply::Unhandled();
	}
}

FLinearColor SDefault_GraphPinColor::GetColor() const
{
	FString ColorString = GraphPinObj->GetDefaultAsString();
	FLinearColor PinColor;

	// Ensure value is sensible
	if (!PinColor.InitFromString(ColorString))
	{
		PinColor = FLinearColor::Black;
	}
	return PinColor;
}

void SDefault_GraphPinColor::OnColorCommitted(FLinearColor InColor)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	// Update pin object
	FString ColorString = InColor.ToString();

	if (GraphPinObj->GetDefaultAsString() != ColorString)
	{
		const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeColorPinValue", "Change Color Pin Value"));
		GraphPinObj->Modify();

		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, ColorString);

		if (OwnerNodePtr.IsValid())
		{
			OwnerNodePtr.Pin()->UpdateGraphNode();
		}
	}
}

#pragma endregion

#pragma region Exec

void SDefault_GraphPinExec::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);

	CachePinIcons();
}

void SDefault_GraphPinExec::CachePinIcons()
{
	CachedImg_Pin_ConnectedHovered = FAppStyle::GetBrush(TEXT("Graph.ExecPin.ConnectedHovered"));
	CachedImg_Pin_Connected = FAppStyle::GetBrush(TEXT("Graph.ExecPin.Connected"));
	CachedImg_Pin_DisconnectedHovered = FAppStyle::GetBrush(TEXT("Graph.ExecPin.DisconnectedHovered"));
	CachedImg_Pin_Disconnected = FAppStyle::GetBrush(TEXT("Graph.ExecPin.Disconnected"));
}

TSharedRef<SWidget> SDefault_GraphPinExec::GetDefaultValueWidget()
{
	return SNullWidget::NullWidget; // not used for exec pin		
}

const FSlateBrush* SDefault_GraphPinExec::GetPinIcon() const
{
	const FSlateBrush* Brush = NULL;

	if (IsConnected())
	{
		Brush = IsHovered() ? CachedImg_Pin_ConnectedHovered : CachedImg_Pin_Connected;
	}
	else
	{
		Brush = IsHovered() ? CachedImg_Pin_DisconnectedHovered : CachedImg_Pin_Disconnected;
	}

	return Brush;
}
#pragma endregion

//
//void SDefault_GraphPinNum<NumericType>::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}

#pragma region Object
void SDefault_GraphPinObject::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

#define LOCTEXT_NAMESPACE "SGraphPinObject"

namespace GraphPinObjectDefs
{
	// Active Combo pin alpha
	static const float ActiveComboAlpha = 1.f;
	// InActive Combo pin alpha
	static const float InActiveComboAlpha = 0.6f;
	// Active foreground pin alpha
	static const float ActivePinForegroundAlpha = 1.f;
	// InActive foreground pin alpha
	static const float InactivePinForegroundAlpha = 0.15f;
	// Active background pin alpha
	static const float ActivePinBackgroundAlpha = 0.8f;
	// InActive background pin alpha
	static const float InactivePinBackgroundAlpha = 0.4f;
};


TSharedRef<SWidget> SDefault_GraphPinObject::GetDefaultValueWidget()
{
	if (GraphPinObj == nullptr)
	{
		return SNullWidget::NullWidget;
	}
	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();

	if (Schema == nullptr)
	{
		return SNullWidget::NullWidget;
	}

	if (ShouldDisplayAsSelfPin())
	{
		float ErrorReportingSpacing = UDefaultThemeSettings::GetSpacing(
			UPinRestyleSettings::Get()->Inputs.String.ErrorReportingSpacing);
		const auto& Body = UPinRestyleSettings::Get()->Inputs.String.Body.Get();
		auto Padding = UDefaultThemeSettings::GetMargin(Body.Padding);
		return SNew(SDefault_EditableTextBox)
			.Style(FAppStyle::Get(), FPinRestyleStyles::Graph_EditableTextBox)
			.Text(this, &SDefault_GraphPinObject::GetValue)
			.SelectAllTextWhenFocused(false)
			.Visibility(this, &SDefault_GraphPinObject::GetDefaultValueVisibility)
			.IsReadOnly(true)
			.ForegroundColor(FSlateColor::UseForeground())
			.ErrorReportingSpacing(ErrorReportingSpacing)
			.Padding(Padding);
		//.DefaultScrollBarThickness(DefaultScrollBarThickness);
	}

	// Don't show literal buttons for component type objects
	if (Schema->ShouldShowAssetPickerForPin(GraphPinObj))
	{
		const auto Style = UPinRestyleSettings::Get();
		const auto& AssetPicker = Style->Inputs.AssetPicker;
		float GeneralSpacing = UDefaultThemeSettings::GetSpacing(AssetPicker.GeneralSpacing);
		FMargin UtilButtonPadding = UDefaultThemeSettings::GetMargin(AssetPicker.UtilButton.Get().Padding);
		const auto& ComboButton = AssetPicker.ComboButton.Get();
		const auto& Button = ComboButton.Button.Get();
		FMargin ButtonTextPadding = UDefaultThemeSettings::GetMargin(Button.Padding);
		bool bHasDownArrow = ComboButton.bHasDownArrow;
		float DownArrowSpacing = UDefaultThemeSettings::GetSpacing(ComboButton.DownArrowSpacing);
		return
			SNew(SHorizontalBox)
			.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
			+ SHorizontalBox::Slot()
			  .AutoWidth()
			  .Padding(0)
			  .MaxWidth(AssetPicker.ButtonMaxWidth)
			[
				SAssignNew(AssetPickerAnchor, SComboButton)
				.ComboButtonStyle(FAppStyle::Get(), FPinRestyleStyles::AssetPicker_ComboButton)
				.HasDownArrow(bHasDownArrow)
				.ForegroundColor(FSlateColor::UseStyle())
				.MenuPlacement(MenuPlacement_BelowAnchor)
				.IsEnabled(this, &SGraphPin::IsEditingEnabled)
				.ContentPadding(ButtonTextPadding)
				.ButtonContent()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.FillWidth(1)
					[
						SNew(STextBlock)
						.ColorAndOpacity(FSlateColor::UseForeground())
						//.ColorAndOpacity(this, &SDefault_GraphPinObject::OnGetComboForeground)
						.TextStyle(FAppStyle::Get(), FPinRestyleStyles::AssetPicker_ComboButton_Text)
						.Text(this, &SDefault_GraphPinObject::OnGetComboTextValue)
						.ToolTipText(this, &SDefault_GraphPinObject::GetObjectToolTip)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SSpacer).Size(FVector2D(bHasDownArrow ? DownArrowSpacing : 0, 0))
					]
				]
				.OnGetMenuContent(this, &SDefault_GraphPinObject::GenerateAssetPicker)
			]
			+ SHorizontalBox::Slot().Padding(0, 0, GeneralSpacing, 0)
			// Use button
			+ SHorizontalBox::Slot()
			  .AutoWidth()
			  .VAlign(VAlign_Center)
			[
				SAssignNew(UseButton, SButton)
				.ButtonStyle(FAppStyle::Get(), FPinRestyleStyles::AssetPicker_Button_Use)
				.OnClicked(GetOnUseButtonDelegate())
				.ToolTipText(NSLOCTEXT("GraphEditor", "ObjectGraphPin_Use_Tooltip", "Use asset browser selection"))
				.IsEnabled(this, &SGraphPin::IsEditingEnabled)
				.ContentPadding(UtilButtonPadding)
				.Content()
				[
					SNew(SImage)
					.ColorAndOpacity(FSlateColor::UseStyle())
					.Image(FAppStyle::GetBrush("Icons.CircleArrowLeft"))
				]
			]
			// Browse button
			+ SHorizontalBox::Slot()
			  .AutoWidth()
			  .VAlign(VAlign_Center)
			[
				SAssignNew(BrowseButton, SButton)
				.ButtonStyle(FAppStyle::Get(), FPinRestyleStyles::AssetPicker_Button_Browse)
				.OnClicked(GetOnBrowseButtonDelegate())
				.ToolTipText(NSLOCTEXT("GraphEditor", "ObjectGraphPin_Browse_Tooltip", "Browse"))
				.ContentPadding(UtilButtonPadding)
				.Content()
				[
					SNew(SImage)
					.ColorAndOpacity(FSlateColor::UseStyle())
					.Image(FAppStyle::GetBrush("Icons.Search"))
				]
			];
	}

	return SNullWidget::NullWidget;
}

FOnClicked SDefault_GraphPinObject::GetOnUseButtonDelegate()
{
	return FOnClicked::CreateSP(this, &SDefault_GraphPinObject::OnClickUse);
}

FOnClicked SDefault_GraphPinObject::GetOnBrowseButtonDelegate()
{
	return FOnClicked::CreateSP(this, &SDefault_GraphPinObject::OnClickBrowse);
}

FText SDefault_GraphPinObject::GetObjectToolTip() const
{
	return GetValue();
}

FString SDefault_GraphPinObject::GetObjectToolTipAsString() const
{
	return GetValue().ToString();
}

FReply SDefault_GraphPinObject::OnClickUse()
{
	FEditorDelegates::LoadSelectedAssetsIfNeeded.Broadcast();

	UClass* ObjectClass = Cast<UClass>(GraphPinObj->PinType.PinSubCategoryObject.Get());
	if (ObjectClass != NULL)
	{
		UObject* SelectedObject = GEditor->GetSelectedObjects()->GetTop(ObjectClass);
		if (SelectedObject != NULL)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeObjectPinValue",
			                                               "Change Object Pin Value"));
			GraphPinObj->Modify();

			GraphPinObj->GetSchema()->TrySetDefaultObject(*GraphPinObj, SelectedObject);
		}
	}

	return FReply::Handled();
}

FReply SDefault_GraphPinObject::OnClickBrowse()
{
	const FAssetData& AssetData = GetAssetData(false);
	if (AssetData.IsValid())
	{
		TArray<FAssetData> Objects;
		Objects.Add(AssetData);

		GEditor->SyncBrowserToObjects(Objects);
	}
	return FReply::Handled();
}

TSharedRef<SWidget> SDefault_GraphPinObject::GenerateAssetPicker()
{
	// This class and its children are the classes that we can show objects for
	UClass* AllowedClass = Cast<UClass>(GraphPinObj->PinType.PinSubCategoryObject.Get());

	if (AllowedClass == NULL)
	{
		AllowedClass = UObject::StaticClass();
	}

	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(
		TEXT("ContentBrowser"));

	FAssetPickerConfig AssetPickerConfig;
	AssetPickerConfig.Filter.ClassPaths.Add(AllowedClass->GetClassPathName());
	AssetPickerConfig.bAllowNullSelection = true;
	AssetPickerConfig.Filter.bRecursiveClasses = true;
	AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateSP(
		this, &SDefault_GraphPinObject::OnAssetSelectedFromPicker);
	AssetPickerConfig.OnAssetEnterPressed = FOnAssetEnterPressed::CreateSP(
		this, &SDefault_GraphPinObject::OnAssetEnterPressedInPicker);
	AssetPickerConfig.InitialAssetViewType = EAssetViewType::List;
	AssetPickerConfig.bAllowDragging = false;

	// Check with the node to see if there is any "AllowClasses" or "DisallowedClasses" metadata for the pin
	FString AllowedClassesFilterString = GraphPinObj->GetOwningNode()->GetPinMetaData(
		GraphPinObj->PinName, FName(TEXT("AllowedClasses")));
	if (!AllowedClassesFilterString.IsEmpty())
	{
		// Clear out the allowed class names and have the pin's metadata override.
		AssetPickerConfig.Filter.ClassPaths.Empty();

		// Parse and add the classes from the metadata
		TArray<FString> AllowedClassesFilterNames;
		AllowedClassesFilterString.ParseIntoArrayWS(AllowedClassesFilterNames, TEXT(","), true);
		for (const FString& AllowedClassesFilterName : AllowedClassesFilterNames)
		{
			ensureAlwaysMsgf(!FPackageName::IsShortPackageName(AllowedClassesFilterName), TEXT("Short class names are not supported as AllowedClasses on pin \"%s\": class \"%s\""), *GraphPinObj->PinName.ToString(), *AllowedClassesFilterName);
			AssetPickerConfig.Filter.ClassPaths.Add(FTopLevelAssetPath(AllowedClassesFilterName));
		}
	}

	FString DisallowedClassesFilterString = GraphPinObj->GetOwningNode()->GetPinMetaData(
		GraphPinObj->PinName, FName(TEXT("DisallowedClasses")));
	if (!DisallowedClassesFilterString.IsEmpty())
	{
		TArray<FString> DisallowedClassesFilterNames;
		DisallowedClassesFilterString.ParseIntoArrayWS(DisallowedClassesFilterNames, TEXT(","), true);
		for (const FString& DisallowedClassesFilterName : DisallowedClassesFilterNames)
		{
			ensureAlwaysMsgf(!FPackageName::IsShortPackageName(DisallowedClassesFilterName), TEXT("Short class names are not supported as DisallowedClasses on pin \"%s\": class \"%s\""), *GraphPinObj->PinName.ToString(), *DisallowedClassesFilterName);
			AssetPickerConfig.Filter.RecursiveClassPathsExclusionSet.Add(FTopLevelAssetPath(DisallowedClassesFilterName));
		}
	}

	return
		SNew(SBox)
		.HeightOverride(300)
		.WidthOverride(300)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("Menu.Background"))
			[
				ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig)
			]
		];
}

void SDefault_GraphPinObject::OnAssetSelectedFromPicker(const struct FAssetData& AssetData)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	const FAssetData& CurrentAssetData = GetAssetData(true);
	if (CurrentAssetData != AssetData)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("GraphEditor", "ChangeObjectPinValue", "Change Object Pin Value"));
		GraphPinObj->Modify();

		// Close the asset picker
		AssetPickerAnchor->SetIsOpen(false);

		// Set the object found from the asset picker
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, AssetData.GetObjectPathString());
	}
}

void SDefault_GraphPinObject::OnAssetEnterPressedInPicker(const TArray<FAssetData>& InSelectedAssets)
{
	if (InSelectedAssets.Num() > 0)
	{
		OnAssetSelectedFromPicker(InSelectedAssets[0]);
	}
}

bool SDefault_GraphPinObject::ShouldDisplayAsSelfPin() const
{
	if (AllowSelfPinWidget() && GraphPinObj)
	{
		if (GraphPinObj->GetSchema()->IsSelfPin(*GraphPinObj))
		{
			return true;
		}

		// Also check function/node metadata
		const FString DefaultToSelfString = GraphPinObj->GetOwningNode()->GetPinMetaData(
			GraphPinObj->PinName, FBlueprintMetadata::MD_DefaultToSelf);
		if (DefaultToSelfString == GraphPinObj->PinName.ToString())
		{
			return true;
		}
	}

	return false;
}


FText SDefault_GraphPinObject::GetValue() const
{
	const FAssetData& CurrentAssetData = GetAssetData(true);
	FText Value;
	if (CurrentAssetData.IsValid())
	{
		Value = FText::FromString(CurrentAssetData.GetFullName());
	}
	else
	{
		if (GraphPinObj->GetSchema()->IsSelfPin(*GraphPinObj))
		{
			Value = FText::FromName(GraphPinObj->PinName);
		}
		else if (ShouldDisplayAsSelfPin())
		{
			Value = FText::FromName(UEdGraphSchema_K2::PN_Self);
		}
		else
		{
			Value = FText::GetEmpty();
		}
	}
	return Value;
}

FText SDefault_GraphPinObject::GetObjectName() const
{
	FText Value = FText::GetEmpty();

	if (GraphPinObj != NULL)
	{
		const FAssetData& CurrentAssetData = GetAssetData(true);
		if (CurrentAssetData.IsValid())
		{
			Value = FText::FromString(CurrentAssetData.AssetName.ToString());
			int32 StringLen = Value.ToString().Len();

			//If string is too long, then truncate (eg. "abcdefgijklmnopq" is converted as "abcd...nopq")
			const int32 MaxAllowedLength = 16;
			if (StringLen > MaxAllowedLength)
			{
				//Take first 4 characters
				FString TruncatedStr(Value.ToString().Left(4));
				TruncatedStr += FString(TEXT("..."));

				//Take last 4 characters
				TruncatedStr += Value.ToString().Right(4);
				Value = FText::FromString(TruncatedStr);
			}
		}
	}
	return Value;
}

FText SDefault_GraphPinObject::GetDefaultComboText() const
{
	return LOCTEXT("DefaultComboText", "Select Asset");
}

FText SDefault_GraphPinObject::OnGetComboTextValue() const
{
	FText Value = GetDefaultComboText();

	if (GraphPinObj != nullptr)
	{
		const FAssetData& CurrentAssetData = GetAssetData(true);

		UObject* DefaultObject = GraphPinObj->DefaultObject;
		if (UField* Field = Cast<UField>(DefaultObject))
		{
			Value = Field->GetDisplayNameText();
		}
		else if (CurrentAssetData.IsValid())
		{
			Value = FText::FromString(CurrentAssetData.AssetName.ToString());
		}
	}
	return Value;
}

FSlateColor SDefault_GraphPinObject::OnGetComboForeground() const
{
	float Alpha = (IsHovered() || bOnlyShowDefaultValue)
		              ? GraphPinObjectDefs::ActiveComboAlpha
		              : GraphPinObjectDefs::InActiveComboAlpha;
	return FSlateColor(FLinearColor(1.f, 1.f, 1.f, Alpha));
}

FSlateColor SDefault_GraphPinObject::OnGetWidgetForeground() const
{
	float Alpha = (IsHovered() || bOnlyShowDefaultValue)
		              ? GraphPinObjectDefs::ActivePinForegroundAlpha
		              : GraphPinObjectDefs::InactivePinForegroundAlpha;
	return FSlateColor(FLinearColor(1.f, 1.f, 1.f, Alpha));
}

FSlateColor SDefault_GraphPinObject::OnGetWidgetBackground() const
{
	float Alpha = (IsHovered() || bOnlyShowDefaultValue)
		              ? GraphPinObjectDefs::ActivePinBackgroundAlpha
		              : GraphPinObjectDefs::InactivePinBackgroundAlpha;
	return FSlateColor(FLinearColor(1.f, 1.f, 1.f, Alpha));
}

const FAssetData& SDefault_GraphPinObject::GetAssetData(bool bRuntimePath) const
{
	// For normal assets, the editor and runtime path are the same
	if (GraphPinObj->DefaultObject)
	{
		if (!GraphPinObj->DefaultObject->GetPathName().Equals(CachedAssetData.GetObjectPathString(), ESearchCase::CaseSensitive))
		{
			// This always uses the exact object pointed at
			CachedAssetData = FAssetData(GraphPinObj->DefaultObject, true);
		}
	}
	else if (!GraphPinObj->DefaultValue.IsEmpty())
	{
		FSoftObjectPath ObjectPath = FSoftObjectPath(GraphPinObj->DefaultValue);
		if (ObjectPath != CachedAssetData.GetSoftObjectPath())
		{
			const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

			CachedAssetData = AssetRegistryModule.Get().GetAssetByObjectPath(ObjectPath);

			if (!CachedAssetData.IsValid())
			{
				FString PackageName = FPackageName::ObjectPathToPackageName(GraphPinObj->DefaultValue);
				FString PackagePath = FPackageName::GetLongPackagePath(PackageName);
				FString ObjectName = FPackageName::ObjectPathToObjectName(GraphPinObj->DefaultValue);

				// Fake one
				CachedAssetData = FAssetData(FName(*PackageName), FName(*PackagePath), FName(*ObjectName), UObject::StaticClass()->GetClassPathName());
			}
		}
	}
	else
	{
		if (CachedAssetData.IsValid())
		{
			CachedAssetData = FAssetData();
		}
	}

	return CachedAssetData; 
}

#undef LOCTEXT_NAMESPACE

#pragma endregion

#pragma region String
void SDefault_GraphPinString::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SDefault_GraphPinString::GetDefaultValueWidget()
{
	// Only allow actual string pins to be multi-line
	// Other text based pins (such as names and numbers) should be single-line only
	const bool bIsMultiLine = GraphPinObj->PinType.PinCategory == UEdGraphSchema_K2::PC_String;
	const auto& Body = UPinRestyleSettings::Get()->Inputs.String.Body.Get();
	auto Padding = UDefaultThemeSettings::GetMargin(Body.Padding);
	float ErrorReportingSpacing = UDefaultThemeSettings::GetSpacing(
		UPinRestyleSettings::Get()->Inputs.String.ErrorReportingSpacing);
	if (bIsMultiLine)
	{
		return SNew(SBox)
			.MinDesiredWidth(18)
			.MaxDesiredHeight(200)
		[
			SNew(SDefault_MultiLineEditableTextBox)
			.Style(FAppStyle::Get(), FPinRestyleStyles::Graph_EditableTextBox)
			.Text(this, &SDefault_GraphPinString::GetTypeInValue)
			.SelectAllTextWhenFocused(true)
			.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
			.IsReadOnly(this, &SDefault_GraphPinString::GetDefaultValueIsReadOnly)
			.OnTextCommitted(this, &SDefault_GraphPinString::SetTypeInValue)
			.WrapTextAt(400)
			.ModiferKeyForNewLine(EModifierKey::Shift)
			.ErrorReportingSpacing(ErrorReportingSpacing)
			//.Padding(Padding)
			//.DefaultScrollBarThickness(DefaultScrollBarThickness)
		];
	}
	else
	{
		return SNew(SBox)
			.MinDesiredWidth(18)
			.MaxDesiredWidth(400)
		[
			SNew(SDefault_EditableTextBox)
			.Style(FAppStyle::Get(), FPinRestyleStyles::Graph_EditableTextBox)
			.Text(this, &SDefault_GraphPinString::GetTypeInValue)
			.SelectAllTextWhenFocused(true)
			.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
			.IsReadOnly(this, &SDefault_GraphPinString::GetDefaultValueIsReadOnly)
			.OnTextCommitted(this, &SDefault_GraphPinString::SetTypeInValue)
			.ErrorReportingSpacing(ErrorReportingSpacing)
			//.Padding(Padding)
			//.DefaultScrollBarThickness(DefaultScrollBarThickness)
		];
	}
}

FText SDefault_GraphPinString::GetTypeInValue() const
{
	return FText::FromString(GraphPinObj->GetDefaultAsString());
}

void SDefault_GraphPinString::SetTypeInValue(const FText& NewTypeInValue, ETextCommit::Type /*CommitInfo*/)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	if (!GraphPinObj->GetDefaultAsString().Equals(NewTypeInValue.ToString()))
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("GraphEditor", "ChangeStringPinValue", "Change String Pin Value"));
		GraphPinObj->Modify();

		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, NewTypeInValue.ToString());
	}
}

bool SDefault_GraphPinString::GetDefaultValueIsReadOnly() const
{
	return GraphPinObj->bDefaultValueIsReadOnly;
}

#pragma endregion

#pragma region StructInstance


#define LOCTEXT_NAMESPACE "SGraphPinStructInstance"

void SDefault_GraphPinStructInstance::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	if (InGraphPinObj->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct && InGraphPinObj->PinType.
		PinSubCategoryObject.Get())
	{
		// See if a wrapper struct was passed in to use for automatic UI creation
		UScriptStruct* DataStruct = Cast<UScriptStruct>(InGraphPinObj->PinType.PinSubCategoryObject.Get());
		const UScriptStruct* PinEditableStruct = InArgs._StructEditWrapper;

		if (DataStruct && PinEditableStruct)
		{
			EditWrapperInstance = MakeShared<FStructOnScope>(PinEditableStruct);
		}
	}
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}


void SDefault_GraphPinStructInstance::ParseDefaultValueData()
{
	FPinStructEditWrapper* EditInstance = GetEditWrapper();

	if (EditInstance && GraphPinObj)
	{
		// Read Pin Data
		FString DefaultValueString = GraphPinObj->GetDefaultAsString();

		UScriptStruct* StructDefinition = const_cast<UScriptStruct*>(Cast<UScriptStruct>(
			EditInstance->GetDataScriptStruct()));

		FOutputDeviceNull NullOutput;
		StructDefinition->ImportText(*DefaultValueString, EditInstance->GetDataMemory(), nullptr,
		                             PPF_SerializedAsImportText, &NullOutput, GraphPinObj->PinName.ToString());
	}
}

void SDefault_GraphPinStructInstance::SaveDefaultValueData()
{
	FPinStructEditWrapper* EditInstance = GetEditWrapper();

	ensureMsgf(EditInstance,
	           TEXT("SaveDefaultValueData must be overriden by any widget that does not use an edit wrapper struct!"));

	if (EditInstance && GraphPinObj)
	{
		// Set Pin Data
		FString ExportText;

		UScriptStruct* StructDefinition = const_cast<UScriptStruct*>(Cast<UScriptStruct>(
			EditInstance->GetDataScriptStruct()));
		StructDefinition->ExportText(ExportText, EditInstance->GetDataMemory(), EditInstance->GetDataMemory(), nullptr,
		                             PPF_SerializedAsImportText, nullptr);

		if (ExportText != GraphPinObj->GetDefaultAsString())
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangePinValue", "Change Pin Value"));
			GraphPinObj->Modify();
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, ExportText);
			RefreshCachedData();
		}
	}
}

void SDefault_GraphPinStructInstance::RefreshCachedData()
{
	FPinStructEditWrapper* EditInstance = GetEditWrapper();

	if (EditInstance)
	{
		CachedDescription = EditInstance->GetPreviewDescription();
	}
}


TSharedRef<SWidget> SDefault_GraphPinStructInstance::GetDefaultValueWidget()
{
	if (GraphPinObj == nullptr)
	{
		return SNullWidget::NullWidget;
	}

	ParseDefaultValueData();

	//Create widget
	return SNew(SVerticalBox)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(ComboButton, SComboButton)
			.OnGetMenuContent(this, &SDefault_GraphPinStructInstance::GetEditContent)
			.ContentPadding(FMargin(2.0f, 2.0f))
			.ButtonContent()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("EditText", "Edit"))
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			GetDescriptionContent()
		];
}

TSharedRef<SWidget> SDefault_GraphPinStructInstance::GetEditContent()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(
		"PropertyEditor");

	FDetailsViewArgs ViewArgs;
	ViewArgs.bAllowSearch = false;
	ViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	ViewArgs.bHideSelectionTip = true;
	ViewArgs.bLockable = false;
	ViewArgs.bUpdatesFromSelection = false;
	ViewArgs.bShowOptions = false;
	ViewArgs.bShowModifiedPropertiesOption = false;

	FStructureDetailsViewArgs StructureViewArgs;
	StructureViewArgs.bShowObjects = true;
	StructureViewArgs.bShowAssets = true;
	StructureViewArgs.bShowClasses = true;
	StructureViewArgs.bShowInterfaces = true;

	StructureDetailsView = PropertyEditorModule.CreateStructureDetailView(
		ViewArgs, StructureViewArgs, EditWrapperInstance, LOCTEXT("DefaultValue", "Value"));
	StructureDetailsView->GetOnFinishedChangingPropertiesDelegate().AddSP(
		this, &SDefault_GraphPinStructInstance::PropertyValueChanged);

	return SNew(SBox)
		.MaxDesiredHeight(350)
		.MinDesiredWidth(350)
	[
		SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		[
			StructureDetailsView->GetWidget().ToSharedRef()
		]
	];
}

TSharedRef<SWidget> SDefault_GraphPinStructInstance::GetDescriptionContent()
{
	RefreshCachedData();

	return SNew(STextBlock)
		.Text(this, &SDefault_GraphPinStructInstance::GetCachedDescriptionText)
		.AutoWrapText(true);
}

FText SDefault_GraphPinStructInstance::GetCachedDescriptionText() const
{
	return CachedDescription;
}

FPinStructEditWrapper* SDefault_GraphPinStructInstance::GetEditWrapper() const
{
	if (EditWrapperInstance.IsValid() && EditWrapperInstance->IsValid())
	{
		return (FPinStructEditWrapper*)EditWrapperInstance->GetStructMemory();
	}
	return nullptr;
}

void SDefault_GraphPinStructInstance::PropertyValueChanged(const FPropertyChangedEvent& PropertyChangedEvent)
{
	SaveDefaultValueData();
}

#undef LOCTEXT_NAMESPACE

#pragma endregion

//
//void SDefault_GraphPinNameList::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//
//void SDefault_PhysicsAssetGraphNodeOutputPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}
//



#define LOCTEXT_NAMESPACE "SDefault_GraphPinPose"

/////////////////////////////////////////////////////
// SDefault_GraphPinPose

void SDefault_GraphPinPose::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InPin);

	CachedImg_Pin_ConnectedHovered = FAppStyle::GetBrush(TEXT("Graph.PosePin.ConnectedHovered"));
	CachedImg_Pin_Connected = FAppStyle::GetBrush(TEXT("Graph.PosePin.Connected"));
	CachedImg_Pin_DisconnectedHovered = FAppStyle::GetBrush(TEXT("Graph.PosePin.DisconnectedHovered"));
	CachedImg_Pin_Disconnected = FAppStyle::GetBrush(TEXT("Graph.PosePin.Disconnected"));

	ReconfigureWidgetForAttributes();
}

const FSlateBrush* SDefault_GraphPinPose::GetPinIcon() const
{
	const FSlateBrush* Brush = NULL;

	if (IsConnected())
	{
		Brush = IsHovered() ? CachedImg_Pin_ConnectedHovered : CachedImg_Pin_Connected;
	}
	else
	{
		Brush = IsHovered() ? CachedImg_Pin_DisconnectedHovered : CachedImg_Pin_Disconnected;
	}

	return Brush;
}


enum class EAttributeUsage
{
	// Attribute is input/output by the pin, but is not currently connected to a producer/consumer
	Unused,

	// Attribute is input/output by the pin and is currently connected to a producer/consumer
	Used,

	// Attribute is not an input/output of the pin but passes through the node
	Passthrough,
};

class SAttributeIndicator : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAttributeIndicator) {}

	SLATE_ARGUMENT(FName, Attribute)

		SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, UAnimBlueprint* InAnimBlueprint, const FAnimGraphAttributeDesc* InAttributeDesc, const UEdGraphPin* InPin, EAttributeUsage InUsage, const UAnimGraphNode_Base* InAnimGraphNode)
	{
		AnimBlueprint = InAnimBlueprint;
		AttributeDesc = InAttributeDesc;
		Pin = InPin;
		Usage = InUsage;
		AnimGraphNode = InAnimGraphNode;
		ActiveColor = AttributeDesc->Color.GetSpecifiedColor();
		Color = ActiveColor;
		Value = 0.0f;

		ChildSlot
			[
				SNew(SImage)
				.Visibility_Lambda([this]() { return Value == 0.0f ? EVisibility::Hidden : EVisibility::Visible; })
			.Image(&AttributeDesc->Icon)
			.ColorAndOpacity_Lambda([this]() { return Color; })
			];
	}

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override
	{
		bool bActive = false;

		if ((Usage == EAttributeUsage::Used || AttributeDesc->Blend == EAnimGraphAttributeBlend::Blendable) && AnimBlueprint && AnimBlueprint->GetObjectBeingDebugged() != nullptr)
		{
			UAnimBlueprintGeneratedClass* AnimBlueprintClass = (UAnimBlueprintGeneratedClass*)(*(AnimBlueprint->GeneratedClass));
			int32 SourceNodeId = AnimBlueprintClass->GetNodeIndexFromGuid(AnimGraphNode->NodeGuid);
			if (SourceNodeId != INDEX_NONE)
			{
				const TArray<FAnimBlueprintDebugData::FAttributeRecord>* LinkAttributes;
				if (Pin->Direction == EGPD_Input)
				{
					LinkAttributes = AnimBlueprintClass->GetAnimBlueprintDebugData().NodeInputAttributesThisFrame.Find(SourceNodeId);
				}
				else
				{
					LinkAttributes = AnimBlueprintClass->GetAnimBlueprintDebugData().NodeOutputAttributesThisFrame.Find(SourceNodeId);
				}

				bActive = LinkAttributes && LinkAttributes->ContainsByPredicate([this](const FAnimBlueprintDebugData::FAttributeRecord& InRecord) { return InRecord.Attribute == AttributeDesc->Name; });
			}
		}

		if (bActive)
		{
			Value = 1.0f;
		}
		else
		{
			Value = FMath::FInterpTo(Value, 0.0f, InDeltaTime, 4.0f);
		}

		Color = FMath::Lerp(FLinearColor::Transparent, ActiveColor, Value);
	}

	UAnimBlueprint* AnimBlueprint;
	const FAnimGraphAttributeDesc* AttributeDesc;
	const UEdGraphPin* Pin;
	EAttributeUsage Usage;
	const UAnimGraphNode_Base* AnimGraphNode;
	FLinearColor ActiveColor;
	FLinearColor Color;
	float Value;
};

void SDefault_GraphPinPose::ReconfigureWidgetForAttributes()
{
	AttributeInfos.Empty();

	if (UAnimGraphNode_Base* AnimGraphNode = Cast<UAnimGraphNode_Base>(GraphPinObj->GetOwningNode()))
	{
		if (UAnimBlueprint* AnimBlueprint = Cast<UAnimBlueprint>(FBlueprintEditorUtils::FindBlueprintForNode(AnimGraphNode)))
		{

			auto AddAttributes = [this, AnimBlueprint, AnimGraphNode](TArrayView<const FName> InUsedAttributes, TArrayView<const FName> InUnusedAttributes, TArrayView<const FName> InPassThroughAttributes)
			{
				auto AddAttribute = [this, AnimBlueprint, AnimGraphNode](FName InAttribute, EAttributeUsage InUsage)
				{
					const FAnimGraphAttributeDesc* AttributeDesc = GetDefault<UAnimGraphAttributes>()->FindAttributeDesc(InAttribute);

					// Early out if we don't want to display this attribute
					if (AttributeDesc)
					{
						if (AttributeDesc->DisplayMode == EAnimGraphAttributesDisplayMode::HideOnPins)
						{
							return;
						}

						// Only store cached attributes for wires on used pins
						if (InUsage != EAttributeUsage::Unused)
						{
							AttributeInfos.Emplace(InAttribute, AttributeDesc->Color.GetSpecifiedColor(), AttributeDesc->Blend, AttributeDesc->SortOrder);

							// Skip displaying passthrough attributes on pins
							if (InUsage != EAttributeUsage::Passthrough && AnimGraphNode->ShouldShowAttributesOnPins())
							{
								const UAnimGraphNode_Base* ProxyGraphNode = AnimGraphNode->GetProxyNodeForAttributes();

								GetLabelAndValue()->AddSlot()
									.Padding(2.0f, 0.0f, 0.0f, 0.0f)
									[
										SNew(SAttributeIndicator, AnimBlueprint, AttributeDesc, GraphPinObj, InUsage, ProxyGraphNode)
									];
							}
						}
					}
				};

				for (const FName& Attribute : InUsedAttributes)
				{
					AddAttribute(Attribute, EAttributeUsage::Used);
				}

				for (const FName& Attribute : InUnusedAttributes)
				{
					AddAttribute(Attribute, EAttributeUsage::Unused);
				}

				for (const FName& Attribute : InPassThroughAttributes)
				{
					AddAttribute(Attribute, EAttributeUsage::Passthrough);
				}
			};

			UAnimBlueprintGeneratedClass* AnimBlueprintClass = (UAnimBlueprintGeneratedClass*)(*(AnimBlueprint->GeneratedClass));

			UAnimGraphNode_Base::FNodeAttributeArray PinAttributes;
			switch (GraphPinObj->Direction)
			{
			case EGPD_Input:
				AnimGraphNode->GetInputLinkAttributes(PinAttributes);
				break;
			case EGPD_Output:
				AnimGraphNode->GetOutputLinkAttributes(PinAttributes);
				break;
			}

			UAnimGraphNode_Base::FNodeAttributeArray NodeAttributes;
			AnimGraphNode->GetInputLinkAttributes(NodeAttributes);
			AnimGraphNode->GetOutputLinkAttributes(NodeAttributes);

			// Unlinked pins display attributes if they are inputs and the node takes them as inputs
			if (GraphPinObj->LinkedTo.Num() == 0 || AnimBlueprintClass == nullptr)
			{
				AddAttributes(TArrayView<const FName>(), PinAttributes, TArrayView<const FName>());
			}
			else if (GraphPinObj->LinkedTo.Num() > 0)
			{
				TArrayView<const FName> CompilerGeneratedAttributes = AnimBlueprintClass->GetAnimBlueprintDebugData().GetNodeAttributes(AnimGraphNode);
				UAnimGraphNode_Base::FNodeAttributeArray UsedAttributes;
				UAnimGraphNode_Base::FNodeAttributeArray UnusedAttributes;
				if (PinAttributes.Num() > 0)
				{
					for (const FName& Name : PinAttributes)
					{
						if (CompilerGeneratedAttributes.Contains(Name))
						{
							UsedAttributes.Add(Name);
						}
						else
						{
							UnusedAttributes.Add(Name);
						}
					}
				}

				UAnimGraphNode_Base::FNodeAttributeArray PassthroughAttributes;
				for (const FName& Name : CompilerGeneratedAttributes)
				{
					if (!PinAttributes.Contains(Name))
					{
						PassthroughAttributes.Add(Name);
					}
				}

				AddAttributes(UsedAttributes, UnusedAttributes, PassthroughAttributes);
			}

			// sort pin attributes
			Algo::Sort(AttributeInfos, [](const FAttributeInfo& InValue0, const FAttributeInfo& InValue1)
				{
					return InValue0.SortOrder < InValue1.SortOrder;
				});

			// overrides attribute set in the base class Construct()
			SetToolTipText(MakeAttributeSP(this, &SDefault_GraphPinPose::GetAttributeTooltipText));
		}
	}
}

TArrayView<const SDefault_GraphPinPose::FAttributeInfo> SDefault_GraphPinPose::GetAttributeInfo() const
{
	SGraphNode* MyOwnerNode = OwnerNodePtr.Pin().Get();
	if (MyOwnerNode && MyOwnerNode->GetOwnerPanel().IsValid())
	{
		if (MyOwnerNode->GetOwnerPanel()->GetCurrentLOD() <= EGraphRenderingLOD::LowDetail)
		{
			return TArrayView<const FAttributeInfo>();
		}
	}

	return AttributeInfos;
}

float SDefault_GraphPinPose::GetZoomAmount() const
{
	SGraphNode* MyOwnerNode = OwnerNodePtr.Pin().Get();
	if (MyOwnerNode && MyOwnerNode->GetOwnerPanel().IsValid())
	{
		return MyOwnerNode->GetOwnerPanel()->GetZoomAmount();
	}

	return 1.0f;
}

FText SDefault_GraphPinPose::GetAttributeTooltipText() const
{
	if (GraphPinObj)
	{
		UEdGraphPin* OtherPin = GraphPinObj->LinkedTo.Num() > 0 ? GraphPinObj->LinkedTo[0] : nullptr;
		if (OtherPin)
		{
			UAnimGraphNode_Base* Node1 = Cast<UAnimGraphNode_Base>(GraphPinObj->GetOwningNode());
			UAnimGraphNode_Base* Node2 = Cast<UAnimGraphNode_Base>(OtherPin->GetOwningNode());
			if (Node1 && Node2)
			{
				if (UAnimBlueprint* AnimBlueprint = Cast<UAnimBlueprint>(FBlueprintEditorUtils::FindBlueprintForNode(Node1)))
				{
					if (AnimBlueprint->GetObjectBeingDebugged() != nullptr)
					{
						UAnimBlueprintGeneratedClass* AnimBlueprintClass = (UAnimBlueprintGeneratedClass*)(*(AnimBlueprint->GeneratedClass));
						int32 SourceNodeId = AnimBlueprintClass->GetNodeIndexFromGuid(Node1->NodeGuid);
						int32 TargetNodeId = AnimBlueprintClass->GetNodeIndexFromGuid(Node2->NodeGuid);

						if (AttributeInfos.Num() > 0)
						{
							FTextBuilder TextBuilder;
							TextBuilder.AppendLine(SGraphPin::GetTooltipText());

							bool bAddedAttributeSubtitle = false;

							for (const SDefault_GraphPinPose::FAttributeInfo& AttributeInfo : AttributeInfos)
							{


								if (SourceNodeId != INDEX_NONE && TargetNodeId != INDEX_NONE)
								{
									const TArray<FAnimBlueprintDebugData::FAttributeRecord>* LinkAttributes;

									if (GraphPinObj->Direction == EGPD_Input)
									{
										LinkAttributes = AnimBlueprintClass->GetAnimBlueprintDebugData().NodeInputAttributesThisFrame.Find(SourceNodeId);
									}
									else
									{
										LinkAttributes = AnimBlueprintClass->GetAnimBlueprintDebugData().NodeOutputAttributesThisFrame.Find(SourceNodeId);
									}

									const bool bAttributeUsedInLink = LinkAttributes && LinkAttributes->ContainsByPredicate(
										[&AttributeInfo, TargetNodeId](const FAnimBlueprintDebugData::FAttributeRecord& InRecord)
										{
											return InRecord.Attribute == AttributeInfo.Attribute && InRecord.OtherNode == TargetNodeId;
										});

									if (bAttributeUsedInLink)
									{
										if (!bAddedAttributeSubtitle)
										{
											TextBuilder.AppendLine(LOCTEXT("AttributesSubtitle", "Attributes:"));
											bAddedAttributeSubtitle = true;
										}

										TextBuilder.AppendLine(AttributeInfo.Attribute);
									}
								}
							}

							return TextBuilder.ToText();
						}
					}
				}
			}
		}
	}

	return SGraphPin::GetTooltipText();
}

#undef LOCTEXT_NAMESPACE