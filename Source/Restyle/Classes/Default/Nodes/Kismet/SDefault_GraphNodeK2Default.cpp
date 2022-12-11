// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_GraphNodeK2Default.h"
#include "SDefault_GraphNodeK2Base.h"
#include "K2Node.h"
#include "KismetNodes/SGraphNodeK2Base.h"
#include "Internationalization/Culture.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SToolTip.h"
#include "SCommentBubble.h"
#include "SGraphPin.h"
#include "K2Node_Timeline.h"
#include "Kismet2/Breakpoint.h"
#include "IDocumentation.h"
#include "TutorialMetaData.h"
#include "Widgets/Layout/SBox.h"
#include "Default/Nodes/Common/SDefault_CommentBubble.h"
#include "Default/Nodes/Common/SDefault_NodeTitle.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Default/Nodes/Common/SDefault_ErrorText.h"
#include "Components/ScaleBox.h"
#include "Slate/SObjectWidget.h"
#include "Themes/Default/NodeRestyleDefault.h"
#include "Themes/Default/PinRestyleDefault.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"



void SDefault_GraphNodeK2Default::Construct(const FArguments& InArgs, UK2Node* InNode)
{
	GraphNode = InNode;
	auto Style = UNodeRestyleSettings::Get();
	CachedState = IsInvalid() ? EDTGraphNodeState::Invalid : EDTGraphNodeState::Normal;
	CachedOutlineWidth = UDefaultThemeSettings::GetOutlineWidth(
		Style->Node.GetTypeData(GetNodeType()).GetState(CachedState).Body.Get().OutlineWidth
	);
	EnabledStateWidgetAdditionalPadding = UDefaultThemeSettings::GetMargin(Style->StateWidget.Padding);
	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}
 
