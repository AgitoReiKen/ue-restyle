// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
#include "CoreMinimal.h"

#include "Utils/ColorUtils.h"

#include "DefaultThemeSettings.generated.h"

class UDefaultThemeSettings;

USTRUCT()
struct FDTColor
{
	GENERATED_BODY()

	FDTColor()
	{
		Id = NAME_None;
		bOverrideOpacity = false;
		Opacity = 1.0f;
	}

	FDTColor(const char* Id) : Id(Id), bOverrideOpacity(false), Opacity(1.0f)
	{
	}

	FDTColor(const FName& Id, float Opacity)
		: Id(Id),
		  bOverrideOpacity(true),
		  Opacity(Opacity)
	{
	}

	FDTColor(const FName& Id)
		: Id(Id),
		  bOverrideOpacity(false),
		  Opacity(1.0f)
	{
	}

	FLinearColor Get() const;

	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTColor")
	FName Id;

	UPROPERTY(EditAnywhere, Category = "DTColor")
	bool bOverrideOpacity;

	UPROPERTY(EditAnywhere,
		meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverrideOpacity", EditConditionHides), Category = "DTColor")
	float Opacity;
};

USTRUCT()
struct FDTTextShadowData
{
	GENERATED_BODY()

	FDTTextShadowData()
	{
		Offset = FVector2D(0.375f);
		BlackOpacity = .15f;
	}

	FDTTextShadowData(const FVector2D& Offset, float BlackOpacity)
		: Offset(Offset),
		  BlackOpacity(BlackOpacity)
	{
	}

	UPROPERTY(EditAnywhere, Category = "DTTextShadowData")
	FVector2D Offset;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0"), Category = "DTTextShadowData")
	float BlackOpacity;
};

USTRUCT()
struct FDTTextShadowRef
{
	GENERATED_BODY()
	FDTTextShadowRef() { Id = NAME_None; }

	FDTTextShadowRef(const char* Id) : Id(Id)
	{
	}

	FDTTextShadowRef(const FName& Id) : Id(Id)
	{
	}

	const FDTTextShadowData& Get() const;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Text Shadow", GetOptions = "Restyle.DefaultThemeSettings.GetTextShadowOptions"), Category = "DTTextShadowRef")
	FName Id;
};

USTRUCT()
struct FDTTextData
{
	GENERATED_BODY()

	FDTTextData()
	{
		Size = "Medium";
		Typeface = "Regular";
		Shadow = "Default";
		Color = FDTColor("Light-1");
	}

	FDTTextData(const FName& Size, const FName& Typeface, const FName& Shadow, const FDTColor& TextColor)
		: Size(Size),
		  Typeface(Typeface),
		  Shadow(Shadow),
		  Color(TextColor)
	{
	}

	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetFontSizeOptions"), Category = "DTTextData")
	FName Size;

	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetFontOptions"), Category = "DTTextData")
	FName Typeface;

	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetTextShadowOptions"), Category = "DTTextData")
	FDTTextShadowRef Shadow;

	UPROPERTY(EditAnywhere, Category = "DTTextData")
	FDTColor Color;
};

USTRUCT()
struct FDTTextRef
{
	GENERATED_BODY()
		FDTTextRef() { Id = NAME_None; bOverrideColor = false; Color = "Light-1"; }

	FDTTextRef(const char* Id) : Id(Id), bOverrideColor(false), Color("Light-1")
	{
	}

	FDTTextRef(const FName& Id) : Id(Id), bOverrideColor(false), Color("Light-1")
	{
	}

	FDTTextRef(const FName& Id, FName BackgroundColor) : Id(Id), bOverrideColor(true), Color(BackgroundColor)
	{
	}

	FDTTextData Get() const;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Text", GetOptions = "Restyle.DefaultThemeSettings.GetTextOptions"), Category = "DTTextRef")
	FName Id;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetTextOptions"), Category = "DTTextRef")
	bool bOverrideColor;
	UPROPERTY(EditAnywhere,
		meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions", EditCondition = "bOverrideColor",
			EditConditionHides), Category = "DTTextRef")
	FName Color;
};

