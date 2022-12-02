// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "Themes/Default/DefaultThemeSettings.h"

#include "RestyleProcessor.h"

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleMacros.h"


void UDefaultThemeSettings::SetDefaults()
{
	auto GetHuePalette = [](FString Name, float Hue) -> TMap<FName, FColorOkLch>
	{
		//HueShift
		float HS = 3;
		return {
			{FName(FString::Printf(L"%s-0", *Name)), FColorOkLch(0.95, .03, Hue)},
			{FName(FString::Printf(L"%s-1", *Name)), FColorOkLch(0.84, .1, Hue - HS)},
			{FName(FString::Printf(L"%s-2", *Name)), FColorOkLch(0.72, .15, Hue)},
			{FName(FString::Printf(L"%s-3", *Name)), FColorOkLch(0.56, .2, Hue + HS)},
			{FName(FString::Printf(L"%s-4", *Name)), FColorOkLch(0.48, .08, Hue)},
			{FName(FString::Printf(L"%s-5", *Name)), FColorOkLch(0.56, .04, Hue)}
		};
	};
	PaletteMap = {
		{"Dark-1", FColorOkLch(.30, 0, 0)},
		{"Dark-2", FColorOkLch(.24, 0, 0)},
		{"Light-1", FColorOkLch(.95, 0, 0)},
		{"Light-2", FColorOkLch(.84, 0, 0)},
		{"Light-3", FColorOkLch(.72, 0, 0)},
		{"Light-4", FColorOkLch(.48, 0, 0)}
	};
	PaletteMap.Append(GetHuePalette("Red", 25));
	PaletteMap.Append(GetHuePalette("Orange", 70));
	PaletteMap.Append(GetHuePalette("YGreen", 115 + 5));
	PaletteMap.Append(GetHuePalette("Green", 160 + 5));
	PaletteMap.Append(GetHuePalette("LBlue", 205));
	PaletteMap.Append(GetHuePalette("Blue", 250 + 5));
	PaletteMap.Append(GetHuePalette("Violet", 295));
	PaletteMap.Append(GetHuePalette("Pink", 340));


	FontSizeMap = {
		{"Large", 16},
		{"Medium+", 12},
		{"Medium", 10},
		{"Small", 8}
	};
	IconSizeMap = {
		{"Large+", 32},
		{"Large", 24},
		{"Medium", 16},
		{"Small", 12}
	};
	OutlineWidthMap = {
		{"Large", 2.f},
		{"Medium", 1.f},
		{"Zero", .0f}
	};
	MarginMap = {
		{"Huge", FMargin(32.f)},
		{"HugeX", FMargin(32.f, 0.f)},
		{"HugeXMediumY", FMargin(32.f, 4.f)},
		{"Large", FMargin(8.f)},
		{"LargeLeft", FMargin(8.f, 0.f, 0.f, 0.f)},
		{"LargeXMediumY", FMargin(8.f, 4.f, 8.f, 4.f)},
		{"LargeY", FMargin(0.f, 8.f)},
		{"Medium", FMargin(4.f)},
		{"MediumLeft", FMargin(4.f, 0.f, 0.f, 0.f)},
		{"MediumX", FMargin(4.f, 0.f, 4.f, 0.f)},
		{"MediumY", FMargin(0.f, 4.f)},
		{"Small", FMargin(2.f)},
		{"SmallLeft", FMargin(2.f, 0.f, 0.f, 0.f)},
		{"SmallY", FMargin(0.f, 2.f)},
		{"Zero", FMargin(0.f)}
	};
	CornerRadiusMap = {
		{
			"Default", FVector4{4., 4., 4., 4.}
		},
		{
			"HalfDefault", FVector4{2., 2., 2., 2.}
		},
		{
			"DefaultTop", FVector4{4., 4., 0., 0.}
		},
		{
			"DefaultBottom", FVector4{0., 0., 4., 4.}
		},
		{
			"Zero", FVector4{0., 0., 0., 0.}
		}

	};
	SpacingMap = {
		{"Huge", 32.f},
		{"Large+", 16.f},
		{"Large", 8.f},
		{"Medium+", 6.f},
		{"Medium", 4.f},
		{"Small", 2.f},
		{"Zero", .0f}
	};
	TextShadowMap = {
		{"Zero", {FVector2D(0.375), 0.0f}},
		{"Default", {FVector2D(0.375), 0.15f}},
		{"Small", {FVector2D(0.5), 0.15f}}
	};
	BrushMap = {};

	BrushMap.Append(TMap<FName, FDTBrushData>{
		{"Transparent", FDTBrushData("Default", "Zero", FDTColor("Light-4", .0f), FDTColor("Dark-2", .0f))},
		{"Box", FDTBrushData("Zero", "Zero", FDTColor("Light-4", .0f), FDTColor("Dark-1"))},
		{"BoxDefault", FDTBrushData("Default", "Zero", FDTColor("Light-4", .0f), FDTColor("Dark-1"))}
	});

	BrushMap.Append(TMap<FName, FDTBrushData>{
		{"NodeNormal", FDTBrushData("Default", "Medium", FDTColor("Light-4", .5f), FDTColor("Dark-2", .9f))},
		{"NodeFocused", FDTBrushData("Default", "Large", FDTColor("Light-4"), FDTColor("Dark-2", .9f))},
	});
	BrushMap.Append(TMap<FName, FDTBrushData>{
		{"NodeNormalTop", FDTBrushData("DefaultTop", "Medium", FDTColor("Light-4"), FDTColor("Dark-2", .9f))},
		{"NodeNormalBottom", FDTBrushData("DefaultBottom", "Medium", FDTColor("Light-4"), FDTColor("Dark-2", .9f))},
		{"NodeReport", FDTBrushData("DefaultBottom", "Zero", FDTColor("Light-4"), FDTColor("Dark-2", .9f))},
	});
	BrushMap.Append(TMap<FName, FDTBrushData>{
		{"InputNormal", FDTBrushData("Default", "Zero", FDTColor("Light-4"), FDTColor("Dark-1", .75f))},
		{"InputHovered", FDTBrushData("Default", "Medium", FDTColor("Light-4", .5f), FDTColor("Dark-1", .75f))},
		{"InputFocused", FDTBrushData("Default", "Medium", FDTColor("Light-4"), FDTColor("Dark-1", .75f))},
		{"InputReadOnly", FDTBrushData("Default", "Zero", FDTColor("Light-4"), FDTColor("Dark-1", .75f))}
	});

	BrushMap.Append(TMap<FName, FDTBrushData>{
		{"ButtonNormal", FDTBrushData("Default", "Zero", FDTColor("Light-4"), FDTColor("Dark-1", .75f))},
		{"ButtonHovered", FDTBrushData("Default", "Zero", FDTColor("Light-4"), FDTColor("Light-4", .5f))},
		{"ButtonPressed", FDTBrushData("Default", "Zero", FDTColor("Light-4"), FDTColor("Light-4", .75f))},
		{"ButtonDisabled", FDTBrushData("Default", "Zero", FDTColor("Light-4"), FDTColor("Dark-1", .75f))}
	});
	BrushMap.Append(TMap<FName, FDTBrushData>{
		{"MenuRow", FDTBrushData("Zero", "Zero", FDTColor("Light-4"), FDTColor("Dark-2"))},
		{"MenuRowHighlighted", FDTBrushData("Zero", "Zero", FDTColor("Light-4"), FDTColor("Dark-1"))},
		{"MenuRowHovered", FDTBrushData("Zero", "Zero", FDTColor("Light-4"), FDTColor("Dark-1"))},
		{"MenuRowActive", FDTBrushData("Zero", "Zero", FDTColor("Light-4"), FDTColor("Light-4", .5f))},
		{"MenuRowHighlightedActive", FDTBrushData("Zero", "Zero", FDTColor("Light-4"), FDTColor("Light-4"))},
		{"MenuRowHoveredActive", FDTBrushData("Zero", "Zero", FDTColor("Light-4"), FDTColor("Light-4"))},
	});
	BrushMap.Append(TMap<FName, FDTBrushData>{
		{"ScrollBarNormal", FDTBrushData("Zero", "Zero", FDTColor("Light-4"), FDTColor("Light-4", .5f))},
		{"ScrollBarHovered", FDTBrushData("Zero", "Zero", FDTColor("Light-4"), FDTColor("Light-4"))},
		{"ScrollBarDragged", FDTBrushData("Zero", "Zero", FDTColor("Light-4"), FDTColor("Light-3"))},
	});

	TextMap = {
		{"Large", FDTTextData("Large", "Medium", "Zero", "Light-2")},
		{"Medium+", FDTTextData("Medium+", "Medium", "Zero", "Light-2")},
		{"MediumBold", FDTTextData("Medium", "Bold", "Zero", "Light-1")},
		{"Medium", FDTTextData("Medium", "Medium", "Default", "Light-2")},
		{"MediumRegular", FDTTextData("Medium", "Regular", "Zero", "Light-2")},
		{"Small", FDTTextData("Small", "Medium", "Small", "Light-2")},
		{"SmallItalic", FDTTextData("Small", "Italic", "Small", "Light-2")}
	};

	EditableTextBoxMap = {
		{
			"Default",
			FDTEditableTextBoxData("InputNormal", "InputHovered", "InputFocused", "InputReadOnly", "Light-2", "Light-2",
			                       "Light-3", "MediumRegular", "Medium", "Input")
		},
		{
			"Transparent",
			FDTEditableTextBoxData("Transparent", "Transparent", "Transparent", "InputReadOnly", "Light-2", "Light-2",
			                       "Light-3", "MediumRegular", "Medium", "Input")
		},
		{
			"TransparentNoPadding",
			FDTEditableTextBoxData("Transparent", "Transparent", "Transparent", "InputReadOnly", "Light-2", "Light-2",
			                       "Light-3", "MediumRegular", "Zero", "Input")
		},
		{
			"Transparent-2",
			FDTEditableTextBoxData("Transparent", "Transparent", "Transparent", "InputReadOnly", "Light-3", "Light-3",
			                       "Light-4", "MediumRegular", "Medium", "Input")
		},
	};

	ButtonMap = {
		{
			"Default",
			FDTButtonData("ButtonNormal", "ButtonHovered", "ButtonPressed", "ButtonDisabled", "MediumRegular",
			              "Light-2",
			              "Light-2", "Light-2", "Light-4", "Medium", "Small")
		},
		{
			"DefaultMedium",
			FDTButtonData("ButtonNormal", "ButtonHovered", "ButtonPressed", "ButtonDisabled", "MediumRegular",
			              "Light-2",
			              "Light-2", "Light-2", "Light-4", "LargeXMediumY", "Medium")
		},
		{
			"Transparent",
			FDTButtonData("Transparent", "Transparent", "Transparent", "Transparent", "MediumRegular", "Light-4",
			              "Light-3", "Light-3", FDTColor("Light-4", .5f), "Medium", "Small")
		},
		{
			"TextNoPadding",
			FDTButtonData("Transparent", "Transparent", "Transparent", "Transparent", "Small", "Light-3",
			              "Light-2", "Light-2", FDTColor("Light-3", .5f), "Zero", "Small")
		}
	};

	CheckBoxMap = {
		{
			"Default",
			FDTCheckBoxData("ButtonNormal", "ButtonHovered", "ButtonPressed", "Light-3", "Light-2", "Light-2",
							"Light-3", "Light-2", "Light-2", "Light-3", "Light-2", "Light-2", "Medium", "Zero")
		},
		{
			"Transparent",
			FDTCheckBoxData("Transparent", "Transparent", "Transparent", "Light-4", "Light-3", "Light-3",
							"Light-4", "Light-3", "Light-3", "Light-4", "Light-3", "Light-3", "Medium", "Zero")
		},
		{
			"TransparentLight",
			FDTCheckBoxData(
				"Transparent",
				FDTBrushRef("BoxDefault").SetBackgroundColor(true, "Light-1").SetBackgroundOpacity(true, 0.15f),
				FDTBrushRef("BoxDefault").SetBackgroundColor(true, "Light-1").SetBackgroundOpacity(true, 0.25f),
				FDTColor("Light-1", 0.9f),
				"Light-1", 
				"Light-1",
				FDTColor("Light-1", 0.9f),
				"Light-1", 
				"Light-1", 
				FDTColor("Light-1", 0.9f),
				"Light-1", 
				"Light-1", 
				"Small", 
				"Small")
		}
	};

	ComboButtonMap
		=
		{
			{"Default", FDTComboButtonData("Default", "Transparent", "Zero", true, "Large", "Small", .75f)},
			{"DefaultNoArrow", FDTComboButtonData("Default", "Transparent", "Zero", false, "Large", "Small", .75f)},
			{"Transparent", FDTComboButtonData("Transparent", "Transparent", "Zero", false, "Large", "Small", .75f)},
		};

	ComboBoxRowMap
		=
		{
			{
				"Default",
				FDTComboBoxRowData("MediumRegular", "MenuRowActive", "MenuRowHighlightedActive", "MenuRowHoveredActive",
				                   "MenuRow",
				                   "MenuRowHighlighted", "MenuRowHovered", "MenuRow", "MenuRowHovered", "MenuRow",
				                   "MenurowHovered", "Light-2", "Light-2")
			}
		};

	ComboBoxMap
		=
		{
			{
				"Default", FDTComboBoxData("Default", "Default", "Medium")
			}
		};

	ScrollBarMap
		=
		{
			{
				"Input",
				FDTScrollBarData("ScrollBarNormal", "ScrollBarHovered", "ScrollBarDragged", 4, FMargin(0), FMargin(0))
			}
		};
}

