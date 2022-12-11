// Alexander (AgitoReiKen) Moskalenko (C) 2022

#include "SDefault_AnimationGraphNode.h" 
#include "Widgets/SBoxPanel.h"
#include "Layout/WidgetPath.h"
#include "Framework/Application/MenuStack.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "AnimGraphNode_Base.h"
#include "IDocumentation.h"
#include "AnimationEditorUtils.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Animation/AnimInstance.h"
#include "GraphEditorSettings.h"
#include "SLevelOfDetailBranchNode.h"
#include "Widgets/Layout/SSpacer.h"
#include "AnimationGraphSchema.h"
#include "AnimGraphNode_CustomProperty.h"
#include "BlueprintMemberReferenceCustomization.h"
#include "SGraphPin.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Brushes/SlateColorBrush.h"
#include "PropertyEditorModule.h"
#include "IPropertyRowGenerator.h"
#include "IDetailTreeNode.h"
#include "Restyle.h"

#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "SGraphPanel.h"
#include "Restyle/ThirdParty/AccessPrivate/AccessPrivate.h"

#include "Themes/Default/PinRestyleDefault.h"
#include "Restyle/ThirdParty/AccessPrivate/AccessPrivate.h"
#define LOCTEXT_NAMESPACE "AnimationGraphNode"

ACCESS_PRIVATE_FIELD(SAnimationGraphNode, FVector2D, LastHighDetailSize);
ACCESS_PRIVATE_FIELD(SAnimationGraphNode, TSharedPtr<SWidget>, IndicatorWidget);
ACCESS_PRIVATE_FIELD(SAnimationGraphNode, TSharedPtr<SWidget>, CachedContentArea);
void SDefault_AnimationGraphNode::Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode)
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

	ReconfigurePinWidgetsForPropertyBindings(CastChecked<UAnimGraphNode_Base>(GraphNode), SharedThis(this), [this](UEdGraphPin* InPin) { return FindWidgetForPin(InPin); });

	const FSlateBrush* ImageBrush = FAppStyle::Get().GetBrush(TEXT("Graph.AnimationFastPathIndicator"));
	
	access_private::IndicatorWidget(*this) =
		SNew(SImage)
		.Image(ImageBrush)
		.ToolTip(IDocumentation::Get()->CreateToolTip(LOCTEXT("AnimGraphNodeIndicatorTooltip", "Fast path enabled: This node is not using any Blueprint calls to update its data."), NULL, TEXT("Shared/GraphNodes/Animation"), TEXT("GraphNode_FastPathInfo")))
		.Visibility(EVisibility::Visible);


	PoseViewWidget = SNew(SDefault_PoseWatchOverlay, InNode);
	access_private::LastHighDetailSize(*this) = FVector2D::ZeroVector;
}

void SDefault_AnimationGraphNode::HandleNodeTitleChangedNew()
{
	if (TitleExtraText.IsValid())
	{
		TitleExtraText->MarkDirty();
	}
}

void SDefault_AnimationGraphNode::CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox)
{
	if (UAnimGraphNode_Base* AnimNode = CastChecked<UAnimGraphNode_Base>(GraphNode, ECastCheckedType::NullAllowed))
	{
		auto UseLowDetailNode = [this]()
		{
			return GetCurrentLOD() <= EGraphRenderingLOD::LowDetail;
		};

		// Insert above the error reporting bar
		MainBox->InsertSlot(FMath::Max(0, MainBox->NumSlots() - TagAndFunctionsSlotReverseIndex))
		.AutoHeight()
		.Padding(4.0f, 2.0f, 4.0f, 2.0f)
		[
			SNew(SVerticalBox)
			.IsEnabled_Lambda([this](){ return IsNodeEditable(); })
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				CreateNodeFunctionsWidgetNew(AnimNode, MakeAttributeLambda(UseLowDetailNode))
			]
		];

		MainBox->InsertSlot(FMath::Max(0, MainBox->NumSlots() - TagAndFunctionsSlotReverseIndex))
		.AutoHeight()
		.Padding(4.0f, 2.0f, 4.0f, 2.0f)
		[
			SNew(SVerticalBox)
			.IsEnabled_Lambda([this](){ return IsNodeEditable(); })
			+SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Right)
			[
				CreateNodeTagWidget(AnimNode, MakeAttributeLambda(UseLowDetailNode))
			]
		];
	}
}

