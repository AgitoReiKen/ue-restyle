// Copyright Epic Games, Inc. All Rights Reserved.

#include "Restyle.h"

#include "RestyleUtils.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FRestyleModule"
#define DATA_BASEDIR IPluginManager::Get().FindPlugin("Restyle")->GetBaseDir() / TEXT("Data/")
#define RESOUCES_BASEDIR IPluginManager::Get().FindPlugin("Restyle")->GetBaseDir() / TEXT("Resources/")
#define THEMES_BASEDIR RESOUCES_BASEDIR / TEXT("Themes/")

#pragma region Utils & Wrappers
class FSlateStyleSetWrapper : public FSlateStyleSet
{
public:
	static void DumpStyle(FSlateStyleSetWrapper* Set, FString FilePath)
	{
		FString dump;
		UE_LOG(LogTemp, Warning, TEXT("DumpStyle"));
		{
			FString iterating = TEXT("WidgetStyleValues");
			for (const auto& it : Set->WidgetStyleValues)
			{
				FString key = it.Key.ToString();
				FString value = FRestyleUtils::ToString(&it.Value.Get(), 1);
				 
				dump += FString::Printf(TEXT("(%s) (%s) %s : \n%s\n\n"),
					*iterating, 
					*it.Value->GetTypeName().ToString(),
					*key, 
					*value);
			}
		}

		{
			FString iterating = TEXT("FloatValues");
			for (const auto& it : Set->FloatValues)
			{
				FString key = it.Key.ToString();
				float value = it.Value;
				dump += (FString::Printf(TEXT("(%s) %s : %f\n"), *iterating, *key, value));
			}
		}

		{
			FString iterating = TEXT("Vector2DValues");
			for (const auto& it : Set->Vector2DValues)
			{
				FString key = it.Key.ToString();
				FString value = it.Value.ToString();
				dump += (FString::Printf(TEXT("(%s) %s : %s\n"), *iterating, *key, *value));
			}
		}

		{
			FString iterating = TEXT("ColorValues");
			for (const auto& it : Set->ColorValues)
			{
				FString key = it.Key.ToString();
				FString value = it.Value.ToString();
				dump += (FString::Printf(TEXT("(%s) %s : %s\n"), *iterating, *key, *value));
			}
		}

		{
			FString iterating = TEXT("SlateColorValues");
			for (const auto& it : Set->SlateColorValues)
			{
				FString key = it.Key.ToString();
				FString value = FRestyleUtils::ToString(it.Value);
				dump += (FString::Printf(TEXT("(%s) %s : %s\n"), *iterating, *key, *value));
			}
		}

		{
			FString iterating = TEXT("MarginValues");
			for (const auto& it : Set->MarginValues)
			{
				FString key = it.Key.ToString();
				FString value = FRestyleUtils::ToString(it.Value);
				dump += (FString::Printf(TEXT("(%s) %s : %s\n"), *iterating, *key, *value));
			}
		}

		{
			FString iterating = TEXT("BrushResources");
			for (const auto& it : Set->BrushResources)
			{
				FString key = it.Key.ToString();
				FString value = FRestyleUtils::ToString(it.Value, 1);
				dump += (FString::Printf(TEXT("(%s) %s\n%s\n"), *iterating, *key, *value));
			}
		}

		/* Sounds */
		/* FontInfoResources */

		UE_LOG(LogTemp, Warning, TEXT("%s: Dumping %d bytes to %s"), *FString(__FUNCTION__), dump.Len(), *FilePath);


		FFileHelper::SaveStringToFile(dump, *FilePath);
	}

	static TSharedRef<FSlateWidgetStyle, ESPMode::ThreadSafe>* GetWidgetStyle(FSlateStyleSetWrapper* Set, FName Id)
	{
		return Set->WidgetStyleValues.Find(Id);
	}
};
#pragma endregion

