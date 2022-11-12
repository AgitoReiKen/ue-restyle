// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_Pins.h"

#include "ClassViewerFilter.h"
#include "ClassViewerModule.h"
#include "ContentBrowserModule.h"

#include "Themes/Default/PinRestyleDefault.h"

#include "Widgets/Input/SNumericEntryBox.h"

#include "EdGraphSchema_K2.h"
#include "IContentBrowserSingleton.h"

#include "SPinTypeSelector.h"
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
//void SDefault_GraphPinCollisionProfile::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
//{
//	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
//}

#pragma region GraphPin
void SDefault_GraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	const UGraphEditorSettings* GraphSettings = GetDefault<UGraphEditorSettings>();
	const auto& Style = UPinRestyleSettings::Get()->Base;
	const float Spacing = UDefaultThemeSettings::GetSpacing(Style.Spacing);
	bUsePinColorForText = InArgs._UsePinColorForText;
	SetCursor(EMouseCursor::Default);
	SetVisibility(MakeAttributeSP(this, &SDefault_GraphPin::GetPinVisiblity));
	GraphPinObj = InGraphPinObj;
	check(GraphPinObj != NULL);

	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	checkf(
		Schema,
		TEXT("Missing schema for pin: %s with outer: %s of type %s" ),
		*(GraphPinObj->GetName()),
		GraphPinObj->GetOuter() ? *(GraphPinObj->GetOuter()->GetName()) : TEXT("NULL OUTER"),
		GraphPinObj->GetOuter() ? *(GraphPinObj->GetOuter()->GetClass()->GetName()) : TEXT("NULL OUTER")
	);


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
	static const FName NAME_NoBorder("NoBorder");
	TSharedRef<SWidget> PinStatusIndicator =
		SNew(SButton)
		.ButtonStyle(FEditorStyle::Get(), NAME_NoBorder)
		.Visibility(this, &SDefault_GraphPin::GetPinStatusIconVisibility)
		.ContentPadding(0)
		.OnClicked(this, &SDefault_GraphPin::ClickedOnPinStatusIcon)
		[
			SNew(SImage)
			.Image(this, &SDefault_GraphPin::GetPinStatusIcon)
		];
	TSharedRef<SWidget> LabelWidget = GetLabelWidget(InArgs._PinLabelStyle);

	// Create the widget used for the pin body (status indicator, label, and value)
	LabelAndValue =
			SNew(SWrapBox)
			.PreferredSize(Style.PreferredWrapSize);

	TSharedPtr<SHorizontalBox> PinContent;
	if (GetDirection() == EGPD_Input)
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

		// Input pin
		FullPinHorizontalRowWidget = PinContent =
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
	else
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
		FullPinHorizontalRowWidget = PinContent = SNew(SHorizontalBox)
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
	// Set up a hover for pins that is tinted the color of the pin.
	SBorder::Construct(SBorder::FArguments()
	.BorderImage(FAppStyle::Get().GetBrush("NoBorder"))
	.Padding(0)
	.OnMouseButtonDown(this, &SDefault_GraphPin::OnPinNameMouseDown)
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
				PinContent.ToSharedRef()
			]
		]
		 
	]);

	TSharedPtr<IToolTip> TooltipWidget = SNew(SToolTip)
		.Text(this, &SDefault_GraphPin::GetTooltipText);

	SetToolTip(TooltipWidget);
}

SDefault_GraphPin::SDefault_GraphPin() : SGraphPin()
{
	CachedImg_SetPin_Connected = FAppStyle::Get().GetBrush(
		FPinRestyleStyles::Kismet_VariableList_SetTypeIcon_Connected);
	CachedImg_SetPin_Disconnected = FAppStyle::Get().GetBrush(
		FPinRestyleStyles::Kismet_VariableList_SetTypeIcon_Disconnected);
	CachedImg_MapPin_Value_Connected = FAppStyle::Get().GetBrush(
		FPinRestyleStyles::Kismet_VariableList_MapValueTypeIcon_Connected);
	CachedImg_MapPin_Value_Disconnected = FAppStyle::Get().GetBrush(
		FPinRestyleStyles::Kismet_VariableList_MapValueTypeIcon_Disconnected);
}

FSlateColor SDefault_GraphPin::GetPinTextColor() const
{
	const auto& Style = UPinRestyleSettings::Get()->Base;
	UEdGraphPin* GraphPin = GetPinObj();
	FLinearColor EditableState = FLinearColor(1, 1, 1, IsEditingEnabled() ? 1.0f : Style.NonEditableOpacity);
	// If there is no schema there is no owning node (or basically this is a deleted node)
	if (GraphPin)
	{
		if (GraphPin->bOrphanedPin)
		{
			return Style.OrphanedColor.Get() * EditableState;
		}
		if (GraphPin->bIsDiffing)
		{
			return Style.DiffingColor.Get() * EditableState;
		}
	}
	return Style.NormalColor.Get() * EditableState;
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
	const auto& Style = UPinRestyleSettings::Get()->Base;
	FLinearColor EditableState = FLinearColor(1, 1, 1, IsEditingEnabled() ? 1.0f : Style.NonEditableOpacity);
	UEdGraphPin* GraphPin = GetPinObj();
	if (GraphPin && !GraphPin->IsPendingKill())
	{
		if (GraphPin->bIsDiffing)
		{
			return EditableState * Style.DiffingColor.Get();
		}
		if (GraphPin->bOrphanedPin)
		{
			return EditableState * Style.OrphanedColor.Get();
		}
		if (const UEdGraphSchema* Schema = GraphPin->GetSchema())
		{
			return EditableState * Schema->GetPinTypeColor(GraphPin->PinType) * PinColorModifier;
		}
	}

	return EditableState * Style.NormalColor.Get();
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
	const auto& Style = UPinRestyleSettings::Get()->Base;
	FLinearColor EditableState = FLinearColor(1, 1, 1, IsEditingEnabled() ? 1.0f : Style.NonEditableOpacity);
	UEdGraphPin* GraphPin = GetPinObj();
	if (GraphPin && !GraphPin->IsPendingKill())
	{
		if (GraphPin->bIsDiffing)
		{
			return EditableState * Style.DiffingColor.Get();
		}
		if (GraphPin->bOrphanedPin)
		{
			return EditableState * Style.OrphanedColor.Get();
		}
		if (const UEdGraphSchema* Schema = GraphPin->GetSchema())
		{
			return EditableState * Schema->GetSecondaryPinTypeColor(GraphPin->PinType) * PinColorModifier;
		}
	}

	return EditableState * Style.NormalColor.Get();
}

