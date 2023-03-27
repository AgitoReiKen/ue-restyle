// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "Themes/Default/NodeRestyleDefault.h"


#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "RestyleProcessor.h"

#include "Default/Nodes/Kismet/SDefault_GraphNodeK2Default.h"

#include "Interfaces/IPluginManager.h"

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleMacros.h"

#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Nodes/K2Node_CreateWidget.h"

#ifdef PLATFORM_WINDOWS
#include "Windows/WindowsWindow.h"
#include "Windows.h"
#include "ImageHlp.h"
#include "Restyle/ThirdParty/MinHook/MinHook.h"
#endif

void UNodeRestyleSettings::SetDefaults()
{
	Node = FDTNode();
	CompactNode = FDTNodeCompact();
	VarNode = FDTVarNode();
	NodeReports[(int)EDTNodeReportType::Error] = {
		FString("ERROR"),
		FDTTextRef("MediumBold", "Red-1"),
		FDTBrushRef("NodeReport").SetOutlineColor(true, "Red-2").SetBackgroundColor(true, "Red-3"),
		"Medium"
	};
	NodeReports[(int)EDTNodeReportType::Warning] = {
		FString("WARNING"),
		FDTTextRef("MediumBold", "Orange-1"),
		FDTBrushRef("NodeReport").SetOutlineColor(true, "Orange-2").SetBackgroundColor(true, "Orange-3"),
		"Medium"

	};
	NodeReports[(int)EDTNodeReportType::Info] = {

		FString("NOTE"),
		FDTTextRef("MediumBold", "LBlue-1"),
		FDTBrushRef("NodeReport").SetOutlineColor(true, "LBlue-2").SetBackgroundColor(true, "LBlue-3"),
		"Medium"

	};
	NodeReports[(int)EDTNodeReportType::Upgrade] = {

		FString("UPGRADE"),
		FDTTextRef("MediumBold", "Violet-1"),
		FDTBrushRef("NodeReport").SetOutlineColor(true, "Violet-2").SetBackgroundColor(true, "Violet-3"),
		"Medium"
	};
	AdvancedDisplay = FDTAdvancedDisplay();
	StateWidget = FDTEnabledStateWidget();
	CommentBubble = FDTCommentBubble();
	Zoom = FDTZoomSettings();
	bNewZoom = false;
	HorizontalSpacing = "Medium";
	//VerticalSpacing = "Medium+";
	VerticalSpacing = "Small";
	DisabledOpacity = .5f;
	CommentNode = FDTCommentNode();
	bUpdateIcons = true;
	DisabledWidgets = FDTNodeDisabledWidgets();
	bOverrideGraphEditorSettings = true;
}

void UNodeRestyleSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() ==
		GET_MEMBER_NAME_CHECKED(UNodeRestyleSettings, bRestoreDefaults))
	{
		if (bRestoreDefaults)
		{
			SetDefaults();
			bRestoreDefaults = false;
		}
	}
	if (PropertyChangedEvent.GetPropertyName() ==
		GET_MEMBER_NAME_CHECKED(FDTZoomSettings, Smoothness))
	{
		Zoom.UpdateZoomLevels();
	}
	if (PropertyChangedEvent.GetPropertyName() ==
		GET_MEMBER_NAME_CHECKED(FDTZoomSettings, ZoomLevels))
	{
		if (Zoom.ZoomLevels.Num() == 0)
		{
			Zoom.UpdateZoomLevels();
		}
		else
		{
			Zoom.UpdateDefaultZoomLevelId();
		}
	}
	if (PropertyChangedEvent.GetPropertyName() ==
		GET_MEMBER_NAME_CHECKED(FDTZoomSettings, UseLowLodIfBelow))
	{
		if (Zoom.ZoomLevels.Num() == 0)
		{
			Zoom.UpdateZoomLevels();
		}
		else
		{
			Zoom.UpdateLowerZoomLevelId();
		}
	}
	if (PropertyChangedEvent.GetPropertyName() ==
		GET_MEMBER_NAME_CHECKED(UNodeRestyleSettings, bResetDisabledWidgetsToDefault))
	{
		if (bResetDisabledWidgetsToDefault) {
			DisabledWidgets = FDTNodeDisabledWidgets();
			bResetDisabledWidgetsToDefault = false;
		}
	}
}

