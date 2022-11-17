// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once
#include "CoreMinimal.h"
#include "ConnectionDrawingPolicy.h"
#include "PackageTools.h"
#include "SlateMaterialBrush.h"

#include "Default/DefaultGraphPanelWireFactory.h"
#include "Themes/ThemeInterfaces.h"
#include "WireRestyleDefault.generated.h"

class FWireRestyleDefault : public IWireRestyleInterface
{
public:
	explicit FWireRestyleDefault();
	virtual ERestyleSubject GetSubject() override;
	virtual void Register() override;
	virtual void Unregister() override;
	virtual TSharedPtr<FGraphPanelPinConnectionFactory> GetFactory() override;
	virtual void Update() override;
	virtual bool IsRegistered() override;
private:
	bool OnSettingsChanged();
	bool bRegistered;
	TSharedPtr<FDefaultGraphPanelWireFactory> Factory;

};
UENUM()
enum class EWireRestylePriority
{
	Output,
	Equal,
	Input
};
UCLASS(Config = Restyle, GlobalUserConfig)
class UWireRestyleSettings : public UObject
{
	GENERATED_BODY()
public:
	UWireRestyleSettings()
	{
		SetDefaults();
	};

	static const UWireRestyleSettings* Get()
	{
		return GetDefault<UWireRestyleSettings>();
	}

	static UWireRestyleSettings* GetM()
	{
		return GetMutableDefault<UWireRestyleSettings>();
	} 
	void SetDefaults(); 
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	UPROPERTY(EditAnywhere, meta = (Category = "Commands"))
		bool bRestoreDefaults;

#pragma region Properties

	/*
	 * wire will stick to the nearest snap point of 
	 * if output: output node
	 * if equal: in between
	 * if input: input node
	 *
	 *		 _______
	 *		|Output |
	 *		|______x|-x
	 *	x_____________|
	 *	|
	 *	|
	 *  |  ______
	 *	| |Input |
	 *	x-|x_____|
	 */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings")
		EWireRestylePriority BackwardConnectionPriority;
	/*
	 * if output: wire transition near input
	 * if equal: wire transition in between
	 * if input: wire transition near output
	 *
	 * [output]----------x
	 *	                  \____[input]
	 */ 
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings")
		EWireRestylePriority TransitionPriority;
	 
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings")
		EWireRestylePriority ExecToExecTransitionPriority;
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings")
		EWireRestylePriority KnotToExecTransitionPriority;
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings")
		EWireRestylePriority ExecToKnotTransitionPriority;
	/*
	 * Determines desired minimal of x length to be used
	 * [x]---x
	 *        \
	*          x---[x]
	 */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings")
		float MinHorizontalLength;
	/* Drawn when debugging */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings", meta = (ClampMin = "1", ClampMax = "20"))
		int NumBubbles;
	/* Drawn when debugging */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings", meta = (ClampMin = "1", ClampMax = "4"))
		float BubbleSpeed;
	/*
	 * Smooths 90 degrees corners
	 * x-----x
	 *	     |
	 *	     |
	 *	     x
	 * to
	 * x--x
	 *	   \
	 *	    x
	 *	    |
	 *	    x
	 */		
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings", meta = (ClampMin = "0.0", ClampMax = "0.5"))
		float CornerRadius;
	/*
	 * Applies circular geometry to line joins/corners
	 *
	 */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings")
		bool bRoundCorners;
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings", meta = (DisplayName = "45-Deg Style"))
		bool b45DegreeStyle;
	/*
	 * Space where the line goes (above or under node) [relative to node]
	 *
	 */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings")
		float BackwardSnapPointOffset;

	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings", meta = (ClampMin = "0.0", ClampMax = "256.0"))
		float GoesBackwardTolerance;
	/* VerticalMiddleRightOf(Start) - FVector2D(StartFudgeX, 0) */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings", meta = (ClampMin = "-16.0", ClampMax = "16.0"))
		float StartFudgeX;
	/* VerticalMiddleLeftOf(End) + FVector2D(EndFudgeX, 0) */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings", meta = (ClampMin = "-16.0", ClampMax = "16.0"))
		float EndFudgeX;

	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Debug")
		bool bDebug;  
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Debug")
		bool bDrawWireframe; 
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Debug")
		bool bDrawBubbles; 
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Debug")
		int DebugInteger; 


#pragma endregion
};