// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "Themes/Default/WireRestyleDefault.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "PackageTools.h"

#include "AssetRegistry/AssetRegistryModule.h"

#include "Factories/MaterialFactoryNew.h"

#include "MaterialEditor/Public/MaterialEditingLibrary.h"

#include "Materials/MaterialExpressionConstant.h"
#include "Materials/MaterialExpressionConstant4Vector.h"
#include "Materials/MaterialInstanceDynamic.h"

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
	TransitionPriority = EWireRestylePriority::Output;
	ExecToExecTransitionPriority = EWireRestylePriority::Input;
	ExecToKnotTransitionPriority = EWireRestylePriority::Input;
	KnotToExecTransitionPriority = EWireRestylePriority::Output;

	BackwardSnapPointOffset = 8.f;
	MinHorizontalLength = 16.f;

	NumBubbles = 4;
	BubbleSpeed = 2;

	CornerRadius = 0.25f;
	bRoundCorners = true;
	b45DegreeStyle = true;

	bDebug = false;
	bDrawWireframe = false; 
	bDrawBubbles = false;
	DebugInteger = 2;
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
}