FNodeRestyleDefault::FNodeRestyleDefault()
{
	Factory = MakeShared<FDefaultGraphPanelNodeFactory>();
	bRegistered = false;
}

TSharedPtr<FGraphPanelNodeFactory> FNodeRestyleDefault::GetFactory()
{
	return Factory;
}

ERestyleSubject FNodeRestyleDefault::GetSubject()
{
	return ERestyleSubject::Node;
}

void FNodeRestyleDefault::Register()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		auto SettingsSection = SettingsModule->RegisterSettings(
			"Editor", "Plugins", "RestyleDefaultNode",
			FText::FromString("Restyle [Default] [Node]"),
			FText::FromString(
				"MAKING A CHANGE REQUIRES YOU TO CLOSE ALL OPENED GRAPH EDITORS!\nOTHERWISE, EDITOR MAY CRASH\nTIP: Use Right Mouse Button (Copy/Paste, Expand/Collapse)"),
			GetMutableDefault<UNodeRestyleSettings>());
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this,
			                                      &FNodeRestyleDefault::OnSettingsChanged);
		}
	}
	Update();
	Hook();
	bRegistered = true;
}

void FNodeRestyleDefault::Unregister()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Editor", "Plugins", "RestyleDefaultNode");
	}
	Unhook();
	bRegistered = false;
}

