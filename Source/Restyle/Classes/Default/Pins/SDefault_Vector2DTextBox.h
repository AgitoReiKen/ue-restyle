// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once
#include "Restyle/Public/Themes/Default/PinRestyleDefault.h"
#include "Widgets/SCompoundWidget.h"


#define LOCTEXT_NAMESPACE "Vector2DTextBox"
template<typename NumericType>
class SDefault_Vector2DTextBox : public SCompoundWidget
{
public:
	// Notification for numeric value committed
	DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);

	SLATE_BEGIN_ARGS(SDefault_Vector2DTextBox){}
		SLATE_ATTRIBUTE(FString, VisibleText_X)
		SLATE_ATTRIBUTE(FString, VisibleText_Y)
		SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_X)
		SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_Y)
	SLATE_END_ARGS()

		//Construct editable text boxes with the appropriate getter & setter functions along with tool tip text
	void Construct(const FArguments& InArgs)
	{
		const auto& Vector = UPinRestyleSettings::Get()->Inputs.Vector;
		const auto& Base = UPinRestyleSettings::Get()->Base;
		float BaseSpacing = UDefaultThemeSettings::GetSpacing(Base.Spacing);
		float LabelSpacing = UDefaultThemeSettings::GetSpacing(Vector.Spacing);
		const FLinearColor LabelClr = Vector.LabelsColor.Get();
		const FLinearColor XColor = Vector.ForegroundX.Get();
		const FLinearColor YColor = Vector.ForegroundY.Get();
		VisibleText_X = InArgs._VisibleText_X;
		VisibleText_Y = InArgs._VisibleText_Y;

		this->ChildSlot
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth().Padding(0, 0, 0, 0).HAlign(HAlign_Fill)
				[
					//Create Text box 0 
					SNew(SNumericEntryBox<NumericType>)
					.LabelVAlign(VAlign_Center)
					.Label()
					[
						SNew(STextBlock)
						.Font(FAppStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
						.Text(LOCTEXT("VectorNodeXAxisValueLabel", "X"))
						.ColorAndOpacity(LabelClr)
					]
					.LabelPadding(FMargin(0, 0, LabelSpacing, 0))
					.Value(this, &SDefault_Vector2DTextBox::GetTypeInValue_X)
					.OnValueCommitted(InArgs._OnNumericCommitted_Box_X)
					.Font(FAppStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
					.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
					.ToolTipText(LOCTEXT("VectorNodeXAxisValueLabel_ToolTip", "X value"))
					.EditableTextBoxStyle(
						&FAppStyle::GetWidgetStyle<FEditableTextBoxStyle>(
							FPinRestyleStyles::Graph_VectorEditableTextBox))
					.BorderForegroundColor(XColor)
					]
				+ SHorizontalBox::Slot()
				.AutoWidth().Padding(BaseSpacing, 0, 0, 0).HAlign(HAlign_Fill)
				[
				//Create Text box 1
				SNew(SNumericEntryBox<NumericType>)
				.LabelVAlign(VAlign_Center)
				.Label()
				[
					SNew(STextBlock)
					.Font(FAppStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
					.Text(LOCTEXT("VectorNodeYAxisValueLabel", "Y"))
					.ColorAndOpacity(LabelClr)
				]
				.LabelPadding(FMargin(0, 0, LabelSpacing, 0))
				.Value(this, &SDefault_Vector2DTextBox::GetTypeInValue_Y)
				.OnValueCommitted(InArgs._OnNumericCommitted_Box_Y)
				.Font(FAppStyle::GetFontStyle(FPinRestyleStyles::Graph_VectorEditableTextBox))
				.UndeterminedString(LOCTEXT("MultipleValues", "Multiple Values"))
				.ToolTipText(LOCTEXT("VectorNodeYAxisValueLabel_ToolTip", "Y value"))
				.EditableTextBoxStyle(
					&FAppStyle::GetWidgetStyle<FEditableTextBoxStyle>(
						FPinRestyleStyles::Graph_VectorEditableTextBox))
				.BorderForegroundColor(YColor)
				]
			];
	}

private: 
	NumericType GetValueType(const FString& InString) const
	{
		static_assert(std::is_floating_point_v<NumericType>);
		
		if constexpr (std::is_same_v<float, NumericType>)
		{
			return FCString::Atof(*InString);
		}
		else if constexpr (std::is_same_v<double, NumericType>)
		{
			return FCString::Atod(*InString);
		}

		return NumericType{};
	}

	// Get value for X text box
	TOptional<NumericType> GetTypeInValue_X() const
	{
		return GetValueType(VisibleText_X.Get());
	}

	// Get value for Y text box
	TOptional<NumericType> GetTypeInValue_Y() const
	{
		return GetValueType(VisibleText_Y.Get());
	}

	TAttribute<FString> VisibleText_X;
	TAttribute<FString> VisibleText_Y;
};

#undef LOCTEXT_NAMESPACE