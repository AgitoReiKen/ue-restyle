// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "Themes/Default/WireRestyleDefault.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "PackageTools.h"
#include "RestyleProcessor.h"

#include "AssetRegistry/AssetRegistryModule.h"

#include "Factories/MaterialFactoryNew.h"

#include "MaterialEditor/Public/MaterialEditingLibrary.h"

#include "Materials/MaterialExpressionConstant.h"
#include "Materials/MaterialExpressionConstant4Vector.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleMacros.h"

#include "UObject/ObjectSaveContext.h"
#include "UObject/SavePackage.h"

FWireRestyleDefault::FWireRestyleDefault()
{
	Factory = MakeShared<FDefaultGraphPanelWireFactory>();
}

ERestyleSubject FWireRestyleDefault::GetSubject()
{
	return ERestyleSubject::PinConnection;
}

void FWireRestyleDefault::Register()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		auto SettingsSection = SettingsModule->RegisterSettings(
			"Editor", "Plugins", "RestyleDefaultWire",
			FText::FromString("Restyle [Default] [Wire]"),
			FText::FromString("TIP: Use Right Mouse Button (Copy/Paste, Expand/Collapse)"),
			GetMutableDefault<UWireRestyleSettings>());
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this,
				&FWireRestyleDefault::OnSettingsChanged);
		}
	}
	Update();
	bRegistered = true;
}

void FWireRestyleDefault::Unregister()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Editor", "Plugins", "RestyleDefaultWire");
	}

	bRegistered = false;
}

TSharedPtr<FGraphPanelPinConnectionFactory> FWireRestyleDefault::GetFactory()
{
	return Factory;
}

void FWireRestyleDefault::Update()
{
#define RootToContentDir StyleSet->RootToContentDir
#define ChevronDownSvg RootToContentDir("Common/ChevronDown", TEXT(".svg"))

	FSlateStyleSet* StyleSet = FRestyleProcessor::Get().GetStyle();
	auto Style = UWireRestyleSettings::Get();
	FVector2d Icon16 = FVector2d(16);
	switch (Style->BubbleIcon)
	{

	case EWireRestyleBubbleIcon::Circle:
		StyleSet->Set("Graph.ExecutionBubble", new IMAGE_BRUSH_SVG(TEXT("Common/Circle"), Icon16));
		break;
	case EWireRestyleBubbleIcon::Heat:
		StyleSet->Set("Graph.ExecutionBubble", new IMAGE_BRUSH_SVG(TEXT("Wire/ExecBubble_Heat"), Icon16));
		break;
	case EWireRestyleBubbleIcon::Square:
		StyleSet->Set("Graph.ExecutionBubble", new IMAGE_BRUSH_SVG(TEXT("Wire/ExecBubble_Square"), Icon16));
		break;
	case EWireRestyleBubbleIcon::Diamond:
		StyleSet->Set("Graph.ExecutionBubble", new IMAGE_BRUSH_SVG(TEXT("Wire/ExecBubble_Diamond"), Icon16));
		break;
	default: break;
	} 
}

bool FWireRestyleDefault::IsRegistered()
{
	return bRegistered;
}

bool FWireRestyleDefault::OnSettingsChanged()
{
	Update();
	auto Mutable = GetMutableDefault<UWireRestyleSettings>();
	Mutable->SaveConfig(CPF_Config, *Mutable->GetGlobalUserConfigFilename());
	return true;
}

void UWireRestyleSettings::SetDefaults()
{
	BackwardConnectionPriority = EWireRestylePriority::Input;
	TransitionPriority = EWireRestylePriority::Input;
	ExecToExecTransitionPriority = EWireRestylePriority::Input;
	KnotToExecTransitionPriority = EWireRestylePriority::Output;
	ExecToKnotTransitionPriority = EWireRestylePriority::Input;

	BackwardSnapPointOffset = 8.f;
	MinHorizontalLength = 20.f;

	NumBubbles = 4;
	BubbleSpeed = 2;

	CornerRadius = 0.01f;
	bRoundCorners = false;
	b45DegreeStyle = true;

	GoesBackwardTolerance = 4.f;

	StartFudgeX = 2.f;
	EndFudgeX = 2.f;

	HoverThicknessMultiplier = 2.f;
	HoverFadeInBias = 0.75f;
	HoverFadeInPeriod = 0.6f;
	HoverLightFraction = 0.25f;
	HoverDarkenedColor = FLinearColor(0.f, 0.f, 0.f, 0.5f);
	HoverLigthenedColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	AttributeWireColor = "Orange-2";
	AttributeWireThicknessMultiplier = 0.33;
	AttributeDisableBubbles = true;
	BubbleIcon = EWireRestyleBubbleIcon::Diamond;

	bDebug = false;
	bDrawWireframe = false;
	bDrawBubbles = false;
	DebugInteger = 2;

	bAntiCollision = true;
	AntiCollisionPinPriority = EWireRestylePriority::Input;
	EdgeOffsetPeriod = 4;
	AbsoluteMinHorizontalLength = 10;
	UpdateAntiCollisionLevels();
}

void UWireRestyleSettings::UpdateAntiCollisionLevels()
{
	bool bIsPeriodOdd = EdgeOffsetPeriod % 2 == 1;
	AntiCollisionLevels = EdgeOffsetPeriod - (bIsPeriodOdd ? 2 : 1);
}

void UWireRestyleSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() ==
		GET_MEMBER_NAME_CHECKED(UWireRestyleSettings, bRestoreDefaults))
	{
		if (bRestoreDefaults)
		{
			SetDefaults();
			bRestoreDefaults = false;
		}
	}
	else if (PropertyChangedEvent.GetPropertyName() ==
		GET_MEMBER_NAME_CHECKED(UWireRestyleSettings, EdgeOffsetPeriod))
	{
		UpdateAntiCollisionLevels();
	}
}
