// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "DataTableEditorUtils.h"
#include "DefaultThemeSettings.h"
#include "GraphEditorSettings.h"

#include "Themes/ThemeInterfaces.h"
#include "Default/DefaultGraphPanelNodeFactory.h"
#include "SNodePanel.h"
#include "NodeRestyleDefault.generated.h"

class FNodeRestyleDefault
: public INodeRestyleInterface
{
public:
	explicit FNodeRestyleDefault();
	virtual TSharedPtr<FGraphPanelNodeFactory> GetFactory() override;
	virtual ERestyleSubject GetSubject() override;
	virtual void Register() override;
	virtual void Unregister() override;
	virtual void Update() override;
	virtual bool IsRegistered() override;
private:
	void Hook();
	void Unhook();
	bool OnSettingsChanged();
	bool bRegistered;
	TSharedPtr<FDefaultGraphPanelNodeFactory> Factory;
};

class UNodeRestyleSettings;

#pragma region Common

UENUM()
enum class EDTGraphNodeState
{
	Normal,
	Selected,
	// Deprecated, Disabled, Unrelated
	Invalid,
	Num
};

UENUM()
enum class EDTGraphNodeTitleType
{
	Default,
	Event,
	Function,
	PureFunction,
	ParentFunction,
	/*When editing function*/
	FunctionTerminator,
	/* Branch, Macro */
	ExecBranch,
	ExecSequence,
	Result,
	Preview,
	/* Animation CachedPose*/
	Black,
	/* Animation PlaySequence*/
	PlaySequence,
	LinkedLayer,
	Num UMETA(Hidden)
};

#pragma endregion

#pragma region Node
#pragma region Title

USTRUCT()
struct FDTNodeTitleDynamic
{
	GENERATED_BODY()

	FDTNodeTitleDynamic()
	{
		MainText = "Light-1";
		ExtraText = "Light-2";
		Icon = "Light-1";
		Background = "Light-4";
	}

	FDTNodeTitleDynamic(const FDTColor& MainText, const FDTColor& ExtraText, const FDTColor& Icon,
	                    const FDTColor& Background)
		: MainText(MainText),
		  ExtraText(ExtraText),
		  Icon(Icon),
		  Background(Background)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor MainText;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor ExtraText;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor Icon;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor Background;
};

USTRUCT()
struct FDTNodeTitle
{
	GENERATED_BODY()
	FDTNodeTitle()
	{
		MainText = "Medium";
		ExtraText = "SmallItalic";
		CornerRadius = "DefaultTop";
		Padding = "Medium";
		ItemSpacing = "Medium";
		AltItemSpacing = "Large";
		bAlternativeStyle = true;
		DelegatePinSpacing = "Large";
		bRemoveTargetIsTitle = true;
	}

	FDTNodeTitle(const FDTTextRef& MainText, const FDTTextRef& ExtraText, const FName& CornerRadius,
	             const FName& Padding, const FName& ItemSpacing, const FName& AltItemSpacing,
	             const FName& DelegatePinSpacing,
	             bool bAlternativeStyle, bool bRemoveTargetIsTitle)
		: MainText(MainText),
		  ExtraText(ExtraText),
		  CornerRadius(CornerRadius),
		  Padding(Padding),
		  ItemSpacing(ItemSpacing),
		  AltItemSpacing(AltItemSpacing),
		  DelegatePinSpacing(DelegatePinSpacing),
		  bAlternativeStyle(bAlternativeStyle),
			bRemoveTargetIsTitle(bRemoveTargetIsTitle)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTTextRef MainText;

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTTextRef ExtraText;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetCornerOptions"))
	FName CornerRadius;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName Padding;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName ItemSpacing;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName AltItemSpacing;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName DelegatePinSpacing;

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	bool bAlternativeStyle;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	bool bRemoveTargetIsTitle;
};
#pragma endregion

USTRUCT()
struct FDTNodeStateData
{
	GENERATED_BODY()

	FDTNodeStateData()
	{
		Title = FDTNodeTitleDynamic();
		Body = FDTBrushRef();
	}

	FDTNodeStateData(const FDTNodeTitleDynamic& Title, const FDTBrushRef& Body)
		: Title(Title),
		  Body(Body)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTNodeTitleDynamic Title;

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTBrushRef Body;
};

USTRUCT()
struct FDTNodeTypeData
{
	GENERATED_BODY()

	FDTNodeTypeData()
	{
	}

	FDTNodeTypeData(const FDTNodeStateData& Normal, const FDTNodeStateData& Selected, const FDTNodeStateData& Invalid)
		: Normal(Normal),
		  Selected(Selected),
		  Invalid(Invalid)
	{
	}

	const FDTNodeStateData& GetState(EDTGraphNodeState State) const
	{
		switch (State)
		{
		case EDTGraphNodeState::Selected: return Selected;
		case EDTGraphNodeState::Invalid: return Invalid;
		default: return Normal;
		}
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTNodeStateData Normal;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTNodeStateData Selected;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTNodeStateData Invalid;
};

USTRUCT()
struct FDTNode
{
	GENERATED_BODY()