void FRestyleModule::StartupModule()
{
	if (GIsEditor && !IsRunningCommandlet())
	{
		Style = (FSlateStyleSet*)(&FEditorStyle::Get());
		auto RegistryIterator = [](const ISlateStyle& x) -> bool
		{
			/*
				LogTemp: Warning: Restyle: AudioStyleSet
				LogTemp: Warning: Restyle: CoreStyle
				LogTemp: Warning: Restyle: UMGCoreStyle
				LogTemp: Warning: Restyle: EditorStyle
				LogTemp: Warning: Restyle: WidgetReflectorStyleStyle
				LogTemp: Warning: Restyle: UMGStyle
				LogTemp: Warning: Restyle: CollisionAnalyzerStyle
				LogTemp: Warning: Restyle: TreeMapStyle
				LogTemp: Warning: Restyle: PixelInspectorStyle
				LogTemp: Warning: Restyle: EventFilter
				LogTemp: Warning: Restyle: NiagaraEditorStyle
				LogTemp: Warning: Restyle: PythonScriptPluginEditorStyle
				LogTemp: Warning: Restyle: EditorDebugToolsStyle
				LogTemp: Warning: Restyle: PluginStyle
				LogTemp: Warning: Restyle: DatasmithContentEditorStyle
				LogTemp: Warning: Restyle: NiagaraEditorWidgetsStyle
				LogTemp: Warning: Restyle: FractureEditorStyle
				LogTemp: Warning: Restyle: ChaosSolverEditorStyle
				LogTemp: Warning: Restyle: GeometryCollectionEditorStyle
				LogTemp: Warning: Restyle: GeometryCollectionStyle
				LogTemp: Warning: Restyle: Groom
				LogTemp: Warning: Restyle: SynthesisStyle
				LogTemp: Warning: Restyle: InterchangeEditorPipelineStyle
				LogTemp: Warning: Restyle: InterchangeResultsBrowserStyle
			 */
			//UE_LOG(LogTemp, Warning, L"Restyle: %s", *x.GetStyleSetName().ToString());
			return true;
		};
		FSlateStyleRegistry::IterateAllStyles(RegistryIterator);

		FSlateStyleSetWrapper::DumpStyle((FSlateStyleSetWrapper*)Style,
		                                 DATA_BASEDIR + FApp::GetBuildVersion() + FString(TEXT("-Default.dump")));

		ApplyTheme(ERestyleTheme::Default);
		RegisterCommands();
	}
}

void FRestyleModule::ShutdownModule()
{
}

void FRestyleModule::ReloadStyle()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

void FRestyleModule::ApplyTheme(ERestyleTheme ForTheme)
{
	Theme = ForTheme;
	switch (ForTheme)
	{
	case ERestyleTheme::Default:
		ApplyDefaultTheme();
		break;
	case ERestyleTheme::MAX: break;
	}
	ReloadStyle();
}

void FRestyleModule::RegisterCommands()
{
	CmdRestyle_Delegate.BindRaw(this, &FRestyleModule::CmdRestyle);

	IConsoleManager::Get().RegisterConsoleCommand(
		L"restyle",
		*FString::Printf(
			L"- restyle // Reload\n- restyle set <theme(%s)> // Set theme & Reload\n - restyle reset // Reset to editor theme>",
			*GetAvailableThemesStr()),
		CmdRestyle_Delegate);
}

void FRestyleModule::CmdRestyle(const TArray<FString>& Args)
{
	if (Args.Num() > 0)
	{
		/* Set Theme */
		if (Args[0].Equals("set"))
		{
			if (Args.IsValidIndex(1))
			{
				if (ERestyleTheme ThemeId = GetThemeId(Args[1]); ThemeId != ERestyleTheme::MAX)
				{
					ApplyTheme(ThemeId);
					UE_LOG(LogTemp, Warning, L"restyle - %s applied", *Args[1]);
				}
				else
				{
					UE_LOG(LogTemp, Warning, L"restyle - There is no %s theme (%s)", *Args[1], *GetAvailableThemesStr())
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, L"restyle - No theme specified (theme|none)")
			}
		}
		else if (Args[0].Equals("reset"))
		{
			ResetToDefault();
			UE_LOG(LogTemp, Warning,
			       L"restyle - Reset to engine defaults. To reapply previous theme, use 'restyle' command")
		}
		else if (Args[0].Equals("dump"))
		{
			FString dir = DATA_BASEDIR + FApp::GetBuildVersion() + FString(TEXT(".dump"));
			FSlateStyleSetWrapper::DumpStyle((FSlateStyleSetWrapper*)Style, dir);
			UE_LOG(LogTemp, Warning, L"restyle - Dump saved to %s", *dir);
		}
	}
	/* Reload */
	else
	{
		ApplyTheme(Theme);
	}
}