USTRUCT()
struct FDTBrushData
{
	GENERATED_BODY()
	FDTBrushData()
	{
		CornerRadius = "Default";
		OutlineWidth = "Medium";
		OutlineColor = FDTColor("Light-4", .5f);
		BackgroundColor = FDTColor("Dark-2", .9f);
	}

	FDTBrushData(const FName& CornerRadius, const FName& OutlineWidth, const FDTColor& OutlineColor,
	             const FDTColor& BackgroundColor)
		: CornerRadius(CornerRadius),
		  OutlineWidth(OutlineWidth),
		  OutlineColor(OutlineColor),
		  BackgroundColor(BackgroundColor)
	{
	}

	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetCornerOptions"), Category = "DTBrushData")
	FName CornerRadius;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetOutlineWidthOptions"), Category = "DTBrushData")
	FName OutlineWidth;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTBrushData")
	FDTColor OutlineColor;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTBrushData")
	FDTColor BackgroundColor;
};

USTRUCT()
struct FDTBrushRef
{
	GENERATED_BODY()
	FDTBrushRef()
	{
		Id = NAME_None;
		bOverrideOutlineColor = false;
		OutlineColor = "Light-4";
		bOverrideOutlineOpacity = false;
		OutlineOpacity = 1.0f;
		bOverrideBackgroundColor = false;
		BackgroundColor = "Light-4";
		bOverrideBackgroundOpacity = false;
		BackgroundOpacity = 1.0f;
	}

	FDTBrushRef(const char* Id)
	  : Id(Id),
		bOverrideOutlineColor(false),
		OutlineColor("Light-4"),
		bOverrideOutlineOpacity(false),
		OutlineOpacity(1.0f),
		bOverrideBackgroundColor(false),
		BackgroundColor("Light-4"),
		bOverrideBackgroundOpacity(false),
		BackgroundOpacity(1.0f)
	{
	}
	FDTBrushRef& SetOutlineColor(bool bOverride, const FName& InOutlineColor = "Light-4")
	{
		bOverrideOutlineColor = bOverride;
		if (bOverride)
		OutlineColor = InOutlineColor;
		return *this;
	}
	FDTBrushRef& SetOutlineOpacity(bool bOverride, float InOutlineOpacity = 1.0f)
	{
		bOverrideOutlineOpacity = bOverride;
		if (bOverride)
		OutlineOpacity = InOutlineOpacity;
		return *this;
	}
	FDTBrushRef& SetBackgroundColor(bool bOverride, const FName& InBackgroundColor = "Light-4")
	{
		bOverrideBackgroundColor = bOverride;
		if (bOverride)
		BackgroundColor = InBackgroundColor;
		return *this;
	}
	FDTBrushRef& SetBackgroundOpacity(bool bOverride, float InBackgroundOpacity = 1.0f)
	{
		bOverrideBackgroundOpacity = bOverride;
		if (bOverride)
		BackgroundOpacity = InBackgroundOpacity;
		return *this;
	} 

	FDTBrushData Get() const;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Brush", GetOptions = "Restyle.DefaultThemeSettings.GetBrushOptions"), Category = "DTBrushRef")
	FName Id;
	UPROPERTY(EditAnywhere, Category = "DTBrushRef")
	bool bOverrideOutlineColor;
	UPROPERTY(EditAnywhere,
		meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions", EditCondition="bOverrideOutlineColor",
			EditConditionHides), Category = "DTBrushRef")
	FName OutlineColor;
	UPROPERTY(EditAnywhere, Category = "DTBrushRef")
		bool bOverrideOutlineOpacity;
	UPROPERTY(EditAnywhere,
		meta = (ClampMin="0.0", ClampMax="1.0", EditCondition = "bOverrideOutlineOpacity",
			EditConditionHides), Category = "DTBrushRef")
	float OutlineOpacity;

	UPROPERTY(EditAnywhere, Category = "DTBrushRef")
		bool bOverrideBackgroundColor;
	UPROPERTY(EditAnywhere,
		meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions", EditCondition = "bOverrideBackgroundColor",
			EditConditionHides), Category = "DTBrushRef")
		FName BackgroundColor;
	UPROPERTY(EditAnywhere, Category = "DTBrushRef")
		bool bOverrideBackgroundOpacity;
	UPROPERTY(EditAnywhere,
		meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverrideBackgroundOpacity",
			EditConditionHides), Category = "DTBrushRef")
		float BackgroundOpacity;
};