TArray<FString> UDefaultThemeSettings::GetColorOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->PaletteMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetCornerOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->CornerRadiusMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetTextShadowOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->TextShadowMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetCheckBoxOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->CheckBoxMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetComboBoxOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->ComboBoxMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetComboBoxRowOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->ComboBoxRowMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetComboButtonOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->ComboButtonMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetTextOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->TextMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetEditableTextBoxOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->EditableTextBoxMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetButtonOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->ButtonMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetBrushOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->BrushMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetScrollBarOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->ScrollBarMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetOutlineWidthOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->OutlineWidthMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetMarginOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->MarginMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetFontSizeOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->FontSizeMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetIconSizeOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->IconSizeMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetSpacingOptions()
{
	TArray<FString> x;
	for (const auto& it : Get()->SpacingMap)
	{
		x.Add(it.Key.ToString());
	}
	return x;
}

TArray<FString> UDefaultThemeSettings::GetFontOptions()
{
	const auto& NormalFont = DEFAULT_FONT("Regular", FCoreStyle::RegularTextSize);
	TArray<FString> x;
	if (NormalFont.CompositeFont)
	{
		for (const auto& it : NormalFont.CompositeFont->DefaultTypeface.Fonts)
		{
			x.Add(it.Name.ToString());
		}
	}

	return x;
}


