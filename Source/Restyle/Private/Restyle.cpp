// Copyright Epic Games, Inc. All Rights Reserved.

#include "Restyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define LOCTEXT_NAMESPACE "FRestyleModule"
#define THEMES_BASEDIR IPluginManager::Get().FindPlugin("Restyle")->GetBaseDir() / TEXT("Themes")
#pragma region Utils
class FSlateStyleSetWrapper : public FSlateStyleSet
{
public:
	static void DumpStyle(FSlateStyleSetWrapper* Set, FString FilePath)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
		FString dump;

		for (const auto& it : Set->BrushResources)
		{
			auto key = it.Key.ToString();
			dump += FString::Printf(
				TEXT("BrushResource: %s - %s\n"),
				*key,
				it.Value ? *it.Value->GetResourceName().ToString() : TEXT("None")
			);
		}
		for (const auto& it : Set->WidgetStyleValues)
		{
			auto key = it.Key.ToString();
			dump += FString::Printf(
				TEXT("WidgetStyleResource: %s - %s\n"),
				*key,
				*it.Value->GetTypeName().ToString()
			);
		}
		UE_LOG(LogTemp, Warning, TEXT("%s: Dumping %d bytes"), *FString(__FUNCTION__), dump.Len());

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
		ApplyTheme(Theme);
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
	switch (ForTheme)
	{
	case ERestyleTheme::RestyleTheme_Default:
		ApplyDefaultTheme();
		ReloadStyle();
		break;
	}
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

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRestyleModule, Restyle)