	FDTNode()
	{
		FDTNodeStateData Normal, Selected, Invalid;
		auto MakeTypeData = [&Normal, &Selected, &Invalid](FName Content, FName TitleBg,
		                                                   FName NormalOutline) -> FDTNodeTypeData
		{
			Normal = {
				{
					FDTColor(Content),
					FDTColor(Content, .75f),
					FDTColor(Content),
					FDTColor(TitleBg),
				},
				FDTBrushRef("NodeNormal").SetOutlineColor(true, NormalOutline)
			};
			Selected = {
				{
					FDTColor(Content),
					FDTColor(Content, .75f),
					FDTColor(Content),
					FDTColor(TitleBg),
				},
				FDTBrushRef("NodeFocused").SetOutlineColor(true, TitleBg)
			};
			Invalid = {
					{
					FDTColor(Content),
					FDTColor(Content, .75f),
					FDTColor(Content),
					FDTColor(TitleBg),
				},
				FDTBrushRef("NodeNormal").SetOutlineColor(true, "Red-3")

			};
			return {Normal, Selected, Invalid};
		};

		Default = MakeTypeData("Light-1", "Light-4", "Light-4");
		Event = MakeTypeData("Red-0", "Red-4", "Light-4");
		Function = MakeTypeData("Blue-0", "Blue-4", "Light-4");
		PureFunction = MakeTypeData("Green-0", "Green-4", "Light-4");
		ParentFunction = MakeTypeData("YGreen-0", "YGreen-4", "Light-4");
		FunctionTerminator = MakeTypeData("Violet-0", "Violet-4", "Light-4");
		ExecBranch = Default;
		ExecSequence = Default;
		Result = Default;
		Preview = Default;
		Black = []() -> FDTNodeTypeData
		{
			FName Content = "Light-1";
			FName TitleBg = "Light-4";
			FName NormalOutline = "Light-4";
			FDTNodeStateData Normal, Selected, Invalid;
			Normal = {
				{
					FDTColor(Content),
					FDTColor(Content, .75f),
					FDTColor(Content),
					FDTColor(TitleBg, .5f),
				},
				FDTBrushRef("NodeNormal").SetOutlineColor(true, NormalOutline)
			};
			Selected = {
				{
					FDTColor(Content),
					FDTColor(Content, .75f),
					FDTColor(Content),
					FDTColor(TitleBg, .5f),
				},
				FDTBrushRef("NodeFocused").SetOutlineColor(true, TitleBg)
			};
			Invalid = {
					{
					FDTColor(Content),
					FDTColor(Content, .75f),
					FDTColor(Content),
					FDTColor(TitleBg, .5f),
				},
				FDTBrushRef("NodeNormal").SetOutlineColor(true, "Red-3")

			};
			return { Normal, Selected, Invalid };
		}();
		LinkedLayer = FunctionTerminator;
		PlaySequence = Event;
		Edit = EDTGraphNodeTitleType::Default;
		ContentSpacing = "Large+";
	}

	const FDTNodeTypeData& GetTypeData(EDTGraphNodeTitleType TitleType) const
	{
		switch (TitleType)
		{
		case EDTGraphNodeTitleType::Event: return Event;
		case EDTGraphNodeTitleType::Function: return Function;
		case EDTGraphNodeTitleType::PureFunction: return PureFunction;
		case EDTGraphNodeTitleType::ParentFunction: return ParentFunction;
		case EDTGraphNodeTitleType::FunctionTerminator: return FunctionTerminator;
		case EDTGraphNodeTitleType::ExecBranch: return ExecBranch;
		case EDTGraphNodeTitleType::ExecSequence: return ExecSequence;
		case EDTGraphNodeTitleType::Result: return Result;
		case EDTGraphNodeTitleType::Preview: return Preview;
		case EDTGraphNodeTitleType::Black: return Black;
		case EDTGraphNodeTitleType::PlaySequence: return PlaySequence;
		case EDTGraphNodeTitleType::LinkedLayer: return LinkedLayer;
		default: return Default;
		}
	}

	// unreal becomes laggy when open settings 
	//UPROPERTY(Category = "DTNodeData",/*EditAnywhere, */meta = (ArraySizeEnum = "EDTGraphNodeTitleType"))
	//FDTNodeTypeData Types[(int32)EDTGraphNodeTitleType::Num];

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	EDTGraphNodeTitleType Edit;

	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::Default", EditConditionHides))
	FDTNodeTypeData Default;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::Event", EditConditionHides))
	FDTNodeTypeData Event;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::Function", EditConditionHides))
	FDTNodeTypeData Function;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::PureFunction", EditConditionHides))
	FDTNodeTypeData PureFunction;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::ParentFunction", EditConditionHides))
	FDTNodeTypeData ParentFunction;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::FunctionTerminator",
			EditConditionHides))
	FDTNodeTypeData FunctionTerminator;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::ExecBranch", EditConditionHides))
	FDTNodeTypeData ExecBranch;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::ExecSequence", EditConditionHides))
	FDTNodeTypeData ExecSequence;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::Result", EditConditionHides))
	FDTNodeTypeData Result;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::Preview", EditConditionHides))
	FDTNodeTypeData Preview;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::Black", EditConditionHides))
	FDTNodeTypeData Black;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::PlaySequence", EditConditionHides))
	FDTNodeTypeData PlaySequence;
	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (EditCondition = "Edit==EDTGraphNodeTitleType::LinkedLayer", EditConditionHides))
	FDTNodeTypeData LinkedLayer;

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTNodeTitle Title;


	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName ContentSpacing;
};

USTRUCT()
struct FDTCompactNodeStateData
{
	GENERATED_BODY()
	FDTCompactNodeStateData()
	{
		TitleColor = FDTColor("Light-3");
	}

	FDTCompactNodeStateData(const FDTColor& TitleColor, const FDTBrushRef& Body)
		: TitleColor(TitleColor),
		  Body(Body)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTColor TitleColor;

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTBrushRef Body;
};

USTRUCT()
struct FDTNodeCompactStates
{
	GENERATED_BODY()

	FDTNodeCompactStates()
	{
		Normal = {
			FDTColor("Light-3"),
			FDTBrushRef("NodeNormal")
		};
		Selected = {
			FDTColor("Light-3"),
			FDTBrushRef("NodeFocused")
		};
		Invalid = {
			FDTColor("Light-3", .5f),
			FDTBrushRef("NodeNormal").SetOutlineColor(true, "Red-3")
		};
	}

	FDTNodeCompactStates(const FDTCompactNodeStateData& Normal, const FDTCompactNodeStateData& Selected,
	                     const FDTCompactNodeStateData& Invalid)
		: Normal(Normal),
		  Selected(Selected),
		  Invalid(Invalid)
	{
	}