TArray<FOverlayWidgetInfo> SDefault_AnimationGraphNode::GetOverlayWidgets(bool bSelected, const FVector2D& WidgetSize) const
{
	TArray<FOverlayWidgetInfo> Widgets;

	if (UAnimGraphNode_Base* AnimNode = CastChecked<UAnimGraphNode_Base>(GraphNode, ECastCheckedType::NullAllowed))
	{
		if (AnimNode->BlueprintUsage == EBlueprintUsage::DoesNotUseBlueprint)
		{
			const FSlateBrush* ImageBrush = FAppStyle::Get().GetBrush(TEXT("Graph.AnimationFastPathIndicator"));

			FOverlayWidgetInfo Info;
			Info.OverlayOffset = FVector2D(WidgetSize.X - (ImageBrush->ImageSize.X * 0.5f), -(ImageBrush->ImageSize.Y * 0.5f));
			Info.Widget = access_private::IndicatorWidget(*this);

			Widgets.Add(Info);
		}

		if (PoseViewWidget->IsPoseWatchValid())
		{
			FOverlayWidgetInfo Info;
			Info.OverlayOffset = PoseViewWidget->GetOverlayOffset();
			Info.Widget = PoseViewWidget;
			Widgets.Add(Info);
		}
	}

	return Widgets;
}

bool SDefault_AnimationGraphNode::UseLowDetailNodeContent() const
{
	if (access_private::LastHighDetailSize(*this).IsNearlyZero())
	{
		return false;
	}

	if (const SGraphPanel* MyOwnerPanel = GetOwnerPanel().Get())
	{
		return (MyOwnerPanel->GetCurrentLOD() <= EGraphRenderingLOD::LowestDetail);
	}
	return false;
}

FVector2D SDefault_AnimationGraphNode::GetLowDetailDesiredSize() const
{
	return access_private::LastHighDetailSize(*this);
}

TSharedRef<SWidget> SDefault_AnimationGraphNode::CreateTitleWidget(TSharedPtr<SNodeTitle> InNodeTitle)
{
	// hook up invalidation delegate
	UAnimGraphNode_Base* AnimGraphNode = CastChecked<UAnimGraphNode_Base>(GraphNode);
	AnimGraphNode->OnNodeTitleChangedEvent().AddSP(this, &SDefault_AnimationGraphNode::HandleNodeTitleChangedNew);

	return SDefault_AnimationGraphNodeRestyleBase::CreateTitleWidget(InNodeTitle);
}
TSharedRef<SWidget> SDefault_AnimationGraphNode::CreateNodeContentArea()
{
	access_private::CachedContentArea(*this) = SDefault_AnimationGraphNodeRestyleBase::CreateNodeContentArea();

	return SNew(SLevelOfDetailBranchNode)
		.UseLowDetailSlot(this, &SDefault_AnimationGraphNode::UseLowDetailNodeContent)
		.LowDetail()
		[
			SNew(SSpacer)
			.Size(this, &SDefault_AnimationGraphNode::GetLowDetailDesiredSize)
		]
		.HighDetail()
		[
			access_private::CachedContentArea(*this).ToSharedRef()
		];
}
  
