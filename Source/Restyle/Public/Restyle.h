// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyle.h"

enum class ERestyleTheme : uint8
{
	Default,
	MAX
};

class FRestyleModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	FSlateStyleSet* Style;
	ERestyleTheme Theme;
	void ReloadStyle();
	void ApplyTheme(ERestyleTheme ForTheme);
	void RegisterCommands();
	FConsoleCommandWithArgsDelegate CmdRestyle_Delegate;
	void CmdRestyle(const TArray<FString>& Args);
	FString GetAvailableThemesStr(FString Delim = "|");
	FString GetThemeId(ERestyleTheme ForTheme);
	ERestyleTheme GetThemeId(FString ForTheme); 
private:
	void ApplyDefaultTheme();
	void ResetToDefault();
};

 