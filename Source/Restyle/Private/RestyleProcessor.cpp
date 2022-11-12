// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "RestyleProcessor.h"
#include "Utils/RestyleUtils.h"
#include "Misc/FileHelper.h"

#pragma region Wrapper
namespace FSlateStyleSetWrapper_Data
{
	/** float property storage. */
	static TMap<FName, float> Cached_FloatValues;

	/** FVector2D property storage. */
	static TMap<FName, FVector2D> Cached_Vector2DValues;

	/** Color property storage. */
	static TMap<FName, FLinearColor> Cached_ColorValues;

	/** FSlateColor property storage. */
	static TMap<FName, FSlateColor> Cached_SlateColorValues;

	/** FMargin property storage. */
	static TMap<FName, FMargin> Cached_MarginValues;

	/* FSlateBrush property storage */
	static TMap<FName, FSlateBrush*> Cached_BrushResources;

	/** FSlateFontInfo property storage. */
	static TMap<FName, FSlateFontInfo> Cached_FontInfoResources;

	static bool bCached;
}

class FSlateStyleSetWrapper : public FSlateStyleSet
{
public:
	static void CacheData(FSlateStyleSetWrapper* Set)
	{
		if (!FSlateStyleSetWrapper_Data::bCached) {
			FSlateStyleSetWrapper_Data::bCached = true;
			FSlateStyleSetWrapper_Data::Cached_FloatValues = Set->FloatValues;
			FSlateStyleSetWrapper_Data::Cached_Vector2DValues = Set->Vector2DValues;
			FSlateStyleSetWrapper_Data::Cached_ColorValues = Set->ColorValues;
			FSlateStyleSetWrapper_Data::Cached_SlateColorValues = Set->SlateColorValues;
			FSlateStyleSetWrapper_Data::Cached_MarginValues = Set->MarginValues;
			FSlateStyleSetWrapper_Data::Cached_BrushResources = Set->BrushResources;
			FSlateStyleSetWrapper_Data::Cached_FontInfoResources = Set->FontInfoResources;
		}
	}

	static void RestoreData(FSlateStyleSetWrapper* Set)
	{
		if (ensureMsgf(FSlateStyleSetWrapper_Data::bCached, L"Restyle: Tried to RestoreData, not cached before"))
		{
			Set->FloatValues = FSlateStyleSetWrapper_Data::Cached_FloatValues;
			Set->Vector2DValues = FSlateStyleSetWrapper_Data::Cached_Vector2DValues;
			Set->ColorValues = FSlateStyleSetWrapper_Data::Cached_ColorValues;
			Set->SlateColorValues = FSlateStyleSetWrapper_Data::Cached_SlateColorValues;
			Set->MarginValues = FSlateStyleSetWrapper_Data::Cached_MarginValues;
			Set->BrushResources = FSlateStyleSetWrapper_Data::Cached_BrushResources;
			Set->FontInfoResources = FSlateStyleSetWrapper_Data::Cached_FontInfoResources;
		}
	}

	static void DumpStyle(FSlateStyleSetWrapper* Set, FString FilePath)
	{
		FString dump;

		{
			FString iterating = TEXT("WidgetStyleValues");
			for (const auto& it : Set->WidgetStyleValues)
			{
				FString key = it.Key.ToString();
				FString value = FRestyleUtils::ToString(&it.Value.Get(), 1);

				dump += FString::Printf(TEXT("(%s) %s\n%s\n"),
					*iterating,
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

		{
			FString iterating = TEXT("FontInfoResources");
			for (const auto& it : Set->FontInfoResources)
			{
				FString key = it.Key.ToString();
				FString value = FRestyleUtils::ToString(&it.Value, 1);
				dump += (FString::Printf(TEXT("(%s) %s\n%s\n"), *iterating, *key, *value));
			}
		}

		/* Sounds */

		UE_LOG(LogTemp, Warning, TEXT("%s: Dumping %d bytes to %s"), *FString(__FUNCTION__), dump.Len(), *FilePath);

		FFileHelper::SaveStringToFile(dump, *FilePath);
	}
	static TMap<FName, FSlateBrush*>& GetBrushResources(FSlateStyleSetWrapper* Set)
	{
		return Set->BrushResources;
	}
	static TMap<FName, TSharedRef<FSlateWidgetStyle>>& GetWidgetStyles(FSlateStyleSetWrapper* Set)
	{
		return Set->WidgetStyleValues;
	}
};
 
#pragma endregion
void FRestyleProcessor::ResetEditorStyle()
{
	FSlateStyleSetWrapper::RestoreData((FSlateStyleSetWrapper*)GetStyle());
}

void FRestyleProcessor::CacheEditorStyle()
{
	FSlateStyleSetWrapper::CacheData((FSlateStyleSetWrapper*)GetStyle());
}

TMap<FName, FSlateBrush*>& FRestyleProcessor::GetBrushResources()
{
	return FSlateStyleSetWrapper::GetBrushResources((FSlateStyleSetWrapper*)GetStyle());
}

TMap<FName, FSlateBrush*>& FRestyleProcessor::GetCachedBrushResources()
{
	return FSlateStyleSetWrapper_Data::Cached_BrushResources;
}

TMap<FName, TSharedRef<FSlateWidgetStyle>>& FRestyleProcessor::GetWidgetStyles()
{
	return FSlateStyleSetWrapper::GetWidgetStyles((FSlateStyleSetWrapper*)GetStyle());
}

void FRestyleProcessor::ReloadEditorStyle()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

void FRestyleProcessor::ReloadEditorStyleSafe()
{
	if (GWorld && GWorld->bIsWorldInitialized) {
		GWorld->GetTimerManager().ClearTimer(GlobalReloadHandle);
		GWorld->GetTimerManager().SetTimer(GlobalReloadHandle, [this]()
			{
				ReloadEditorStyle();
			}, 2, false);
	}
	else
	{
		ReloadEditorStyle();
	}
}

void FRestyleProcessor::DumpEditorStyle(FString FilePath)
{
	FSlateStyleSetWrapper::DumpStyle((FSlateStyleSetWrapper*)GetStyle(), FilePath);
} 


#undef RootToContentDir 
