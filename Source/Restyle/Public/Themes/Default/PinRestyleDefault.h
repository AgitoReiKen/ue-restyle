// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#include "CoreMinimal.h"
#include "Themes/ThemeInterfaces.h"
#include "Default/DefaultGraphPanelPinFactory.h"
#include "DefaultThemeSettings.h"
#include "PinRestyleDefault.generated.h"


UENUM()
enum class EPinIconSet_Disconnected
{
	/* Center empty*/
	A,
	/* Center has 50% opacity shape*/
	B
};

UENUM()
enum class EPinIconSet_Connected
{
	A,
	B
};

USTRUCT()
struct FDTStringInput
{
	GENERATED_BODY()
	FDTStringInput()
	{
		Body = "Default";
		ErrorReportingSpacing = "Large";
	}

	FDTStringInput(const FDTEditableTextBoxRef& Body, const FName& ErrorReportingSpacing)
		: Body(Body),
		  ErrorReportingSpacing(ErrorReportingSpacing)
	{
	}

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTEditableTextBoxRef Body;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName ErrorReportingSpacing;
};

USTRUCT()
struct FDTVectorInput
{
	GENERATED_BODY()
	FDTVectorInput()
	{
		Body = "Default";
		ForegroundX = FDTColor("Light-2");
		ForegroundY = FDTColor("Light-2");
		ForegroundZ = FDTColor("Light-2");
		ForegroundW = FDTColor("Light-2");
		Padding = "Medium";
		LabelsText = "Medium";
		LabelsColor = FDTColor("Light-4");
		bNewLabelsForRotator = false;
		Spacing = "Small";
	}

	FDTVectorInput(const FDTEditableTextBoxRef& Body, const FDTColor& ForegroundX, const FDTColor& ForegroundY,
	               const FDTColor& ForegroundZ, const FDTColor& ForegroundW, const FName& Padding,
	               const FDTTextRef& LabelsText,
	               const FDTColor& LabelsColor, bool bNewLabelsForRotator, const FName& Spacing)
		: Body(Body),
		  ForegroundX(ForegroundX),
		  ForegroundY(ForegroundY),
		  ForegroundZ(ForegroundZ),
		  ForegroundW(ForegroundW),
		  Padding(Padding),
		  LabelsText(LabelsText),
		  LabelsColor(LabelsColor),
		  bNewLabelsForRotator(bNewLabelsForRotator),
		  Spacing(Spacing)
	{
	}

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTEditableTextBoxRef Body;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor ForegroundX;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor ForegroundY;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor ForegroundZ;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor ForegroundW;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName Padding;

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTTextRef LabelsText;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor LabelsColor;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	bool bNewLabelsForRotator;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName Spacing;
};

USTRUCT()
struct FDTAssetPickerUtilButton
{
	GENERATED_BODY()

	FDTAssetPickerUtilButton()
	{
		Size = "Medium";
		Spacing = "Small";
		Normal = FDTColor("Light-4");
		Hovered = FDTColor("Light-3");
		Pressed = FDTColor("Light-2");
		Disabled = FDTColor("Light-4", .5f);
	}

	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetIconSizeOptions"))
	FName Size;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName Spacing;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Normal;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Hovered;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Pressed;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Disabled;
};

USTRUCT()
struct FDTAssetPicker
{
	GENERATED_BODY()
	FDTAssetPicker()
	{
		ButtonMaxWidth = 200.f;
		ComboButton = "Default";
		GeneralSpacing = "Medium";
		UtilButton = "Transparent";
	}

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	float ButtonMaxWidth;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTComboButtonRef ComboButton;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName GeneralSpacing;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTButtonRef UtilButton;
};

USTRUCT()
struct FDTTextInput
{
	GENERATED_BODY()
	FDTTextInput()
	{
		AdvancedTextButton = "Transparent";
		Spacing = "Medium";
	}

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTComboButtonRef AdvancedTextButton;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName Spacing;
};

USTRUCT()
struct FDTKeyInput
{
	GENERATED_BODY()
	FDTKeyInput()
	{
		ComboButton = "DefaultNoArrow";
		Button = "DefaultMedium";
		Spacing = "Medium";
	}

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTComboButtonRef ComboButton;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTButtonRef Button;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName Spacing;
};

USTRUCT()
struct FDTPinColor
{
	GENERATED_BODY()
	FDTPinColor()
	{
		Padding = "Small";
		Border = "Light-4";
		Size = "Medium";
	}

	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName Padding;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Border;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetIconSizeOptions"))
	FName Size;
};
	