TSharedRef<SWidget> SDefault_GraphPin::GetLabelWidget(const FName& InPinLabelStyle)
{
	return SNew(STextBlock)
		.Text(this, &SDefault_GraphPin::GetPinLabel)
		.TextStyle(FEditorStyle::Get(), InPinLabelStyle)
		.Visibility(this, &SDefault_GraphPin::GetPinLabelVisibility)
		.ColorAndOpacity(this, &SDefault_GraphPin::GetPinTextColor);
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
	FMargin ButtonTextPadidng = UDefaultThemeSettings::GetMargin(Button.Padding);
	//FLinearColor Color = Button.NormalForeground.Get();
	float SpacingBetweenTextAndArrow = UDefaultThemeSettings::GetSpacing(ComboButton.DownArrowSpacing);
	return SAssignNew(NameComboBox, SDefault_NameComboBox)
		.ItemStyle(FAppStyle::Get(), FPinRestyleStyles::ComboBox_Row)
		.Font(FAppStyle::Get().GetFontStyle(FPinRestyleStyles::ComboBox_Button_FontInfo))
		//.ColorAndOpacity(Color)
		.ButtonTextPadding(ButtonTextPadidng)
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

		return SNew(SComboButton)
			.ContentPadding(3)
			.MenuPlacement(MenuPlacement_BelowAnchor)
			.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
			.ButtonContent()
			[
				// Wrap in configurable box to restrain height/width of menu
				SNew(SBox)
				.MinDesiredWidth(84.0f)
				[
					SNew(STextBlock)
					.Text_Lambda(GetComboButtonText)
					.Font(FEditorStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")))
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
			Filter->RequiredInterface = FindObject<UClass>(ANY_PACKAGE, *PossibleInterface);
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
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
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

	FString CachedRuntimePath = CachedEditorAssetData.ObjectPath.ToString() + TEXT("_C");

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
			const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(
				TEXT("AssetRegistry"));

			CachedEditorAssetData = AssetRegistryModule.Get().GetAssetByObjectPath(FName(*EditorPath));

			if (!CachedEditorAssetData.IsValid())
			{
				FString PackageName = FPackageName::ObjectPathToPackageName(EditorPath);
				FString PackagePath = FPackageName::GetLongPackagePath(PackageName);
				FString ObjectName = FPackageName::ObjectPathToObjectName(EditorPath);

				// Fake one
				CachedEditorAssetData = FAssetData(FName(*PackageName), FName(*PackagePath), FName(*ObjectName),
				                                   UObject::StaticClass()->GetFName());
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

	virtual bool IsUnloadedStructAllowed(const FStructViewerInitializationOptions& InInitOptions,
	                                     const FName InStructPath,
	                                     TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override
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
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
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

	return SNew(SPinTypeSelector, FGetPinTypeTree::CreateUObject(Schema, &UEdGraphSchema_K2::GetVariableTypeTree))
		.TargetPinType(this, &SDefault_GraphPinIndex::OnGetPinType)
		.OnPinTypeChanged(this, &SDefault_GraphPinIndex::OnTypeChanged)
		.Schema(Schema)
		.TypeTreeFilter(ETypeTreeFilter::IndexTypesOnly)
		.IsEnabled(true)
		.bAllowArrays(false);
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

		virtual void RequestRefresh() override
		{
		}

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
		.Style(FEditorStyle::Get(), FPinRestyleStyles::Graph_EditableTextBox)
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
	CachedImg_Pin_ConnectedHovered = FEditorStyle::GetBrush(TEXT("Graph.ExecPin.ConnectedHovered"));
	CachedImg_Pin_Connected = FEditorStyle::GetBrush(TEXT("Graph.ExecPin.Connected"));
	CachedImg_Pin_DisconnectedHovered = FEditorStyle::GetBrush(TEXT("Graph.ExecPin.DisconnectedHovered"));
	CachedImg_Pin_Disconnected = FEditorStyle::GetBrush(TEXT("Graph.ExecPin.Disconnected"));
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
			.Style(FEditorStyle::Get(), FPinRestyleStyles::Graph_EditableTextBox)
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
					+SHorizontalBox::Slot()
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
			+ SHorizontalBox::Slot().Padding(0,0, GeneralSpacing, 0)
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
					.Image(FAppStyle::Get().GetBrush("Icons.CircleArrowLeft"))
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
					.Image(FAppStyle::Get().GetBrush("Icons.Search"))
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
	AssetPickerConfig.Filter.ClassNames.Add(AllowedClass->GetFName());
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
		AssetPickerConfig.Filter.ClassNames.Empty();

		// Parse and add the classes from the metadata
		TArray<FString> AllowedClassesFilterNames;
		AllowedClassesFilterString.ParseIntoArrayWS(AllowedClassesFilterNames, TEXT(","), true);
		for (const FString& AllowedClassesFilterName : AllowedClassesFilterNames)
		{
			AssetPickerConfig.Filter.ClassNames.Add(FName(*AllowedClassesFilterName));
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
			AssetPickerConfig.Filter.RecursiveClassesExclusionSet.Add(FName(*DisallowedClassesFilterName));
		}
	}

	return
		SNew(SBox)
		.HeightOverride(300)
		.WidthOverride(300)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Menu.Background"))
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
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, AssetData.ObjectPath.ToString());
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
		if (!GraphPinObj->DefaultObject->GetPathName().Equals(CachedAssetData.ObjectPath.ToString(),
		                                                      ESearchCase::CaseSensitive))
		{
			// This always uses the exact object pointed at
			CachedAssetData = FAssetData(GraphPinObj->DefaultObject, true);
		}
	}
	else if (!GraphPinObj->DefaultValue.IsEmpty())
	{
		FName ObjectPath = FName(*GraphPinObj->DefaultValue);
		if (ObjectPath != CachedAssetData.ObjectPath)
		{
			const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(
				TEXT("AssetRegistry"));

			CachedAssetData = AssetRegistryModule.Get().GetAssetByObjectPath(ObjectPath);

			if (!CachedAssetData.IsValid())
			{
				FString PackageName = FPackageName::ObjectPathToPackageName(GraphPinObj->DefaultValue);
				FString PackagePath = FPackageName::GetLongPackagePath(PackageName);
				FString ObjectName = FPackageName::ObjectPathToObjectName(GraphPinObj->DefaultValue);

				// Fake one
				CachedAssetData = FAssetData(FName(*PackageName), FName(*PackagePath), FName(*ObjectName),
				                             UObject::StaticClass()->GetFName());
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
			.Style(FEditorStyle::Get(), FPinRestyleStyles::Graph_EditableTextBox)
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
			.Style(FEditorStyle::Get(), FPinRestyleStyles::Graph_EditableTextBox)
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
			.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
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

#pragma region Vector
#define LOCTEXT_NAMESPACE "VectorTextBox"

void SDefault_GraphPinVector::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

//Class implementation to create 3 editable text boxes to represent vector/rotator graph pin
class SVectorTextBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVectorTextBox)
		{
		}

		SLATE_ATTRIBUTE(FString, VisibleText_0)
		SLATE_ATTRIBUTE(FString, VisibleText_1)
		SLATE_ATTRIBUTE(FString, VisibleText_2)
		SLATE_EVENT(FOnFloatValueCommitted, OnFloatCommitted_Box_0)
		SLATE_EVENT(FOnFloatValueCommitted, OnFloatCommitted_Box_1)
		SLATE_EVENT(FOnFloatValueCommitted, OnFloatCommitted_Box_2)
	SLATE_END_ARGS()

	//Construct editable text boxes with the appropriate getter & setter functions along with tool tip text
	void Construct(const FArguments& InArgs, const bool bInIsRotator)
	{
		const auto& Vector = UPinRestyleSettings::Get()->Inputs.Vector;
		const auto& Base = UPinRestyleSettings::Get()->Base;
		float BaseSpacing = UDefaultThemeSettings::GetSpacing(Base.Spacing);
		float LabelSpacing = UDefaultThemeSettings::GetSpacing(Vector.Spacing);
		bIsRotator = bInIsRotator;
		const bool bUseRPY = Vector.bNewLabelsForRotator;
		VisibleText_0 = InArgs._VisibleText_0;
		VisibleText_1 = InArgs._VisibleText_1;
		VisibleText_2 = InArgs._VisibleText_2;
		const FLinearColor LabelClr = Vector.LabelsColor.Get();
		const FLinearColor XColor = Vector.ForegroundX.Get();
		const FLinearColor YColor = Vector.ForegroundY.Get();
		const FLinearColor ZColor = Vector.ForegroundZ.Get();
		// @formatter:off
		this->ChildSlot
			[
			 
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth().Padding(0, 0, 0, 0).HAlign(HAlign_Fill)
				[
					//Create Text box 0 
					SNew(SNumericEntryBox<float>)
					.LabelVAlign(VAlign_Center)
					.Label()
					[
						SNew(STextBlock)
						.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
						.Text(bIsRotator && bUseRPY
							? LOCTEXT("VectorNodeRollValueLabel", "R")
							: LOCTEXT("VectorNodeXAxisValueLabel", "X"))
							.ColorAndOpacity(LabelClr)
					]
					.LabelPadding(FMargin(0, 0, LabelSpacing, 0))
					.Value(this, &SVectorTextBox::GetTypeInValue_0)
					.OnValueCommitted(InArgs._OnFloatCommitted_Box_0)
					.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
					.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
					.ToolTipText(bIsRotator
						? LOCTEXT("VectorNodeRollValueLabel_ToolTip", "Roll value (around X)")
						: LOCTEXT("VectorNodeXAxisValueLabel_ToolTip", "X value"))
					.EditableTextBoxStyle(&FEditorStyle::GetWidgetStyle<FEditableTextBoxStyle>(
						FPinRestyleStyles::Graph_VectorEditableTextBox))
					.BorderForegroundColor(XColor)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth().Padding(BaseSpacing, 0, 0, 0).HAlign(HAlign_Fill)
				[
					//Create Text box 1
					SNew(SNumericEntryBox<float>)
					.LabelVAlign(VAlign_Center)
					.Label()
					[
						SNew(STextBlock)
						.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
						.Text(bIsRotator && bUseRPY
						? LOCTEXT("VectorNodePitchValueLabel", "P")
						: LOCTEXT("VectorNodeYAxisValueLabel", "Y"))
						.ColorAndOpacity(LabelClr)
					]
					.LabelPadding(FMargin(0, 0, LabelSpacing, 0))
					.Value(this, &SVectorTextBox::GetTypeInValue_1)
					.OnValueCommitted(InArgs._OnFloatCommitted_Box_1)
					.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
					.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
					.ToolTipText(bIsRotator
						? LOCTEXT("VectorNodePitchValueLabel_ToolTip", "Pitch value (around Y)")
						: LOCTEXT("VectorNodeYAxisValueLabel_ToolTip", "Y value"))
					.EditableTextBoxStyle(&FEditorStyle::GetWidgetStyle<FEditableTextBoxStyle>(
						FPinRestyleStyles::Graph_VectorEditableTextBox))
					.BorderForegroundColor(YColor)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth().Padding(BaseSpacing, 0, 0, 0).HAlign(HAlign_Fill)
				[
					//Create Text box 2
					SNew(SNumericEntryBox<float>)
					.LabelVAlign(VAlign_Center)
					.Label()
					[
						SNew(STextBlock)
						.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
						.Text(bIsRotator && bUseRPY
						? LOCTEXT("VectorNodeYawValueLabel", "Y")
						: LOCTEXT("VectorNodeZAxisValueLabel", "Z"))
						.ColorAndOpacity(LabelClr)
					]
					.LabelPadding(FMargin(0, 0, LabelSpacing, 0))
					.Value(this, &SVectorTextBox::GetTypeInValue_2)
					.OnValueCommitted(InArgs._OnFloatCommitted_Box_2)
					.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
					.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
					.ToolTipText(bIsRotator
						? LOCTEXT("VectorNodeYawValueLabel_Tooltip", "Yaw value (around Z)")
						: LOCTEXT("VectorNodeZAxisValueLabel_ToolTip", "Z value"))
					.EditableTextBoxStyle(&FEditorStyle::GetWidgetStyle<FEditableTextBoxStyle>(
						FPinRestyleStyles::Graph_VectorEditableTextBox))
					.BorderForegroundColor(ZColor)
					]
			];
		// @formatter:on
	}

private:
	//Get value for text box 0
	TOptional<float> GetTypeInValue_0() const
	{
		return FCString::Atof(*(VisibleText_0.Get()));
	}

	//Get value for text box 1
	TOptional<float> GetTypeInValue_1() const
	{
		return FCString::Atof(*(VisibleText_1.Get()));
	}

	//Get value for text box 2
	TOptional<float> GetTypeInValue_2() const
	{
		return FCString::Atof(*(VisibleText_2.Get()));
	}

	TAttribute<FString> VisibleText_0;
	TAttribute<FString> VisibleText_1;
	TAttribute<FString> VisibleText_2;

	bool bIsRotator;
};

TSharedRef<SWidget> SDefault_GraphPinVector::GetDefaultValueWidget()
{
	UScriptStruct* RotatorStruct = TBaseStructure<FRotator>::Get();
	bIsRotator = (GraphPinObj->PinType.PinSubCategoryObject == RotatorStruct) ? true : false;

	//Create widget
	return SNew(SVectorTextBox, bIsRotator)
		.VisibleText_0(this, &SDefault_GraphPinVector::GetCurrentValue_0)
		.VisibleText_1(this, &SDefault_GraphPinVector::GetCurrentValue_1)
		.VisibleText_2(this, &SDefault_GraphPinVector::GetCurrentValue_2)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
		.OnFloatCommitted_Box_0(this, &SDefault_GraphPinVector::OnChangedValueTextBox_0)
		.OnFloatCommitted_Box_1(this, &SDefault_GraphPinVector::OnChangedValueTextBox_1)
		.OnFloatCommitted_Box_2(this, &SDefault_GraphPinVector::OnChangedValueTextBox_2);
}

//Rotator is represented as X->Roll, Y->Pitch, Z->Yaw

FString SDefault_GraphPinVector::GetCurrentValue_0() const
{
	//Text box 0: Rotator->Roll, Vector->X
	return GetValue(bIsRotator ? TextBox_2 : TextBox_0);
}

FString SDefault_GraphPinVector::GetCurrentValue_1() const
{
	//Text box 1: Rotator->Pitch, Vector->Y
	return GetValue(bIsRotator ? TextBox_0 : TextBox_1);
}

FString SDefault_GraphPinVector::GetCurrentValue_2() const
{
	//Text box 2: Rotator->Yaw, Vector->Z
	return GetValue(bIsRotator ? TextBox_1 : TextBox_2);
}

FString SDefault_GraphPinVector::GetValue(ETextBoxIndex Index) const
{
	FString DefaultString = GraphPinObj->GetDefaultAsString();
	TArray<FString> ResultString;

	//Parse string to split its contents separated by ','
	DefaultString.TrimStartInline();
	DefaultString.TrimEndInline();
	DefaultString.ParseIntoArray(ResultString, TEXT(","), true);

	if (Index < ResultString.Num())
	{
		return ResultString[Index];
	}
	else
	{
		return FString(TEXT("0"));
	}
}

void SDefault_GraphPinVector::OnChangedValueTextBox_0(float NewValue, ETextCommit::Type CommitInfo)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);

	FString DefaultValue;
	if (bIsRotator)
	{
		//Update Roll value
		DefaultValue = GetValue(TextBox_0) + FString(TEXT(",")) + GetValue(TextBox_1) + FString(TEXT(",")) + ValueStr;
	}
	else
	{
		//Update X value
		DefaultValue = ValueStr + FString(TEXT(",")) + GetValue(TextBox_1) + FString(TEXT(",")) + GetValue(TextBox_2);
	}

	if (GraphPinObj->GetDefaultAsString() != DefaultValue)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("GraphEditor", "ChangeVectorPinValue", "Change Vector Pin Value"));
		GraphPinObj->Modify();

		//Set new default value
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
	}
}

void SDefault_GraphPinVector::OnChangedValueTextBox_1(float NewValue, ETextCommit::Type CommitInfo)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);

	FString DefaultValue;
	if (bIsRotator)
	{
		//Update Pitch value
		DefaultValue = ValueStr + FString(TEXT(",")) + GetValue(TextBox_1) + FString(TEXT(",")) + GetValue(TextBox_2);
	}
	else
	{
		//Update Y value
		DefaultValue = GetValue(TextBox_0) + FString(TEXT(",")) + ValueStr + FString(TEXT(",")) + GetValue(TextBox_2);
	}

	if (GraphPinObj->GetDefaultAsString() != DefaultValue)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("GraphEditor", "ChangeVectorPinValue", "Change Vector Pin Value"));
		GraphPinObj->Modify();

		//Set new default value
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
	}
}

