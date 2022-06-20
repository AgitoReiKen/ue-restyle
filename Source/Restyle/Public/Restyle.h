// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyle.h"
enum class ERestyleTheme : uint8
{
	RestyleTheme_Default
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
private:
	void ApplyDefaultTheme();
};
