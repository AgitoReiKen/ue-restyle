// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "Restyle.h"
#include <Developer/Settings/Public/ISettingsModule.h>
#include "BlueprintEditor.h"
#include "EdGraphUtilities.h"
#include "GraphEditorSettings.h"
#include "ISettingsSection.h"
#include "RestyleProcessor.h"

#include "Themes/Default/DefaultTheme.h"

#include "Utils/ColorUtils.h"
#include "Async/TaskGraphInterfaces.h"
#include "Utils/Privates.h"

#define LOCTEXT_NAMESPACE "FRestyleModule"

uint32 FDelayLoadRunnable::Run()
{
	while (!GEditor || !GWorld) { FPlatformProcess::Sleep(1); }
	FFunctionGraphTask::CreateAndDispatchWhenReady([]()
		{
			auto Restyle = FModuleManager::Get().GetModule("Restyle");
			reinterpret_cast<FRestyleModule*>(Restyle)->Load();
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	return 1;
}

//@note plugin is set as DeveloperTool because its the only way to make it work with shaders (as i know)
//but technically it is made out to be an editor's extension, so we wait until GEditor get loaded
void FRestyleModule::StartupModule()
{
	if (GIsEditor && !IsRunningCommandlet()) 
	{
		FString ShaderDirectory = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("/Restyle/Shaders"));
		AddShaderSourceDirectoryMapping("/Plugin/Restyle", ShaderDirectory);
		DelayLoadThread = FRunnableThread::Create(new FDelayLoadRunnable(), TEXT("RestyleDelayLoad"));
		if (!DelayLoadThread)
		{
			UE_LOG(LogTemp, Error, TEXT("Couldn't create delay load for Restyle in FRunnableThread::Create"));
		};
	}
}

void FRestyleModule::Load()
{
	FRestyleProcessor::Get().CacheEditorStyle();
	RegisterCommands();
	RegisterSettings();
	RegisterDefaultThemes();
	OnSettingsChanged();
	if (DelayLoadThread) {
		DelayLoadThread->Kill();
		delete DelayLoadThread;
	}
}

void FRestyleModule::ShutdownModule()
{
	if (IsEngineExitRequested()) return;
	UnregisterCommands();
	UnregisterSettings();
	SetSubjectProvider(ERestyleSubject::Node, NAME_None);
	SetSubjectProvider(ERestyleSubject::Pin, NAME_None);
	SetSubjectProvider(ERestyleSubject::PinConnection, NAME_None);

	for (const auto& it : AvailableThemes)
	{
		it->Unregister();
	}
	AvailableThemes.Empty();
}

void FRestyleModule::RegisterTheme(TSharedPtr<IRestyleThemeInterface> Theme)
{
	AvailableThemes.Add(Theme);
}

void FRestyleModule::UnregisterTheme(const FName& Id)
{
	for (auto& it : AvailableThemes)
	{
		if (it->GetId() == Id)
		{
			AvailableThemes.Remove(it);
			break;
		}
	}
}

void FRestyleModule::SetSubjectProvider(ERestyleSubject Subject, const FName& Id)
{
	if (auto Prev = SubjectProviders.Find(Subject); Prev)
	{
		if (*Prev == Id) return;

		if (*Prev != NAME_None) {
			if (auto PrevProvider = TryGetSubjectProvider(*Prev, Subject);
				PrevProvider.IsValid())
			{
				PrevProvider->Unregister();
				SetFactory(Subject, PrevProvider, false);
			}
		}
		 
	}
	SubjectProviders.Add(Subject, NAME_None);

	if (auto Provider = TryGetSubjectProvider(Id, Subject);
		Provider.IsValid())
	{
		SubjectProviders.Add(Subject, Id);
		Provider->Register();
		SetFactory(Subject, Provider);
	}
}

bool FRestyleModule::IsSubjectProviderRegistered(const FName& ThemeId, ERestyleSubject Subject)
{
	return SubjectProviders[Subject] == ThemeId;
}

TSharedPtr<ISubjectRestyleInterface> FRestyleModule::TryGetSubjectProvider(
	const FName& ThemeId, ERestyleSubject Subject)
{
	if (auto Theme = GetThemeById(ThemeId); Theme.IsValid())
	{
		return Theme->GetSubjectFactoryProvider(Subject);
	}
	return nullptr;
}

TSharedPtr<IRestyleThemeInterface> FRestyleModule::GetThemeById(const FName& Id)
{
	for (const auto& it : AvailableThemes)
	{
		if (it->GetId() == Id)
		{
			return it;
		}
	}
	return nullptr;
}

TArray<FName> FRestyleModule::GetAvailableSubjectProviderOptions(ERestyleSubject Subject)
{
	TArray<FName> Result;
	Result.Add(TEXT("None"));
	for (const auto& it : AvailableThemes)
	{
		if (it->GetSubjectFactoryProvider(Subject).IsValid())
		{
			Result.Add(it->GetId());
		}
	}
	return Result;
}

void FRestyleModule::RegisterCommands()
{
	CmdRestyle_Delegate.BindRaw(this, &FRestyleModule::CmdRestyle);
	IConsoleManager::Get().RegisterConsoleCommand(
		L"restyle",
		L"- restyle // Reload\n - restyle reset // Reset to editor theme>",
		CmdRestyle_Delegate);
}

void FRestyleModule::UnregisterCommands()
{
	CmdRestyle_Delegate.Unbind();
	IConsoleManager::Get().UnregisterConsoleObject(L"restyle");
}

void FRestyleModule::RegisterSettings()
{ 
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		auto SettingsSection = SettingsModule->RegisterSettings(
			"Editor", "Plugins", "Restyle",
			FText::FromString("Restyle"),
			FText::FromString("Reopen graphs to apply changes"),
			GetMutableDefault<URestyleSettings>());
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FRestyleModule::OnSettingsChanged);
		}
	}
}