USTRUCT()
struct FDTScrollBarData
{
	GENERATED_BODY()
	FDTScrollBarData()
	{
		Normal = "ScrollBarNormal";
		Hovered = "ScrollBarHovered";
		Dragged = "ScrollBarDragged";
		Thickness = 4;
		HPadding = 0;
		VPadding = 0;
	}

	FDTScrollBarData(const FDTBrushRef& Normal, const FDTBrushRef& Hovered, const FDTBrushRef& Dragged,
		float Thickness, const FMargin& HPadding, const FMargin& VPadding)
		: Normal(Normal),
		  Hovered(Hovered),
		  Dragged(Dragged),
		  Thickness(Thickness),
		  HPadding(HPadding),
		  VPadding(VPadding)
	{
	}

	UPROPERTY(EditAnywhere, Category = "DTScrollBarData")
	FDTBrushRef Normal;
	UPROPERTY(EditAnywhere, Category = "DTScrollBarData")
	FDTBrushRef Hovered;
	UPROPERTY(EditAnywhere, Category = "DTScrollBarData")
	FDTBrushRef Dragged;
	UPROPERTY(EditAnywhere, Category = "DTScrollBarData")
	float Thickness;
	UPROPERTY(EditAnywhere, Category = "DTScrollBarData")
	FMargin HPadding;
	UPROPERTY(EditAnywhere, Category = "DTScrollBarData")
	FMargin VPadding;
};

USTRUCT()
struct FDTScrollBarRef
{
	GENERATED_BODY()
	FDTScrollBarRef() { Id = NAME_None; }

	FDTScrollBarRef(const char* Id) : Id(Id)
	{
	}

	FDTScrollBarRef(const FName& Id) : Id(Id)
	{
	}

	const FDTScrollBarData& Get() const;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Scroll Bar", GetOptions = "Restyle.DefaultThemeSettings.GetScrollBarOptions"), Category = "DTScrollBarRef")
	FName Id;
};

USTRUCT()
struct FDTEditableTextBoxData
{
	GENERATED_BODY()

	FDTEditableTextBoxData()
	{
		BackgroundNormal = "InputNormal";
		BackgroundHovered = "InputHovered";
		BackgroundFocused = "InputFocused";
		BackgroundReadOnly = "InputReadOnly";
		Text = "Input";
		ForegroundNormal = "Light-2";
		ForegroundFocused = "Light-2";
		ForegroundReadOnly = "Light-3";
		Padding = "Medium";
		ScrollBar = "Input";
	}

	FDTEditableTextBoxData(const FDTBrushRef& BackgroundNormal, const FDTBrushRef& BackgroundHovered,
	                       const FDTBrushRef& BackgroundFocused, const FDTBrushRef& BackgroundReadOnly,
	                       const FDTColor& ForegroundNormal,
	                       const FDTColor& ForegroundFocused, const FDTColor& ForegroundReadOnly,
	                       const FDTTextRef& Text,
	                       const FName& Padding, const FDTScrollBarRef& ScrollBar)
		: BackgroundNormal(BackgroundNormal),
		  BackgroundHovered(BackgroundHovered),
		  BackgroundFocused(BackgroundFocused),
		  BackgroundReadOnly(BackgroundReadOnly),
		  ForegroundNormal(ForegroundNormal),
		  ForegroundFocused(ForegroundFocused),
		  ForegroundReadOnly(ForegroundReadOnly),
		  Text(Text),
		  Padding(Padding),
		  ScrollBar(ScrollBar)
	{
	}

	UPROPERTY(EditAnywhere, Category = "DTEditableTextBoxData")
	FDTBrushRef BackgroundNormal;
	UPROPERTY(EditAnywhere, Category = "DTEditableTextBoxData")
	FDTBrushRef BackgroundHovered;
	UPROPERTY(EditAnywhere, Category = "DTEditableTextBoxData")
	FDTBrushRef BackgroundFocused;
	UPROPERTY(EditAnywhere, Category = "DTEditableTextBoxData")
	FDTBrushRef BackgroundReadOnly;
	UPROPERTY(EditAnywhere, Category = "DTEditableTextBoxData")
	FDTColor ForegroundNormal;
	UPROPERTY(EditAnywhere, Category = "DTEditableTextBoxData")
	FDTColor ForegroundFocused;
	UPROPERTY(EditAnywhere, Category = "DTEditableTextBoxData")
	FDTColor ForegroundReadOnly;
	UPROPERTY(EditAnywhere, Category = "DTEditableTextBoxData")
	FDTTextRef Text;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"), Category = "DTEditableTextBoxData")
	FName Padding;
	UPROPERTY(EditAnywhere, Category = "DTEditableTextBoxData")
	FDTScrollBarRef ScrollBar;
};