void SDefault_GraphPinVector::OnChangedValueTextBox_2(float NewValue, ETextCommit::Type CommitInfo)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);

	FString DefaultValue;
	if (bIsRotator)
	{
		//Update Yaw value
		DefaultValue = GetValue(TextBox_0) + FString(TEXT(",")) + ValueStr + FString(TEXT(",")) + GetValue(TextBox_2);
	}
	else
	{
		//Update Z value
		DefaultValue = GetValue(TextBox_0) + FString(TEXT(",")) + GetValue(TextBox_1) + FString(TEXT(",")) + ValueStr;
	}

	if (GraphPinObj->GetDefaultAsString() != DefaultValue)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("GraphEditor", "ChangeVectorPinValue", "Change Vector Pin Value"));
		GraphPinObj->Modify();

		//Set new default value
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
	}
}
#undef LOCTEXT_NAMESPACE
#pragma endregion

#pragma region Vector2D

void SDefault_GraphPinVector2D::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

#define LOCTEXT_NAMESPACE "VectorTextBox"

//Class implementation to create 2 editable text boxes to represent vector2D graph pin
class SVector2DTextBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVector2DTextBox)
		{
		}

		SLATE_ATTRIBUTE(FString, VisibleText_X)
		SLATE_ATTRIBUTE(FString, VisibleText_Y)
		SLATE_EVENT(FOnFloatValueCommitted, OnFloatCommitted_Box_X)
		SLATE_EVENT(FOnFloatValueCommitted, OnFloatCommitted_Box_Y)
	SLATE_END_ARGS()

	//Construct editable text boxes with the appropriate getter & setter functions along with tool tip text
	void Construct(const FArguments& InArgs)
	{
		const auto& Vector = UPinRestyleSettings::Get()->Inputs.Vector;
		const auto& Base = UPinRestyleSettings::Get()->Base;
		float BaseSpacing = UDefaultThemeSettings::GetSpacing(Base.Spacing);
		float LabelSpacing = UDefaultThemeSettings::GetSpacing(Vector.Spacing);
		const FLinearColor LabelClr = Vector.LabelsColor.Get();
		const FLinearColor XColor = Vector.ForegroundX.Get();
		const FLinearColor YColor = Vector.ForegroundY.Get();
		VisibleText_X = InArgs._VisibleText_X;
		VisibleText_Y = InArgs._VisibleText_Y;

		this->ChildSlot
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .AutoWidth().Padding(0, 0, 0, 0).HAlign(HAlign_Fill)
			[
				//Create Text box 0 
				SNew(SNumericEntryBox<float>)
				.LabelVAlign(VAlign_Center)
				.Label()
				                             [
					                             SNew(STextBlock)
					.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
					.Text(LOCTEXT("VectorNodeXAxisValueLabel", "X"))
					.ColorAndOpacity(LabelClr)
				                             ]
				.LabelPadding(FMargin(0, 0, LabelSpacing, 0))
				.Value(this, &SVector2DTextBox::GetTypeInValue_X)
				.OnValueCommitted(InArgs._OnFloatCommitted_Box_X)
				.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
				.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
				.ToolTipText(LOCTEXT("VectorNodeXAxisValueLabel_ToolTip", "X value"))
				.EditableTextBoxStyle(
					                             &FEditorStyle::GetWidgetStyle<FEditableTextBoxStyle>(
						                             FPinRestyleStyles::Graph_VectorEditableTextBox))
				.BorderForegroundColor(XColor)
			]
			+ SHorizontalBox::Slot()
			  .AutoWidth().Padding(BaseSpacing, 0, 0, 0).HAlign(HAlign_Fill)
			[
				//Create Text box 1
				SNew(SNumericEntryBox<float>)
				.LabelVAlign(VAlign_Center)
				.Label()
				                             [
					                             SNew(STextBlock)
					.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
					.Text(LOCTEXT("VectorNodeYAxisValueLabel", "Y"))
					.ColorAndOpacity(LabelClr)
				                             ]
				.LabelPadding(FMargin(0, 0, LabelSpacing, 0))
				.Value(this, &SVector2DTextBox::GetTypeInValue_Y)
				.OnValueCommitted(InArgs._OnFloatCommitted_Box_Y)
				.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
				.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
				.ToolTipText(LOCTEXT("VectorNodeYAxisValueLabel_ToolTip", "Y value"))
				.EditableTextBoxStyle(
					                             &FEditorStyle::GetWidgetStyle<FEditableTextBoxStyle>(
						                             FPinRestyleStyles::Graph_VectorEditableTextBox))
				.BorderForegroundColor(YColor)
			]
		];
	}