	const FDTCompactNodeStateData& GetState(EDTGraphNodeState State) const
	{
		switch (State)
		{
		case EDTGraphNodeState::Selected: return Selected;
		case EDTGraphNodeState::Invalid: return Invalid;
		default: return Normal;
		}
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCompactNodeStateData Normal;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCompactNodeStateData Selected;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCompactNodeStateData Invalid;
};

USTRUCT()
struct FDTNodeCompactTitleDefault
{
	GENERATED_BODY()
	FDTNodeCompactTitleDefault()
	{
		Text = "Medium+";
		OneSymbolText = "Large";
		Padding = "HugeX";
		WrapAt = 128.0f;
		FunctionIconColor = FDTColor("Blue-2", .25f);
		MacroIconColor = FDTColor("Light-2", .25f);
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTTextRef Text;

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTTextRef OneSymbolText;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName Padding;

	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (ClampMin = "64.0", ClampMax = "512.0"))
	float WrapAt;

	/*Array/Set/Map Icons have static 25% opacity of its type color */
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor FunctionIconColor;

	/*Array/Set/Map Icons have static 25% opacity of its type color */
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor MacroIconColor;
};

USTRUCT()
struct FDTNodeCompactTitleAlternative
{
	GENERATED_BODY()
	FDTNodeCompactTitleAlternative()
	{
		Text = "Medium";
		Padding = "Medium";
		WrapAt = 128.0f;
		ItemSpacing = "Large";
		FunctionIconColor = "Blue-4";
		MacroIconColor = "Light-4";
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTTextRef Text;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName Padding;

	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (ClampMin = "64.0", ClampMax = "512.0"))
	float WrapAt;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName ItemSpacing;

	/*Array/Set/Map Icons have static 25% opacity of its type color */
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor FunctionIconColor;

	/*Array/Set/Map Icons have static 25% opacity of its type color */
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor MacroIconColor;
};

USTRUCT()
struct FDTNodeCompact
{
	GENERATED_BODY()

	FDTNodeCompact()
	{
		States = FDTNodeCompactStates();
		BodyCornerRadius = "Default";
		ContentSpacing = "Large+";
		Title = FDTNodeCompactTitleDefault();
		AlternativeTitle = FDTNodeCompactTitleAlternative();
		AltFuncIfGreater = 5;
		AltMacroIfGreater = -1;
		MinWidth = 128.0f;
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTNodeCompactStates States;

	/*Uses alternative title style if length of compact node title is greater than this N*/
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ClampMin="-1", ClampMax="256"))
	int32 AltFuncIfGreater;
	/*Uses alternative title style if length of compact node title is greater than this N*/
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ClampMin="-1", ClampMax="256"))
	int32 AltMacroIfGreater;

	UPROPERTY(Category = "DTNodeData",EditAnywhere,
		meta = (DisplayName = "Alternative Title"))
	FDTNodeCompactTitleAlternative AlternativeTitle;

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTNodeCompactTitleDefault Title;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetCornerOptions"))
	FName BodyCornerRadius;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName ContentSpacing;

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ClampMin = "64", ClampMax = "512"))
	float MinWidth;
};

USTRUCT()
struct FDTVarNodeState
{
	GENERATED_BODY()
	FDTVarNodeState()
	{
		TitleColor = "Light-2";
		TitleBody = "Transparent";
		Body = "NodeNormal";
	}

	FDTVarNodeState(const FDTColor& TitleColor, const FDTBrushRef& TitleBody, const FDTBrushRef& Body)
		: TitleColor(TitleColor),
		  TitleBody(TitleBody),
		  Body(Body)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTColor TitleColor;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTBrushRef TitleBody;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTBrushRef Body;
};

USTRUCT()
struct FDTVarNodeTypeData
{
	GENERATED_BODY()
	FDTVarNodeTypeData()
	{
		Normal = {"Light-2", "Transparent", "NodeNormal"};
		Selected = {"Light-2", "Transparent", "NodeFocused"};
		Invalid = {
			"Light-2", "Transparent", FDTBrushRef("NodeNormal").SetOutlineColor(true, "Red-3")
		};
	}

	FDTVarNodeTypeData(const FDTVarNodeState& Normal, const FDTVarNodeState& Selected, const FDTVarNodeState& Invalid)
		: Normal(Normal),
		  Selected(Selected),
		  Invalid(Invalid)
	{
	}

	const FDTVarNodeState& GetState(EDTGraphNodeState State) const
	{
		switch (State)
		{
		case EDTGraphNodeState::Selected: return Selected;
		case EDTGraphNodeState::Invalid: return Invalid;
		default: return Normal;
		}
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTVarNodeState Normal;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTVarNodeState Selected;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTVarNodeState Invalid;
};

UENUM()
enum class EDTVarType : uint8
{
	Default,
	Execution,
	Index,
	Wildcard,
	Boolean,
	Byte,
	Int,
	Int64,
	Float,
	Double,
	Real,
	Text,
	String,
	Name,
	Struct,
	Class,
	SoftClass,
	Object,
	SoftObject,
	Delegate,
	Interface,
	Vector,
	Rotator,
	Transform,
	MAX UMETA(Hidden)
};

USTRUCT()
struct FDTVarNode
{
	GENERATED_BODY()
	FDTVarNode()
	{
		Default = FDTVarNodeTypeData();
		TitleText = "Medium";
		ContentSpacing = "Large+";
		TitlePadding = "HugeXMediumY";
		ContentAreaPadding = "Zero";
		bHideGetTitle = false;
		TitleHeight = 20;
	}