USTRUCT()
struct FDTPinSequenceInput
{
	GENERATED_BODY()
	FDTPinSequenceInput()
	{
		ButtonStyle = "TextNoPadding";
		Spacing = "Medium";
		IconSize = "Small";
		OverrideText = FText::FromString("Pin");
		//SpacingToPreventOverlapping = 7.f;

	}
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTButtonRef ButtonStyle;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName Spacing;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetIconSizeOptions"))
	FName IconSize;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FText OverrideText;
	/*UPROPERTY(Category = "DTPinData",EditAnywhere)
	float SpacingToPreventOverlapping;*/
};
 
USTRUCT()
struct FDTPinInputs
{
	GENERATED_BODY()
	FDTPinInputs()
	{
		String = FDTStringInput();
		Text = FDTTextInput();
		Vector = FDTVectorInput();
		Boolean = "Default";
		Select = "Default";
		PinSelectorContentSpacing = "Medium";
		AssetPicker = FDTAssetPicker();
		Color = FDTPinColor();
	}

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTStringInput String;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTTextInput Text;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTVectorInput Vector;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTCheckBoxRef Boolean;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTComboBoxRef Select;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName PinSelectorContentSpacing;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTAssetPicker AssetPicker;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTKeyInput Key;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTPinColor Color;
	// Is a "add pin" button
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTPinSequenceInput Sequence;
};

USTRUCT()
struct FDTMiscIconColorSet
{
	GENERATED_BODY()
	FDTMiscIconColorSet()
	{
		bWatch = true;
		Watch = FDTColor("Light-2");
	}

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	bool bWatch;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (EditCondition = "bWatch", EditConditionHides))
	FDTColor Watch;
};

USTRUCT()
struct FDTPinTypeColorSet
{
	GENERATED_BODY()
	FDTPinTypeColorSet()
	{
		Default = FDTColor("Light-2");
		Execution = FDTColor("Light-2");
		Index = FDTColor("Light-2");
		Wildcard = FDTColor("Light-2");

		Boolean = FDTColor("Red-3");

		Byte = FDTColor("Green-4");
		Int = FDTColor("Green-2");
		Int64 = FDTColor("Green-5");
		Float = FDTColor("Green-3");
		Double = FDTColor("Green-3");
		Real = FDTColor("Green-3");

		Text = FDTColor("Pink-1");
		String = FDTColor("Pink-2");
		Name = FDTColor("Pink-3");

		Struct = FDTColor("Blue-2");
		Class = FDTColor("Violet-2");
		SoftClass = FDTColor("Violet-3");

		Object = FDTColor("LBlue-2");
		SoftObject = FDTColor("LBlue-3");

		Delegate = FDTColor("Red-2");
		Interface = FDTColor("YGreen-2");

		Vector = FDTColor("Orange-2");
		Rotator = FDTColor("Blue-2");
		Transform = FDTColor("Orange-3");
	}

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Default;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Execution;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Index;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Wildcard;

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Boolean;

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Byte;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Int;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Int64;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Float;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Double;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Real;

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Text;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor String;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Name;

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Struct;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Class;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor SoftClass;

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Object;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor SoftObject;

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Delegate;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Interface;

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Vector;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Rotator;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor Transform;
};

USTRUCT()
struct FDTPinBase
{
	GENERATED_BODY()
public:
	FDTPinBase()
	{
		Text = "Small";
		NormalColor = FDTColor("Light-2");
		DiffingColor = FDTColor("LBlue-2");
		OrphanedColor = FDTColor("Red-3");
		NonEditableOpacity = .75f;
		HoverOpacity = .25f;
		Spacing = "Medium";
		PreferredWrapSize = 250.f;
		IconSize = "Small";
		MinDesiredHeight = 24;
	}
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (ClampMin = "0", ClampMax = "96"))
	float MinDesiredHeight;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTTextRef Text;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor NormalColor;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor DiffingColor;
	UPROPERTY(Category = "DTPinData",EditAnywhere)
	FDTColor OrphanedColor;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (ClampMin = "0.25", ClampMax = "1.0"))
	float NonEditableOpacity;
	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float HoverOpacity;

	UPROPERTY(Category = "DTPinData",EditAnywhere,
		meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName Spacing;

	UPROPERTY(Category = "DTPinData",EditAnywhere,
		meta = (GetOptions = "Restyle.DefaultThemeSettings.GetIconSizeOptions"))
	FName IconSize;

	UPROPERTY(Category = "DTPinData",EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float PreferredWrapSize;
};

USTRUCT()
struct FDTCustomPins
{
	GENERATED_BODY()
	FDTCustomPins()
	{
		bVector4 = true;
	}

	UPROPERTY(Category = "DTPinData",EditAnywhere)
	bool bVector4;
};

UCLASS(Config = Restyle, GlobalUserConfig)
class UPinRestyleSettings : public UObject
{
	GENERATED_BODY()

public:
	UPinRestyleSettings()
	{
		SetDefaults();
	}

	static const UPinRestyleSettings* Get();
	static UPinRestyleSettings* GetM();
	void SetDefaults();
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Category = "Commands"))
	bool bRestoreDefaults;

	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	bool bApplyIcons;

	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	FDTPinBase Base;

	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	FDTPinInputs Inputs;

	UPROPERTY(Config, EditAnywhere, meta = (Category = "Functional"))
	FDTCustomPins CustomPins;

	UPROPERTY(Config, EditAnywhere, meta = (EditCondition="bApplyIcons", EditConditionHides, Category = "Settings"))
	FDTMiscIconColorSet IconColors;

	UPROPERTY(Config, EditAnywhere, meta = (Category = "Graph Editor"))
	bool bOverrideGraphEditorSettings;

	UPROPERTY(Config, EditAnywhere, meta = (Category = "Graph Editor"))
	FDTPinTypeColorSet PinColors;
};