private:
	//Get value for X text box
	TOptional<float> GetTypeInValue_X() const
	{
		return FCString::Atof(*(VisibleText_X.Get()));
	}

	//Get value for Y text box
	TOptional<float> GetTypeInValue_Y() const
	{
		return FCString::Atof(*(VisibleText_Y.Get()));
	}

	TAttribute<FString> VisibleText_X;
	TAttribute<FString> VisibleText_Y;
};

TSharedRef<SWidget> SDefault_GraphPinVector2D::GetDefaultValueWidget()
{
	//Create widget
	return SNew(SVector2DTextBox)
		.VisibleText_X(this, &SDefault_GraphPinVector2D::GetCurrentValue_X)
		.VisibleText_Y(this, &SDefault_GraphPinVector2D::GetCurrentValue_Y)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
		.OnFloatCommitted_Box_X(this, &SDefault_GraphPinVector2D::OnChangedValueTextBox_X)
		.OnFloatCommitted_Box_Y(this, &SDefault_GraphPinVector2D::OnChangedValueTextBox_Y);
}

FString SDefault_GraphPinVector2D::GetCurrentValue_X() const
{
	return GetValue(TextBox_X);
}

FString SDefault_GraphPinVector2D::GetCurrentValue_Y() const
{
	return GetValue(TextBox_Y);
}