	const FDTVarNodeTypeData& GetTypeData(EDTVarType Type) const
	{
		switch (Type)
		{
		case EDTVarType::Default:
		case EDTVarType::Execution:
		case EDTVarType::Index:
		case EDTVarType::Wildcard:
		case EDTVarType::Boolean:
		case EDTVarType::Byte:
		case EDTVarType::Int:
		case EDTVarType::Int64:
		case EDTVarType::Float:
		case EDTVarType::Double:
		case EDTVarType::Real:
		case EDTVarType::Text:
		case EDTVarType::String:
		case EDTVarType::Name:
		case EDTVarType::Struct:
		case EDTVarType::Class:
		case EDTVarType::SoftClass:
		case EDTVarType::Object:
		case EDTVarType::SoftObject:
		case EDTVarType::Delegate:
		case EDTVarType::Interface:
		case EDTVarType::Vector:
		case EDTVarType::Rotator:
		case EDTVarType::Transform:
		case EDTVarType::MAX:
		default: return Default;
		}
	}
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName TitlePadding;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTVarNodeTypeData Default;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTTextRef TitleText;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName ContentSpacing;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName ContentAreaPadding;
	UPROPERTY(Category = "DTNodeData", EditAnywhere)
		bool bHideGetTitle;
	UPROPERTY(Category = "DTNodeData", EditAnywhere, meta = (ClampMin = "0", ClampMax = "64"))
		float TitleHeight;
};

USTRUCT()
struct FDTCollapsedNodeTitleDynamic
{
	GENERATED_BODY()

	FDTCollapsedNodeTitleDynamic()
	{
		MainText = "Light-1";
		ExtraText = "Light-2";
		Icon = "Light-1";
	}

	FDTCollapsedNodeTitleDynamic(const FDTColor& MainText, const FDTColor& ExtraText, const FDTColor& Icon)
		: MainText(MainText),
		  ExtraText(ExtraText),
		  Icon(Icon)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor MainText;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor ExtraText;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor Icon;
};


USTRUCT()
struct FDTCollapsedNodeState
{
	GENERATED_BODY()
	FDTCollapsedNodeState()
	{
		Title = FDTCollapsedNodeTitleDynamic();
		Body = "NodeNormal";
	}

	FDTCollapsedNodeState(const FDTCollapsedNodeTitleDynamic& Title, const FDTBrushRef& Body)
		: Title(Title),
		  Body(Body)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCollapsedNodeTitleDynamic Title;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTBrushRef Body;
};

USTRUCT()
struct FDTCollapsedNodeTypeData
{
	GENERATED_BODY()
	FDTCollapsedNodeTypeData()
	{
		Normal = {{"Light-2", "Light-4", "Light-2"}, "NodeNormal"};
		Selected = {{"Light-2", "Light-4", "Light-2"}, "NodeFocused"};
		Invalid = {{"Light-2", "Light-4", "Light-2"}, "NodeNormal"};
	}

	FDTCollapsedNodeTypeData(const FDTCollapsedNodeState& Normal, const FDTCollapsedNodeState& Selected,
	                         const FDTCollapsedNodeState& Invalid)
		: Normal(Normal),
		  Selected(Selected),
		  Invalid(Invalid)
	{
	}

	const FDTCollapsedNodeState& GetState(EDTGraphNodeState State) const
	{
		switch (State)
		{
		case EDTGraphNodeState::Selected: return Selected;
		case EDTGraphNodeState::Invalid: return Invalid;
		default: return Normal;
		}
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCollapsedNodeState Normal;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCollapsedNodeState Selected;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCollapsedNodeState Invalid;
};

UENUM()
enum class EDTCollapsedNodeType : uint8
{
	Default,
	MathExpression,
	Collapsed,
	MAX UMETA(Hidden)
};

USTRUCT()
struct FDTCollapsedNodeTitle
{
	GENERATED_BODY()
	FDTCollapsedNodeTitle()
	{
		MainText = "Medium";
		ExtraText = "Small";
		ItemSpacing = "Large+";
		Padding = "Medium";
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTTextRef MainText;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTTextRef ExtraText;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName ItemSpacing;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName Padding;
};

USTRUCT()
struct FDTCollapsedNode
{
	GENERATED_BODY()
	FDTCollapsedNode()
	{
		Default = FDTCollapsedNodeTypeData();
	}