USTRUCT()
struct FDTEditableTextBoxRef
{
	GENERATED_BODY()
	FDTEditableTextBoxRef() { Id = NAME_None; }

	FDTEditableTextBoxRef(const char* Id) : Id(Id)
	{
	}

	FDTEditableTextBoxRef(const FName& Id) : Id(Id)
	{
	}

	const FDTEditableTextBoxData& Get() const;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Editable Text Box", GetOptions = "Restyle.DefaultThemeSettings.GetEditableTextBoxOptions"), Category = "DTEditableTextBoxRef")
	FName Id;
};

USTRUCT()
struct FDTButtonData
{
	GENERATED_BODY()
	FDTButtonData()
	{
		Normal = "ButtonNormal";
		Hovered = "ButtonHovered";
		Pressed = "ButtonPressed";
		Disabled = "ButtonDisabled";
		NormalForeground = "Light-2";
		HoveredForeground = "Light-2";
		PressedForeground = "Light-2";
		DisabledForeground = "Light-3";
		Text = "Input";
		Padding = "Medium";
	}

	FDTButtonData(const FDTBrushRef& Normal, const FDTBrushRef& Hovered, const FDTBrushRef& Pressed,
		const FDTBrushRef& Disabled, const FDTTextRef& Text, const FDTColor& NormalForeground,
		const FDTColor& HoveredForeground, const FDTColor& PressedForeground, const FDTColor& DisabledForeground,
		const FName& Padding, const FName& IconSize)
		: Normal(Normal),
		  Hovered(Hovered),
		  Pressed(Pressed),
		  Disabled(Disabled),
		  Text(Text),
		  NormalForeground(NormalForeground),
		  HoveredForeground(HoveredForeground),
		  PressedForeground(PressedForeground),
		  DisabledForeground(DisabledForeground),
		  Padding(Padding),
		  IconSize(IconSize)
	{
	}

	UPROPERTY(EditAnywhere, Category = "DTButtonData")
	FDTBrushRef Normal;
	UPROPERTY(EditAnywhere, Category = "DTButtonData")
	FDTBrushRef Hovered;
	UPROPERTY(EditAnywhere, Category = "DTButtonData")
	FDTBrushRef Pressed;
	UPROPERTY(EditAnywhere, Category = "DTButtonData")
	FDTBrushRef Disabled;
	UPROPERTY(EditAnywhere, Category = "DTButtonData")
	FDTTextRef Text;
	UPROPERTY(EditAnywhere, Category = "DTButtonData")
	FDTColor NormalForeground;
	UPROPERTY(EditAnywhere, Category = "DTButtonData")
	FDTColor HoveredForeground;
	UPROPERTY(EditAnywhere, Category = "DTButtonData")
	FDTColor PressedForeground;
	UPROPERTY(EditAnywhere, Category = "DTButtonData")
	FDTColor DisabledForeground;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"), Category = "DTButtonData")
	FName Padding;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetIconSizeOptions"), Category = "DTButtonData")
	FName IconSize;
};

USTRUCT()
struct FDTButtonRef
{
	GENERATED_BODY()
	FDTButtonRef() { Id = NAME_None; }

	FDTButtonRef(const char* Id) : Id(Id)
	{
	}

	FDTButtonRef(const FName& Id) : Id(Id)
	{
	}

	const FDTButtonData& Get() const;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Button", GetOptions = "Restyle.DefaultThemeSettings.GetButtonOptions"), Category = "DTButtonRef")
	FName Id;
};

USTRUCT()
struct FDTComboButtonData
{
	GENERATED_BODY()
	FDTComboButtonData()
	{
		Button = "Default";
		MenuBorder = "Transparent";
		MenuBorderPadding = "Zero";
		bHasDownArrow = true;
		DownArrowSpacing = "Large";
		ArrowSize = "Small";
		ArrowOpacity = .75f;
	}