void FRestyleModule::UnregisterSettings()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Restyle");
	}
}

void FRestyleModule::RegisterDefaultThemes()
{
	RegisterTheme(MakeShared<FRestyleDefaultTheme>());
}

void FRestyleModule::CmdRestyle(const TArray<FString>& Args)
{
	if (Args.Num() > 0)
	{
		if (Args[0].Equals("reset"))
		{
			auto Settings = GetMutableDefault<URestyleSettings>();
			Settings->NodeFactoryProviderId = NAME_None;
			Settings->PinFactoryProviderId = NAME_None;
			Settings->WireFactoryProviderId = NAME_None;
			OnSettingsChanged();
			FRestyleProcessor::Get().ResetEditorStyle();
			UE_LOG(LogTemp, Warning,
			       L"restyle - Providers disabled. To enable them, use 'restyle' command")
		}
		else if (Args[0].Equals("reload"))
		{
			FRestyleProcessor::Get().ReloadEditorStyle();
			UE_LOG(LogTemp, Warning,
				L"restyle - Resources reloaded")
		}
		else if (Args[0].Equals("test"))
		{
			if (Args.IsValidIndex(3))
			{
				float L = FCString::Atof(*Args[1]);
				float C = FCString::Atof(*Args[2]);
				float H = FCString::Atof(*Args[3]);
				auto RGB = FColorOkLch(L, C, H).ToRGB();
				auto RGBC = FColorOkLch(L, C, H).ToRGBCorrected();
				UE_LOG(LogTemp, Warning, L"%s", *RGB.ToString());
				UE_LOG(LogTemp, Warning, L"%s", *RGBC.ToString());
			}
		}
	}
	/* Restore */
	else
	{
		auto Settings = GetMutableDefault<URestyleSettings>();
		if (PreviousSubjectProviders.Find(ERestyleSubject::Node))
		Settings->NodeFactoryProviderId = PreviousSubjectProviders[ERestyleSubject::Node];
		if (PreviousSubjectProviders.Find(ERestyleSubject::Pin))
			Settings->PinFactoryProviderId = PreviousSubjectProviders[ERestyleSubject::Pin];
		if (PreviousSubjectProviders.Find(ERestyleSubject::PinConnection))
			Settings->WireFactoryProviderId = PreviousSubjectProviders[ERestyleSubject::PinConnection];
		OnSettingsChanged();
		UE_LOG(LogTemp, Warning,
			L"restyle - Providers enabled")
	}
}

