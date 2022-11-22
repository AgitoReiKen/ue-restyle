// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "RestyleShadersModule.h"
#include "ShaderCore.h"

#define LOCTEXT_NAMESPACE "FRestyleShadersModule"

void FRestyleShadersModule::StartupModule()
{
	FString ShaderDirectory = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("/Restyle/Shaders"));
	AddShaderSourceDirectoryMapping("/Plugin/Restyle", ShaderDirectory);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRestyleShadersModule, RestyleShaders);