void SDefault_GraphNodeK2Default::UpdateCompactNode_New()
{
	UpdateState();
	LastUpdatedState = CachedState;
	const auto& State = UNodeRestyleSettings::Get()->CompactNode.States.GetState(LastUpdatedState);
	EDTGraphNodeTitleType TitleType = GetNodeType();
	const auto& CompactNode = UNodeRestyleSettings::Get()->CompactNode;
	float ContentSpacing = UDefaultThemeSettings::GetSpacing(CompactNode.ContentSpacing);
	{
		InputPins.Empty();
		OutputPins.Empty();

		RightNodeBox.Reset();
		LeftNodeBox.Reset();
	}
	SetupRenderOpacity();
	ContentScale.Bind(this, &SGraphNode::GetContentScale);

	FGraphNodeMetaData TagMeta(TEXT("Graphnode"));
	PopulateMetaTag(&TagMeta);
	 
	TSharedRef<SOverlay> NodeOverlay = SNew(SOverlay);
	TSharedRef<SOverlay> PinOverlay = SNew(SOverlay);
	TSharedRef<SWidget> AlternativeTitleWidget = SNullWidget::NullWidget;

	auto AddIdentificationContent = [this, &NodeOverlay, &State, &TitleType, &CompactNode, &AlternativeTitleWidget]()
	{
		TSharedPtr<SDefault_NodeTitle> NodeTitle = SNew(SDefault_NodeTitle, GraphNode, FLinearColor::Black,
		                                                FNodeRestyleStyles::GraphNode_Title_ExtraText)
			.Text(this, &SDefault_GraphNodeK2Base::GetNodeCompactTitle);
		TSharedPtr<SWidget> Image = GraphNode->CreateNodeImage();
		//CastNode
		//FText CastSymbol = NSLOCTEXT("K2Node", "CastSymbol", "\x2022");
		bool bIsMacro = false;
		bool bIsFunc = false;
		switch (TitleType)
		{
		case EDTGraphNodeTitleType::Function:
		case EDTGraphNodeTitleType::PureFunction:
			bIsFunc = true;
			break;
		case EDTGraphNodeTitleType::ExecBranch:
			bIsMacro = true;
			break;
		default: break;
		}
		float LenValue = bIsFunc ? CompactNode.AltFuncIfGreater : CompactNode.AltMacroIfGreater;
		FString NodeTitleStr = NodeTitle->GetHeadTitle().ToString();
		bool bAlternative = /*LenValue != -1 && */ NodeTitleStr.Len() > LenValue;
		bool bIsOneSymbolText = NodeTitleStr.Len() == 1;
		//Map, Set, Array Nodes Check
		if (!Image.IsValid())
		{
			FName Id = "";
			FLinearColor IdColor = FLinearColor::Transparent;
			if (bIsFunc)
			{
				Id = "Kismet.AllClasses.FunctionIcon";
				IdColor = bAlternative
					          ? CompactNode.AlternativeTitle.FunctionIconColor.Get()
					          : CompactNode.Title.FunctionIconColor.Get();
			}
			else if (bIsMacro)
			{
				Id = "GraphEditor.Macro_16x";
				IdColor = bAlternative
					          ? CompactNode.AlternativeTitle.MacroIconColor.Get()
					          : CompactNode.Title.MacroIconColor.Get();
			}

			Image = SNew(SImage).Image(FAppStyle::Get().GetBrush(Id)).ColorAndOpacity(IdColor);
		}

		if (bAlternative)
		{
			//@formatter:off
			auto Padding = UDefaultThemeSettings::GetMargin(CompactNode.AlternativeTitle.Padding);
			float ItemSpacing = UDefaultThemeSettings::GetSpacing(CompactNode.AlternativeTitle.ItemSpacing);
			AlternativeTitleWidget = SNew(SBox).Padding(Padding)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .HAlign(HAlign_Fill)
				  .VAlign(VAlign_Top)
				[
					// MIDDLE
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					  .HAlign(HAlign_Center)
					  .AutoHeight()
					[
						SAssignNew(CompactTitleTextBlock, STextBlock)
						.TextStyle(FEditorStyle::Get(), FNodeRestyleStyles::GraphNode_Compact_AlternativeTitle)
						.ColorAndOpacity(State.TitleColor.Get())
						//.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
						.Text(NodeTitle->GetHeadTitle())
						.WrapTextAt(CompactNode.AlternativeTitle.WrapAt)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						NodeTitle.ToSharedRef()
					]
				]
				+ SHorizontalBox::Slot()
				  .HAlign(HAlign_Right)
				  .VAlign(VAlign_Center)
				  .Padding(ItemSpacing, 0, 0, 0)
				[
					SNew(SScaleBox)
					.RenderTransform(FSlateRenderTransform(FScale2D(1.0f)))
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.Stretch(EStretch::ScaleToFit)
					.StretchDirection(EStretchDirection::Both)
					[
						Image.ToSharedRef()
					]
				]
			];
			//@formatter:on
		}
		else
		{
			NodeOverlay->AddSlot()
			           .HAlign(HAlign_Fill)
			           .VAlign(VAlign_Fill)
			           .Padding(0.f)
			[
				SNew(SScaleBox)
				.RenderTransform(FSlateRenderTransform(FScale2D(.5f)))
				.RenderTransformPivot(.5f)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Stretch(EStretch::ScaleToFit)
				.StretchDirection(EStretchDirection::Both)
				[
					Image.ToSharedRef()
				]
			];
			//@formatter:off 
			auto Padding = UDefaultThemeSettings::GetMargin(CompactNode.Title.Padding);
			NodeOverlay->AddSlot()
			           .HAlign(HAlign_Center)
			           .VAlign(VAlign_Center)
			           .Padding(Padding)
			[
				// MIDDLE
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				  .HAlign(HAlign_Center)
				  .AutoHeight()
				[
					SAssignNew(CompactTitleTextBlock, STextBlock)
					.TextStyle(FEditorStyle::Get(),
					           bIsOneSymbolText
						           ? FNodeRestyleStyles::GraphNode_Compact_Title_OneSymbol
						           : FNodeRestyleStyles::GraphNode_Compact_Title)
				.ColorAndOpacity(State.TitleColor.Get())
				//.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
				.Text(NodeTitle->GetHeadTitle())
				.WrapTextAt(CompactNode.Title.WrapAt)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					NodeTitle.ToSharedRef()
				]
			];
			//@formatter:on
		}
	};
	AddIdentificationContent();

	PinOverlay->AddSlot()
	          .HAlign(HAlign_Fill)
	          .VAlign(VAlign_Top)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SAssignNew(LeftNodeBox, SVerticalBox)
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0)
		[
			SNew(SSpacer)
			.Size(ContentSpacing)

		] + SHorizontalBox::Slot()
		.AutoWidth()
		[
			SAssignNew(RightNodeBox, SVerticalBox)
		]
	];
	NodeOverlay->AddSlot()
	[
		SNew(SBox)
			.Padding(0)
		.MinDesiredWidth(CompactNode.MinWidth)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			  .Padding(0)
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			[
				AlternativeTitleWidget
			]
			+ SVerticalBox::Slot()
			  .Padding(0)
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			[
				PinOverlay
			]
		]
	];
	auto MakeInnerVerticalBox = [this, &NodeOverlay, &State]()-> TSharedRef<SVerticalBox>
	{
		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				// NODE CONTENT AREA
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SAssignNew(CompactBody, SImage)
					.Image(FEditorStyle::GetBrush(FNodeRestyleStyles::GraphNode_Compact_Body(CachedState)))
				]
				+ SOverlay::Slot()
				.Padding(0.f)
				[
					NodeOverlay
				]
			];
	};

	TSharedRef<SVerticalBox> InnerVerticalBox = MakeInnerVerticalBox();

	auto AddEnabledStateWidget = [this, &InnerVerticalBox]()
	{
		
		EnabledStateWidget = CreateEnabledStateWidget();
		if (EnabledStateWidget.IsValid())
		{
			InnerVerticalBox->AddSlot()
			                .AutoHeight()
			                .HAlign(HAlign_Fill)
			                .VAlign(VAlign_Top)
			[
				SAssignNew(EnabledStateWidgetBox, SBox)
				.Padding(GetEnabledStateWidgetPadding())
				[
					EnabledStateWidget.ToSharedRef()
				]
			];
		} 
	};
	AddEnabledStateWidget();

	auto AddErrorReporting = [this, &InnerVerticalBox]()
	{
		SetupErrorReporting_New();
		InnerVerticalBox->AddSlot()
		                .AutoHeight()
		                .Padding(0)
		[
			ErrorReporting->AsWidget()
		];
	};
	AddErrorReporting();


	auto Style = UNodeRestyleSettings::Get();
	auto AddComment = [this, Style]()
	{
		// Create comment bubble
		TSharedPtr<SDefault_CommentBubble> CommentBubble;

		SAssignNew(CommentBubble, SDefault_CommentBubble)
			.GraphNode(GraphNode)
			.Text(this, &SGraphNode::GetNodeComment)
			.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
			.AllowPinning(true)
			.EnableTitleBarBubble(true)
			.EnableBubbleCtrls(true)
			.GraphLOD(this, &SGraphNode::GetCurrentLOD)
			.IsGraphNodeHovered(this, &SGraphNodeK2Base::IsHovered);

		GetOrAddSlot(ENodeZone::TopCenter)
			.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
			.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
			.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
			.VAlign(VAlign_Top)
			[
				CommentBubble.ToSharedRef()
			];
	};
	AddComment();
	this->GetOrAddSlot(ENodeZone::Center)
	    .HAlign(HAlign_Center)
	    .VAlign(VAlign_Center)
	[
		InnerVerticalBox
	];

	CreatePinWidgets();

	// Hide pin labels
	for (auto InputPin : this->InputPins)
	{
		if (InputPin->GetPinObj()->ParentPin == nullptr)
		{
			InputPin->SetShowLabel(false);
		}
	}

	for (auto OutputPin : this->OutputPins)
	{
		if (OutputPin->GetPinObj()->ParentPin == nullptr)
		{
			OutputPin->SetShowLabel(false);
		}
	}

	CreateInputSideAddButton(LeftNodeBox);
	CreateOutputSideAddButton(RightNodeBox);
}