void UDefaultThemeSettings::ModifyCheckBox(FCheckBoxStyle* Style, const FDTCheckBoxData& Config,
                                           const FString& UncheckedIconPath, const FString& CheckedIconPath,
                                           const FString& UndeterminedIconPath) const
{
	auto IconSize = FVector2D(GetIconSize(Config.IconSize));
	auto Padding = GetMargin(Config.Padding);
	auto UncheckedIcon = GetVectorImageBrush(UncheckedIconPath, IconSize);
	auto CheckedIcon = GetVectorImageBrush(CheckedIconPath, IconSize);
	auto UndeterminedIcon = GetVectorImageBrush(UndeterminedIconPath, IconSize);
	ModifyBrush(&Style->BackgroundImage, Config.BackgroundImage.Get());
	ModifyBrush(&Style->BackgroundHoveredImage, Config.BackgroundHoveredImage.Get());
	ModifyBrush(&Style->BackgroundPressedImage, Config.BackgroundPressedImage.Get());

	Style->UncheckedHoveredImage =
		Style->UncheckedImage =
		Style->UncheckedPressedImage = static_cast<FSlateBrush>(UncheckedIcon);

	Style->CheckedHoveredImage =
		Style->CheckedImage =
		Style->CheckedPressedImage = static_cast<FSlateBrush>(CheckedIcon);

	Style->UndeterminedHoveredImage =
		Style->UndeterminedImage =
		Style->UndeterminedPressedImage = static_cast<FSlateBrush>(UndeterminedIcon);

	Style->UncheckedImage.TintColor = Config.UncheckedImageColor.Get();
	Style->UncheckedHoveredImage.TintColor = Config.UncheckedHoveredImageColor.Get();
	Style->UncheckedPressedImage.TintColor = Config.UncheckedPressedImageColor.Get();

	Style->CheckedImage.TintColor = Config.CheckedImageColor.Get();
	Style->CheckedHoveredImage.TintColor = Config.CheckedHoveredImageColor.Get();
	Style->CheckedPressedImage.TintColor = Config.CheckedPressedImageColor.Get();

	Style->UndeterminedImage.TintColor = Config.UndeterminedImageColor.Get();
	Style->UndeterminedHoveredImage.TintColor = Config.UndeterminedHoveredImageColor.Get();
	Style->UndeterminedPressedImage.TintColor = Config.UndeterminedPressedImageColor.Get();


	Style->ForegroundColor = FLinearColor::White;
	Style->HoveredForeground = FLinearColor::White;
	Style->PressedForeground = FLinearColor::White;

	Style->CheckedForeground = FLinearColor::White;
	Style->CheckedHoveredForeground = FLinearColor::White;
	Style->CheckedPressedForeground = FLinearColor::White;

	Style->UndeterminedForeground = FLinearColor::White;

	Style->Padding = Padding;
}