FString FRestyleModule::GetAvailableThemesStr(FString Delim)
{
	FString result = "";
	for (uint8 it = 0; it < (uint8)ERestyleTheme::MAX; it++)
	{
		result += GetThemeId((ERestyleTheme)it) + Delim;
	}
	result.RemoveFromEnd(Delim);
	return result;
}

FString FRestyleModule::GetThemeId(ERestyleTheme ForTheme)
{
	switch (ForTheme)
	{
	case ERestyleTheme::Default:
		return "default";
	case ERestyleTheme::MAX:
		return "None";
	default:
		return "None";
	}
}

ERestyleTheme FRestyleModule::GetThemeId(FString ForTheme)
{
	if (ForTheme == "default")
		return ERestyleTheme::Default;
	return ERestyleTheme::MAX;
}

void FRestyleModule::ApplyDefaultTheme()
{
#define RootToContentDir Style->RootToContentDir
	Style->SetContentRoot(THEMES_BASEDIR / TEXT("Default"));

	/* Pin */
	{
		Style->Set("Graph.WatchedPinIcon_Pinned",
		           new IMAGE_BRUSH_SVG("WatchedPinIcon_Pinned", FVector2D(16, 12)));

		Style->Set("Kismet.VariableList.TypeIcon",
		           new IMAGE_BRUSH_SVG("pill", FVector2D(11, 11)));

		Style->Set("Kismet.VariableList.ArrayTypeIcon",
		           new IMAGE_BRUSH_SVG("ArrayPin_connected", FVector2D(11, 11)));

		Style->Set("Kismet.VariableList.SetTypeIcon",
		           new IMAGE_BRUSH_SVG("pillset", FVector2D(11, 11)));

		Style->Set("Kismet.VariableList.MapValueTypeIcon",
		           new IMAGE_BRUSH_SVG("pillmapvalue", FVector2D(11, 11)));

		Style->Set("Kismet.VariableList.MapKeyTypeIcon",
		           new IMAGE_BRUSH_SVG("pillmapkey", FVector2D(11, 11)));

		Style->Set("Graph.RefPin.Connected",
		           new IMAGE_BRUSH_SVG("RefPin_connected", FVector2D(11, 11)));

		Style->Set("Graph.RefPin.Disconnected",
		           new IMAGE_BRUSH_SVG("RefPin_disconnected", FVector2D(11, 11)));

		Style->Set("Graph.ArrayPin.Connected",
		           new IMAGE_BRUSH_SVG("ArrayPin_connected", FVector2D(11, 11)));

		Style->Set("Graph.ArrayPin.Disconnected",
		           new IMAGE_BRUSH_SVG("ArrayPin_disconnected", FVector2D(11, 11)));

		Style->Set("Graph.Pin.Connected",
		           new IMAGE_BRUSH_SVG("Pin_connected", FVector2D(11, 11)));

		Style->Set("Graph.Pin.Disconnected",
		           new IMAGE_BRUSH_SVG("Pin_disconnected", FVector2D(11, 11)));

		Style->Set("Graph.Pin.Connected_VarA",
		           new IMAGE_BRUSH_SVG("Pin_connected_VarA", FVector2D(11, 11)));

		Style->Set("Graph.Pin.Disconnected_VarA",
		           new IMAGE_BRUSH_SVG("Pin_disconnected_VarA", FVector2D(11, 11)));

		Style->Set("Graph.DelegatePin.Connected",
		           new IMAGE_BRUSH_SVG("DelegatePin_connected", FVector2D(11, 11)));

		Style->Set("Graph.DelegatePin.Disconnected",
		           new IMAGE_BRUSH_SVG("DelegatePin_disconnected", FVector2D(11, 11)));

		Style->Set("Graph.ExecPin.Connected",
		           new IMAGE_BRUSH_SVG("ExecPin_Connected", FVector2D(11.0f, 11.0f)));

		Style->Set("Graph.ExecPin.Disconnected",
		           new IMAGE_BRUSH_SVG("ExecPin_Disconnected", FVector2D(11.0f, 11.0f)));

		Style->Set("Graph.ExecPin.ConnectedHovered",
		           new IMAGE_BRUSH_SVG("ExecPin_Connected", FVector2D(11.0f, 11.0f)));

		Style->Set("Graph.ExecPin.DisconnectedHovered",
		           new IMAGE_BRUSH_SVG("ExecPin_Disconnected", FVector2D(11.0f, 11.0f)));
	}
	/* Node */
	{
		Style->Set("Graph.Node.ShadowSize", FVector2D(12, 12));
		Style->Set("Graph.Node.ShadowSelected",
		           new BOX_BRUSH("RegularNode_shadow_selected", FMargin(18.0f / 64.0f)));
		Style->Set("Graph.Node.Shadow",
		           new BOX_BRUSH("RegularNode_shadow", FMargin(18.0f / 64.0f)));
		Style->Set("Graph.Node.Body",
		           new BOX_BRUSH("RegularNode_body", FMargin(0, 0, 0, 0)));
		Style->Set("Graph.Node.TintedBody",
		           new BOX_BRUSH("TintedNode_body", FMargin(0)));
		Style->Set("Graph.Node.TitleGloss",
		           new BOX_BRUSH("RegularNode_title_gloss", FMargin(0)));
		Style->Set("Graph.Node.ColorSpill",
		           new BOX_BRUSH_SVG("RegularNode_color_spill", FMargin(0)));
		Style->Set("Graph.Node.TitleHighlight",
		           new BOX_BRUSH("RegularNode_title_highlight", FMargin(0.0f)));
	}
	/* VarNode */
	{
		Style->Set("Graph.VarNode.ColorSpill",
		           new BOX_BRUSH("VarNode_color_spill", FMargin(0)));
		Style->Set("Graph.VarNode.Body",
		           new BOX_BRUSH("VarNode_body", FMargin(16.f / 64.f, 12.f / 28.f)));
		Style->Set("Graph.VarNode.ShadowSelected",
		           new BOX_BRUSH("VarNode_shadow_selected", FMargin(26.0f / 64.0f)));
		Style->Set("Graph.VarNode.Shadow",
		           new BOX_BRUSH("VarNode_shadow", FMargin(26.0f / 64.0f)));
		Style->Set("Graph.VarNode.Gloss",
		           new BOX_BRUSH("VarNode_gloss", FMargin(16.f / 64.f, 16.f / 28.f, 16.f / 64.f, 4.f / 28.f)));
	}
	/* CollapsedNode */
	{
		Style->Set("Graph.CollapsedNode.Body",
		           new BOX_BRUSH("RegularNode_body",
		                         FMargin(16.f / 64.f, 25.f / 64.f, 16.f / 64.f, 16.f / 64.f)));
		Style->Set("Graph.CollapsedNode.BodyColorSpill",
		           new BOX_BRUSH("CollapsedNode_Body_ColorSpill",
		                         FMargin(16.f / 64.f, 25.f / 64.f, 16.f / 64.f, 16.f / 64.f)));
	}
	/* KismetExpression */
	{
		Style->Set("KismetExpression.ReadVariable.Body",
		           new BOX_BRUSH("VarNode_body", FMargin(16.f / 64.f, 12.f / 28.f)));
		//Style->Set("KismetExpression.ReadVariable.Gloss", new BOX_BRUSH("Linear_VarNode_Gloss", FMargin(16.f / 64.f, 12.f / 28.f)));
		Style->Set("KismetExpression.ReadAutogeneratedVariable.Body",
		           new BOX_BRUSH("VarNode_body", FMargin(16.f / 64.f, 12.f / 28.f)));
	}
	/* PhysicsAssetEditor */
	{
		Style->Set("PhysicsAssetEditor.Graph.Node.Shadow",
		           new BOX_BRUSH("RegularNode_shadow", FMargin(18.0f / 64.0f)));
	}
	/* Wire */
	{
		Style->Set("Graph.ExecutionBubble",
		           new IMAGE_BRUSH_SVG("ExecutionBubble", FVector2D(16, 16)));
	}
	/* Comment */
	{
		Style->Set("Graph.Node.CommentBubble",
		           new BOX_BRUSH_SVG("CommentBubble", FMargin(0)));
		Style->Set("Graph.Node.CommentArrow",
		           new IMAGE_BRUSH_SVG("CommentBubbleArrow", FVector2D(8, 8)));
		Style->Set("Kismet.Comment.Background",
		           new BOX_BRUSH_SVG("Comment_Background", FMargin(0)));
	}
}

void FRestyleModule::ResetToDefault()
{
	/*
	 * 
	TMap<FName, const ISlateStyle*> FSlateStyleRegistry::SlateStyleRepository;
		void FSlateStyleRegistry::RegisterSlateStyle(const ISlateStyle & InSlateStyle)
	 */
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRestyleModule, Restyle)