template<typename ChildType, int At = 0, typename WidgetType>
TSharedRef<ChildType> GetChild(WidgetType Widget)
{
	auto x = Widget->GetChildren();
	auto y = x->GetChildAt(At);
	return StaticCastSharedRef<ChildType>(y);
}
ACCESS_PRIVATE_FIELD(SButton, FOnClicked, OnClicked);
ACCESS_PRIVATE_FIELD(SMenuAnchor, TPanelChildren<FBasicLayoutWidgetSlot>, Children);
// Widget used to allow functions to be viewed and edited on nodes
class SAnimNodeFunctionsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAnimNodeFunctionsWidget) {}

	SLATE_ATTRIBUTE(bool, UseLowDetail)

	SLATE_END_ARGS()
		PRAGMA_DISABLE_OPTIMIZATION
	void Construct(const FArguments& InArgs, UAnimGraphNode_Base* InNode)
	{
		UseLowDetail = InArgs._UseLowDetail;

		FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyRowGenerator = PropertyEditorModule.CreatePropertyRowGenerator(FPropertyRowGeneratorArgs());
		PropertyRowGenerator->RegisterInstancedCustomPropertyTypeLayout(FMemberReference::StaticStruct()->GetFName(), 
			FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FBlueprintMemberReferenceDetails::MakeInstance));
		PropertyRowGenerator->SetObjects({ InNode });

		TSharedPtr<SBox> Box;
		TSharedPtr<SVerticalBox> VerticalBox;

		/*ChildSlot
		[
			SAssignNew(GridPanel, SGridPanel)
		];*/
		const auto& AnimationStyle = UNodeRestyleSettings::Get()->OtherNodes.Animation;
		ChildSlot
		[
			SNew(SLevelOfDetailBranchNode)
			.UseLowDetailSlot(UseLowDetail)
			.HighDetail()
			[
				SAssignNew(Box, SBox)
				.VAlign(VAlign_Fill)
				.Padding(UDefaultThemeSettings::GetMargin(AnimationStyle.FunctionBinding.Padding))
				[
					SAssignNew(VerticalBox, SVerticalBox)
				]
			]
		];
	 
		Box->SetVisibility(EVisibility::Collapsed);

		// Add bound functions
		auto AddFunctionBindingWidget = [this, InNode, &Box, &VerticalBox, &AnimationStyle](FName InCategory, FName InMemberName)
		{
			Box->SetVisibility(EVisibility::Visible);

			// Find row
			TSharedPtr<IPropertyHandle> PropertyHandle;
			TSharedPtr<IDetailTreeNode> DetailTreeNode;

			for (const TSharedRef<IDetailTreeNode>& RootTreeNode : PropertyRowGenerator->GetRootTreeNodes())
			{
				if (RootTreeNode->GetNodeName() == InCategory)
				{
					TArray<TSharedRef<IDetailTreeNode>> Children;
					RootTreeNode->GetChildren(Children);

					for (int32 ChildIdx = 0; ChildIdx < Children.Num(); ChildIdx++)
					{
						TSharedPtr<IPropertyHandle> ChildPropertyHandle = Children[ChildIdx]->CreatePropertyHandle();
						if (ChildPropertyHandle.IsValid() && ChildPropertyHandle->GetProperty() && ChildPropertyHandle->GetProperty()->GetFName() == InMemberName)
						{
							DetailTreeNode = Children[ChildIdx];
							PropertyHandle = ChildPropertyHandle;
							PropertyHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateLambda([InNode]()
								{
									InNode->ReconstructNode();
								}));
							break;
						}
					}
				}
			}

			if (DetailTreeNode.IsValid() && PropertyHandle.IsValid())
			{
				DetailNodes.Add(DetailTreeNode);

				FNodeWidgets NodeWidgets = DetailTreeNode->CreateNodeWidgets(); 
				/*
				 * NameWidget Structure
				 * SLevelOfDetailBranchNode
				 *	SHorizontalBox
				 *		SBox
				 *			SPropertyNameWidget
				 *				SHorizontalBox
				 *					SBorder
				 *						SPropertyEditorTitle
				 *							STextBlock
				 */
				 
				TSharedRef<SWidget> NameWidget = NodeWidgets.NameWidget.ToSharedRef();
				TSharedRef<SWidget> ValueWidget = NodeWidgets.ValueWidget.ToSharedRef();
				FText NameWidgetText = FText::GetEmpty();
				bool bPinsRegistered = FRestyleModule::Get()->IsSubjectProviderRegistered("Default", ERestyleSubject::Pin);
				try {
					auto _Box = GetChild<SBox>(NameWidget);
					auto _PropNameWidget = GetChild<SWidget>(_Box);
					auto _HorizontalBox = GetChild<SHorizontalBox>(_PropNameWidget);
					auto _Border = GetChild<SBorder>(_HorizontalBox);
					auto _PropEditorTitle = GetChild<SWidget>(_Border);
					auto _TextBlock = GetChild<STextBlock>(_PropEditorTitle);
					NameWidgetText = _TextBlock->GetText(); 
				} catch (...)
				{
					checkf(false, L"SPropertyNameWidget's structure has been changed, code needs to be updated");
				}
				/* ValueWidget Structure
				 * SLevelOfDetailBranchNode
				 *	SConstrainedBox
				 *		 SHorizontalBox
				 *			SBox
				 *				SPropertyBinding
				 *					SHorizontalBox
				 *						 SComboButton
				 *						 SButton
				 *							 SImage
				 *
				 *
				 */
				TSharedRef<SWidget> FunctionWidget = SNullWidget::NullWidget;
				FText FunctionName = FText::FromString("");
				try {
					auto _Box = GetChild<SBox>(ValueWidget);
					auto _Box2 = GetChild<SBox>(_Box);
					auto _PropBinding = GetChild<SWidget>(_Box2);
					auto _HorizontalBox = GetChild<SHorizontalBox>(_PropBinding);
					auto _ComboButton = GetChild<SComboButton, 0>(_HorizontalBox);
					auto& _Children = access_private::Children(_ComboButton.Get());
					auto _ComboButton_Button = StaticCastSharedRef<SButton>(_Children.GetChildAt(0));
					auto _ComboButton_Button_HorizontalBox = GetChild<SHorizontalBox>(_ComboButton_Button);
					_ComboButton_Button->SetVisibility(EVisibility::Hidden);
					FunctionWidget = GetChild<SWidget>(_ComboButton_Button_HorizontalBox);
					auto _FW_TextBlock = GetChild<STextBlock, 1>(FunctionWidget);
					FunctionName = _FW_TextBlock->GetText();
					auto _Button = GetChild<SButton, 1>(_HorizontalBox);
					auto _Image = GetChild<SImage>(_Button);
				}
				catch (...)
				{
					checkf(false, L"SPropertyBinding's structure has been changed, code needs to be updated");
				}
				const FButtonStyle* ButtonStyle = bPinsRegistered
				? &FAppStyle::Get().GetWidgetStyle<FComboButtonStyle>(FPinRestyleStyles::ComboButton).ButtonStyle
				: &FAppStyle::Get().GetWidgetStyle<FButtonStyle>("Button")
				;
				bool bSpacing = VerticalBox->NumSlots() != 0;
				TSharedPtr<SButton> ReplacedButton = SNew(SButton)
				.Cursor(EMouseCursor::Hand)
				// Padding is in ButtonStyle
				.ButtonStyle(ButtonStyle)
				.HAlign(HAlign_Left)
				.ToolTipText(FunctionName)
				.OnClicked_Lambda([ValueWidget]() -> FReply
				{
					auto _Box = GetChild<SBox>(ValueWidget);
					auto _Box2 = GetChild<SBox>(_Box);
					auto _PropBinding = GetChild<SWidget>(_Box2);
					auto _HorizontalBox = GetChild<SHorizontalBox>(_PropBinding);
					auto _ComboButton = GetChild<SComboButton, 0>(_HorizontalBox);
					auto& _Children = access_private::Children(_ComboButton.Get());
					auto _ComboButton_Button = StaticCastSharedRef<SButton>(_Children.GetChildAt(0));
					auto _ComboButton_Button_HorizontalBox = GetChild<SHorizontalBox>(_ComboButton_Button);
					auto& OnClicked = access_private::OnClicked(_ComboButton_Button.Get());
					return OnClicked.Execute();
					})
				[
					FunctionWidget
				];
				uint16 IconSize = UDefaultThemeSettings::GetIconSize(AnimationStyle.FunctionBinding.GotoButton.Get().IconSize);
				TSharedPtr<SButton> GotoButton = SNew(SButton)
				.Cursor(EMouseCursor::Hand)
				.ButtonStyle(FAppStyle::Get(), FNodeRestyleStyles::AnimationNode_FunctionBinding_GotoButton)
				.OnClicked_Lambda([ValueWidget]()->FReply
				{
					auto _Box = GetChild<SBox>(ValueWidget);
					auto _Box2 = GetChild<SBox>(_Box);
					auto _PropBinding = GetChild<SWidget>(_Box2);
					auto _HorizontalBox = GetChild<SHorizontalBox>(_PropBinding);
					auto _Button = GetChild<SButton, 1>(_HorizontalBox);
					auto& OnClicked = access_private::OnClicked(_Button.Get());
					return OnClicked.Execute();
				})
				[
					SNew(SImage)
					.DesiredSizeOverride(FVector2D(IconSize))
					.ColorAndOpacity(FSlateColor::UseStyle())
					.Image(FAppStyle::Get().GetBrush("Icons.Search"))
				];

				float YSpacing = UDefaultThemeSettings::GetSpacing(AnimationStyle.FunctionBinding.SpacingY);
				float XSpacing = UDefaultThemeSettings::GetSpacing(AnimationStyle.FunctionBinding.SpacingX);
				VerticalBox->AddSlot().Padding(0, bSpacing ? YSpacing : 0, 0, 0)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SBox)
						.MinDesiredWidth(AnimationStyle.FunctionBinding.NameWidth)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.TextStyle(FAppStyle::Get(), "Graph.Node.PinName")
							.Text(NameWidgetText)
						]
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SBox)
						.WidthOverride(AnimationStyle.FunctionBinding.ValueWidth)
						[
							SNew(SOverlay)
							+SOverlay::Slot()
							[
								SNew(SBox)
								.RenderOpacity(0.0)
								.VAlign(VAlign_Center)
								.HAlign(HAlign_Center)
								[
									ValueWidget
								]
							]
							+SOverlay::Slot()
							[
								 ReplacedButton.ToSharedRef()
							]
						]
					]
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					.AutoWidth()
					.Padding(XSpacing, 0, 0, 0)
					[
						GotoButton.ToSharedRef()
					]
				];
			}
		};

		if (InNode->InitialUpdateFunction.ResolveMember<UFunction>(InNode->GetBlueprintClassFromNode()) != nullptr)
		{
			AddFunctionBindingWidget("Functions", GET_MEMBER_NAME_CHECKED(UAnimGraphNode_Base, InitialUpdateFunction));
		}
		if (InNode->BecomeRelevantFunction.ResolveMember<UFunction>(InNode->GetBlueprintClassFromNode()) != nullptr)
		{
			AddFunctionBindingWidget("Functions", GET_MEMBER_NAME_CHECKED(UAnimGraphNode_Base, BecomeRelevantFunction));
		}
		if (InNode->UpdateFunction.ResolveMember<UFunction>(InNode->GetBlueprintClassFromNode()) != nullptr)
		{
			AddFunctionBindingWidget("Functions", GET_MEMBER_NAME_CHECKED(UAnimGraphNode_Base, UpdateFunction));
		}

		if (DetailNodes.Num() == 0)
		{
			// If we didnt add a function binding, remove the row generator as we dont need it and its expensive (as it ticks)
			PropertyRowGenerator.Reset();
		}
	}
	PRAGMA_ENABLE_OPTIMIZATION
	// Property row generator used to display function properties on nodes
	TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;

	// Hold a reference to the root ptr of the details tree we use to display function properties
	TArray<TSharedPtr<IDetailTreeNode>> DetailNodes;

	// Attribute allowing LOD
	TAttribute<bool> UseLowDetail;
};

