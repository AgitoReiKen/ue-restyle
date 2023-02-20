// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "Themes/Default/PinRestyleDefault.h"

#include "GraphEditorSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "RestyleProcessor.h"

#include "Interfaces/IPluginManager.h"

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleMacros.h"

FPinRestyleDefault::FPinRestyleDefault()
{
	Factory = MakeShared<FDefaultGraphPanelPinFactory>();
	bRegistered = false;
}

ERestyleSubject FPinRestyleDefault::GetSubject()
{
	return ERestyleSubject::Pin;
}

void FPinRestyleDefault::Register()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		auto SettingsSection = SettingsModule->RegisterSettings(
			"Editor", "Plugins", "RestyleDefaultPin",
			FText::FromString("Restyle [Default] [Pin]"),
			FText::FromString(
				"MAKING A CHANGE REQUIRES YOU TO CLOSE ALL OPENED GRAPH EDITORS!\nOTHERWISE, EDITOR MAY CRASH\nTIP: Use Right Mouse Button (Copy/Paste, Expand/Collapse)"),
			GetMutableDefault<UPinRestyleSettings>());
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this,
				&FPinRestyleDefault::OnSettingsChanged);
		}
	}
	Update();
	bRegistered = true;
}

void FPinRestyleDefault::Unregister()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Editor", "Plugins", "RestyleDefaultPin");
	}
	bRegistered = false;
}

TSharedPtr<FGraphPanelPinFactory> FPinRestyleDefault::GetFactory()
{
	return Factory;
}
 