void UDefaultThemeSettings::ModifyEditableTextBox(FEditableTextBoxStyle* Style,
                                                  const FDTEditableTextBoxData& Config) const
{
	ModifyBrush(&Style->BackgroundImageNormal, Config.BackgroundNormal.Get());
	ModifyBrush(&Style->BackgroundImageHovered, Config.BackgroundHovered.Get());
	ModifyBrush(&Style->BackgroundImageFocused, Config.BackgroundFocused.Get());
	ModifyBrush(&Style->BackgroundImageReadOnly, Config.BackgroundReadOnly.Get());
	ModifyFontInfo(&Style->TextStyle.Font, Config.Text.Get());
	Style->ForegroundColor = Config.ForegroundNormal.Get();
	Style->FocusedForegroundColor = Config.ForegroundFocused.Get();
	Style->ReadOnlyForegroundColor = Config.ForegroundReadOnly.Get();
	const auto& ScrollBarData = Config.ScrollBar.Get();

	ModifyBrush(&Style->ScrollBarStyle.NormalThumbImage, ScrollBarData.Normal.Get());
	ModifyBrush(&Style->ScrollBarStyle.HoveredThumbImage, ScrollBarData.Hovered.Get());
	ModifyBrush(&Style->ScrollBarStyle.DraggedThumbImage, ScrollBarData.Dragged.Get());
	Style->HScrollBarPadding = ScrollBarData.HPadding;
	Style->ScrollBarStyle.Thickness = ScrollBarData.Thickness;
	Style->VScrollBarPadding = ScrollBarData.VPadding;
	Style->Padding = GetMargin(Config.Padding);
}