	FDTComboButtonData(const FDTButtonRef& Button, const FDTBrushRef& MenuBorder, const FName& MenuBorderPadding,
	                   bool bHasDownArrow, const FName& DownArrowSpacing, const FName& ArrowSize, float ArrowOpacity)
		: Button(Button),
		  MenuBorder(MenuBorder),
		  MenuBorderPadding(MenuBorderPadding),
		  bHasDownArrow(bHasDownArrow),
		  DownArrowSpacing(DownArrowSpacing),
		  ArrowSize(ArrowSize),
		  ArrowOpacity(ArrowOpacity)
	{
	}

	UPROPERTY(EditAnywhere, Category = "DTComboButtonData")
	FDTButtonRef Button;
	UPROPERTY(EditAnywhere, Category = "DTComboButtonData")
	FDTBrushRef MenuBorder;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"), Category = "DTComboButtonData")
	FName MenuBorderPadding;

	UPROPERTY(EditAnywhere, Category = "DTComboButtonData")
	bool bHasDownArrow;

	UPROPERTY(EditAnywhere,
		meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions", EditCondition = "bHasDownArrow",
			EditConditionHides), Category = "DTComboButtonData")
	FName DownArrowSpacing;
	UPROPERTY(EditAnywhere,
		meta = (GetOptions = "Restyle.DefaultThemeSettings.GetIconSizeOptions", EditCondition = "bHasDownArrow",
			EditConditionHides), Category = "DTComboButtonData")
	FName ArrowSize;
	UPROPERTY(EditAnywhere,
		meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition="bHasDownArrow", EditConditionHides), Category = "DTComboButtonData")
	float ArrowOpacity;
};

USTRUCT()
struct FDTComboButtonRef
{
	GENERATED_BODY()
	FDTComboButtonRef() { Id = NAME_None; }

	FDTComboButtonRef(const char* Id) : Id(Id)
	{
	}

	FDTComboButtonRef(const FName& Id) : Id(Id)
	{
	}

	const FDTComboButtonData& Get() const;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Combo Button", GetOptions = "Restyle.DefaultThemeSettings.GetComboButtonOptions"), Category = "DTComboButtonRef")
	FName Id;
};

USTRUCT()
struct FDTCheckBoxData
{
	GENERATED_BODY()
	FDTCheckBoxData()
	{
		BackgroundImage = "InputNormal";
		BackgroundHoveredImage = "InputNormal";
		BackgroundPressedImage = "InputNormal";
		UncheckedImageColor = FDTColor("Light-2");
		UncheckedHoveredImageColor = FDTColor("Light-1");
		UncheckedPressedImageColor = FDTColor("Light-1");
		CheckedImageColor = FDTColor("Light-2");
		CheckedHoveredImageColor = FDTColor("Light-1");
		CheckedPressedImageColor = FDTColor("Light-1");
		UndeterminedImageColor = FDTColor("Light-2");
		UndeterminedHoveredImageColor = FDTColor("Light-1");
		UndeterminedPressedImageColor = FDTColor("Light-1");
		IconSize = "Medium";
		Padding = "Zero";
	}

	FDTCheckBoxData(const FDTBrushRef& BackgroundImage, const FDTBrushRef& BackgroundHoveredImage,
		const FDTBrushRef& BackgroundPressedImage, const FDTColor& UncheckedImageColor,
		const FDTColor& UncheckedHoveredImageColor, const FDTColor& UncheckedPressedImageColor,
		const FDTColor& CheckedImageColor, const FDTColor& CheckedHoveredImageColor,
		const FDTColor& CheckedPressedImageColor, const FDTColor& UndeterminedImageColor,
		const FDTColor& UndeterminedHoveredImageColor, const FDTColor& UndeterminedPressedImageColor,
		const FName& IconSize, const FName& Padding)
		: BackgroundImage(BackgroundImage),
		  BackgroundHoveredImage(BackgroundHoveredImage),
		  BackgroundPressedImage(BackgroundPressedImage),
		  UncheckedImageColor(UncheckedImageColor),
		  UncheckedHoveredImageColor(UncheckedHoveredImageColor),
		  UncheckedPressedImageColor(UncheckedPressedImageColor),
		  CheckedImageColor(CheckedImageColor),
		  CheckedHoveredImageColor(CheckedHoveredImageColor),
		  CheckedPressedImageColor(CheckedPressedImageColor),
		  UndeterminedImageColor(UndeterminedImageColor),
		  UndeterminedHoveredImageColor(UndeterminedHoveredImageColor),
		  UndeterminedPressedImageColor(UndeterminedPressedImageColor),
		  IconSize(IconSize),
		  Padding(Padding)
	{
	}

