// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"

class FRestyleUtils
{
public:
	static FString ToString(const FSlateBrush* SlateBrush, int32 NumOfTabs = 0);
	static FString ToString(const FCheckBoxStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FButtonStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FComboBoxStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FComboButtonStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FEditableTextBoxStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FEditableTextStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FProgressBarStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FScrollBarStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FScrollBoxStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FSpinBoxStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FTextBlockStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FSlateWidgetStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FSlateFontInfo* FontInfo, int32 NumOfTabs = 0);
	static FString ToString(const FFontOutlineSettings* Settings, int32 NumOfTabs = 0);
	static FString ToString(const FHyperlinkStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FSplitterStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FTableViewStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FTableRowStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FScrollBorderStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FInlineEditableTextBlockStyle* Style, int32 NumOfTabs = 0);
	static FString ToString(const FCompositeFont* Font, int32 NumOfTabs = 0);
	static FString ToString(const FTypeface& Typeface, int32 NumOfTabs = 0);
	static FString ToString(const FTypefaceEntry& Entry, int32 NumOfTabs = 0);
	static FString ToString(ESlateBrushDrawType::Type Type);
	static FString ToString(ESlateBrushImageType::Type Type);
	static FString ToString(ESlateBrushMirrorType::Type Type);
	static FString ToString(ESlateBrushTileType::Type Type);
	static FString ToString(ESlateCheckBoxType::Type Type);
	static FString ToString(const FMargin& Margin);
	static FString ToString(const FSlateColor& Color);
	static FString ToString(TEnumAsByte<EVerticalAlignment> Type);
	static FString ToString(ETextOverflowPolicy Type);
	static FString ToString(ETextTransformPolicy Type);
};