struct FPinRestyleStyles
{
	static inline const FName Kismet_VariableList_ArrayTypeIcon_Disconnected =
		"Restyle.Kismet.VariableList.ArrayTypeIcon.Disconnected";
	static inline const FName Kismet_VariableList_ArrayTypeIcon_Connected =
		"Restyle.Kismet.VariableList.ArrayTypeIcon.Connected";
	static inline const FName Kismet_VariableList_SetTypeIcon_Disconnected =
		"Restyle.Kismet.VariableList.SetTypeIcon.Disconnected";
	static inline const FName Kismet_VariableList_SetTypeIcon_Connected =
		"Restyle.Kismet.VariableList.SetTypeIcon.Connected";
	static inline const FName Kismet_VariableList_MapValueTypeIcon_Disconnected =
		"Restyle.Kismet.VariableList.MapValueTypeIcon.Disconnected";
	static inline const FName Kismet_VariableList_MapValueTypeIcon_Connected =
		"Restyle.Kismet.VariableList.MapValueTypeIcon.Connected";


	static inline const FName AssetPicker_Button_Use = "Restyle.AssetPicker.Button.Use";
	static inline const FName AssetPicker_Button_Browse = "Restyle.AssetPicker.Button.Browse";
	static inline const FName Graph_TextInput_AdvancedText_ComboButton = "Restyle.Graph.TextInput.AdvancedTextButton";
	static inline const FName Graph_Checkbox = "Restyle.Checkbox";
	static inline const FName ComboBox = "Restyle.ComboBox";
	static inline const FName ComboBox_Row = "Restyle.ComboBox.Row";
	static inline const FName ComboButton = "Restyle.ComboButton";
	static inline const FName ComboButton_Text = "Restyle.ComboButton.Text";
	static inline const FName EditableTextBox = "Restyle.EditableTextBox";
	static inline const FName TransparentButton = "Restyle.TransparentButton";
	static inline const FName Button = "Restyle.Button";
	static inline const FName ComboBox_Button_FontInfo = "Restyle.ComboBox.Button.FontInfo";
	static inline const FName Graph_EditableTextBox = "Restyle.Graph.EditableTextBox";
	static inline const FName AssetPicker_ComboButton = "Restyle.AssetPicker.ComboButton ";
	static inline const FName AssetPicker_ComboButton_Text = "Restyle.AssetPicker.ComboButton.Text";
	static inline const FName Graph_VectorEditableTextBox = "Restyle.Graph.VectorEditableTextBox";
	static inline const FName KeyInput_ComboButton = "Restyle.KeyInput.ComboButton";
	static inline const FName KeyInput_Button = "Restyle.KeyInput.Button";
	static inline const FName Sequence_Button = "Restyle.SequenceInput.Button";
	static inline const FName Sequence_Button_Text = "Restyle.SequenceInput.Button.Text";
	static inline const FName Icon_AddPin = "Restyle.Icon.AddPin";
};

class FPinRestyleDefault : public IPinRestyleInterface
{
public:
	explicit FPinRestyleDefault();
	virtual ERestyleSubject GetSubject() override;
	virtual void Register() override;
	virtual void Unregister() override;
	virtual TSharedPtr<FGraphPanelPinFactory> GetFactory() override;
	virtual void Update() override;
	virtual bool IsRegistered() override;
private:
	bool OnSettingsChanged();
	bool bRegistered;
	TSharedPtr<FDefaultGraphPanelPinFactory> Factory;
};