	UPROPERTY(EditAnywhere, Category = "DTCheckBoxData")
	FDTBrushRef BackgroundImage;
	UPROPERTY(EditAnywhere, Category = "DTCheckBoxData")
	FDTBrushRef BackgroundHoveredImage;
	UPROPERTY(EditAnywhere, Category = "DTCheckBoxData")
	FDTBrushRef BackgroundPressedImage;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTCheckBoxData")
	FDTColor UncheckedImageColor;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTCheckBoxData")
	FDTColor UncheckedHoveredImageColor;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTCheckBoxData")
	FDTColor UncheckedPressedImageColor;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTCheckBoxData")
	FDTColor CheckedImageColor;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTCheckBoxData")
	FDTColor CheckedHoveredImageColor;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTCheckBoxData")
	FDTColor CheckedPressedImageColor;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTCheckBoxData")
	FDTColor UndeterminedImageColor;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTCheckBoxData")
	FDTColor UndeterminedHoveredImageColor;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"), Category = "DTCheckBoxData")
	FDTColor UndeterminedPressedImageColor;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetIconSizeOptions"), Category = "DTCheckBoxData")
	FName IconSize;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"), Category = "DTCheckBoxData")
	FName Padding;
};

USTRUCT()
struct FDTCheckBoxRef
{
	GENERATED_BODY()
	FDTCheckBoxRef() { Id = NAME_None; }

	FDTCheckBoxRef(const char* Id) : Id(Id)
	{
	}

	FDTCheckBoxRef(const FName& Id) : Id(Id)
	{
	}

	const FDTCheckBoxData& Get() const;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Check Box", GetOptions = "Restyle.DefaultThemeSettings.GetCheckBoxOptions"), Category = "DTCheckBoxRef")
	FName Id;
};

USTRUCT()
struct FDTComboBoxRowData
{
	GENERATED_BODY()
	FDTComboBoxRowData()
	{
		Text = "Input";
		Inactive = "MenuRow";
		InactiveHighlighted = "MenuRowHighlighted";
		InactiveHovered = "MenuRowHovered";
		Active = "MenuRowActive";
		ActiveHighlighted = "MenuRowHoveredActive";
		ActiveHovered = "MenuRowHighlightedActive";
		Even = Odd = Inactive;
		EvenHovered = OddHovered = InactiveHovered;
		NormalTextColor = "Light-2";
		SelectedTextColor = "Light-2";
	}

	FDTComboBoxRowData(const FDTTextRef& Text, const FDTBrushRef& Active, const FDTBrushRef& ActiveHighlighted,
	                   const FDTBrushRef& ActiveHovered, const FDTBrushRef& Inactive,
	                   const FDTBrushRef& InactiveHighlighted,
	                   const FDTBrushRef& InactiveHovered, const FDTBrushRef& Even, const FDTBrushRef& EvenHovered,
	                   const FDTBrushRef& Odd, const FDTBrushRef& OddHovered, const FDTColor& NormalTextColor,
	                   const FDTColor& SelectedTextColor)
		: Text(Text),
		  Active(Active),
		  ActiveHighlighted(ActiveHighlighted),
		  ActiveHovered(ActiveHovered),
		  Inactive(Inactive),
		  InactiveHighlighted(InactiveHighlighted),
		  InactiveHovered(InactiveHovered),
		  Even(Even),
		  EvenHovered(EvenHovered),
		  Odd(Odd),
		  OddHovered(OddHovered),
		  NormalTextColor(NormalTextColor),
		  SelectedTextColor(SelectedTextColor)
	{
	}

	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTTextRef Text;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTBrushRef Active;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTBrushRef ActiveHighlighted;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTBrushRef ActiveHovered;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTBrushRef Inactive;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTBrushRef InactiveHighlighted;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTBrushRef InactiveHovered;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTBrushRef Even;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTBrushRef EvenHovered;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTBrushRef Odd;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTBrushRef OddHovered;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTColor NormalTextColor;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxRowData")
	FDTColor SelectedTextColor;
};

