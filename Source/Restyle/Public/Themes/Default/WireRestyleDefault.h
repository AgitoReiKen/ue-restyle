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
UENUM()
enum class EWireRestyleBubbleIcon
{
	Circle,
	Heat,
	Square,
	Diamond,
};
UCLASS(Config = Restyle_v50, GlobalUserConfig)
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
	void UpdateAntiCollisionLevels();
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	UPROPERTY(EditAnywhere, meta = (Category = "Commands"))
		bool bRestoreDefaults;

#pragma region Properties

	 
	/*
	 * Applies circular geometry to line joins/corners
	 *
	 */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Style")
		bool bRoundCorners;
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Style", meta = (DisplayName = "45-Deg Style"))
		bool b45DegreeStyle;
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
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Priorities")
		EWireRestylePriority BackwardConnectionPriority;
	/*
	 * if output: wire transition near input
	 * if equal: wire transition in between
	 * if input: wire transition near output
	 *
	 * [output]----------x
	 *	                  \____[input]
	 */ 
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Priorities")
		EWireRestylePriority TransitionPriority;
	 
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Priorities")
		EWireRestylePriority ExecToExecTransitionPriority;
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Priorities")
		EWireRestylePriority KnotToExecTransitionPriority;
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Priorities")
		EWireRestylePriority ExecToKnotTransitionPriority;

	/*
	 * Determines desired minimal of x length to be used
	 * [x]---x
	 *        \
	 *          x---[x]
	 */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Geometry", meta = (ClampMin = "4", ClampMax = "64"))
		float MinHorizontalLength;
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
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Geometry", meta = (ClampMin = "0.0", ClampMax = "0.5"))
		float CornerRadius;
	/*
	 * Space where the line goes (above or under node) [relative to node]
	 *
	 */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Geometry")
		float BackwardSnapPointOffset;

	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Geometry", meta = (ClampMin = "0.0", ClampMax = "256.0"))
		float GoesBackwardTolerance;
	/* VerticalMiddleRightOf(Start) - FVector2D(StartFudgeX, 0) */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Geometry", meta = (ClampMin = "-16.0", ClampMax = "16.0"))
		float StartFudgeX;
	/* VerticalMiddleLeftOf(End) + FVector2D(EndFudgeX, 0) */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Geometry", meta = (ClampMin = "-16.0", ClampMax = "16.0"))
		float EndFudgeX;


	/* Drawn when debugging */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Bubbles", meta = (ClampMin = "1", ClampMax = "20"))
		int NumBubbles;
	/* Drawn when debugging */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Bubbles", meta = (ClampMin = "1", ClampMax = "4"))
		float BubbleSpeed;

	 
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Hover", DisplayName = "Thickness Multiplier", meta = (ClampMin = "1.0", ClampMax = "4.0"))
		float HoverThicknessMultiplier;
	// Time in seconds before the fading starts to occur
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Hover", DisplayName = "FadeInBias", meta = (ClampMin = "0.0", ClampMax = "4.0"))
		float HoverFadeInBias;
	// Time in seconds after the bias before the fade is fully complete
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Hover", DisplayName = "FadeInPeriod", meta = (ClampMin = "0.0", ClampMax = "4.0"))
		float HoverFadeInPeriod;
	// Determines how lightened color blends (0 = no color applied, 1 = full color applied)
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Hover", DisplayName = "LightFraction", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float HoverLightFraction;
	// Determines how darkened color blends (0 = no color applied, 1 = full color applied)
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Hover", DisplayName = "DarkFraction", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float HoverDarkFraction;
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Hover", DisplayName = "DarkenedColor")
		FLinearColor HoverDarkenedColor;
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Hover", DisplayName = "LightenedColor")
		FLinearColor HoverLigthenedColor;
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|Icons")
		EWireRestyleBubbleIcon BubbleIcon;
	

	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|AnimationEditor")
		FDTColor AttributeWireColor;
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|AnimationEditor", meta = (ClampMin = "0.0", ClampMax = "2.0"))
		float AttributeWireThicknessMultiplier;
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|AnimationEditor")
		bool AttributeDisableBubbles;

	/*
	 * This feature applies offset based on PinIndex to avoid wire blending
	 */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|AntiCollision")
		bool bAntiCollision;

	/* Preferred pins to use. Input/Output. It will get changed ynamically if it makes sense. Equal state not implemented*/
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|AntiCollision")
		EWireRestylePriority AntiCollisionPinPriority;

	/* Just like MinHorizontalLength this is used to determine a length for output/input. Anti-collision technique requires such value to work with*/
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|AntiCollision", meta = (ClampMin = "4", ClampMax = "64"))
		float AbsoluteMinHorizontalLength;
	/*
	 * Offset gets calculated by triangular wave function. So it gets predictable what offset to use for specific PinIndex
	 * 1. Horizontal (X value) difference between output/input is divided by <levels>
	 * (Level is the maximum value that tri-wave func can return)
	 * (Level is calculated for period)
	 * 2. Offset-to-apply is a result of: tri-wave(PinIndex) * level
	 * Example values for period 4 returned by tri-wave:
	 * 0 1 2 1 0 1 2 1 0, where pin indexes will be:
	 * 0 1 2 3 4 5 6 7 8
	 * where 0 - no offset applied, 1 - minimum offset applied, 2 - maximum
	 * x---.
	 * x--.|_x
	 * x-.|_x
	 *	 |_x
	 */
	UPROPERTY(Config, EditAnywhere, Category = "WireRestyleSettings|AntiCollision", meta = (ClampMin = "2", ClampMax = "16"))
		int EdgeOffsetPeriod;
	UPROPERTY(Config)
		int AntiCollisionLevels;

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