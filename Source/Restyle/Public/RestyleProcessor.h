// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "CoreMinimal.h"
#include "RestyleSettings.h"
class FSlateStyleSet;
struct FSlateBoxBrush;

class FRestyleProcessor
{
public:
	FORCEINLINE static FRestyleProcessor& Get()
	{
		static FRestyleProcessor proc;
		return proc;
	}
	/**
	 * @brief Don't make changes directly, as it will break the reset function
	 * Do it with Set() 
	 */
	FORCEINLINE FSlateStyleSet* GetStyle()
	{
		return (FSlateStyleSet*)(&FAppStyle::Get());
	}
	TMap<FName, FSlateBrush*>& GetBrushResources();
	TMap<FName, FSlateBrush*>& GetCachedBrushResources();
	TMap<FName, TSharedRef<FSlateWidgetStyle>>& GetWidgetStyles();
	void ReloadEditorStyle();
	void ReloadEditorStyleSafe();
	void ResetEditorStyle();
	void CacheEditorStyle();
private:
	FTimerHandle GlobalReloadHandle;
};