void FNodeRestyleDefault::Update()
{
#define RootToContentDir StyleSet->RootToContentDir
#define ChevronDownSvg RootToContentDir("Common/ChevronDown", TEXT(".svg"))
#define RoundChevronDownSvg RootToContentDir("Common/RoundChevronDown", TEXT(".svg"))
#define RoundChevronUpSvg RootToContentDir("Common/RoundChevronUp", TEXT(".svg"))
#define MinusSvg RootToContentDir("Common/Minus", TEXT(".svg"))
	FSlateStyleSet* StyleSet = FRestyleProcessor::Get().GetStyle();
	auto Style = UNodeRestyleSettings::Get();
	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin("Restyle")->GetBaseDir() / TEXT("Resources"));
	auto& BrushResources = FRestyleProcessor::Get().GetBrushResources();
	auto& WidgetStyles = FRestyleProcessor::Get().GetWidgetStyles();
	/* Icons */
	{
		FVector2D I16 = FVector2D(16);
		StyleSet->Set("Icons.Restyle.MathExpression", new IMAGE_BRUSH_SVG("/Node/MathExpression", I16));
		FVector2D I32 = FVector2D(32);

		if (Style->bUpdateIcons)
		{
			StyleSet->Set("Graph.Replication.AuthorityOnly", new IMAGE_BRUSH_SVG("/Node/AuthorityOnly", I32));
			StyleSet->Set("Graph.Replication.ClientEvent", new IMAGE_BRUSH_SVG("/Node/ClientEvent", I32));
			StyleSet->Set("Graph.Replication.Replicated", new IMAGE_BRUSH_SVG("/Node/Replicated", I32));
			StyleSet->Set("Graph.Editor.EditorOnlyIcon", new IMAGE_BRUSH_SVG("/Node/EditorOnly", I32));
			StyleSet->Set("Graph.Event.InterfaceEventIcon", new IMAGE_BRUSH_SVG("/Node/InterfaceEventIcon", I32));
		}
		else
		{
			auto& CachedBrushes = FRestyleProcessor::Get().GetCachedBrushResources();
			StyleSet->Set("Graph.Replication.AuthorityOnly", CachedBrushes["Graph.Replication.AuthorityOnly"]);
			StyleSet->Set("Graph.Replication.ClientEvent", CachedBrushes["Graph.Replication.ClientEvent"]);
			StyleSet->Set("Graph.Replication.Replicated", CachedBrushes["Graph.Replication.Replicated"]);
			StyleSet->Set("Graph.Editor.EditorOnlyIcon", CachedBrushes["Graph.Editor.EditorOnlyIcon"]);
			StyleSet->Set("Graph.Event.InterfaceEventIcon", CachedBrushes["Graph.Event.InterfaceEventIcon"]);
		}
	}

	/* Overrides */
	{
		if (Style->bOverrideGraphEditorSettings)
		{
			auto* Settings = GetMutableDefault<UGraphEditorSettings>();
			auto HS = UDefaultThemeSettings::GetSpacing(Style->HorizontalSpacing);
			auto VS = UDefaultThemeSettings::GetSpacing(Style->VerticalSpacing);
			Settings->PaddingAbovePin = VS;
			Settings->PaddingBelowPin = VS;
			Settings->PaddingLeftOfOutput = HS;
			Settings->PaddingRightOfInput = HS;
			Settings->PaddingTowardsNodeEdge = HS;
		}
		else
		{
			auto* Settings = GetMutableDefault<UGraphEditorSettings>();
			auto Default = NewObject<UGraphEditorSettings>();
			Settings->PaddingAbovePin = Default->PaddingAbovePin;
			Settings->PaddingBelowPin = Default->PaddingBelowPin;
			Settings->PaddingLeftOfOutput = Default->PaddingLeftOfOutput;
			Settings->PaddingRightOfInput = Default->PaddingRightOfInput;
			Settings->PaddingTowardsNodeEdge = Default->PaddingTowardsNodeEdge;
		}
	}

	/* GraphNode_Body */
	{
		for (int x = 0; x < (int)EDTGraphNodeTitleType::Num; x++)
		{
			for (int y = 0; y < (int)EDTGraphNodeState::Num; y++)
			{
				FName Id = FNodeRestyleStyles::GraphNode_Body((EDTGraphNodeTitleType)x, (EDTGraphNodeState)y);
				const auto& State = Style->Node.GetTypeData((EDTGraphNodeTitleType)x)
				                         .GetState((EDTGraphNodeState)y);

				if (auto Found = BrushResources.Find(Id))
				{
					UDefaultThemeSettings::Get()->ModifyBrush(*Found, State.Body.Get());
				}
				else
				{
					auto Brush = new FSlateRoundedBoxBrush(FLinearColor::Transparent);
					UDefaultThemeSettings::Get()->ModifyBrush(Brush, State.Body.Get());
					StyleSet->Set(Id, Brush);
				}
			}
		}
	}

	/* GraphNode_Title_ */
	{
		auto& Node = Style->Node;

		{
			auto x = StyleSet->GetWidgetStyle<FInlineEditableTextBlockStyle>(
				"Graph.Node.NodeTitleInlineEditableText");
			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&x.TextStyle, Node.Title.MainText.Get(), true);
			x.EditableTextBoxStyle.Font = x.TextStyle.Font;
			x.EditableTextBoxStyle.ForegroundColor = x.TextStyle.ColorAndOpacity;
			x.EditableTextBoxStyle.FocusedForegroundColor = x.TextStyle.ColorAndOpacity;
			// dunno why it adds some sort of padding when getting into editing mode
			x.EditableTextBoxStyle.Padding = FMargin(-1.f, -.5f, 0, 0);
			x.EditableTextBoxStyle.BackgroundImageNormal.DrawAs = ESlateBrushDrawType::NoDrawType;
			x.EditableTextBoxStyle.BackgroundImageFocused.DrawAs = ESlateBrushDrawType::NoDrawType;
			x.EditableTextBoxStyle.BackgroundImageHovered.DrawAs = ESlateBrushDrawType::NoDrawType;
			x.EditableTextBoxStyle.BackgroundImageReadOnly.DrawAs = ESlateBrushDrawType::NoDrawType;
			StyleSet->Set(FNodeRestyleStyles::GraphNode_Title_MainText, x);
		}

		{
			auto x = StyleSet->GetWidgetStyle<FTextBlockStyle>("Graph.Node.NodeTitleExtraLines");
			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&x, Node.Title.ExtraText.Get(), true);
			StyleSet->Set(FNodeRestyleStyles::GraphNode_Title_ExtraText, x);
		}

		{
			auto ModifyBrush = [&Node](FSlateBrush* Brush, int TitleType, int State) -> FSlateBrush*
			{
				auto& x = *Brush;
				{
					x.OutlineSettings.Color = Node.GetTypeData((EDTGraphNodeTitleType)TitleType).GetState(
						(EDTGraphNodeState)State).Title.Background.Get();
					x.OutlineSettings.Width = 0.f;
					x.OutlineSettings.CornerRadii = UDefaultThemeSettings::GetCorner(Node.Title.CornerRadius);
					x.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
					x.TintColor = FLinearColor::White;
				}
				return &x;
			};

			for (int x = 0; x < (int)EDTGraphNodeTitleType::Num; x++)
			{
				for (int y = 0; y < (int)EDTGraphNodeState::Num; y++)
				{
					FName Id = FNodeRestyleStyles::GraphNode_Title_Body((EDTGraphNodeTitleType)x, (EDTGraphNodeState)y);
					if (auto Found = BrushResources.Find(Id))
					{
						ModifyBrush(*Found, x, y);
					}
					else
					{
						StyleSet->Set(
							Id,
							ModifyBrush(new FSlateRoundedBoxBrush(FLinearColor::Transparent), x, y)
						);
					}
				}
			}
		}
	}

	/* GraphNode_Compact */
	{
		auto& CompactNode = Style->CompactNode;
		/* Title */
		{
			auto x = StyleSet->GetWidgetStyle<FTextBlockStyle>(
				"Graph.CompactNode.Title");

			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&x, CompactNode.Title.Text.Get(), true);
			StyleSet->Set(FNodeRestyleStyles::GraphNode_Compact_Title, x);

			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&x, CompactNode.Title.OneSymbolText.Get(), true);
			StyleSet->Set(FNodeRestyleStyles::GraphNode_Compact_Title_OneSymbol, x);

			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&x, CompactNode.AlternativeTitle.Text.Get(), true);
			StyleSet->Set(FNodeRestyleStyles::GraphNode_Compact_AlternativeTitle, x);
		}

		/* Body */
		{
			for (int x = 0; x < (int)EDTGraphNodeState::Num; x++)
			{
				EDTGraphNodeState State = (EDTGraphNodeState)x;
				FName Id = FNodeRestyleStyles::GraphNode_Compact_Body(State);
				auto Config = CompactNode.States.GetState(State).Body.Get();

				if (auto Found = BrushResources.Find(Id))
				{
					UDefaultThemeSettings::Get()->ModifyBrush(*Found, Config);
				}
				else
				{
					FSlateRoundedBoxBrush* Brush = new FSlateRoundedBoxBrush(FLinearColor::Transparent);
					UDefaultThemeSettings::Get()->ModifyBrush(Brush, Config);
					StyleSet->Set(Id, Brush);
				}
			}
		}
	}

	/* VarNode */
	{
		// Body
		{
			const auto& VarNode = Style->VarNode;
			EDTVarType Type = EDTVarType::Default;
			const auto& TypeData = VarNode.GetTypeData(Type);
			for (int i = 0; i < (int)EDTGraphNodeState::Num; i++)
			{
				EDTGraphNodeState StateType = EDTGraphNodeState(i);
				const auto& State = TypeData.GetState(StateType);

				FSlateBrush* Body = new FSlateBrush();
				UDefaultThemeSettings::Get()->ModifyBrush(Body, State.Body.Get());

				StyleSet->Set(FNodeRestyleStyles::VarNode_Body(Type, StateType), Body);

				FTextBlockStyle Title = FTextBlockStyle();
				UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&Title, VarNode.TitleText.Get());
				StyleSet->Set(FNodeRestyleStyles::VarNode_Title_Text, Title);
			}
		}
	}

	/* CollapsedNode*/
	{
		// Body
		{
			const auto& CollapsedNode = Style->CollapsedNode;
			const auto& TypeData = Style->CollapsedNode.Default;
			EDTCollapsedNodeType Type = EDTCollapsedNodeType::Default;
			for (int i = 0; i < (int)EDTGraphNodeState::Num; i++)
			{
				EDTGraphNodeState StateType = EDTGraphNodeState(i);
				const auto& State = TypeData.GetState(StateType);

				FSlateBrush* Body = new FSlateBrush();
				UDefaultThemeSettings::Get()->ModifyBrush(Body, State.Body.Get());

				StyleSet->Set(FNodeRestyleStyles::CollapsedNode_Body(Type, StateType), Body);
			}

			FInlineEditableTextBlockStyle MainText = FInlineEditableTextBlockStyle();
			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&MainText.TextStyle, CollapsedNode.Title.MainText.Get(),
			                                                   true);
			MainText.EditableTextBoxStyle.Font = MainText.TextStyle.Font;
			MainText.EditableTextBoxStyle.ForegroundColor = MainText.TextStyle.ColorAndOpacity;
			MainText.EditableTextBoxStyle.FocusedForegroundColor = MainText.TextStyle.ColorAndOpacity;
			// dunno why it adds some sort of padding when getting into editing mode
			MainText.EditableTextBoxStyle.Padding = FMargin(-1.f, -.5f, 0, 0);
			MainText.EditableTextBoxStyle.BackgroundImageNormal.DrawAs = ESlateBrushDrawType::NoDrawType;
			MainText.EditableTextBoxStyle.BackgroundImageFocused.DrawAs = ESlateBrushDrawType::NoDrawType;
			MainText.EditableTextBoxStyle.BackgroundImageHovered.DrawAs = ESlateBrushDrawType::NoDrawType;
			MainText.EditableTextBoxStyle.BackgroundImageReadOnly.DrawAs = ESlateBrushDrawType::NoDrawType;

			StyleSet->Set(FNodeRestyleStyles::CollapsedNode_Title_MainText, MainText);

			FTextBlockStyle ExtraText = FTextBlockStyle();
			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&ExtraText, CollapsedNode.Title.ExtraText.Get(), true);
			StyleSet->Set(FNodeRestyleStyles::CollapsedNode_Title_ExtraText, ExtraText);
		}
	}

	/* OtherNodes */
	{
		/* CreateDelegate */
		{
			const auto& CD = Style->OtherNodes.CreateDelegate;
			FComboBoxStyle ComboBoxStyle;
			UDefaultThemeSettings::Get()->ModifyComboBox(&ComboBoxStyle, CD.SearchComboBox.Get(), ChevronDownSvg);
			StyleSet->Set(FNodeRestyleStyles::CreateDelegate_SearchComboBox, ComboBoxStyle);

			FTableRowStyle ComboBoxRowStyle;
			UDefaultThemeSettings::Get()->ModifyComboBoxRow(&ComboBoxRowStyle, CD.SearchComboBox.Get().Row.Get());
			StyleSet->Set(FNodeRestyleStyles::CreateDelegate_SearchComboBox_Row, ComboBoxRowStyle);

			auto ComboBoxTextStyleConfig = CD.SearchComboBox.Get().ComboButton.Get().Button.Get().Text.Get();
			FTextBlockStyle ComboBoxTextStyle;
			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&ComboBoxTextStyle, ComboBoxTextStyleConfig);
			StyleSet->Set(FNodeRestyleStyles::CreateDelegate_SearchComboBox_Button_Text, ComboBoxTextStyle);

			auto SignatureTextConfig = CD.SignatureTitle.Get();
			FTextBlockStyle SignatureTextStyle;
			UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&SignatureTextStyle, SignatureTextConfig);
			StyleSet->Set(FNodeRestyleStyles::CreateDelegate_SignatureTitle, SignatureTextStyle);
		}
		/* Material */
		{
			const auto& Material = Style->OtherNodes.Material;
			const auto& CheckBoxData = Material.PreviewCheckbox.Get();
			FCheckBoxStyle CheckBoxStyle;
			UDefaultThemeSettings::Get()->ModifyCheckBox(&CheckBoxStyle, CheckBoxData, RoundChevronDownSvg, RoundChevronUpSvg, MinusSvg);
			StyleSet->Set(FNodeRestyleStyles::MaterialNode_PreviewCheckbox, CheckBoxStyle);
		}
		/* Animation */
		{
			const auto& Animation = Style->OtherNodes.Animation;
			const auto& Button = Animation.FunctionBinding.GotoButton.Get();
			FButtonStyle ButtonStyle;
			UDefaultThemeSettings::Get()->ModifyButtonStyle(&ButtonStyle, Button);
			StyleSet->Set(FNodeRestyleStyles::AnimationNode_FunctionBinding_GotoButton, ButtonStyle);
		}
	}

	/* CommentBubble */
	{
		const auto& CommentBubble = Style->CommentBubble;
		const auto& Pin = CommentBubble.Buttons.Pin;
		const auto& Toggle = CommentBubble.Buttons.Toggle;
		const FString IconPinOn = RootToContentDir("/Node/CommentPinOn", TEXT(".svg"));
		const FString IconPinOff = RootToContentDir("/Node/CommentPinOn", TEXT(".svg"));
		const FString IconToggle = RootToContentDir("/Node/Comment", TEXT(".svg"));
		{
			FName Id = FNodeRestyleStyles::CommentBubble_Checkbox_Pin;
			if (auto Found = WidgetStyles.Find(Id))
			{
				auto& x = (FCheckBoxStyle&)**Found;
				UDefaultThemeSettings::Get()->ModifyCheckBox(&x, Pin.Get(), IconPinOff, IconPinOn, "");
			}
			else
			{
				auto x = StyleSet->GetWidgetStyle<FCheckBoxStyle>("CommentBubblePin");
				UDefaultThemeSettings::Get()->ModifyCheckBox(&x, Pin.Get(), IconPinOff, IconPinOn, "");
				StyleSet->Set(Id, x);
			}
		}
		{
			FName Id = FNodeRestyleStyles::CommentBubble_Checkbox_Button;
			if (auto Found = WidgetStyles.Find(Id))
			{
				auto& x = (FCheckBoxStyle&)**Found;

				UDefaultThemeSettings::Get()->ModifyCheckBox(&x, Toggle.Get(), IconToggle, IconToggle, "");
			}
			else
			{
				auto x = StyleSet->GetWidgetStyle<FCheckBoxStyle>("CommentBubbleButton");
				UDefaultThemeSettings::Get()->ModifyCheckBox(&x, Toggle.Get(), IconToggle, IconToggle, "");
				StyleSet->Set(Id, x);
			}
		}
		{
			FName Id = FNodeRestyleStyles::CommentBubble_Checkbox_TitleButton;
			if (auto Found = WidgetStyles.Find(Id))
			{
				auto& x = (FCheckBoxStyle&)**Found;
				UDefaultThemeSettings::Get()->ModifyCheckBox(&x, Toggle.Get(), IconToggle, IconToggle, "");
			}
			else
			{
				auto x = StyleSet->GetWidgetStyle<FCheckBoxStyle>("CommentTitleButton");
				UDefaultThemeSettings::Get()->ModifyCheckBox(&x, Toggle.Get(), IconToggle, IconToggle, "");
				StyleSet->Set(Id, x);
			}
		}

		{
			FName Id = FNodeRestyleStyles::CommentBubble_EditableText;
			if (auto Found = WidgetStyles.Find(Id))
			{
				auto& x = (FEditableTextBoxStyle&)**Found;
				UDefaultThemeSettings::Get()->ModifyEditableTextBox(&x, CommentBubble.Text.Get());
			}
			else
			{
				auto x = StyleSet->GetWidgetStyle<FEditableTextBoxStyle>("Graph.CommentBubble.EditableText");
				UDefaultThemeSettings::Get()->ModifyEditableTextBox(&x, CommentBubble.Text.Get());
				StyleSet->Set(Id, x);
			}
		}
		{
			FName Id = FNodeRestyleStyles::CommentBubble_Body;
			if (auto Found = BrushResources.Find(Id))
			{
				auto& x = (FSlateBrush&)**Found;
				UDefaultThemeSettings::Get()->ModifyBrush(*Found, CommentBubble.Body.Get());
			}
			else
			{
				auto Brush = new FSlateRoundedBoxBrush(FLinearColor::Transparent);
				UDefaultThemeSettings::Get()->ModifyBrush(Brush, CommentBubble.Body.Get());

				StyleSet->Set(Id, Brush);
			}
			Id = FNodeRestyleStyles::CommentBubble_Body_White;
			if (auto Found = BrushResources.Find(Id))
			{
				auto& x = (FSlateBrush&)**Found;
				UDefaultThemeSettings::Get()->ModifyBrush(*Found, CommentBubble.Body.Get());
				x.TintColor = FLinearColor(1, 1, 1, x.TintColor.GetSpecifiedColor().A);
				x.OutlineSettings.Color = FLinearColor(1, 1, 1, x.OutlineSettings.Color.GetSpecifiedColor().A);
			}
			else
			{
				auto Brush = new FSlateRoundedBoxBrush(FLinearColor::Transparent);
				UDefaultThemeSettings::Get()->ModifyBrush(Brush, CommentBubble.Body.Get());
				Brush->TintColor = FLinearColor(1, 1, 1, Brush->TintColor.GetSpecifiedColor().A);
				Brush->OutlineSettings.Color =
					FLinearColor(1, 1, 1, Brush->OutlineSettings.Color.GetSpecifiedColor().A);
				StyleSet->Set(Id, Brush);
			}
		}
		{
			FName Id = FNodeRestyleStyles::CommentBubble_CommentArrow;
			if (auto Found = BrushResources.Find(Id))
			{
				auto x = *Found;
				x->TintColor = CommentBubble.ArrowColor.Get();
			}
			else
			{
				auto* x = new IMAGE_BRUSH_SVG("/Node/CommentArrow", FVector2D(8, 6));
				x->TintColor = CommentBubble.ArrowColor.Get();
				StyleSet->Set(Id, x);
			}
		}
	}

	/* CommentNode */
	{
		FInlineEditableTextBlockStyle TextStyle;
		const auto& CommentNode = Style->CommentNode;
		UDefaultThemeSettings::Get()->ModifyInlineEditableTextBox(&TextStyle, CommentNode.Title.Get());
		TextStyle.EditableTextBoxStyle.Padding.Left -= 1;

		StyleSet->Set(FNodeRestyleStyles::CommentNode_Title_Text, TextStyle);
	}

	/* NodeReport */
	{
		/* Body */
		{
			for (int i = 0; i < (int)EDTNodeReportType::Num; i++)
			{
				FName Id = FNodeRestyleStyles::NodeReport_Body((EDTNodeReportType)i);
				auto& NodeReport = Style->NodeReports[i];
				if (auto Found = BrushResources.Find(Id))
				{
					UDefaultThemeSettings::Get()->ModifyBrush(*Found, NodeReport.Body.Get());
				}
				else
				{
					auto Brush = new FSlateRoundedBoxBrush(FLinearColor::Transparent);
					UDefaultThemeSettings::Get()->ModifyBrush(Brush, NodeReport.Body.Get());
					StyleSet->Set(Id, Brush);
				}
			}
		}
		/* Text */
		{
			for (int i = 0; i < (int)EDTNodeReportType::Num; i++)
			{
				FName Id = FNodeRestyleStyles::NodeReport_Text((EDTNodeReportType)i);
				auto x = FTextBlockStyle();
				auto& NodeReport = Style->NodeReports[i];
				UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&x, NodeReport.Text.Get());
				StyleSet->Set(Id, x);
			}
		}
	}

	/* EnabledState */
	{
		{
			for (int i = 0; i < (int)EDTEnabledStateType::Num; i++)
			{
				FName Id = FNodeRestyleStyles::EnabledState_Body((EDTEnabledStateType)i);
				const auto& Config = Style->StateWidget.Types[i];
				if (auto Found = BrushResources.Find(Id))
				{
					UDefaultThemeSettings::Get()->ModifyBrush(*Found, Config.Body.Get());
				}
				else
				{
					auto Brush = new FSlateRoundedBoxBrush(FLinearColor::Transparent);
					UDefaultThemeSettings::Get()->ModifyBrush(Brush, Config.Body.Get());
					StyleSet->Set(Id, Brush);
				}
			}
		}
		{
			for (int i = 0; i < (int)EDTEnabledStateType::Num; i++)
			{
				FName Id = FNodeRestyleStyles::EnabledState_Text((EDTEnabledStateType)i);
				const auto& Config = Style->StateWidget.Types[i];
				auto TextBlockStyle = FTextBlockStyle();
				UDefaultThemeSettings::Get()->ModifyTextBlockStyle(&TextBlockStyle, Config.Text.Get());
				StyleSet->Set(Id, TextBlockStyle);
			}
		}
	}

	/* AdvancedDisplay */
	{
		FButtonStyle ButtonStyle;
		const auto& AdvancedDisplay = Style->AdvancedDisplay.Button.Get();
		UDefaultThemeSettings::Get()->ModifyButtonStyle(&ButtonStyle, AdvancedDisplay);
		StyleSet->Set(FNodeRestyleStyles::AdvancedDisplay, ButtonStyle);
	}

	/* Restyle.NoDrawBrush */
	{
		FName Id = FNodeRestyleStyles::NoDrawBrush;
		if (!BrushResources.Find(Id))
		{
			auto* NoDrawBrush = new FSlateBrush();
			NoDrawBrush->DrawAs = ESlateBrushDrawType::NoDrawType;
			StyleSet->Set(Id, NoDrawBrush);
		}
	}

	FRestyleProcessor::Get().ReloadEditorStyleSafe();
}