void UDefaultThemeSettings::ModifyInlineEditableTextBox(FInlineEditableTextBlockStyle* Style,
	const FDTEditableTextBoxData& Config) const
{
	ModifyEditableTextBox(&Style->EditableTextBoxStyle, Config);
	ModifyTextBlockStyle(&Style->TextStyle, Config.Text.Get());
} 

void UDefaultThemeSettings::ModifyButtonStyle(FButtonStyle* Style, const FDTButtonData& Config) const
{
	ModifyBrush(&Style->Normal, Config.Normal.Get());
	ModifyBrush(&Style->Hovered, Config.Hovered.Get());
	ModifyBrush(&Style->Pressed, Config.Pressed.Get());
	ModifyBrush(&Style->Disabled, Config.Disabled.Get());
	Style->NormalForeground = Config.NormalForeground.Get();
	Style->HoveredForeground = Config.HoveredForeground.Get();
	Style->PressedForeground = Config.PressedForeground.Get();
	Style->DisabledForeground = Config.DisabledForeground.Get();
	//Style->NormalPadding = GetMargin(Config.Padding);
	//Style->PressedPadding = GetMargin(Config.Padding);
}

void UDefaultThemeSettings::ModifyComboButtonStyle(FComboButtonStyle* Style, const FDTComboButtonData& Config,
                                                   const FString& IconPath) const
{
	ModifyButtonStyle(&Style->ButtonStyle, Config.Button.Get());
	ModifyBrush(&Style->MenuBorderBrush, Config.MenuBorder.Get());
	Style->ContentPadding = GetMargin(Config.Button.Get().Padding);
	Style->MenuBorderPadding = GetMargin(Config.MenuBorderPadding);
	Style->DownArrowPadding = FMargin(0);
	Style->DownArrowImage = GetVectorImageBrush(IconPath, FVector2D(GetIconSize(Config.ArrowSize)));
	Style->DownArrowImage.TintColor = FLinearColor(1, 1, 1, Config.ArrowOpacity);
}