void FPinRestyleDefault::Update()
{
	/** Original Pin Styles */
	static const FName NAME_Pin_Connected("Graph.Pin.Connected");
	static const FName NAME_Pin_Disconnected("Graph.Pin.Disconnected");

	/** Variant A Pin Styles */
	static const FName NAME_Pin_Connected_VarA("Graph.Pin.Connected_VarA");
	static const FName NAME_Pin_Disconnected_VarA("Graph.Pin.Disconnected_VarA");

	static const FName NAME_ArrayPin_Connected("Graph.ArrayPin.Connected");
	static const FName NAME_ArrayPin_Disconnected("Graph.ArrayPin.Disconnected");

	static const FName NAME_RefPin_Connected("Graph.RefPin.Connected");
	static const FName NAME_RefPin_Disconnected("Graph.RefPin.Disconnected");

	static const FName NAME_DelegatePin_Connected("Graph.DelegatePin.Connected");
	static const FName NAME_DelegatePin_Disconnected("Graph.DelegatePin.Disconnected");

	static const FName NAME_SetPin("Kismet.VariableList.SetTypeIcon");
	static const FName NAME_MapPinKey("Kismet.VariableList.MapKeyTypeIcon");
	static const FName NAME_MapPinValue("Kismet.VariableList.MapValueTypeIcon");

	static const FName NAME_Pin_Background("Graph.Pin.Background");
	static const FName NAME_Pin_BackgroundHovered("Graph.Pin.BackgroundHovered");

	static const FName NAME_PosePin_Connected("Graph.PosePin.Connected");
	static const FName NAME_PosePin_Disconnected("Graph.PosePin.Disconnected");

#define RootToContentDir StyleSet->RootToContentDir
#define ChevronDownSvg RootToContentDir("Common/ChevronDown", TEXT(".svg"))

	FSlateStyleSet* StyleSet = FRestyleProcessor::Get().GetStyle();
	auto Style = UPinRestyleSettings::Get();
	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin("Restyle")->GetBaseDir() / TEXT("Resources"));
	auto& BrushResources = FRestyleProcessor::Get().GetBrushResources();
	auto& WidgetStyles = FRestyleProcessor::Get().GetWidgetStyles();
	FVector2d I16 = FVector2d(16);

	/* Overrides */
	{
		if (Style->bOverrideGraphEditorSettings)
		{
			const auto& PC = Style->PinColors;
			auto* Settings = GetMutableDefault<UGraphEditorSettings>();
			Settings->DefaultPinTypeColor = PC.Default.Get();
			Settings->ExecutionPinTypeColor = PC.Execution.Get();
			Settings->IndexPinTypeColor = PC.Index.Get();
			Settings->WildcardPinTypeColor = PC.Wildcard.Get();
			Settings->BooleanPinTypeColor = PC.Boolean.Get();
			Settings->BytePinTypeColor = PC.Byte.Get();
			Settings->IntPinTypeColor = PC.Int.Get();
			Settings->Int64PinTypeColor = PC.Int64.Get();
			Settings->FloatPinTypeColor = PC.Float.Get();
			Settings->DoublePinTypeColor = PC.Double.Get();
			Settings->RealPinTypeColor = PC.Real.Get();
			Settings->TextPinTypeColor = PC.Text.Get();
			Settings->StringPinTypeColor = PC.String.Get();
			Settings->NamePinTypeColor = PC.Name.Get();
			Settings->StructPinTypeColor = PC.Struct.Get();
			Settings->ClassPinTypeColor = PC.Class.Get();
			Settings->SoftClassPinTypeColor = PC.SoftClass.Get();
			Settings->ObjectPinTypeColor = PC.Object.Get();
			Settings->SoftObjectPinTypeColor = PC.SoftObject.Get();
			Settings->DelegatePinTypeColor = PC.Delegate.Get();
			Settings->InterfacePinTypeColor = PC.Interface.Get();
			Settings->VectorPinTypeColor = PC.Vector.Get();
			Settings->RotatorPinTypeColor = PC.Rotator.Get();
			Settings->TransformPinTypeColor = PC.Transform.Get();
		}
		else
		{
			auto* Settings = GetMutableDefault<UGraphEditorSettings>();
			auto Default = NewObject<UGraphEditorSettings>();
			Default->LoadConfig();
			Settings->DefaultPinTypeColor = Default->DefaultPinTypeColor;
			Settings->ExecutionPinTypeColor = Default->ExecutionPinTypeColor;
			Settings->IndexPinTypeColor = Default->IndexPinTypeColor;
			Settings->WildcardPinTypeColor = Default->WildcardPinTypeColor;
			Settings->BooleanPinTypeColor = Default->BooleanPinTypeColor;
			Settings->BytePinTypeColor = Default->BytePinTypeColor;
			Settings->IntPinTypeColor = Default->IntPinTypeColor;
			Settings->Int64PinTypeColor = Default->Int64PinTypeColor;
			Settings->FloatPinTypeColor = Default->FloatPinTypeColor;
			Settings->DoublePinTypeColor = Default->DoublePinTypeColor;
			Settings->RealPinTypeColor = Default->RealPinTypeColor;
			Settings->TextPinTypeColor = Default->TextPinTypeColor;
			Settings->StringPinTypeColor = Default->StringPinTypeColor;
			Settings->NamePinTypeColor = Default->NamePinTypeColor;
			Settings->StructPinTypeColor = Default->StructPinTypeColor;
			Settings->ClassPinTypeColor = Default->ClassPinTypeColor;
			Settings->SoftClassPinTypeColor = Default->SoftClassPinTypeColor;
			Settings->ObjectPinTypeColor = Default->ObjectPinTypeColor;
			Settings->SoftObjectPinTypeColor = Default->SoftObjectPinTypeColor;
			Settings->DelegatePinTypeColor = Default->DelegatePinTypeColor;
			Settings->InterfacePinTypeColor = Default->InterfacePinTypeColor;
			Settings->VectorPinTypeColor = Default->VectorPinTypeColor;
			Settings->RotatorPinTypeColor = Default->RotatorPinTypeColor;
			Settings->TransformPinTypeColor = Default->TransformPinTypeColor;
		}
	}

	/* Icons */
	{
		StyleSet->Set("Icons.Restyle.Edit", new IMAGE_BRUSH_SVG("Common/Edit", I16));
		if (Style->bApplyIcons)
		{
			auto PinIconSize = FVector2D(UDefaultThemeSettings::GetIconSize(Style->Base.IconSize));
			//FVector2d(18,12)
			StyleSet->Set("Graph.WatchedPinIcon_Pinned",
				new IMAGE_BRUSH_SVG("Common/Starship_Visibility",
					FVector2d(PinIconSize.X * 1.5, PinIconSize.Y),
					Style->IconColors.Watch.Get()));
		}
		StyleSet->Set("Icons.Restyle.LocalizationDashboard.MenuIcon", new IMAGE_BRUSH_SVG("Common/LocalizationDashboard", I16));

	}

	/* Base */
	{
		StyleSet->Set("Graph.Pin.BackgroundHovered",
			new FSlateImageBrush(NAME_None, FVector2d(32, 8),
				FLinearColor(1, 1, 1, Style->Base.HoverOpacity)));

		FTextBlockStyle PinNameStyle = FTextBlockStyle();
		UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&PinNameStyle, Style->Base.Text.Get());
		StyleSet->Set("Graph.Node.PinName", PinNameStyle);
	}

	/* Pins */
	{
		auto PinIconSize = FVector2D(UDefaultThemeSettings::GetIconSize(Style->Base.IconSize));
		/** Original Pin Styles */
		StyleSet->Set("Graph.Pin.Connected", new IMAGE_BRUSH_SVG("/Pin/Pin_connected", PinIconSize));
		StyleSet->Set("Graph.Pin.Disconnected", new IMAGE_BRUSH_SVG("/Pin/Pin_disconnected", PinIconSize));
		StyleSet->Set("Graph.Pin.Connected_VarA", new IMAGE_BRUSH_SVG("/Pin/Pin_connected", PinIconSize));
		StyleSet->Set("Graph.Pin.Disconnected_VarA", new IMAGE_BRUSH_SVG("/Pin/Pin_disconnected", PinIconSize));
		/*	StyleSet->Set("Kismet.VariableList.PromotableTypeOuterIcon",
				new IMAGE_BRUSH_SVG("Pin/MapType_Key", PinIconSize));
			StyleSet->Set("Kismet.VariableList.PromotableTypeInnerIcon",
				new IMAGE_BRUSH_SVG("Pin/MapType_Key", PinIconSize));*/

		StyleSet->Set("Graph.ArrayPin.Connected", new IMAGE_BRUSH_SVG("/Pin/ArrayPin_connected", PinIconSize));
		StyleSet->Set("Graph.ArrayPin.Disconnected", new IMAGE_BRUSH_SVG("/Pin/ArrayPin_disconnected", PinIconSize));
		StyleSet->Set("Graph.RefPin.Connected", new IMAGE_BRUSH_SVG("/Pin/RefPin_connected", PinIconSize));
		StyleSet->Set("Graph.RefPin.Disconnected", new IMAGE_BRUSH_SVG("/Pin/RefPin_disconnected", PinIconSize));

		//StyleSet->Set("Graph.Pin.CopyNodePinLeft_Connected", new IMAGE_BRUSH("/Graph/CopyNodePinLeft_connected", FVector2D(12, 24)));
		//StyleSet->Set("Graph.Pin.CopyNodePinLeft_Disconnected", new IMAGE_BRUSH("/Graph/CopyNodePinLeft_disconnected", FVector2D(12, 24)));

		//StyleSet->Set("Graph.Pin.CopyNodePinRight_Connected", new IMAGE_BRUSH("/Graph/CopyNodePinRight_connected", FVector2D(12, 24)));
		//StyleSet->Set("Graph.Pin.CopyNodePinRight_Disconnected", new IMAGE_BRUSH("/Graph/CopyNodePinRight_disconnected", FVector2D(12, 24)));

		// Variant A Pin Styles */


		StyleSet->Set("Graph.DelegatePin.Connected", new IMAGE_BRUSH_SVG("/Pin/DelegatePin_Connected", PinIconSize));
		StyleSet->Set("Graph.DelegatePin.Disconnected",
			new IMAGE_BRUSH_SVG("/Pin/DelegatePin_Disconnected", PinIconSize));

		//StyleSet->Set("Graph.Replication.AuthorityOnly", new IMAGE_BRUSH("/Graph/AuthorityOnly", FVector2D(32, 32)));
		//StyleSet->Set("Graph.Replication.ClientEvent", new IMAGE_BRUSH("/Graph/ClientEvent", FVector2D(32, 32)));
		//StyleSet->Set("Graph.Replication.Replicated", new IMAGE_BRUSH("/Graph/Replicated", FVector2D(32, 32)));

		//StyleSet->Set("Graph.Editor.EditorOnlyIcon", new IMAGE_BRUSH("/Graph/EditorOnly", FVector2D(32, 32)));

		//StyleSet->Set("Graph.Event.InterfaceEventIcon", new IMAGE_BRUSH("/Graph/InterfaceEventIcon", FVector2D(32, 32)));

		//StyleSet->Set("Graph.Latent.LatentIcon", new IMAGE_BRUSH("/Graph/LatentIcon", FVector2D(32, 32)));
		//StyleSet->Set("Graph.Message.MessageIcon", new IMAGE_BRUSH("/Graph/MessageIcon", FVector2D(32, 32)));

		StyleSet->Set("Graph.ExecPin.Connected", new IMAGE_BRUSH_SVG("Pin/ExecPin_Connected", PinIconSize));
		StyleSet->Set("Graph.ExecPin.Disconnected", new IMAGE_BRUSH_SVG("Pin/ExecPin_Disconnected", PinIconSize));
		StyleSet->Set("Graph.ExecPin.ConnectedHovered", new IMAGE_BRUSH_SVG("Pin/ExecPin_Connected", PinIconSize));
		StyleSet->Set("Graph.ExecPin.DisconnectedHovered",
			new IMAGE_BRUSH_SVG("Pin/ExecPin_Disconnected", PinIconSize));

		// Events Exec Pins
		StyleSet->Set("Graph.ExecEventPin.Connected", new IMAGE_BRUSH_SVG("Pin/EventPin_Connected", PinIconSize));
		StyleSet->Set("Graph.ExecEventPin.Disconnected", new IMAGE_BRUSH_SVG("Pin/EventPin_Disconnected", PinIconSize));
		StyleSet->Set("Graph.ExecEventPin.ConnectedHovered",
			new IMAGE_BRUSH_SVG("Pin/EventPin_Connected", PinIconSize));
		StyleSet->Set("Graph.ExecEventPin.DisconnectedHovered",
			new IMAGE_BRUSH_SVG("Pin/EventPin_Disconnected", PinIconSize));


		// StyleSet->Set("Graph.Pin.Background", new FSlateNoResource());

		/*StyleSet->Set("Graph.Pin.ObjectSet", new IMAGE_BRUSH_SVG("Pin/Pin_ObjectSet", PinIconSize));
		StyleSet->Set("Graph.Pin.ObjectEmpty", new IMAGE_BRUSH_SVG("Pin/Pin_ObjectEmpty", PinIconSize));*/

		StyleSet->Set("Kismet.AllClasses.VariableIcon", new IMAGE_BRUSH_SVG("Pin/BaseType", I16));
		StyleSet->Set("Kismet.AllClasses.ArrayVariableIcon", new IMAGE_BRUSH_SVG("Pin/ArrayPin_Connected", I16));
		StyleSet->Set("Kismet.AllClasses.SetVariableIcon", new IMAGE_BRUSH_SVG("Pin/SetType_Disconnected", I16));
		StyleSet->Set("Kismet.AllClasses.MapValueVariableIcon", new IMAGE_BRUSH_SVG("Pin/MapType_Value", I16));
		StyleSet->Set("Kismet.AllClasses.MapKeyVariableIcon", new IMAGE_BRUSH_SVG("Pin/MapType_Key_Connected", I16));
		StyleSet->Set("Kismet.VariableList.TypeIcon", new IMAGE_BRUSH_SVG("Pin/BaseType", I16));

		StyleSet->Set(FPinRestyleStyles::Kismet_VariableList_ArrayTypeIcon_Disconnected,
			new IMAGE_BRUSH_SVG("Pin/ArrayPin_Disconnected", PinIconSize));

		StyleSet->Set(FPinRestyleStyles::Kismet_VariableList_ArrayTypeIcon_Connected,
			new IMAGE_BRUSH_SVG("Pin/ArrayPin_Connected", PinIconSize));

		StyleSet->Set("Kismet.VariableList.ArrayTypeIcon", new IMAGE_BRUSH_SVG("Pin/ArrayPin_Connected", PinIconSize));

		StyleSet->Set(FPinRestyleStyles::Kismet_VariableList_SetTypeIcon_Disconnected,
			new IMAGE_BRUSH_SVG("Pin/SetType_Disconnected", PinIconSize));

		StyleSet->Set(FPinRestyleStyles::Kismet_VariableList_SetTypeIcon_Connected,
			new IMAGE_BRUSH_SVG("Pin/SetType_Connected", PinIconSize));

		StyleSet->Set("Kismet.VariableList.SetTypeIcon", new IMAGE_BRUSH_SVG("Pin/SetType_Connected", PinIconSize));


		StyleSet->Set(FPinRestyleStyles::Kismet_VariableList_MapValueTypeIcon_Disconnected,
			new IMAGE_BRUSH_SVG("Pin/MapType_Value_Disconnected", PinIconSize));

		StyleSet->Set(FPinRestyleStyles::Kismet_VariableList_MapValueTypeIcon_Connected,
			new IMAGE_BRUSH_SVG("Pin/MapType_Value_Connected", PinIconSize));

		StyleSet->Set("Kismet.VariableList.MapValueTypeIcon",
			new IMAGE_BRUSH_SVG("Pin/MapType_Value_Connected", PinIconSize));

		StyleSet->Set("Kismet.VariableList.MapKeyTypeIcon",
			new IMAGE_BRUSH_SVG("Pin/MapType_Key", PinIconSize));

		StyleSet->Set("Graph.PosePin.ConnectedHovered", new IMAGE_BRUSH_SVG("Pin/Pose_Connected", PinIconSize));
		StyleSet->Set("Graph.PosePin.Connected", new IMAGE_BRUSH_SVG("Pin/Pose_Connected", PinIconSize));
		StyleSet->Set("Graph.PosePin.DisconnectedHovered", new IMAGE_BRUSH_SVG("Pin/Pose_Disconnected", PinIconSize));
		StyleSet->Set("Graph.PosePin.Disconnected", new IMAGE_BRUSH_SVG("Pin/Pose_Disconnected", PinIconSize));
	}

	{
		{
			const auto& String = Style->Inputs.String;
			FEditableTextBoxStyle TextBoxStyle = FEditableTextBoxStyle();
			UDefaultThemeSettings::Get()->ModifyEditableTextBox(&TextBoxStyle, String.Body.Get());
			StyleSet->Set(FPinRestyleStyles::Graph_EditableTextBox, TextBoxStyle);
		}

		// VectorEditableTextBox
		{
			const auto& Vector = Style->Inputs.Vector;
			FEditableTextBoxStyle TextBoxStyle = FEditableTextBoxStyle();
			UDefaultThemeSettings::Get()->ModifyEditableTextBox(&TextBoxStyle, Vector.Body.Get());
			StyleSet->Set(FPinRestyleStyles::Graph_VectorEditableTextBox, TextBoxStyle);
			StyleSet->Set(FPinRestyleStyles::Graph_VectorEditableTextBox, TextBoxStyle.TextStyle.Font);
		}
		//CheckBox
		{
			const auto& Boolean = Style->Inputs.Boolean;
			auto CheckBoxStyle = FCheckBoxStyle();
			auto Config = Boolean.Get();
			const FString IconCheckmark = RootToContentDir("Common/Checkmark", TEXT(".svg"));
			const FString IconMinus = RootToContentDir("Common/Minus", TEXT(".svg"));
			UDefaultThemeSettings::Get()->ModifyCheckBox(&CheckBoxStyle, Boolean.Get(), "", IconCheckmark, IconMinus);
			StyleSet->Set(FPinRestyleStyles::Graph_Checkbox, CheckBoxStyle);
		}
		// ComboBox
		{

			const auto& Select = Style->Inputs.Select.Get();
			auto ButtonTextData = Select.ComboButton.Get().Button.Get().Text.Get();

			FComboButtonStyle ComboButtonStyle;
			FComboBoxStyle BoxStyle;
			FTextBlockStyle TextBlockStyle;
			FSlateFontInfo FontInfo;

			UDefaultThemeSettings::Get()->ModifyComboButtonStyle(&ComboButtonStyle, Select.ComboButton.Get(),
				ChevronDownSvg);
			BoxStyle.ComboButtonStyle = ComboButtonStyle;
			BoxStyle.MenuRowPadding = UDefaultThemeSettings::GetMargin(Select.MenuRowPadding);

			UDefaultThemeSettings::Get()->ModifyFontInfo(&FontInfo, ButtonTextData);
			StyleSet->Set(FPinRestyleStyles::ComboBox_Button_FontInfo, FontInfo);

			StyleSet->Set(FPinRestyleStyles::ComboBox, BoxStyle);

			StyleSet->Set(FPinRestyleStyles::ComboButton, ComboButtonStyle);

			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&TextBlockStyle, ButtonTextData, true);
			StyleSet->Set(FPinRestyleStyles::ComboButton_Text, TextBlockStyle);
		}
		// ComboBox Row
		{
			const auto& Row = Style->Inputs.Select.Get().Row.Get();
			FTableRowStyle TableRowStyle = FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("ComboBox.Row");
			UDefaultThemeSettings::Get()->ModifyComboBoxRow(&TableRowStyle, Row);
			StyleSet->Set(FPinRestyleStyles::ComboBox_Row, TableRowStyle);
		}
		// AssetPicker
		{
			const auto& AssetPicker = Style->Inputs.AssetPicker;

			FComboButtonStyle ComboButtonStyle;
			UDefaultThemeSettings::Get()->ModifyComboButtonStyle(&ComboButtonStyle, AssetPicker.ComboButton.Get(),
				ChevronDownSvg);
			StyleSet->Set(FPinRestyleStyles::AssetPicker_ComboButton, ComboButtonStyle);

			FTextBlockStyle TextBlockStyle;
			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&TextBlockStyle,
				AssetPicker.ComboButton.Get().Button.Get().Text.Get());
			StyleSet->Set(FPinRestyleStyles::AssetPicker_ComboButton_Text, TextBlockStyle);

			FButtonStyle UseButton;
			FButtonStyle BrowseButton;
			{
				const auto& UtilButton = AssetPicker.UtilButton.Get();
				UDefaultThemeSettings::Get()->ModifyButtonStyle(&UseButton, UtilButton);
				UDefaultThemeSettings::Get()->ModifyButtonStyle(&BrowseButton, UtilButton);
			}
			StyleSet->Set(FPinRestyleStyles::AssetPicker_Button_Use, UseButton);
			StyleSet->Set(FPinRestyleStyles::AssetPicker_Button_Browse, BrowseButton);
		}
		// AdvancedText ComboButton
		{
			FComboButtonStyle ComboButtonStyle;
			UDefaultThemeSettings::Get()->ModifyComboButtonStyle(&ComboButtonStyle,
				Style->Inputs.Text.AdvancedTextButton.Get(),
				ChevronDownSvg);
			StyleSet->Set(FPinRestyleStyles::Graph_TextInput_AdvancedText_ComboButton, ComboButtonStyle);
		}
		{
			FComboButtonStyle ComboButtonStyle;
			UDefaultThemeSettings::Get()->ModifyComboButtonStyle(&ComboButtonStyle,
				Style->Inputs.Key.ComboButton.Get(), ChevronDownSvg);
			StyleSet->Set(FPinRestyleStyles::KeyInput_ComboButton, ComboButtonStyle);

			FButtonStyle ButtonStyle;
			UDefaultThemeSettings::Get()->ModifyButtonStyle(&ButtonStyle, Style->Inputs.Key.Button.Get());
			StyleSet->Set(FPinRestyleStyles::KeyInput_Button, ButtonStyle);
		}

		//Sequence_Button
		{
			FButtonStyle ButtonStyle;
			const auto& Seq = Style->Inputs.Sequence;
			UDefaultThemeSettings::Get()->ModifyButtonStyle(&ButtonStyle, Seq.ButtonStyle.Get());
			StyleSet->Set(FPinRestyleStyles::Sequence_Button, ButtonStyle);

			FTextBlockStyle TextBlockStyle;
			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&TextBlockStyle, Seq.ButtonStyle.Get().Text.Get());
			StyleSet->Set(FPinRestyleStyles::Sequence_Button_Text, TextBlockStyle);

			auto PinIconSize = FVector2D(UDefaultThemeSettings::GetIconSize(Style->Base.IconSize));
			FSlateVectorImageBrush* IconAddPin = new IMAGE_BRUSH_SVG("/Pin/AddPin", PinIconSize);
			StyleSet->Set(FPinRestyleStyles::Icon_AddPin, IconAddPin);
		}
	}
}

