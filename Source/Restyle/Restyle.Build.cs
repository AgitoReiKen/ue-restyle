// Alexander (AgitoReiKen) Moskalenko (C) 2022

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using EpicGames.Core;
using UnrealBuildBase;

public class Restyle : ModuleRules
{
    public Restyle(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "GraphEditor"  });
        // PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        var EngineDir = Path.GetFullPath(Target.RelativeEnginePath);
        PrivateIncludePaths.AddRange(
            new string[]
            {
                "Restyle/Private",
                "Restyle/Classes",
                Path.Combine(EngineDir, @"Source/Editor/GraphEditor/Private"),
                Path.Combine(EngineDir, @"Source/Editor/UMGEditor/Private"),
            }
        ); 
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "RenderCore",
                "Projects",
                "EditorStyle",
                "EngineSettings",
                "Kismet",
                "UnrealEd",
                "BlueprintGraph",
                "KismetWidgets",
                "EditorWidgets",
                "GraphEditor", 
                "UMG",
                "InputCore", 
                "AppFramework",
                "EditorWidgets",
                "ToolWidgets",
                "RHI",
                "UMGEditor",
                "MaterialEditor"
                // ... add private dependencies that you statically link with here ...	
            }
        );
        PublicAdditionalLibraries.Add($"{PluginDirectory}/Binaries/ThirdParty/MinHook/Win64/minhook.x64.lib");
    }
}