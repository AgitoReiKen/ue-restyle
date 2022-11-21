// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "RestyleShadersModule.h"
#include "ShaderCore.h"
void FRestyleShadersModule::StartupModule()
{
	FString ShaderDirectory = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("/Restyle/Shaders"));
	AddShaderSourceDirectoryMapping("/Plugin/Restyle", ShaderDirectory);
}
IMPLEMENT_MODULE(FRestyleShadersModule, RestyleShaders);