void UDefaultThemeSettings::ModifyComboBoxRow(FTableRowStyle* Style, const FDTComboBoxRowData& Config) const
{
	Style->TextColor = Config.NormalTextColor.Get();
	Style->SelectedTextColor = Config.SelectedTextColor.Get();
	ModifyBrush(&Style->EvenRowBackgroundBrush, Config.Even.Get());
	ModifyBrush(&Style->EvenRowBackgroundHoveredBrush, Config.EvenHovered.Get());
	ModifyBrush(&Style->OddRowBackgroundBrush, Config.Odd.Get());
	ModifyBrush(&Style->OddRowBackgroundHoveredBrush, Config.OddHovered.Get());
	ModifyBrush(&Style->InactiveBrush, Config.Inactive.Get());
	ModifyBrush(&Style->InactiveHighlightedBrush, Config.InactiveHighlighted.Get());
	ModifyBrush(&Style->InactiveHoveredBrush, Config.InactiveHovered.Get());
	ModifyBrush(&Style->ActiveBrush, Config.Active.Get());
	ModifyBrush(&Style->ActiveHighlightedBrush, Config.ActiveHighlighted.Get());
	ModifyBrush(&Style->ActiveHoveredBrush, Config.ActiveHovered.Get());
}

void UDefaultThemeSettings::ModifyComboBox(FComboBoxStyle* Style, const FDTComboBoxData& Config, const FString& IconPath) const
{
	FComboButtonStyle ComboButtonStyle;
	ModifyComboButtonStyle(&ComboButtonStyle, Config.ComboButton.Get(), IconPath);
	Style->ComboButtonStyle = ComboButtonStyle;
	Style->MenuRowPadding = GetMargin(Config.MenuRowPadding);
	Style->ContentPadding = 0;
}

void UDefaultThemeSettings::ModifyBrush(FSlateBrush* Brush, const FDTBrushData& Config,
                                        bool WhiteTint) const
{
	Brush->DrawAs = ESlateBrushDrawType::RoundedBox;
	Brush->OutlineSettings.Width = GetOutlineWidth(Config.OutlineWidth);
	if (Brush->OutlineSettings.Width != 0.0f)
	{
		Brush->OutlineSettings.Color = Config.OutlineColor.Get();
	}
	else
	{
		Brush->OutlineSettings.Color = Config.BackgroundColor.Get();
	}

	Brush->OutlineSettings.CornerRadii = GetCorner(Config.CornerRadius);
	Brush->OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	Brush->TintColor = WhiteTint ? FLinearColor::White : Config.BackgroundColor.Get();
}