void SDefault_GraphNodeK2Default::UpdateGraphNode()
{
	 
	UK2Node* K2Node = CastChecked<UK2Node>(GraphNode);
	if (K2Node->ShouldDrawCompact())
	{
		UpdateCompactNode_New();
	}
	else
	{
		SDefault_GraphNodeK2Base::UpdateGraphNode();
	}
}

void SDefault_GraphNodeK2Default::OnStateUpdated(EDTGraphNodeState NewState)
{
	UK2Node* K2Node = CastChecked<UK2Node>(GraphNode);
	const bool bCompactMode = K2Node->ShouldDrawCompact();
	if (bCompactMode)
	{
		auto* Style = UNodeRestyleSettings::Get();
		const auto& State = Style->CompactNode.States.GetState(CachedState);
		if (CompactTitleTextBlock.IsValid())
		{
			CompactTitleTextBlock->SetColorAndOpacity(State.TitleColor.Get());
		}
		if (CompactBody.IsValid())
		{
			auto Body = FEditorStyle::GetBrush(FNodeRestyleStyles::GraphNode_Compact_Body(CachedState));
			CachedOutlineWidth = Body->OutlineSettings.Width;
			CompactBody->SetImage(Body);
		}
	}
	else
	{
		EDTGraphNodeTitleType TitleType = GetNodeType();
		auto* Style = UNodeRestyleSettings::Get();
		const auto& State = Style->Node.GetTypeData(TitleType).GetState(CachedState);
		if (MainBackground.IsValid())
		{
			auto Body = FAppStyle::Get().GetBrush(FNodeRestyleStyles::GraphNode_Body(TitleType, CachedState));
			CachedOutlineWidth = Body->OutlineSettings.Width;
			MainBackground->SetImage(Body);
		}

		if (TitleIcon.IsValid())
		{
			TitleIcon->SetColorAndOpacity(State.Title.Icon.Get());
		}
		if (MainTitleBorder.IsValid())
		{
			auto Body = FAppStyle::Get().
				GetBrush(FNodeRestyleStyles::GraphNode_Title_Body(TitleType, CachedState));
			MainTitleBorder->SetBorderImage(Body);
			MainTitleBorder->SetBorderBackgroundColor(State.Title.Background.Get());
		}
		if (InlineEditableText.IsValid())
		{
			InlineEditableText->SetColorAndOpacity(State.Title.MainText.Get());
		}
		if (TitleExtraText.IsValid() && TitleExtraText->ExtraTextBlock.IsValid())
		{
			TitleExtraText->ExtraTextBlock->SetColorAndOpacity(State.Title.ExtraText.Get());
		}
		if (EnabledStateWidgetBox.IsValid())
		{
			EnabledStateWidgetBox->SetPadding(GetEnabledStateWidgetPadding());
		}
	}
}
 