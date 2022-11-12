// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "CoreMinimal.h"
#include "Themes/ThemeInterfaces.h"
#include "RestyleSettings.generated.h"


UCLASS(Config = Editor, DefaultConfig)
class RESTYLE_API URestyleSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Theme", meta = (GetOptions = "GetNodeProviders"))
	FName NodeFactoryProviderId;
	UPROPERTY(Config, EditAnywhere, Category = "Theme", meta = (GetOptions = "GetPinProviders"))
	FName PinFactoryProviderId;
	UPROPERTY(Config, EditAnywhere, Category = "Theme", meta = (GetOptions = "GetWireProviders"))
	FName WireFactoryProviderId;

	/* Same as 'restyle reload'*/
	UPROPERTY(Config, EditAnywhere, Category = "Commands")
	bool ExecReloadTextures;


private:
	UFUNCTION(CallInEditor)
	TArray<FName> GetNodeProviders();
	UFUNCTION(CallInEditor)
	TArray<FName> GetPinProviders();
	UFUNCTION(CallInEditor)
	TArray<FName> GetWireProviders();
};

/*UPROPERTY(EditAnywhere, config, Category = "Graph|Pin")
EPinS Pin;

UPROPERTY(EditAnywhere, config, Category = "Graph|Palette")
ESignaturePaletteS SignaturePalette;
UPROPERTY(EditAnywhere, config, Category = "Graph|Palette")
EDataPaletteS DataPalette;

UPROPERTY(EditAnywhere, config, Category = "Graph|Node")
EShadowS NodeShadow;
UPROPERTY(EditAnywhere, config, Category = "Graph|Node")
EBackgroundS NodeBackground;
UPROPERTY(EditAnywhere, config, Category = "Graph|Node",
	meta = (EditCondition = "NodeBackground == EBackgroundS::Custom", EditConditionHides))
FLinearColor NodeBackgroundColor;
UPROPERTY(EditAnywhere, config, Category = "Graph|Node")
EOutlineS NodeOutline;
UPROPERTY(EditAnywhere, config, Category = "Graph|Node")
EBorderS NodeBorder;
UPROPERTY(EditAnywhere, config, Category = "Graph|Node")
ENodeTitleS NodeTitle;
UPROPERTY(EditAnywhere, config, Category = "Graph|Node")
ESelectionS NodeSelection;

UPROPERTY(EditAnywhere, config, Category = "Graph|VarNode")
EVarNodeExtraS VarNodeExtra;
UPROPERTY(EditAnywhere, config, Category = "Graph|VarNode")
EShadowS VarNodeShadow;
UPROPERTY(EditAnywhere, config, Category = "Graph|VarNode")
EBackgroundS VarNodeBackground;
UPROPERTY(EditAnywhere, config, Category = "Graph|VarNode",
	meta = (EditCondition="VarNodeBackground == EBackgroundS::Custom", EditConditionHides))
FLinearColor VarNodeBackgroundColor;
UPROPERTY(EditAnywhere, config, Category = "Graph|VarNode")
EOutlineS VarNodeOutline;
UPROPERTY(EditAnywhere, config, Category = "Graph|VarNode")
EBorderS VarNodeBorder;
UPROPERTY(EditAnywhere, config, Category = "Graph|VarNode")
ESelectionS VarNodeSelection;*/