FString SDefault_GraphPinVector2D::GetValue(ETextBoxIndex Index) const
{
	FString DefaultString = GraphPinObj->GetDefaultAsString();
	TArray<FString> ResultString;

	FVector2D Value;
	Value.InitFromString(DefaultString);

	if (Index == TextBox_X)
	{
		return FString::Printf(TEXT("%f"), Value.X);
	}
	else
	{
		return FString::Printf(TEXT("%f"), Value.Y);
	}
}

FString MakeVector2DString(const FString& X, const FString& Y)
{
	return FString(TEXT("(X=")) + X + FString(TEXT(",Y=")) + Y + FString(TEXT(")"));
}

void SDefault_GraphPinVector2D::OnChangedValueTextBox_X(float NewValue, ETextCommit::Type CommitInfo)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);
	const FString Vector2DString = MakeVector2DString(ValueStr, GetValue(TextBox_Y));

	if (GraphPinObj->GetDefaultAsString() != Vector2DString)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("GraphEditor", "ChangeVectorPinValue", "Change Vector Pin Value"));
		GraphPinObj->Modify();

		//Set new default value
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, Vector2DString);
	}
}

void SDefault_GraphPinVector2D::OnChangedValueTextBox_Y(float NewValue, ETextCommit::Type CommitInfo)
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}

	const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);
	const FString Vector2DString = MakeVector2DString(GetValue(TextBox_X), ValueStr);

	if (GraphPinObj->GetDefaultAsString() != Vector2DString)
	{
		const FScopedTransaction Transaction(
			NSLOCTEXT("GraphEditor", "ChangeVectorPinValue", "Change Vector Pin Value"));
		GraphPinObj->Modify();

		//Set new default value
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, Vector2DString);
	}
}