bool FPinRestyleDefault::IsRegistered()
{
	return bRegistered;
}

bool FPinRestyleDefault::OnSettingsChanged()
{
	Update();
	auto Mutable = GetMutableDefault<UPinRestyleSettings>();
	Mutable->SaveConfig(CPF_Config, *Mutable->GetGlobalUserConfigFilename());
	return true;
}

const UPinRestyleSettings* UPinRestyleSettings::Get()
{
	return GetDefault<UPinRestyleSettings>();
}

UPinRestyleSettings* UPinRestyleSettings::GetM()
{
	return GetMutableDefault<UPinRestyleSettings>();
}

void UPinRestyleSettings::SetDefaults()
{
	bApplyIcons = true;
	bOverrideGraphEditorSettings = true;
	Inputs = FDTPinInputs();
	IconColors = FDTMiscIconColorSet();
	Base = FDTPinBase();
	IconColors = FDTMiscIconColorSet();
	PinColors = FDTPinTypeColorSet();
	DisabledWidgets = FDTPinDisabledWidgets();
}

void UPinRestyleSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() ==
		GET_MEMBER_NAME_CHECKED(UPinRestyleSettings, bRestoreDefaults))
	{
		if (bRestoreDefaults)
		{
			SetDefaults();
			bRestoreDefaults = false;
		}
	}
	if (PropertyChangedEvent.GetPropertyName() ==
		GET_MEMBER_NAME_CHECKED(UPinRestyleSettings, bResetDisabledWidgetsToDefault))
	{
		if (bResetDisabledWidgetsToDefault) {
			DisabledWidgets = FDTPinDisabledWidgets();
			bResetDisabledWidgetsToDefault = false;
		}
	}
}