USTRUCT()
struct FDTComboBoxRowRef
{
	GENERATED_BODY()
	FDTComboBoxRowRef() { Id = NAME_None; }

	FDTComboBoxRowRef(const char* Id) : Id(Id)
	{
	}

	FDTComboBoxRowRef(const FName& Id) : Id(Id)
	{
	}

	const FDTComboBoxRowData& Get() const;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Combo Box Row", GetOptions = "Restyle.DefaultThemeSettings.GetComboBoxRowOptions"), Category = "DTComboBoxRowRef")
	FName Id;
};

USTRUCT()
struct FDTComboBoxData
{
	GENERATED_BODY()

	FDTComboBoxData()
	{
		ComboButton = "Default";
		Row = "Default";
		MenuRowPadding = "Medium";
	}

	FDTComboBoxData(const FDTComboButtonRef& ComboButton, const FDTComboBoxRowRef& Row, const FName& MenuRowPadding)
		: ComboButton(ComboButton),
		  Row(Row),
		  MenuRowPadding(MenuRowPadding)
	{
	}

	UPROPERTY(EditAnywhere, Category = "DTComboBoxData")
	FDTComboButtonRef ComboButton;
	UPROPERTY(EditAnywhere, Category = "DTComboBoxData")
	FDTComboBoxRowRef Row;
	UPROPERTY(EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"), Category = "DTComboBoxData")
	FName MenuRowPadding;
};

USTRUCT()
struct FDTComboBoxRef
{
	GENERATED_BODY()

	FDTComboBoxRef() { Id = NAME_None; }

	FDTComboBoxRef(const char* Id) : Id(Id)
	{
	}

	FDTComboBoxRef(const FName& Id) : Id(Id)
	{
	}

	const FDTComboBoxData& Get() const;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Combo Box", GetOptions = "Restyle.DefaultThemeSettings.GetComboBoxOptions"), Category = "DTComboBoxRef")
	FName Id;
};


UCLASS(Config = Restyle, GlobalUserConfig)
class UDefaultThemeSettings : public UObject
{
	GENERATED_BODY()
public:
	UDefaultThemeSettings()
	{
		SetDefaults();
	}

#pragma region Statics
	void SetDefaults();

	static UDefaultThemeSettings* Get()
	{
		return GetMutableDefault<UDefaultThemeSettings>();
	}

	UFUNCTION()
	static TArray<FString> GetFontOptions();
	UFUNCTION()
	static TArray<FString> GetColorOptions();
	UFUNCTION()
	static TArray<FString> GetCornerOptions();
	UFUNCTION()
	static TArray<FString> GetOutlineWidthOptions();
	UFUNCTION()
	static TArray<FString> GetMarginOptions();
	UFUNCTION()
	static TArray<FString> GetFontSizeOptions();
	UFUNCTION()
	static TArray<FString> GetIconSizeOptions();
	UFUNCTION()
	static TArray<FString> GetSpacingOptions();

	UFUNCTION()
	static TArray<FString> GetTextShadowOptions();
	UFUNCTION()
	static TArray<FString> GetCheckBoxOptions();
	UFUNCTION()
	static TArray<FString> GetComboBoxOptions();
	UFUNCTION()
	static TArray<FString> GetComboBoxRowOptions();
	UFUNCTION()
	static TArray<FString> GetComboButtonOptions();
	UFUNCTION()
	static TArray<FString> GetTextOptions();
	UFUNCTION()
	static TArray<FString> GetEditableTextBoxOptions();
	UFUNCTION()
	static TArray<FString> GetButtonOptions();
	UFUNCTION()
	static TArray<FString> GetBrushOptions();
	UFUNCTION()
	static TArray<FString> GetScrollBarOptions();

	static FLinearColor GetColor(const FName& Id);
	static FVector4 GetCorner(const FName& Id);
	static float GetOutlineWidth(const FName& Id);
	static FMargin GetMargin(const FName& Id);
	static uint16 GetFontSize(const FName& Id);
	static uint16 GetIconSize(const FName& Id);
	static float GetSpacing(const FName& Id);