#undef LOCTEXT_NAMESPACE

#pragma endregion

#pragma region Vector4

#define LOCTEXT_NAMESPACE "VectorTextBox"

class SVector4TextBox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVector4TextBox)
		{
		}

		SLATE_ATTRIBUTE(FString, VisibleText_0)
		SLATE_ATTRIBUTE(FString, VisibleText_1)
		SLATE_ATTRIBUTE(FString, VisibleText_2)
		SLATE_ATTRIBUTE(FString, VisibleText_3)
		SLATE_EVENT(FOnFloatValueCommitted, OnFloatCommitted_Box_0)
		SLATE_EVENT(FOnFloatValueCommitted, OnFloatCommitted_Box_1)
		SLATE_EVENT(FOnFloatValueCommitted, OnFloatCommitted_Box_2)
		SLATE_EVENT(FOnFloatValueCommitted, OnFloatCommitted_Box_3)
	SLATE_END_ARGS()

	//Construct editable text boxes with the appropriate getter & setter functions along with tool tip text
	void Construct(const FArguments& InArgs)
	{
		VisibleText_0 = InArgs._VisibleText_0;
		VisibleText_1 = InArgs._VisibleText_1;
		VisibleText_2 = InArgs._VisibleText_2;
		VisibleText_3 = InArgs._VisibleText_3;
		const auto& Vector = UPinRestyleSettings::Get()->Inputs.Vector;
		const auto& Base = UPinRestyleSettings::Get()->Base;
		float BaseSpacing = UDefaultThemeSettings::GetSpacing(Base.Spacing);
		float LabelSpacing = UDefaultThemeSettings::GetSpacing(Vector.Spacing);
		const FLinearColor LabelClr = Vector.LabelsColor.Get();
		const FLinearColor XColor = Vector.ForegroundX.Get();
		const FLinearColor YColor = Vector.ForegroundY.Get();
		const FLinearColor ZColor = Vector.ForegroundZ.Get();
		const FLinearColor WColor = Vector.ForegroundW.Get();
		//@formatter:off
		this->ChildSlot
		[

			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .AutoWidth().Padding(0).HAlign(HAlign_Fill)
			[
				//Create Text box 0 
				SNew(SNumericEntryBox<float>)
				.LabelVAlign(VAlign_Center)
				.Label()
				                             [
					                             SNew(STextBlock)
					.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
					.Text(LOCTEXT("VectorNodeXAxisValueLabel", "X"))
					.ColorAndOpacity(LabelClr)
				                             ]
				.LabelPadding(FMargin(0, 0, LabelSpacing, 0))
				.Value(this, &SVector4TextBox::GetTypeInValue_0)
				.OnValueCommitted(InArgs._OnFloatCommitted_Box_0)
				.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
				.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
				.ToolTipText(LOCTEXT("VectorNodeXAxisValueLabel_ToolTip", "X value"))
				.EditableTextBoxStyle(&FEditorStyle::GetWidgetStyle<FEditableTextBoxStyle>(
					                             FPinRestyleStyles::Graph_VectorEditableTextBox))
				.BorderForegroundColor(XColor)
			]
			+ SHorizontalBox::Slot()
			  .AutoWidth().Padding(BaseSpacing, 0, 0, 0).HAlign(HAlign_Fill)
			[
				//Create Text box 1
				SNew(SNumericEntryBox<float>)
				.LabelVAlign(VAlign_Center)
				.Label()
				                             [
					                             SNew(STextBlock)
					.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
					.Text(LOCTEXT("VectorNodeYAxisValueLabel", "Y"))
					.ColorAndOpacity(LabelClr)
				                             ]
				.LabelPadding(FMargin(0, 0, LabelSpacing, 0))
				.Value(this, &SVector4TextBox::GetTypeInValue_1)
				.OnValueCommitted(InArgs._OnFloatCommitted_Box_1)
				.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
				.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
				.ToolTipText(LOCTEXT("VectorNodeYAxisValueLabel_ToolTip", "Y value"))
				.EditableTextBoxStyle(&FEditorStyle::GetWidgetStyle<FEditableTextBoxStyle>(
					                             FPinRestyleStyles::Graph_VectorEditableTextBox))
				.BorderForegroundColor(YColor)
			]
			+ SHorizontalBox::Slot()
			  .AutoWidth().Padding(BaseSpacing, 0, 0, 0).HAlign(HAlign_Fill)
			[
				//Create Text box 2
				SNew(SNumericEntryBox<float>)
				.LabelVAlign(VAlign_Center)
				.Label()
				                             [
					                             SNew(STextBlock)
					.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
					.Text(LOCTEXT("VectorNodeZAxisValueLabel", "Z"))
					.ColorAndOpacity(LabelClr)
				                             ]
				.LabelPadding(FMargin(0, 0, LabelSpacing, 0))
				.Value(this, &SVector4TextBox::GetTypeInValue_2)
				.OnValueCommitted(InArgs._OnFloatCommitted_Box_2)
				.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
				.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
				.ToolTipText(LOCTEXT("VectorNodeZAxisValueLabel_ToolTip", "Z value"))
				.EditableTextBoxStyle(&FEditorStyle::GetWidgetStyle<FEditableTextBoxStyle>(
					                             FPinRestyleStyles::Graph_VectorEditableTextBox))
				.BorderForegroundColor(ZColor)
			]
			+ SHorizontalBox::Slot()
			  .AutoWidth().Padding(BaseSpacing, 0, 0, 0).HAlign(HAlign_Fill)
			[
				//Create Text box 3
				SNew(SNumericEntryBox<float>)
				.LabelVAlign(VAlign_Center)
				.Label()
				                             [
					                             SNew(STextBlock)
					.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
					.Text(LOCTEXT("VectorNodeWAxisValueLabel", "W"))
					.ColorAndOpacity(LabelClr)
				                             ]
				.LabelPadding(FMargin(0, 0, LabelSpacing, 0))
				.Value(this, &SVector4TextBox::GetTypeInValue_3)
				.OnValueCommitted(InArgs._OnFloatCommitted_Box_3)
				.Font(FEditorStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
				.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
				.ToolTipText(LOCTEXT("VectorNodeWAxisValueLabel_ToolTip", "W value"))
				.EditableTextBoxStyle(&FEditorStyle::GetWidgetStyle<FEditableTextBoxStyle>(
					                             FPinRestyleStyles::Graph_VectorEditableTextBox))
				.BorderForegroundColor(WColor)
			]

		];
		//@formatter:on
	}

private:
	//Get value for text box 0
	TOptional<float> GetTypeInValue_0() const
	{
		return FCString::Atof(*(VisibleText_0.Get()));
	}

	//Get value for text box 1
	TOptional<float> GetTypeInValue_1() const
	{
		return FCString::Atof(*(VisibleText_1.Get()));
	}

	//Get value for text box 2
	TOptional<float> GetTypeInValue_2() const
	{
		return FCString::Atof(*(VisibleText_2.Get()));
	}

	//Get value for text box 3
	TOptional<float> GetTypeInValue_3() const
	{
		return FCString::Atof(*(VisibleText_3.Get()));
	}

	TAttribute<FString> VisibleText_0;
	TAttribute<FString> VisibleText_1;
	TAttribute<FString> VisibleText_2;
	TAttribute<FString> VisibleText_3;
};