TSharedRef<SWidget> SDefault_AnimationGraphNode::CreateNodeFunctionsWidgetNew(UAnimGraphNode_Base* InAnimNode, TAttribute<bool> InUseLowDetail)
{
	return SNew(SAnimNodeFunctionsWidget, InAnimNode)
		.UseLowDetail(InUseLowDetail);
}
 
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "SPoseWatchOverlay"

const FSlateBrush* SDefault_PoseWatchOverlay::IconVisible = nullptr;
const FSlateBrush* SDefault_PoseWatchOverlay::IconNotVisible = nullptr;

void SDefault_PoseWatchOverlay::Construct(const FArguments& InArgs, UEdGraphNode* InNode)
{
	IconVisible = FAppStyle::GetBrush("Level.VisibleIcon16x");
	IconNotVisible = FAppStyle::GetBrush("Level.NotVisibleIcon16x");

	GraphNode = InNode;

	PoseWatch = AnimationEditorUtils::FindPoseWatchForNode(InNode);
	AnimationEditorUtils::OnPoseWatchesChanged().AddSP(this, &SDefault_PoseWatchOverlay::HandlePoseWatchesChanged);

	ChildSlot
	[
		SNew(SButton)
		.ToolTipText(LOCTEXT("TogglePoseWatchVisibility", "Click to toggle visibility"))
		.OnClicked(this, &SDefault_PoseWatchOverlay::TogglePoseWatchVisibility)
		.ButtonColorAndOpacity(this, &SDefault_PoseWatchOverlay::GetPoseViewColor)
		[
			SNew(SImage).Image(this, &SDefault_PoseWatchOverlay::GetPoseViewIcon)
		]
	];
}

