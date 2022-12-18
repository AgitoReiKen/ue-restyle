// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "RestyleShadersModule.h"
#include "ShaderCore.h"
#include <Interfaces/IPluginManager.h>
#define LOCTEXT_NAMESPACE "FRestyleShadersModule"

void FRestyleShadersModule::StartupModule()
{
	FString ShaderDirectory = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("Restyle"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping("/Plugin/Restyle", ShaderDirectory);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRestyleShadersModule, RestyleShaders);