inline FString FRestyleUtils::ToString(const FSlateWidgetStyle* Style, int32 NumOfTabs)
{
	const FName Type = Style->GetTypeName();
	/*static FString ToString(const FCheckBoxStyle* Style);
	static FString ToString(const FButtonStyle* Style);
	static FString ToString(const FComboBoxStyle* Style);
	static FString ToString(const FComboButtonStyle* Style);
	static FString ToString(const FEditableTextBoxStyle* Style);
	static FString ToString(const FEditableTextStyle* Style);
	static FString ToString(const FProgressBarStyle* Style);
	static FString ToString(const FScrollBarStyle* Style);
	static FString ToString(const FScrollBoxStyle* Style);
	static FString ToString(const FSpinBoxStyle* Style);
	static FString ToString(const FTextBlockStyle* Style);
	static FString ToString(const FSlateWidgetStyle* Style);*/
	FString result = FString::Printf(TEXT("Unknown FSlateWidgetStyle: %s"), *Style->GetTypeName().ToString());
	if (Type.IsEqual("FCheckBoxStyle"))
	{
		const FCheckBoxStyle* _ = static_cast<const FCheckBoxStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FButtonStyle"))
	{
		const FButtonStyle* _ = static_cast<const FButtonStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FComboBoxStyle"))
	{
		const FComboBoxStyle* _ = static_cast<const FComboBoxStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FComboButtonStyle"))
	{
		const FComboButtonStyle* _ = static_cast<const FComboButtonStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FEditableTextBoxStyle"))
	{
		const FEditableTextBoxStyle* _ = static_cast<const FEditableTextBoxStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FEditableTextStyle"))
	{
		const FEditableTextStyle* _ = static_cast<const FEditableTextStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FProgressBarStyle"))
	{
		const FProgressBarStyle* _ = static_cast<const FProgressBarStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FScrollBarStyle"))
	{
		const FScrollBarStyle* _ = static_cast<const FScrollBarStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FScrollBoxStyle"))
	{
		const FScrollBoxStyle* _ = static_cast<const FScrollBoxStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FSpinBoxStyle"))
	{
		const FSpinBoxStyle* _ = static_cast<const FSpinBoxStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FTextBlockStyle"))
	{
		const FTextBlockStyle* _ = static_cast<const FTextBlockStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FHyperlinkStyle"))
	{
		const FHyperlinkStyle* _ = static_cast<const FHyperlinkStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FSplitterStyle"))
	{
		const FSplitterStyle* _ = static_cast<const FSplitterStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FTableViewStyle"))
	{
		const FTableViewStyle* _ = static_cast<const FTableViewStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FTableRowStyle"))
	{
		const FTableRowStyle* _ = static_cast<const FTableRowStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FScrollBorderStyle"))
	{
		const FScrollBorderStyle* _ = static_cast<const FScrollBorderStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	else if (Type.IsEqual("FInlineEditableTextBlockStyle"))
	{
		const FInlineEditableTextBlockStyle* _ = static_cast<const FInlineEditableTextBlockStyle*>(Style);
		result = ToString(_, NumOfTabs);
	}
	return result;
}

inline FString FRestyleUtils::ToString(const FSlateBrush* SlateBrush, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *SlateBrush;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("DrawType: %s\n"), *ToString(_.GetDrawType()));
	result += Prefix + FString::Printf(TEXT("ImageSize: %s\n"), *_.GetImageSize().ToString());
	result += Prefix + FString::Printf(TEXT("ImageType: %s\n"), *ToString(_.GetImageType()));
	result += Prefix + FString::Printf(TEXT("Margin: %s\n"), *ToString(_.GetMargin()));
	result += Prefix + FString::Printf(TEXT("Mirroring: %s\n"), *ToString(_.GetMirroring()));
	result += Prefix + FString::Printf(TEXT("ResourceName: %s\n"), *_.GetResourceName().ToString());
	result += Prefix + FString::Printf(TEXT("TintColor: %s\n"), *ToString(_.TintColor));
	result += Prefix + FString::Printf(TEXT("Tiling: %s"), *ToString(_.GetTiling()));
	return result;
	// @formatter:on
}

inline FString FRestyleUtils::ToString(const FCheckBoxStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("BackgroundHoveredImage: \n%s\n"), *ToString(&_.BackgroundHoveredImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("BackgroundImage: \n%s\n"), *ToString(&_.BackgroundImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("BackgroundPressedImage: \n%s\n"), *ToString(&_.BackgroundPressedImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("BorderBackgroundColor: %s\n"), *ToString( _.BorderBackgroundColor));
	result += Prefix + FString::Printf(TEXT("BackCheckBoxTypegroundHoveredImage: %s\n"), *ToString(_.CheckBoxType));
	result += Prefix + FString::Printf(TEXT("CheckedForeground: %s\n"), *ToString(_.CheckedForeground));
	result += Prefix + FString::Printf(TEXT("CheckedHoveredForeground: %s\n"), *ToString(_.CheckedHoveredForeground));
	result += Prefix + FString::Printf(TEXT("CheckedHoveredImage: \n%s\n"), *ToString(&_.CheckedHoveredImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("CheckedImage: \n%s\n"), *ToString(&_.CheckedImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("CheckedPressedForeground: %s\n"), *ToString(_.CheckedPressedForeground));
	result += Prefix + FString::Printf(TEXT("CheckedPressedImage: \n%s\n"), *ToString(&_.CheckedPressedImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ForegroundColor: %s\n"), *ToString(_.ForegroundColor));
	result += Prefix + FString::Printf(TEXT("Padding: %s\n"), *ToString(_.Padding));
	result += Prefix + FString::Printf(TEXT("PressedForeground: %s\n"), *ToString(_.PressedForeground));
	result += Prefix + FString::Printf(TEXT("UncheckedHoveredImage: \n%s\n"), *ToString(&_.UncheckedHoveredImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("UncheckedImage: \n%s\n"), *ToString(&_.UncheckedImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("UncheckedPressedImage: \n%s\n"), *ToString(&_.UncheckedPressedImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("UndeterminedForeground: %s\n"), *ToString(_.UndeterminedForeground));
	result += Prefix + FString::Printf(TEXT("UndeterminedHoveredImage: \n%s\n"), *ToString(&_.UndeterminedHoveredImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("UndeterminedImage: \n%s\n"), *ToString(&_.UndeterminedImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("UndeterminedPressedImage: \n%s"), *ToString(&_.UndeterminedPressedImage, NumOfTabs + 1));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FButtonStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("Disabled: \n%s\n"), *ToString(&_.Disabled, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("DisabledForeground: %s\n"), *ToString(_.DisabledForeground));
	result += Prefix + FString::Printf(TEXT("Hovered: \n%s\n"), *ToString(&_.Hovered, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("HoveredForeground: %s\n"), *ToString(_.HoveredForeground));
	result += Prefix + FString::Printf(TEXT("Normal: \n%s\n"), *ToString(&_.Normal, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("NormalForeground: %s\n"), *ToString(_.NormalForeground));
	result += Prefix + FString::Printf(TEXT("NormalPadding: %s\n"), *ToString(_.NormalPadding));
	result += Prefix + FString::Printf(TEXT("Pressed: \n%s\n"), *ToString(&_.Pressed, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("PressedForeground: %s\n"), *ToString(_.PressedForeground));
	result += Prefix + FString::Printf(TEXT("PressedPadding: %s"), *ToString(_.PressedPadding));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FComboBoxStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("ComboButtonStyle: \n%s\n"), *ToString(&_.ComboButtonStyle, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ContentPadding: %s\n"), *ToString(_.ContentPadding));
	result += Prefix + FString::Printf(TEXT("MenuRowPadding: %s"), *ToString(_.MenuRowPadding));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FComboButtonStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("ButtonStyle: \n%s\n"), *ToString(&_.ButtonStyle, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ContentPadding: %s\n"), *ToString(_.ContentPadding));
	result += Prefix + FString::Printf(TEXT("DownArrowAlign: %s\n"), *ToString(_.DownArrowAlign));
	result += Prefix + FString::Printf(TEXT("DownArrowImage: \n%s\n"), *ToString(&_.DownArrowImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("DownArrowPadding: %s\n"), *ToString(_.DownArrowPadding));
	result += Prefix + FString::Printf(TEXT("MenuBorderBrush: \n%s\n"), *ToString(&_.MenuBorderBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("MenuBorderPadding: %s\n"), *ToString(_.MenuBorderPadding));
	result += Prefix + FString::Printf(TEXT("ShadowColorAndOpacity: %s\n"), *ToString(_.ShadowColorAndOpacity));
	result += Prefix + FString::Printf(TEXT("ShadowOffset: %s"), *ToString(_.ShadowOffset));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FEditableTextBoxStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("BackgroundColor: %s\n"), *ToString(_.BackgroundColor));
	result += Prefix + FString::Printf(TEXT("BackgroundImageFocused: \n%s\n"), *ToString(&_.BackgroundImageFocused, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("BackgroundImageHovered: \n%s\n"), *ToString(&_.BackgroundImageHovered, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("BackgroundImageNormal: \n%s\n"), *ToString(&_.BackgroundImageNormal, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("BackgroundImageReadOnly: \n%s\n"), *ToString(&_.BackgroundImageReadOnly, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("FocusedForegroundColor: %s\n"), *ToString(_.FocusedForegroundColor));
	result += Prefix + FString::Printf(TEXT("Font: \n%s\n"), *ToString(&_.Font, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ForegroundColor: %s\n"), *ToString(_.ForegroundColor));
	result += Prefix + FString::Printf(TEXT("HScrollBarPadding: %s\n"), *ToString(_.HScrollBarPadding));
	result += Prefix + FString::Printf(TEXT("Padding: %s\n"), *ToString(_.Padding));
	result += Prefix + FString::Printf(TEXT("ReadOnlyForegroundColor: %s\n"), *ToString(_.ReadOnlyForegroundColor));
	result += Prefix + FString::Printf(TEXT("ScrollBarStyle: \n%s\n"), *ToString(&_.ScrollBarStyle, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("VScrollBarPadding: %s"), *ToString(_.VScrollBarPadding));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FEditableTextStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("BackgroundImageComposing: \n%s\n"), *ToString(&_.BackgroundImageComposing, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("BackgroundImageSelected: \n%s\n"), *ToString(&_.BackgroundImageSelected, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("CaretImage: \n%s\n"), *ToString(&_.CaretImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ColorAndOpacity: %s\n"), *ToString(_.ColorAndOpacity));
	result += Prefix + FString::Printf(TEXT("TypefaceFontName: \n%s"), *ToString(&_.Font, NumOfTabs + 1));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FProgressBarStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("BackgroundImage: \n%s\n"), *ToString(&_.BackgroundImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("EnableFillAnimation: %d\n"), (uint8)_.EnableFillAnimation);
	result += Prefix + FString::Printf(TEXT("FillImage: \n%s\n"), *ToString(&_.FillImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("MarqueeImage: \n%s"), *ToString(&_.MarqueeImage, NumOfTabs + 1));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FScrollBarStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("DraggedThumbImage: \n%s\n"), *ToString(&_.DraggedThumbImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("HorizontalBackgroundImage: \n%s\n"), *ToString(&_.HorizontalBackgroundImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("HorizontalBottomSlotImage: \n%s\n"), *ToString(&_.HorizontalBottomSlotImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("HorizontalTopSlotImage: \n%s\n"), *ToString(&_.HorizontalTopSlotImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("HoveredThumbImage: \n%s\n"), *ToString(&_.HoveredThumbImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("NormalThumbImage: \n%s\n"), *ToString(&_.NormalThumbImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("Thickness: %f\n"), _.Thickness);
	result += Prefix + FString::Printf(TEXT("VerticalBackgroundImage: \n%s\n"), *ToString(&_.VerticalBackgroundImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("VerticalBottomSlotImage: \n%s\n"), *ToString(&_.VerticalBottomSlotImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("VerticalTopSlotImage: \n%s"), *ToString(&_.VerticalTopSlotImage, NumOfTabs + 1));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FScrollBoxStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("BarThickness: %f\n"), _.BarThickness);
	result += Prefix + FString::Printf(TEXT("BottomShadowBrush: \n%s\n"), *ToString(&_.BottomShadowBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("LeftShadowBrush: \n%s\n"), *ToString(&_.LeftShadowBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("RightShadowBrush: \n%s\n"), *ToString(&_.RightShadowBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("TopShadowBrush: \n%s"), *ToString(&_.TopShadowBrush, NumOfTabs + 1));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FSpinBoxStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("ActiveBackgroundBrush: \n%s\n"), *ToString(&_.ActiveBackgroundBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ActiveFillBrush: \n%s\n"), *ToString(&_.ActiveFillBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ArrowsImage: \n%s\n"), *ToString(&_.ArrowsImage, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("BackgroundBrush: \n%s\n"), *ToString(&_.BackgroundBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ForegroundColor: %s\n"), *ToString(_.ForegroundColor));
	result += Prefix + FString::Printf(TEXT("HoveredBackgroundBrush: \n%s\n"), *ToString(&_.HoveredBackgroundBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("HoveredFillBrush: \n%s\n"), *ToString(&_.HoveredFillBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("InactiveFillBrush: \n%s\n"), *ToString(&_.InactiveFillBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("InsetPadding: %s\n"), *ToString(_.InsetPadding));
	result += Prefix + FString::Printf(TEXT("TextPadding: %s"), *ToString(_.TextPadding));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FTextBlockStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("ColorAndOpacity: %s\n"), *ToString(_.ColorAndOpacity));
	result += Prefix + FString::Printf(TEXT("Font: \n%s\n"), *ToString(&_.Font, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("HighlightColor: %s\n"), *ToString(_.HighlightColor));
	result += Prefix + FString::Printf(TEXT("HighlightShape: \n%s\n"), *ToString(&_.HighlightShape, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("OverflowPolicy: %s\n"), *ToString(_.OverflowPolicy));
	result += Prefix + FString::Printf(TEXT("SelectedBackgroundColor: %s\n"), *ToString(_.SelectedBackgroundColor));
	result += Prefix + FString::Printf(TEXT("ShadowColorAndOpacity: %s\n"), *ToString(_.ShadowColorAndOpacity));
	result += Prefix + FString::Printf(TEXT("ShadowOffset: %s\n"), *ToString(_.ShadowOffset));
	result += Prefix + FString::Printf(TEXT("StrikeBrush: \n%s\n"), *ToString(&_.StrikeBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("TransformPolicy: %s\n"), *ToString(_.TransformPolicy));
	result += Prefix + FString::Printf(TEXT("UnderlineBrush: \n%s"), *ToString(&_.UnderlineBrush, NumOfTabs + 1));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FSlateFontInfo* FontInfo, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = *FontInfo;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("FontObject: %s\n"), _.FontObject ? *_.FontObject->GetPathName() : TEXT("Nullptr"));
	result += Prefix + FString::Printf(TEXT("CompositeFont: \n%s\n"), _.GetCompositeFont() ? *ToString(_.GetCompositeFont(), NumOfTabs + 1) : TEXT("Nullptr"));
	result += Prefix + FString::Printf(TEXT("FontMaterial: %s\n"), _.FontMaterial ? *_.FontMaterial->GetPathName() : TEXT("Nullptr"));
	result += Prefix + FString::Printf(TEXT("TypefaceFontName: %s\n"), *_.TypefaceFontName.ToString());
	result += Prefix + FString::Printf(TEXT("Size: %d\n"), _.Size);
	result += Prefix + FString::Printf(TEXT("OutlineSettings: \n%s\n"), *ToString(&_.OutlineSettings, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("LetterSpacing: %d"), _.LetterSpacing);
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FFontOutlineSettings* Settings, int32 NumOfTabs)
{
	FString result = "";
	if (!Settings) return "None";
	const auto& _ = *Settings;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("bApplyOutlineToDropShadows: %d\n"), (int)_.bApplyOutlineToDropShadows);
	result += Prefix + FString::Printf(TEXT("bSeparateFillAlpha: %d\n"), (int)_.bSeparateFillAlpha);
	result += Prefix + FString::Printf(TEXT("OutlineColor: %s\n"), *ToString(_.OutlineColor));
	result += Prefix + FString::Printf(TEXT("OutlineSize: %d"), _.OutlineSize);
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FHyperlinkStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	if (!Style) return "None";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("Padding: %s\n"), *ToString(_.Padding));
	result += Prefix + FString::Printf(TEXT("TextStyle: \n%s\n"), *ToString(&_.TextStyle, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("UnderlineStyle: \n%s"), *ToString(&_.UnderlineStyle, NumOfTabs + 1));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FSplitterStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	if (!Style) return "None";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("HandleHighlightBrush: \n%s\n"), *ToString(&_.HandleHighlightBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("HandleNormalBrush: \n%s"), *ToString(&_.HandleNormalBrush, NumOfTabs + 1));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FTableViewStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	if (!Style) return "None";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("BackgroundBrush: \n%s"), *ToString(&_.BackgroundBrush, NumOfTabs + 1));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FTableRowStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	if (!Style) return "None";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("ActiveBrush: \n%s\n"), *ToString(&_.ActiveBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ActiveHighlightedBrush: \n%s\n"), *ToString(&_.ActiveHighlightedBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ActiveHoveredBrush: \n%s\n"), *ToString(&_.ActiveHoveredBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("bUseParentRowBrush: %d\n"), (int)_.bUseParentRowBrush);
	result += Prefix + FString::Printf(TEXT("DropIndicator_Above: \n%s\n"), *ToString(&_.DropIndicator_Above, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("DropIndicator_Below: \n%s\n"), *ToString(&_.DropIndicator_Below, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("DropIndicator_Onto: \n%s\n"), *ToString(&_.DropIndicator_Onto, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("EvenRowBackgroundBrush: \n%s\n"), *ToString(&_.EvenRowBackgroundBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("EvenRowBackgroundHoveredBrush: \n%s\n"), *ToString(&_.EvenRowBackgroundHoveredBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("InactiveBrush: \n%s\n"), *ToString(&_.InactiveBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("InactiveHighlightedBrush: \n%s\n"), *ToString(&_.InactiveHighlightedBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("InactiveHoveredBrush: \n%s\n"), *ToString(&_.InactiveHoveredBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("OddRowBackgroundBrush: \n%s\n"), *ToString(&_.OddRowBackgroundBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("OddRowBackgroundHoveredBrush: \n%s\n"), *ToString(&_.OddRowBackgroundHoveredBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ParentRowBackgroundBrush: \n%s\n"), *ToString(&_.ParentRowBackgroundBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("ParentRowBackgroundHoveredBrush: \n%s\n"), *ToString(&_.ParentRowBackgroundHoveredBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("SelectedTextColor: %s\n"), *ToString(_.SelectedTextColor));
	result += Prefix + FString::Printf(TEXT("SelectorFocusedBrush: %s\n"), *ToString(&_.SelectorFocusedBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("TextColor: %s"), *ToString(_.TextColor));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FScrollBorderStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	if (!Style) return "None";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("BottomShadowBrush: \n%s\n"), *ToString(&_.BottomShadowBrush, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("TopShadowBrush: \n%s"), *ToString(&_.TopShadowBrush, NumOfTabs + 1));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FInlineEditableTextBlockStyle* Style, int32 NumOfTabs)
{
	FString result = "";
	if (!Style) return "None";
	const auto& _ = *Style;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("TypeName: %s\n"), *_.TypeName.ToString());
	result += Prefix + FString::Printf(TEXT("EditableTextBoxStyle: \n%s\n"), *ToString(&_.EditableTextBoxStyle, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("TextStyle: \n%s"), *ToString(&_.TextStyle, NumOfTabs + 1));
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FCompositeFont* Font, int32 NumOfTabs)
{
	FString result = "";
	if (!Font) return "None";
	const auto& _ = *Font;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	result += Prefix + FString::Printf(TEXT("DefaultTypeface: \n%s\n"), *ToString(_.DefaultTypeface, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("FallbackTypeface: \n%s\n"), *ToString(_.FallbackTypeface.Typeface, NumOfTabs + 1));
	result += Prefix + FString::Printf(TEXT("SubTypefaces: %d"), _.SubTypefaces.Num());
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FTypeface& Typeface, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = Typeface;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	FString Fonts = "";
	{
		FString FontsPrefix = "";
		for (int i = 0; i < NumOfTabs + 1; i++) FontsPrefix += "\t";
		if (_.Fonts.Num() > 0) {
			for (int it = 0; it < _.Fonts.Num(); it++)
			{
				Fonts += FontsPrefix + FString::Printf(TEXT("Font: \n%s\n"), *ToString(_.Fonts[it], NumOfTabs + 2));
			}
			Fonts.RemoveFromEnd("\n");
		}
		else
		{
			Fonts = FontsPrefix + FString::Printf(TEXT("Empty"));
		}
	}
	result += Prefix + FString::Printf(TEXT("Fonts: \n%s\n"), *Fonts);
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(const FTypefaceEntry& Entry, int32 NumOfTabs)
{
	FString result = "";
	const auto& _ = Entry;
	FString Prefix = "";
	for (int i = 0; i < NumOfTabs; i++) Prefix += "\t";
	// @formatter:off
	if (_.Font.HasFont())
	{
		auto _FontFaceAsset = _.Font.GetFontFaceAsset();
		FString FontFaceAsset = "Nullptr";
		if (_FontFaceAsset) FontFaceAsset = _FontFaceAsset->GetPathName();
		auto FontFilename = _.Font.GetFontFilename();
		result += Prefix + FString::Printf(TEXT("HasFont: True\n"));
		result += Prefix + FString::Printf(TEXT("FontFaceAsset: %s\n"), *FontFaceAsset);
		result += Prefix + FString::Printf(TEXT("FontFilename: %s\n"), *FontFilename);
	}
	else
	{
		result += Prefix + FString::Printf(TEXT("HasFont: False\n"));
	}
	result += Prefix + FString::Printf(TEXT("Name: %s"), *_.Name.ToString());
	// @formatter:on
	return result;
}

inline FString FRestyleUtils::ToString(ESlateBrushDrawType::Type Type)
{
	switch (Type)
	{
	case ESlateBrushDrawType::NoDrawType: return "NoDrawType";
	case ESlateBrushDrawType::Box: return "Box";
	case ESlateBrushDrawType::Border: return "Border";
	case ESlateBrushDrawType::Image: return "Image";
	case ESlateBrushDrawType::RoundedBox: return "RoundedBox";
	default: break;
	}

	return "None";
}

inline FString FRestyleUtils::ToString(ESlateBrushImageType::Type Type)
{
	switch (Type)
	{
	case ESlateBrushImageType::NoImage: return "NoImage";
	case ESlateBrushImageType::FullColor: return "FullColor";
	case ESlateBrushImageType::Linear: return "Linear";
	case ESlateBrushImageType::Vector: return "Vector";
	default: break;
	}
	return "None";
}

inline FString FRestyleUtils::ToString(ESlateBrushMirrorType::Type Type)
{
	switch (Type)
	{
	case ESlateBrushMirrorType::NoMirror: return "NoMirror";
	case ESlateBrushMirrorType::Horizontal: return "Horizontal";
	case ESlateBrushMirrorType::Vertical: return "Vertical";
	case ESlateBrushMirrorType::Both: return "Both";
	default: break;
	}
	return "None";
}

inline FString FRestyleUtils::ToString(ESlateBrushTileType::Type Type)
{
	switch (Type)
	{
	case ESlateBrushTileType::NoTile: return "NoTile";
	case ESlateBrushTileType::Horizontal: return "Horizontal";
	case ESlateBrushTileType::Vertical: return "Vertical";
	case ESlateBrushTileType::Both: return "Both";
	default: break;
	}
	return "None";
}

inline FString FRestyleUtils::ToString(ESlateCheckBoxType::Type Type)
{
	switch (Type)
	{
	case ESlateCheckBoxType::CheckBox: return "CheckBox";
	case ESlateCheckBoxType::ToggleButton: return "ToggleButton";
	default: break;
	}
	return "None";
}

inline FString FRestyleUtils::ToString(const FMargin& Margin)
{
	return FString::Printf(L"%f, %f, %f, %f", Margin.Left, Margin.Top, Margin.Right, Margin.Bottom);
}

inline FString FRestyleUtils::ToString(const FSlateColor& Color)
{
	return Color.IsColorSpecified() ? Color.GetSpecifiedColor().ToString() : "Unknown";
}

inline FString FRestyleUtils::ToString(TEnumAsByte<EVerticalAlignment> Type)
{
	switch (Type.GetValue())
	{
	case VAlign_Fill: return "Fill";
	case VAlign_Top: return "Top";
	case VAlign_Center: return "Center";
	case VAlign_Bottom: return "Bottom";
	default: break;
	}
	return "None";
}

inline FString FRestyleUtils::ToString(ETextOverflowPolicy Type)
{
	switch (Type)
	{
	case ETextOverflowPolicy::Clip: return "Clip";
	case ETextOverflowPolicy::Ellipsis: return "Ellipsis";
	default: break;
	}
	return "None";
}

inline FString FRestyleUtils::ToString(ETextTransformPolicy Type)
{
	switch (Type)
	{
	case ETextTransformPolicy::None: return "None";
	case ETextTransformPolicy::ToLower: return "ToLower";
	case ETextTransformPolicy::ToUpper: return "ToUpper";
	default: break;
	}
	return "None";
}