void SDefault_GraphPinVector4::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SDefault_GraphPinVector4::GetDefaultValueWidget()
{
	return SNew(SVector4TextBox)
		.VisibleText_0(this, &SDefault_GraphPinVector4::GetCurrentValue_0)
		.VisibleText_1(this, &SDefault_GraphPinVector4::GetCurrentValue_1)
		.VisibleText_2(this, &SDefault_GraphPinVector4::GetCurrentValue_2)
		.VisibleText_3(this, &SDefault_GraphPinVector4::GetCurrentValue_3)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
		.OnFloatCommitted_Box_0(this, &SDefault_GraphPinVector4::OnChangedValueTextBox_0)
		.OnFloatCommitted_Box_1(this, &SDefault_GraphPinVector4::OnChangedValueTextBox_1)
		.OnFloatCommitted_Box_2(this, &SDefault_GraphPinVector4::OnChangedValueTextBox_2)
		.OnFloatCommitted_Box_3(this, &SDefault_GraphPinVector4::OnChangedValueTextBox_3);
}

//Rotator is represented as X->Roll, Y->Pitch, Z->Yaw

FString SDefault_GraphPinVector4::GetCurrentValue_0() const
{
	//Text box 0: Rotator->Roll, Vector->X
	return GetValue(TextBox_0);
}