bool FRestyleModule::OnSettingsChanged()
{
	PreviousSubjectProviders.Empty();
	PreviousSubjectProviders = SubjectProviders;
	auto Settings = GetMutableDefault<URestyleSettings>();
	SetSubjectProvider(ERestyleSubject::Node, Settings->NodeFactoryProviderId);
	SetSubjectProvider(ERestyleSubject::Pin, Settings->PinFactoryProviderId);
	SetSubjectProvider(ERestyleSubject::PinConnection, Settings->WireFactoryProviderId);
	UpdateThemes();
	Settings->SaveConfig(CPF_Config, *Settings->GetGlobalUserConfigFilename());
	return true;
}

void FRestyleModule::UpdateThemes()
{
	auto ThemeChanges = DetectThemeChanges();
	for (const auto& it : ThemeChanges)
	{
		if (it.Value == ERestyleThemeChange::Added)
		{
			if (auto Found = GetThemeById(it.Key);
				Found.IsValid())
			{
				Found->Register();
			}
		}
		else if (it.Value == ERestyleThemeChange::Removed)
		{
			if (auto Found = GetThemeById(it.Key);
				Found.IsValid())
			{
				Found->Unregister();
			}
		}
	}
}

TMap<FName, ERestyleThemeChange> FRestyleModule::DetectThemeChanges()
{
	TMap<FName, ERestyleThemeChange> Result;
	auto ContainsValue = [](const TMap<ERestyleSubject, FName>& Map, FName Val) -> bool
	{
		for (const auto& it : Map)
		{
			if (it.Value.IsEqual(Val))
			{
				return true;
			}
		}
		return false;
	};
	for (const auto& it : PreviousSubjectProviders)
	{
		if (!ContainsValue(SubjectProviders, it.Value))
		{
			Result.Add(it.Value ,ERestyleThemeChange::Removed);
		}
	}
	for (const auto& it : SubjectProviders)
	{
		if (!ContainsValue(PreviousSubjectProviders, it.Value))
		{
			Result.Add(it.Value, ERestyleThemeChange::Added);
		}
	}
	return Result;
}

void FRestyleModule::SetFactory(ERestyleSubject Subject, TSharedPtr<ISubjectRestyleInterface> Provider,
                                bool bRegister)
{
	switch (Subject)
	{
	case ERestyleSubject::Node:
	{
		auto& Factories = access_private_static::FEdGraphUtilities::VisualNodeFactories();
		auto Factory = StaticCastSharedPtr<INodeRestyleInterface>(Provider)->GetFactory();
		if (bRegister)
		{
			Factories.Insert(Factory, 0);
		}
		else
		{
			Factories.Remove(Factory);
		}
		break;
	}
	case ERestyleSubject::Pin:
	{
		auto& Factories = access_private_static::FEdGraphUtilities::VisualPinFactories();
		auto Factory = StaticCastSharedPtr<IPinRestyleInterface>(Provider)->GetFactory();
		if (bRegister)
		{
			Factories.Insert(Factory, 0);
		}
		else
		{
			Factories.Remove(Factory);
		}
		break;
	}
	case ERestyleSubject::PinConnection:
	{
		auto& Factories = access_private_static::FEdGraphUtilities::VisualPinConnectionFactories();
		auto Factory = StaticCastSharedPtr<IWireRestyleInterface>(Provider)->GetFactory();
		if (bRegister)
		{
			Factories.Insert(Factory, 0);
		}
		else
		{
			Factories.Remove(Factory);
		}
		break;
	}
	default: break;
	}
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRestyleModule, Restyle)