void SDefault_PoseWatchOverlay::HandlePoseWatchesChanged(UAnimBlueprint* InAnimBlueprint, UEdGraphNode* InNode)
{
	PoseWatch = AnimationEditorUtils::FindPoseWatchForNode(GraphNode.Get());
}

FSlateColor SDefault_PoseWatchOverlay::GetPoseViewColor() const
{
	static constexpr float AlphaTemporary = 0.5f;
	static constexpr float AlphaPermanent = 0.9f;

	UPoseWatch* CurPoseWatch = PoseWatch.Get();
	if (CurPoseWatch)
	{
		TObjectPtr<UPoseWatchPoseElement> PoseElement = CurPoseWatch->GetFirstElementOfType<UPoseWatchPoseElement>();
		if (PoseElement)
		{
			FLinearColor OutColor = PoseElement->GetColor();
			OutColor.A = CurPoseWatch->GetShouldDeleteOnDeselect() ? AlphaTemporary : AlphaPermanent;
			return FSlateColor(OutColor);
		}
	}
	return FSlateColor(FColor::Black);
}

const FSlateBrush* SDefault_PoseWatchOverlay::GetPoseViewIcon() const
{
	return (PoseWatch.IsValid() && PoseWatch->GetIsVisible()) ? IconVisible : IconNotVisible;
}

FReply SDefault_PoseWatchOverlay::TogglePoseWatchVisibility()
{
	if (PoseWatch.IsValid())
	{
		PoseWatch->ToggleIsVisible();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FVector2D SDefault_PoseWatchOverlay::GetOverlayOffset() const
{
	return FVector2D(0 - (IconVisible->ImageSize.X * 0.5f), -(IconVisible->ImageSize.Y * 0.5f));
}

bool SDefault_PoseWatchOverlay::IsPoseWatchValid() const
{
	return PoseWatch.IsValid();
}

#undef LOCTEXT_NAMESPACE