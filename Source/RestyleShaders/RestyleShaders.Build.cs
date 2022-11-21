// Alexander (AgitoReiKen) Moskalenko (C) 2022

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using EpicGames.Core;
using UnrealBuildBase;

public class RestyleShaders : ModuleRules
{
    public RestyleShaders(ReadOnlyTargetRules Target) : base(Target)
    {
        // PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "SlateCore",
                "RenderCore",
                "RHI"
                // ... add private dependencies that you statically link with here ...	
            }
        );
    }
}