void UDefaultThemeSettings::ModifyTextBlockStyle(FTextBlockStyle* Style, const FDTTextData& Config,
                                                 bool WhiteTint) const
{
	Style->Font = FStyleDefaults::GetFontInfo();;
	Style->SetTypefaceFontName(Config.Typeface);
	Style->SetFontSize(GetFontSize(Config.Size));
	auto TextShadow = Config.Shadow.Get();
	Style->SetShadowOffset(TextShadow.Offset);
	Style->SetShadowColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, TextShadow.BlackOpacity));
	Style->SetColorAndOpacity(WhiteTint ? FLinearColor::White : Config.Color.Get());
}

void UDefaultThemeSettings::ModifyFontInfo(FSlateFontInfo* Info, const FDTTextData& Config) const
{
	*Info = FStyleDefaults::GetFontInfo();
	Info->Size = GetFontSize(Config.Size);
	Info->TypefaceFontName = Config.Typeface;
}

void UDefaultThemeSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() ==
		GET_MEMBER_NAME_CHECKED(UDefaultThemeSettings, bRestoreDefaults))
	{
		if (bRestoreDefaults)
		{
			SetDefaults();
			bRestoreDefaults = false;
		}
	}
}

FLinearColor UDefaultThemeSettings::GetColor(const FName& Id)
{
	FLinearColor Result = FLinearColor::Red;
	if (auto Found = Get()->PaletteMap.Find(Id))
	{
		Result = (*Found).ToRGBCorrected();
	}
	return Result;
}

FVector4 UDefaultThemeSettings::GetCorner(const FName& Id)
{
	FVector4 Result = FVector4{0, 0, 0, 0};
	if (auto Found = Get()->CornerRadiusMap.Find(Id)) Result = *Found;
	return Result;
}

float UDefaultThemeSettings::GetOutlineWidth(const FName& Id)
{
	float Result = 0.f;
	if (auto Found = Get()->OutlineWidthMap.Find(Id)) Result = *Found;
	return Result;
}

FMargin UDefaultThemeSettings::GetMargin(const FName& Id)
{
	FMargin Result = FMargin{0, 0, 0, 0};
	if (auto Found = Get()->MarginMap.Find(Id)) Result = *Found;
	return Result;
}

uint16 UDefaultThemeSettings::GetFontSize(const FName& Id)
{
	uint16 Result = 0;
	if (auto Found = Get()->FontSizeMap.Find(Id)) Result = *Found;
	return Result;
}

uint16 UDefaultThemeSettings::GetIconSize(const FName& Id)
{
	uint16 Result = 0;
	if (auto Found = Get()->IconSizeMap.Find(Id)) Result = *Found;
	return Result;
}

float UDefaultThemeSettings::GetSpacing(const FName& Id)
{
	float Result = 0.f;
	if (auto Found = Get()->SpacingMap.Find(Id)) Result = *Found;
	return Result;
}

const FDTTextShadowData& UDefaultThemeSettings::GetTextShadow(const FName& Id)
{
	if (auto Found = Get()->TextShadowMap.Find(Id))
	{
		return *Found;
	}
	static FDTTextShadowData Default;
	return Default;
}

const FDTBrushData& UDefaultThemeSettings::GetBrush(const FName& Id)
{
	if (auto Found = Get()->BrushMap.Find(Id))
	{
		return *Found;
	}
	static FDTBrushData Default;
	return Default;
}

const FDTTextData& UDefaultThemeSettings::GetText(const FName& Id)
{
	if (auto Found = Get()->TextMap.Find(Id))
	{
		return *Found;
	}
	static FDTTextData Default;
	return Default;
}

const FDTCheckBoxData& UDefaultThemeSettings::GetCheckBox(const FName& Id)
{
	if (auto Found = Get()->CheckBoxMap.Find(Id))
	{
		return *Found;
	}
	static FDTCheckBoxData Default;
	return Default;
}

const FDTComboBoxData& UDefaultThemeSettings::GetComboBox(const FName& Id)
{
	if (auto Found = Get()->ComboBoxMap.Find(Id))
	{
		return *Found;
	}
	static FDTComboBoxData Default;
	return Default;
}