FString SDefault_GraphPinVector4::GetCurrentValue_1() const
{
	//Text box 1: Rotator->Pitch, Vector->Y
	return GetValue(TextBox_1);
}

FString SDefault_GraphPinVector4::GetCurrentValue_2() const
{
	//Text box 2: Rotator->Yaw, Vector->Z
	return GetValue(TextBox_2);
}

FString SDefault_GraphPinVector4::GetCurrentValue_3() const
{
	//Text box 3: Vector->W
	return GetValue(TextBox_3);
}

FString SDefault_GraphPinVector4::GetValue(ETextBoxIndex Index) const
{
	FString DefaultString = GraphPinObj->GetDefaultAsString();
	TArray<FString> ResultString;
	FVector4 Vector;
	Vector.InitFromString(DefaultString);

	if (Index == ETextBoxIndex::TextBox_0)
	{
		return FString::Printf(TEXT("%f"), Vector.X);
	}
	if (Index == ETextBoxIndex::TextBox_1)
	{
		return FString::Printf(TEXT("%f"), Vector.Y);
	}
	if (Index == ETextBoxIndex::TextBox_2)
	{
		return FString::Printf(TEXT("%f"), Vector.Z);
	}
	if (Index == ETextBoxIndex::TextBox_3)
	{
		return FString::Printf(TEXT("%f"), Vector.W);
	}
	return FString::Printf(TEXT("0"));
}


void SDefault_GraphPinVector4::OnChangedValueTextBox_0(float NewValue, ETextCommit::Type CommitInfo)
{
	const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);

	//Update X value
	FString DefaultValue = FString::Printf(TEXT("(X=%s,Y=%s,Z=%s,W=%s)"), *ValueStr, *GetValue(TextBox_1),
	                                       *GetValue(TextBox_2),
	                                       *GetValue(TextBox_3));

	if (GraphPinObj->GetDefaultAsString() != DefaultValue)
	{
		const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeVector4PinValue",
		                                               "Change Vector4 Pin Value"));
		GraphPinObj->Modify();

		//Set new default value
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
	}
}

void SDefault_GraphPinVector4::OnChangedValueTextBox_1(float NewValue, ETextCommit::Type CommitInfo)
{
	const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);

	//Update Y value
	FString DefaultValue = FString::Printf(TEXT("(X=%s,Y=%s,Z=%s,W=%s)"), *GetValue(TextBox_0), *ValueStr,
	                                       *GetValue(TextBox_2),
	                                       *GetValue(TextBox_3));

	if (GraphPinObj->GetDefaultAsString() != DefaultValue)
	{
		const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeVector4PinValue",
		                                               "Change Vector4 Pin Value"));
		GraphPinObj->Modify();

		//Set new default value
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
	}
}

void SDefault_GraphPinVector4::OnChangedValueTextBox_2(float NewValue, ETextCommit::Type CommitInfo)
{
	const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);

	//Update Z value
	FString DefaultValue = FString::Printf(TEXT("(X=%s,Y=%s,Z=%s,W=%s)"), *GetValue(TextBox_0), *GetValue(TextBox_1),
	                                       *ValueStr,
	                                       *GetValue(TextBox_3));

	if (GraphPinObj->GetDefaultAsString() != DefaultValue)
	{
		const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeVector4PinValue",
		                                               "Change Vector4 Pin Value"));
		GraphPinObj->Modify();

		//Set new default value
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
	}
}

void SDefault_GraphPinVector4::OnChangedValueTextBox_3(float NewValue, ETextCommit::Type CommitInfo)
{
	const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);

	//Update W value
	FString DefaultValue = FString::Printf(TEXT("(X=%s,Y=%s,Z=%s,W=%s)"), *GetValue(TextBox_0), *GetValue(TextBox_1),
	                                       *GetValue(TextBox_2), *ValueStr);

	if (GraphPinObj->GetDefaultAsString() != DefaultValue)
	{
		const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeVector4PinValue",
		                                               "Change Vector4 Pin Value"));
		GraphPinObj->Modify();

		//Set new default value
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
	}
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