	const FDTCollapsedNodeTypeData& GetTypeData(EDTCollapsedNodeType Type) const
	{
		return Default;
		/*switch (Type)
		{
		case EDTCollapsedNodeType::MathExpression: break;
		case EDTCollapsedNodeType::Collapsed: break;
		default: return Default;
		}*/
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCollapsedNodeTitle Title;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCollapsedNodeTypeData Default;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName ContentSpacing;
};

USTRUCT()
struct FDTCreateDelegateNode
{
	GENERATED_BODY()
	FDTCreateDelegateNode()
	{
		SignatureTitle = "Small";
		SearchComboBox = "Default";
		TitlePadding = "Medium";
		SearchPadding = "Medium";
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTTextRef SignatureTitle;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTComboBoxRef SearchComboBox;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName TitlePadding;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName SearchPadding;
};

USTRUCT()
struct FDTNodeKnot
{
	GENERATED_BODY()
	FDTNodeKnot()
	{
		BodySize = { 32,32 };
		BodyColor = FDTColor("Light-4", .2f);
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
		FVector2D BodySize;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
		FDTColor BodyColor;
};

USTRUCT()
struct FDTMaterialNode
{
	GENERATED_BODY()
		FDTMaterialNode()
	{
		PreviewCheckboxSpacing = "Large";
		PreviewCheckbox = "TransparentLight";
	}
	UPROPERTY(Category = "DTNodeData", EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName PreviewCheckboxSpacing;
	UPROPERTY(Category = "DTNodeData", EditAnywhere)
	FDTCheckBoxRef PreviewCheckbox;
};

USTRUCT()
struct FDTFunctionBinding
{
	GENERATED_BODY()
	FDTFunctionBinding()
	{
		Padding = "Small";
		SpacingY = "Medium";
		SpacingX = "Medium";
		GotoButton = "Transparent";
		NameWidth = 128;
		ValueWidth = 128;
	}
	UPROPERTY(Category = "DTNodeData", EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName Padding;
	/* Spacing between items*/
	UPROPERTY(Category = "DTNodeData", EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName SpacingY;
	UPROPERTY(Category = "DTNodeData", EditAnywhere)
	FDTButtonRef GotoButton;
	/* Spacing between dropdowm and goto */
	UPROPERTY(Category = "DTNodeData", EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName SpacingX;
	UPROPERTY(Category = "DTNodeData", EditAnywhere, meta = (ClampMin = "0", ClampMax = "512"))
	float NameWidth;
	UPROPERTY(Category = "DTNodeData", EditAnywhere, meta = (ClampMin = "0", ClampMax = "512"))
	float ValueWidth;
};

USTRUCT()
struct FDTAnimationNode
{
	GENERATED_BODY()
	FDTAnimationNode()
	{
		FunctionBinding = FDTFunctionBinding();
		TimelineSlider = "Default";
		TimelineSliderPadding = "Zero";
	}

	UPROPERTY(Category = "DTNodeData", EditAnywhere)
	FDTFunctionBinding FunctionBinding;
	UPROPERTY(Category = "DTNodeData", EditAnywhere)
	FDTSliderRef TimelineSlider;
	UPROPERTY(Category = "DTNodeData", EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName TimelineSliderPadding;
};

USTRUCT()
struct FDTOtherNodes
{
	GENERATED_BODY()
	FDTOtherNodes()
	{
		CreateDelegate = FDTCreateDelegateNode();
		Reroute = FDTNodeKnot();
		Material = FDTMaterialNode();
		Animation = FDTAnimationNode();
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCreateDelegateNode CreateDelegate;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTNodeKnot Reroute;
	UPROPERTY(Category = "DTNodeData", EditAnywhere)
	FDTMaterialNode Material;
	UPROPERTY(Category = "DTNodeData", EditAnywhere)
	FDTAnimationNode Animation;
};
#pragma endregion

#pragma region Comment
USTRUCT()
struct FDTCommentBubbleButtonSettings
{
	GENERATED_BODY()
	FDTCommentBubbleButtonSettings()
	{
		Toggle = "Transparent";
		Pin = "Transparent";
		ToggleOffset = FMargin(0, 0, 0, 4);
		Size = "Medium";
		ButtonsBoxOffset = "LargeLeft";
		SpaceBetweenButtons = FVector2D(4, 2);
	}

	FDTCommentBubbleButtonSettings(const FDTCheckBoxRef& Toggle, const FDTCheckBoxRef& Pin, const FName& Size,
	                               const FVector2D& SpaceBetweenButtons, const FMargin& ToggleOffset,
	                               const FName& ButtonsBoxOffset)
		: Toggle(Toggle),
		  Pin(Pin),
		  Size(Size),
		  SpaceBetweenButtons(SpaceBetweenButtons),
		  ToggleOffset(ToggleOffset),
		  ButtonsBoxOffset(ButtonsBoxOffset)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCheckBoxRef Toggle;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCheckBoxRef Pin;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetIconSizeOptions"))
	FName Size;

	/* X when horizontal. Y when vertical*/
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FVector2D SpaceBetweenButtons;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FMargin ToggleOffset;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName ButtonsBoxOffset;
};

USTRUCT()
struct FDTCommentBubbleBackgroundSettings
{
	GENERATED_BODY()
	FDTCommentBubbleBackgroundSettings()
	{
		Body = "NodeFocused";
		ArrowColor = "Light-4";
		InnerPadding = "Large";
	}

	FDTCommentBubbleBackgroundSettings(const FDTBrushRef& Body, const FDTColor& ArrowColor, const FName& InnerPadding)
		: Body(Body),
		  ArrowColor(ArrowColor),
		  InnerPadding(InnerPadding)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTBrushRef Body;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor ArrowColor;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FName InnerPadding;
};

USTRUCT()
struct FDTCommentBubble
{
	GENERATED_BODY()

	FDTCommentBubble()
	{
		Text = "Transparent-2";
		Body = "NodeNormal";
		ArrowColor = "Light-4";
		InnerPadding = "Large";
		Buttons = FDTCommentBubbleButtonSettings();
	}

	FDTCommentBubble(const FDTEditableTextBoxRef& Text, const FDTBrushRef& Body,
	                 const FDTColor& ArrowColor, const FName& InnerPadding,
	                 const FDTCommentBubbleButtonSettings& Buttons)
		: Text(Text),
		  Body(Body),
		  ArrowColor(ArrowColor),
		  InnerPadding(InnerPadding),
		  Buttons(Buttons)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTEditableTextBoxRef Text;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTBrushRef Body;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetColorOptions"))
	FDTColor ArrowColor;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName InnerPadding;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTCommentBubbleButtonSettings Buttons;
};

USTRUCT()
struct FDTCommentNode
{
	GENERATED_BODY()

	FDTCommentNode()
	{
		bNewResizingMethod = true;
		Title = "TransparentNoPadding";
		TitlePadding = "Large";
		NormalOpacity = .1f;
		SelectedOpacity = .2f;
		ResizeIconColor = FDTColor("Light-1", .5f);
	}

	/* Removes an issue of cursor being "desynced" when resizing comment*/
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	bool bNewResizingMethod;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTEditableTextBoxRef Title;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName TitlePadding;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ClampMin = "0.05", ClampMax = "1.0"))
	float NormalOpacity;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ClampMin = "0.1", ClampMax = "1.0"))
	float SelectedOpacity;
	//@TODO find where to apply it
	//UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTColor ResizeIconColor;
 
};
#pragma endregion

#pragma region Report

UENUM()
enum class EDTNodeReportType
{
	Error,
	Warning,
	Info,
	Upgrade,
	Num UMETA(Hidden)
};

USTRUCT()
struct FDTNodeReport
{
	GENERATED_BODY()

	FDTNodeReport()
	{
		Title = "NOTE";
		Text = "MediumBold";
		Body = "NodeReport";
		InnerPadding = "Medium";
	}

	FDTNodeReport(const FString& Title, const FDTTextRef& Text, const FDTBrushRef& Body,
	              const FName& InnerPadding)
		: Title(Title),
		  Text(Text),
		  Body(Body),
		  InnerPadding(InnerPadding)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FString Title;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTTextRef Text;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTBrushRef Body;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName InnerPadding;
};
#pragma endregion

#pragma region EnabledState
UENUM()
enum class EDTEnabledStateType
{
	Development,
	Disabled,
	Num UMETA(Hidden)
};

USTRUCT()
struct FDTEnabledState
{
	GENERATED_BODY()
	FDTEnabledState()
	{
		Title = "EnabledState";
		Text = "Medium";
		Body = "Box";
		InnerPadding = "Small";
	}