const FDTComboBoxRowData& UDefaultThemeSettings::GetComboBoxRow(const FName& Id)
{
	if (auto Found = Get()->ComboBoxRowMap.Find(Id))
	{
		return *Found;
	}
	static FDTComboBoxRowData Default;
	return Default;
}

const FDTComboButtonData& UDefaultThemeSettings::GetComboButton(const FName& Id)
{
	if (auto Found = Get()->ComboButtonMap.Find(Id))
	{
		return *Found;
	}
	static FDTComboButtonData Default;
	return Default;
}

const FDTEditableTextBoxData& UDefaultThemeSettings::GetEditableTextBox(const FName& Id)
{
	if (auto Found = Get()->EditableTextBoxMap.Find(Id))
	{
		return *Found;
	}
	static FDTEditableTextBoxData Default;
	return Default;
}

const FDTButtonData& UDefaultThemeSettings::GetButton(const FName& Id)
{
	if (auto Found = Get()->ButtonMap.Find(Id))
	{
		return *Found;
	}
	static FDTButtonData Default;
	return Default;
}

const FDTScrollBarData& UDefaultThemeSettings::GetScrollBar(const FName& Id)
{
	if (auto Found = Get()->ScrollBarMap.Find(Id))
	{
		return *Found;
	}
	static FDTScrollBarData Default;
	return Default;
}

FSlateVectorImageBrush UDefaultThemeSettings::GetVectorImageBrush(const FString& Path, const FVector2D& Size) const
{
	if (Path.IsEmpty())
	{
		FSlateVectorImageBrush Brush = FSlateVectorImageBrush("", Size);
		Brush.DrawAs = ESlateBrushDrawType::NoDrawType;
		return Brush;
	}
	return FSlateVectorImageBrush(Path, Size);
}


FLinearColor FDTColor::Get() const
{
	FLinearColor Result = UDefaultThemeSettings::GetColor(Id);
	if (bOverrideOpacity)
	{
		Result.A = Opacity;
	}
	return Result;
}

const FDTTextShadowData& FDTTextShadowRef::Get() const
{
	return UDefaultThemeSettings::GetTextShadow(Id);
}

FDTTextData FDTTextRef::Get() const
{
	auto Result = UDefaultThemeSettings::GetText(Id);
	if (bOverrideColor)
	{
		Result.Color.Id = Color;
	}
	return Result;
}

FDTBrushData FDTBrushRef::Get() const
{
	auto Result = UDefaultThemeSettings::GetBrush(Id);
	if (bOverrideBackgroundColor)
	{
		Result.BackgroundColor.Id = BackgroundColor;
	}
	if (bOverrideBackgroundOpacity)
	{
		Result.BackgroundColor.bOverrideOpacity = true;
		Result.BackgroundColor.Opacity = BackgroundOpacity;
	}
	if (bOverrideOutlineColor)
	{
		Result.OutlineColor.Id = OutlineColor;
	}
	if (bOverrideOutlineOpacity)
	{
		Result.OutlineColor.bOverrideOpacity = true;
		Result.OutlineColor.Opacity = OutlineOpacity;
	}
	return Result;
}

const FDTEditableTextBoxData& FDTEditableTextBoxRef::Get() const
{
	return UDefaultThemeSettings::GetEditableTextBox(Id);
}

const FDTButtonData& FDTButtonRef::Get() const
{
	return UDefaultThemeSettings::GetButton(Id);
}

const FDTComboButtonData& FDTComboButtonRef::Get() const
{
	return UDefaultThemeSettings::GetComboButton(Id);
}

const FDTCheckBoxData& FDTCheckBoxRef::Get() const
{
	return UDefaultThemeSettings::GetCheckBox(Id);
}

const FDTComboBoxRowData& FDTComboBoxRowRef::Get() const
{
	return UDefaultThemeSettings::GetComboBoxRow(Id);
}

const FDTComboBoxData& FDTComboBoxRef::Get() const
{
	return UDefaultThemeSettings::GetComboBox(Id);
}

const FDTScrollBarData& FDTScrollBarRef::Get() const
{
	return UDefaultThemeSettings::GetScrollBar(Id);
}