bool FNodeRestyleDefault::IsRegistered()
{
	return bRegistered;
}

/* @todo for more hooks, make util class*/
using FuncType = decltype(&UK2Node_CreateWidget::CreateVisualWidget);
FuncType OriginalFunc = nullptr;
TSharedPtr<SGraphNode, ESPMode::ThreadSafe>* __fastcall UK2Node_CreateWidget_CreateVisualWidget_Hook(UK2Node_CreateWidget* This, 
	TSharedPtr<SGraphNode, ESPMode::ThreadSafe>* Result)
{
	typedef std::remove_reference<decltype(*Result)>::type type;
	new (Result) type(nullptr);
	return Result;
}
//subhook_t CreateVisualWidget_Hook;

void FNodeRestyleDefault::Hook()
{
#ifdef PLATFORM_WINDOWS
	auto MH_INIT_RESULT = MH_Initialize();
	{
		auto Hook = &UK2Node_CreateWidget_CreateVisualWidget_Hook;
		/* @todo [optional] use .pdb (but seems it requires user to install .pdb via epic)*/
		const char* FuncName = "?CreateVisualWidget@UK2Node_CreateWidget@@UEAA?AV?$TSharedPtr@VSGraphNode@@$00@@XZ";
		auto ModuleHandle = GetModuleHandle(TEXT("UnrealEditor-UMGEditor.dll"));
		if (!ModuleHandle)
		{
			UE_LOG(LogTemp, Warning, L"%s GetModuleHandle(UMGEditor) failed", ANSI_TO_TCHAR(__FUNCTION__));
			return;
		}
		FARPROC CreateVisualWidget_Addr = GetProcAddress(ModuleHandle, FuncName);
		if (!CreateVisualWidget_Addr)
		{
			UE_LOG(LogTemp, Warning, L"%s GetProcAddress(UK2Node_CreateWidget::CreateVisualWidget) is null", ANSI_TO_TCHAR(__FUNCTION__));
			return;
		}
		auto MH_CREATE_HOOK_RESULT = MH_CreateHook(CreateVisualWidget_Addr, (void*)Hook, (void**)&OriginalFunc);
		//MH_CreateHook(CreateVisualWidget_Addr, (LPVOID)Hook, (LPVOID*)&OriginalFunc);

		auto MH_ENABLE_HOOK_RESULT = MH_EnableHook(CreateVisualWidget_Addr);

		if (MH_ENABLE_HOOK_RESULT != MH_OK)
		{
			UE_LOG(LogTemp, Warning, L"%s MH_EnableHook failed", ANSI_TO_TCHAR(__FUNCTION__));
		}
	}
#endif
	//auto Hook = &UK2Node_CreateWidget_CreateVisualWidget_Hook;
	///* @todo [optional] use .pdb (but seems it requires user to install .pdb via epic)*/
	//const char* FuncName = "?CreateVisualWidget@UK2Node_CreateWidget@@UEAA?AV?$TSharedPtr@VSGraphNode@@$00@@XZ";
	//auto ModuleHandle = GetModuleHandle(TEXT("UnrealEditor-UMGEditor.dll"));
	//if (!ModuleHandle)
	//{
	//	UE_LOG(LogTemp, Warning, L"%s GetModuleHandle(UMGEditor) failed", ANSI_TO_TCHAR(__FUNCTION__));
	//	return;
	//}
	//FARPROC CreateVisualWidget_Addr = GetProcAddress(ModuleHandle, FuncName);
	//if (!CreateVisualWidget_Addr)
	//{
	//	UE_LOG(LogTemp, Warning, L"%s GetProcAddress(UK2Node_CreateWidget::CreateVisualWidget) is null", ANSI_TO_TCHAR(__FUNCTION__));
	//	return;
	//}
	//CreateVisualWidget_Hook = subhook_new(CreateVisualWidget_Addr, (void*)UK2Node_CreateWidget_CreateVisualWidget_Hook, subhook_flags::SUBHOOK_64BIT_OFFSET);
	//if (CreateVisualWidget_Hook) {
	//	subhook_install(CreateVisualWidget_Hook);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, L"%s MH_EnableHook failed", ANSI_TO_TCHAR(__FUNCTION__));
	//}
}

void FNodeRestyleDefault::Unhook()
{
#ifdef PLATFORM_WINDOWS
	MH_Uninitialize();
#endif
}

bool FNodeRestyleDefault::OnSettingsChanged()
{
	Update();
	auto Mutable = GetMutableDefault<UNodeRestyleSettings>();
	Mutable->SaveConfig(CPF_Config, *Mutable->GetGlobalUserConfigFilename());
	return true;
}