	FDTEnabledState(const FString& Title, const FDTTextRef& Text, const FDTBrushRef& Body,
	                const FName& InnerPadding)
		: Title(Title),
		  Text(Text),
		  Body(Body),
		  InnerPadding(InnerPadding)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FString Title;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTTextRef Text;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FDTBrushRef Body;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName InnerPadding;
};

USTRUCT()
struct FDTEnabledStateWidget
{
	GENERATED_BODY()


	FDTEnabledStateWidget()
	{
		Types[(int)EDTEnabledStateType::Development] = FDTEnabledState(
			"Development Only",
			FDTTextRef("Medium", "Orange-1"),
			FDTBrushRef("Box").SetBackgroundColor(true, "Orange-4"),
			"Small"
		);
		Types[(int)EDTEnabledStateType::Disabled] = FDTEnabledState(
			"Disabled",
			FDTTextRef("Medium", "Light-2"),
			FDTBrushRef("Box").SetBackgroundColor(true, "Light-4"),
			"Small"
		);
		Padding = "SmallY";
	}

	explicit FDTEnabledStateWidget(const FName& Padding, FDTEnabledState Types[(int)EDTEnabledStateType::Num])
		: Padding(Padding)
	{
		FMemory::Memcpy(this->Types, Types, sizeof(FDTEnabledState) * (int)EDTEnabledStateType::Num);
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetMarginOptions"))
	FName Padding;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ArraySizeEnum = "EDTEnabledStateType"))
	FDTEnabledState Types[(int)EDTEnabledStateType::Num];
};
#pragma endregion

#pragma region Zoom

USTRUCT()
struct FZoomLevelEntry
{
	GENERATED_BODY()
	FZoomLevelEntry()
	{
		ZoomAmount = 1.f;
		DisplayText = FText::FromString("1.0");
	}

	FZoomLevelEntry(float ZoomAmount, const FText& DisplayText)
		: ZoomAmount(ZoomAmount),
		  DisplayText(DisplayText)
	{
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	float ZoomAmount;
	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	FText DisplayText;
};

USTRUCT()
struct FDTZoomSettings
{
	GENERATED_BODY()
	FDTZoomSettings()
	{
		Smoothness = 20;
		Min = .1f;
		Max = 2.0f;
		MaxJump = .5f;
		MinJump = .25f;
		Default = 1.0f;
		UseLowLodIfBelow = 0.25f;
		UpdateZoomLevels();
	}

	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ClampMin = "10", ClampMax = "200"))
	int Smoothness;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ClampMin = "0.1", ClampMax = "0.2", Units = "Percent"))
	float Min;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ClampMin = "1.5", ClampMax = "3.0", Units = "Percent"))
	float Max;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ClampMin = "0.25", ClampMax = "0.5", Units = "Percent"))
	float MaxJump;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ClampMin = "0.125", ClampMax = "0.25", Units = "Percent"))
	float MinJump;
	UPROPERTY(Category = "DTNodeData",EditAnywhere, meta = (ClampMin = "0.5", ClampMax = "2.0", Units = "Percent"))
	float Default;

	UPROPERTY(Category = "DTNodeData", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", Units = "Percent"))
		float UseLowLodIfBelow;

	UPROPERTY(Category = "DTNodeData",EditAnywhere)
	TArray<FZoomLevelEntry> ZoomLevels;
	int32 DefaultZoomLevelId;
	int32 LowerZoomLevelId;

	void UpdateZoomLevels()
	{
		float Delta = (Max - Min) / static_cast<float>(Smoothness - 1);

		TFunction<float(int)> Calc = [&](int i)-> float
		{
			if (i != 0)
			{
				float Previous = Calc(i - 1);
				float Value = Min + Delta * static_cast<float>(i);
				float Jump = Value / Previous - 1;
				if (Jump > MaxJump)
				{
					Jump = MaxJump;
					Value = Previous * (Jump + 1);
				}
				else if (Jump < MinJump)
				{
					Jump = MinJump;
					Value = Previous * (Jump + 1);
				}
				return Value;
			}
			float Value = Min + Delta * static_cast<float>(i);
			return Value;
		};
		ZoomLevels.Empty();
		for (int i = 0; i < Smoothness; i++)
		{
			float Value = Calc(i);
			FString StrValue = Value > .5
				                   ? FString::Printf(TEXT("%.1f"), Value)
				                   : FString::Printf(TEXT("%.2f"), Value);
			Value = FCString::Atof(*StrValue);
			ZoomLevels.Add(
				{
					Value,
					FText::FromString("Zoom: " + StrValue)
				}
			);
			if (Value >= Max) break;
		}
		UpdateDefaultZoomLevelId();
		UpdateLowerZoomLevelId();
	}

	void UpdateDefaultZoomLevelId()
	{
		float PrevClosestToDefaultDelta = 2.f;
		for (int i = 0; i < ZoomLevels.Num(); i++)
		{
			float ClosestToDefaultDelta = FMath::Abs(ZoomLevels[i].ZoomAmount - Default);
			if (ClosestToDefaultDelta < PrevClosestToDefaultDelta)
			{
				DefaultZoomLevelId = i;
				PrevClosestToDefaultDelta = ClosestToDefaultDelta;
			}
		}
		SmoothDefaultLevel();
	}
	void UpdateLowerZoomLevelId()
	{
		LowerZoomLevelId = 0; 
		for (int i = ZoomLevels.Num() -1 ; i >= 0; i--)
		{
			if (ZoomLevels[i].ZoomAmount <= UseLowLodIfBelow)
			{
				LowerZoomLevelId = i;
				break;
			}
		}
	}
	void SmoothDefaultLevel()
	{
		ZoomLevels[DefaultZoomLevelId] = {
			Default,
			FText::FromString(FString::Printf(TEXT("Zoom: %.1f"), Default))
		};
	}
};

#pragma endregion