	static const FDTTextShadowData& GetTextShadow(const FName& Id);
	static const FDTBrushData& GetBrush(const FName& Id);
	static const FDTTextData& GetText(const FName& Id);
	static const FDTCheckBoxData& GetCheckBox(const FName& Id);
	static const FDTComboBoxData& GetComboBox(const FName& Id);
	static const FDTComboBoxRowData& GetComboBoxRow(const FName& Id);
	static const FDTComboButtonData& GetComboButton(const FName& Id);
	static const FDTEditableTextBoxData& GetEditableTextBox(const FName& Id);
	static const FDTButtonData& GetButton(const FName& Id);
	static const FDTScrollBarData& GetScrollBar(const FName& Id);
#pragma endregion
	struct FSlateVectorImageBrush GetVectorImageBrush(const FString& Path,  const FVector2D& Size) const;
	void ModifyCheckBox(FCheckBoxStyle* Style, const FDTCheckBoxData& Config, const FString& UncheckedIconPath, const FString& CheckedIconPath, const FString& UndeterminedIconPath) const;
	void ModifyEditableTextBox(FEditableTextBoxStyle* Style, const FDTEditableTextBoxData& Config) const;
	void ModifyInlineEditableTextBox(FInlineEditableTextBlockStyle* Style, const FDTEditableTextBoxData& Config) const;
	void ModifyButtonStyle(FButtonStyle* Style, const FDTButtonData& Config) const;
	void ModifyComboButtonStyle(FComboButtonStyle* Style, const FDTComboButtonData& Config,
	                            const FString& IconPath) const;
	void ModifyComboBoxRow(FTableRowStyle* Style, const FDTComboBoxRowData& Config) const;
	void ModifyComboBox(FComboBoxStyle* Style, const FDTComboBoxData& Config, const FString& IconPath) const;
	void ModifyBrush(FSlateBrush* Brush, const FDTBrushData& Config,
	                 bool WhiteTint = false) const;
	void ModifyTextBlockStyle(FTextBlockStyle* Style, const FDTTextData& Config, bool WhiteTint = false) const;
	void ModifyFontInfo(FSlateFontInfo* Info, const FDTTextData& Config) const;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(EditAnywhere, meta = (Category = "Commands"))
	bool bRestoreDefaults;

	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	TMap<FName, FColorOkLch> PaletteMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	TMap<FName, FVector4> CornerRadiusMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	TMap<FName, float> OutlineWidthMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	TMap<FName, FMargin> MarginMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	TMap<FName, uint16> FontSizeMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	TMap<FName, uint16> IconSizeMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	TMap<FName, float> SpacingMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	TMap<FName, FDTTextShadowData> TextShadowMap;

	UPROPERTY(Config, EditAnywhere, meta = (Category = "Widgets"))
	TMap<FName, FDTScrollBarData> ScrollBarMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Widgets"))
	TMap<FName, FDTBrushData> BrushMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Widgets"))
	TMap<FName, FDTTextData> TextMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Widgets"))
	TMap<FName, FDTButtonData> ButtonMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Widgets"))
	TMap<FName, FDTCheckBoxData> CheckBoxMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Widgets"))
	TMap<FName, FDTEditableTextBoxData> EditableTextBoxMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Widgets"))
	TMap<FName, FDTComboButtonData> ComboButtonMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Widgets"))
	TMap<FName, FDTComboBoxRowData> ComboBoxRowMap;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Widgets"))
	TMap<FName, FDTComboBoxData> ComboBoxMap;   
};
//
//class FDefaultThemeStyles
//{
//	static inline const FName Checkbox = "Restyle.Checkbox";
//	static inline const FName ComboBox = "Restyle.ComboBox";
//	static inline const FName ComboBox_Row = "Restyle.ComboBox.Row";
//	static inline const FName ComboButton = "Restyle.ComboButton";
//	static inline const FName ComboButton_Text = "Restyle.ComboButton.Text";
//	static inline const FName EditableTextBox = "Restyle.EditableTextBox";
//	static inline const FName TransparentButton = "Restyle.TransparentButton";
//	static inline const FName Button = "Restyle.Button";
//};