USTRUCT()
struct FDTAdvancedDisplay
{
	GENERATED_BODY()
	FDTAdvancedDisplay()
	{
		Padding = "Medium";
		Button = "Transparent";
	}


	UPROPERTY(Category ="DTNodeData", EditAnywhere, meta = (GetOptions = "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName Padding;
	UPROPERTY(Category = "DTNodeData", EditAnywhere)
	FDTButtonRef Button;
};

struct FNodeRestyleStyles
{
	static inline const FName CommentBubble_CommentArrow = "Restyle.CommentBubble.CommentArrow";
	static inline const FName CommentBubble_EditableText = "Restyle.CommentBubble.EditableText";
	static inline const FName CommentBubble_Body = "Restyle.CommentBubble.Body";
	static inline const FName CommentBubble_Body_White = "Restyle.CommentBubble.Body.White";
	static inline const FName CommentBubble_Checkbox_Button = "Restyle.CommentBubble.Checkbox.Button";
	static inline const FName CommentBubble_Checkbox_TitleButton = "Restyle.CommentBubble.Checkbox.TitleButton";
	static inline const FName CommentBubble_Checkbox_Pin = "Restyle.CommentBubble.Checkbox.Pin";
	static inline const FName GraphNode_Title_ExtraText = "Restyle.Graph.Node.TitleExtraText";
	static inline const FName GraphNode_Title_MainText = "Restyle.Graph.Node.TitleMainText";
	static inline const FName GraphNode_Compact_Title = "Restyle.Graph.Node.Compact.Title";
	static inline const FName GraphNode_Compact_Title_OneSymbol = "Restyle.Graph.Node.Compact.Title.OneSymbol";
	static inline const FName GraphNode_Compact_AlternativeTitle = "Restyle.Graph.Node.Compact.AlternativeTitle";
	static inline const FName VarNode_Title_Text = "Restyle.Graph.VarNode.Title.Text";
	static inline const FName CollapsedNode_Title_MainText = "Restyle.CollapsedNode.Title.MainText";
	static inline const FName CollapsedNode_Title_ExtraText = "Restyle.CollapsedNode.Title.ExtraText";
	static inline const FName CreateDelegate_SearchComboBox = "Restyle.CreateDelegate.ComboBox";
	static inline const FName CreateDelegate_SearchComboBox_Row = "Restyle.CreateDelegate.ComboBox.Row";
	static inline const FName CreateDelegate_SignatureTitle = "Restyle.CreateDelegate.SignatureTitle";
	static inline const FName CreateDelegate_SearchComboBox_Button_Text = "Restyle.CreateDelegate.ComboBox.Button.Text";
	static inline const FName CommentNode_Title_Text = "Restyle.Commentnode.Title.Text";
	static inline const FName AdvancedDisplay = "Restyle.Graph.AdvancedDisplay";
	static inline const FName MaterialNode_PreviewCheckbox = "Restyle.MaterialNode.PreviewCheckbox";
	static inline const FName AnimationNode_FunctionBinding_GotoButton = "Restyle.AnimationNode.FunctionBinding.GotoButton";


	static FName VarNode_Body(EDTVarType Type, EDTGraphNodeState State)
	{
		return *FString::Printf(TEXT("Restyle.VarNode.Body.%d.%d"), (int)Type, (int)State);
	}

	static FName VarNode_Title_Body(EDTVarType Type, EDTGraphNodeState State)
	{
		return *FString::Printf(TEXT("Restyle.VarNode.Title.Body.%d.%d"), (int)Type, (int)State);
	}

	static FName CollapsedNode_Body(EDTCollapsedNodeType Type, EDTGraphNodeState State)
	{
		return *FString::Printf(TEXT("Restyle.CollapsedNode.Body.%d.%d"), (int)Type, (int)State);
	}

	static FName EnabledState_Body(EDTEnabledStateType Type)
	{
		return *FString::Printf(TEXT("Restyle.EnabledState.Body.%d"), (int)Type);
	}

	static FName EnabledState_Text(EDTEnabledStateType Type)
	{
		return *FString::Printf(TEXT("Restyle.EnabledState.Text.%d"), (int)Type);
	}

	static FName NodeReport_Body(EDTNodeReportType Type)
	{
		return *FString::Printf(TEXT("Restyle.Graph.Node.Report.Body.%d"), (int)Type);
	}

	static FName NodeReport_Text(EDTNodeReportType Type)
	{
		return *FString::Printf(TEXT("Restyle.Graph.Node.Report.Text.%d"), (int)Type);
	}

	static FName GraphNode_Body(EDTGraphNodeTitleType TitleType, EDTGraphNodeState State)
	{
		return *FString::Printf(TEXT("Restyle.Graph.Node.Body.%d.%d"), (int)TitleType, (int)State);
	}

	static FName GraphNode_Compact_Body(EDTGraphNodeState State)
	{
		return *FString::Printf(TEXT("Restyle.Graph.Node.Compact.Body.%d"), (int)State);
	}

	static FName GraphNode_Title_Body(EDTGraphNodeTitleType TitleType, EDTGraphNodeState State)
	{
		return *FString::Printf(TEXT("Restyle.Graph.Node.TitleBody.%d.%d"), (int)TitleType, (int)State);
	}

	static inline const FName NoDrawBrush = "Restyle.NoDrawBrush";
};

UCLASS(Config = Restyle, GlobalUserConfig)
class UNodeRestyleSettings : public UObject
{
	GENERATED_BODY()
public:
	UNodeRestyleSettings()
	{
		SetDefaults();
	};

	static const UNodeRestyleSettings* Get()
	{
		return GetDefault<UNodeRestyleSettings>();
	}

	static UNodeRestyleSettings* GetM()
	{
		return GetMutableDefault<UNodeRestyleSettings>();
	}

	void SetDefaults();
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#pragma region Utils
	static EDTGraphNodeTitleType DetermineTitleTypeByColor(const FLinearColor& RawNodeTitleColor)
	{
		auto& x = RawNodeTitleColor;
		auto Settings = GetDefault<UGraphEditorSettings>();
		if (x == Settings->EventNodeTitleColor)
		{
			return EDTGraphNodeTitleType::Event;
		}
		if (x == Settings->FunctionCallNodeTitleColor)
		{
			return EDTGraphNodeTitleType::Function;
		}
		// Hardcoded: Animation Nodes
		if (x == Settings->PureFunctionCallNodeTitleColor || x == FLinearColor(0.2000, 0.8000, 0.2000))
		{
			return EDTGraphNodeTitleType::PureFunction;
		}
		if (x == Settings->ParentFunctionCallNodeTitleColor)
		{
			return EDTGraphNodeTitleType::ParentFunction;
		}
		if (x == Settings->FunctionTerminatorNodeTitleColor)
		{
			return EDTGraphNodeTitleType::FunctionTerminator;
		}
		if (x == Settings->ExecBranchNodeTitleColor)
		{
			return EDTGraphNodeTitleType::ExecBranch;
		}
		if (x == Settings->ExecSequenceNodeTitleColor)
		{
			return EDTGraphNodeTitleType::ExecSequence;
		}
		if (x == Settings->ResultNodeTitleColor)
		{
			return EDTGraphNodeTitleType::Result;
		}
		/*if (x == Settings->DefaultCommentNodeTitleColor)
		{
			return EDTGraphNodeTitleType::DefaultComment;
		}*/
		if (x == Settings->PreviewNodeTitleColor)
		{
			return EDTGraphNodeTitleType::Preview;
		}
		// Hardcoded: Animation Cached Pose
		if (x == FLinearColor(0,0,0,1))
		{
			return EDTGraphNodeTitleType::Black;
		}
		// Hardcoded: Animation Sequence Player
		if (x == FLinearColor(0.577580452, 0.127437681, 0.127437681))
		{
			return EDTGraphNodeTitleType::PlaySequence;
		}
		// Hardcoded: Animation Linked Layer
		if (x == FLinearColor(0.200000003, 0.0700000003, 0.600000024))
		{
			return EDTGraphNodeTitleType::LinkedLayer;
		}
		return EDTGraphNodeTitleType::Default;
	}
#pragma endregion

	UPROPERTY(EditAnywhere, meta = (Category = "Commands"))
	bool bRestoreDefaults;

#pragma region Properties

	UPROPERTY(Config, EditAnywhere, meta = (Category = "GraphEditor"))
	bool bOverrideGraphEditorSettings;

	UPROPERTY(Config, EditAnywhere,
		meta = (EditCondition = "bOverrideGraphEditorSettings", EditConditionHides, Category = "GraphEditor", GetOptions
			= "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName HorizontalSpacing;
	UPROPERTY(Config, EditAnywhere,
		meta = (EditCondition = "bOverrideGraphEditorSettings", EditConditionHides, Category = "GraphEditor", GetOptions
			= "Restyle.DefaultThemeSettings.GetSpacingOptions"))
	FName VerticalSpacing;

	UPROPERTY(Config, EditAnywhere,
		meta = (EditCondition = "bOverrideGraphEditorSettings", EditConditionHides, Category = "GraphEditor"))
	bool bUpdateIcons;


	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings", ClampMin = "0.25", ClampMax = "1.0"))
	float DisabledOpacity;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	FDTNode Node;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	FDTNodeCompact CompactNode;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	FDTVarNode VarNode;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	FDTCollapsedNode CollapsedNode;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	FDTOtherNodes OtherNodes; 
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings"))
	FDTCommentNode CommentNode;

	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings|Misc"))
	FDTCommentBubble CommentBubble;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings|Misc", ArraySizeEnum = "EDTNodeReportType"))
	FDTNodeReport NodeReports[(int)EDTNodeReportType::Num];
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings|Misc"))
	FDTEnabledStateWidget StateWidget;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Settings|Misc"))
	FDTAdvancedDisplay AdvancedDisplay;


	UPROPERTY(Config, EditAnywhere, meta = (Category = "Zoom"))
	bool bNewZoom;
	UPROPERTY(Config, EditAnywhere, meta = (Category = "Zoom", EditCondition="bNewZoom", EditConditionHides))
	FDTZoomSettings Zoom;

#pragma endregion
};

struct FRestyleZoomLevelsContainer : FZoomLevelsContainer
{
	FRestyleZoomLevelsContainer()
	{
		ZoomLevels = &UNodeRestyleSettings::GetM()->Zoom.ZoomLevels;
		LowerZoomLevel = UNodeRestyleSettings::GetM()->Zoom.LowerZoomLevelId;
	}

	float GetZoomAmount(int32 InZoomLevel) const override
	{
		if (!ZoomLevels->IsValidIndex(InZoomLevel)) return 1.0f;
		return (*ZoomLevels)[InZoomLevel].ZoomAmount;
	}

	int32 GetNearestZoomLevel(float InZoomAmount) const override
	{
		for (int32 ZoomLevelIndex = 0; ZoomLevelIndex < GetNumZoomLevels(); ++ZoomLevelIndex)
		{
			if (InZoomAmount <= GetZoomAmount(ZoomLevelIndex))
			{
				return ZoomLevelIndex;
			}
		}

		return GetDefaultZoomLevel();
	}

	FText GetZoomText(int32 InZoomLevel) const override
	{
		if (!ZoomLevels->IsValidIndex(InZoomLevel)) return FText::FromString("None");
		return (*ZoomLevels)[InZoomLevel].DisplayText;;
	}

	int32 GetNumZoomLevels() const override
	{
		return ZoomLevels->Num();
	}

	int32 GetDefaultZoomLevel() const override
	{
		return UNodeRestyleSettings::Get()->Zoom.DefaultZoomLevelId;
	}

	EGraphRenderingLOD::Type GetLOD(int32 InZoomLevel) const override
	{
		if (InZoomLevel <= LowerZoomLevel)return  EGraphRenderingLOD::LowDetail;
		return EGraphRenderingLOD::FullyZoomedIn;
	}

	TArray<FZoomLevelEntry>* ZoomLevels;
	int32 LowerZoomLevel;
};
