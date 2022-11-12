// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once
//#include "KismetPins/SControlRigGraphPinCurveFloat.h"
//#include "KismetPins/SControlRigGraphPinNameList.h"
//#include "KismetPins/SControlRigGraphPinParameterName.h"
//#include "KismetPins/SControlRigGraphPinVariableBinding.h"
//#include "KismetPins/SControlRigGraphPinVariableName.h"
//#include "KismetPins/SLiveLinkSubjectNameGraphPin.h"
//#include "KismetPins/SLiveLinkSubjectRepresentationGraphPin.h"
//#include "KismetPins/SPrimaryAssetIdGraphPin.h"
//#include "KismetPins/SPrimaryAssetTypeGraphPin.h"
//#include "KismetPins/SGameplayTagQueryGraphPin.h"
//#include "KismetPins/SNiagaraGraphPinNumeric.h"
//#include "KismetPins/SNiagaraGraphPinAdd.h"
//#include "KismetPins/SDataRegistryTypeGraphPin.h"
//#include "KismetPins/SGameplayAttributeGraphPin.h"
//#include "KismetPins/SDMXEntityReferenceGraphPin.h"
//#include "KismetPins/SDynamicNameListGraphPin<TStructType>.h"
//#include "KismetPins/SNullGraphPin.h"
//#include "KismetPins/SDMXPixelMappingComponentPin<TComponentClass>.h"
//#include "KismetPins/SDMXInputPortReferenceGraphPin.h"
//#include "KismetPins/SDMXOutputPortReferenceGraphPin.h"
//#include "KismetPins/SGraphPinAI.h"
//#include "KismetPins/SGraphPinPose.h"
//#include "KismetPins/SStateMachineOutputPin.h"
//#include "KismetPins/SMotionControllerSourceGraphPin.h"
//#include "KismetPins/SCopyNodeGraphPin.h"
#include "KismetPins/SGraphPinCollisionProfile.h"
#include "KismetPins/SGraphPinEnum.h"
#include "KismetPins/SGraphPinIndex.h"
#include "KismetPins/SGraphPinKey.h"
#include "MaterialPins/SGraphPinMaterialInput.h"
//#include "KismetPins/SGraphPinKnot.h"
#include "KismetPins/SGraphPinColor.h"
//#include "KismetPins/SGraphPinNum<NumericType>.h"
#include "KismetPins/SGraphPinObject.h"
#include "KismetPins/SGraphPinStructInstance.h"
#include "KismetPins/SGraphPinNum.h"
#include "SNameComboBox.h"
#include "STextPropertyEditableTextBox.h"
//#include "KismetPins/SGraphPinNameList.h"
//#include "KismetPins/SPhysicsAssetGraphNodeOutputPin.h"
//
//
//class SDefault_ControlRigGraphPinCurveFloat : public SControlRigGraphPinCurveFloat
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_ControlRigGraphPinCurveFloat) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_ControlRigGraphPinNameList : public SControlRigGraphPinNameList
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_ControlRigGraphPinNameList) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_ControlRigGraphPinParameterName : public SControlRigGraphPinParameterName
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_ControlRigGraphPinParameterName) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_ControlRigGraphPinVariableBinding : public SControlRigGraphPinVariableBinding
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_ControlRigGraphPinVariableBinding) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_ControlRigGraphPinVariableName : public SControlRigGraphPinVariableName
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_ControlRigGraphPinVariableName) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_LiveLinkSubjectNameGraphPin : public SLiveLinkSubjectNameGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_LiveLinkSubjectNameGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_LiveLinkSubjectRepresentationGraphPin : public SLiveLinkSubjectRepresentationGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_LiveLinkSubjectRepresentationGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_PrimaryAssetIdGraphPin : public SPrimaryAssetIdGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_PrimaryAssetIdGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_PrimaryAssetTypeGraphPin : public SPrimaryAssetTypeGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_PrimaryAssetTypeGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_GameplayTagQueryGraphPin : public SGameplayTagQueryGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_GameplayTagQueryGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_NiagaraGraphPinNumeric : public SNiagaraGraphPinNumeric
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_NiagaraGraphPinNumeric) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_NiagaraGraphPinAdd : public SNiagaraGraphPinAdd
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_NiagaraGraphPinAdd) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_DataRegistryTypeGraphPin : public SDataRegistryTypeGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_DataRegistryTypeGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_GameplayAttributeGraphPin : public SGameplayAttributeGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_GameplayAttributeGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_DMXEntityReferenceGraphPin : public SDMXEntityReferenceGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_DMXEntityReferenceGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_DynamicNameListGraphPin<TStructType> : public SDynamicNameListGraphPin<TStructType>
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_DynamicNameListGraphPin<TStructType>) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_NullGraphPin : public SNullGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_NullGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_DMXPixelMappingComponentPin<TComponentClass> : public SDMXPixelMappingComponentPin<TComponentClass>
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_DMXPixelMappingComponentPin<TComponentClass>) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_DMXInputPortReferenceGraphPin : public SDMXInputPortReferenceGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_DMXInputPortReferenceGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_DMXOutputPortReferenceGraphPin : public SDMXOutputPortReferenceGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_DMXOutputPortReferenceGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_GraphPinAI : public SDefault_GraphPinAI
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_GraphPinAI) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_GraphPinPose : public SDefault_GraphPinPose
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_GraphPinPose) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_StateMachineOutputPin : public SStateMachineOutputPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_StateMachineOutputPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_MotionControllerSourceGraphPin : public SMotionControllerSourceGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_MotionControllerSourceGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_CopyNodeGraphPin : public SCopyNodeGraphPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_CopyNodeGraphPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_GraphPinCollisionProfile : public SDefault_GraphPinCollisionProfile
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_GraphPinCollisionProfile) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
#include "Default/Widgets/SDefault_Widgets.h"
#include "Themes/Default/PinRestyleDefault.h"
#include "Default/Widgets/SDefault_KeySelector.h"
//};
 
class SDefault_GraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPin)
		: _PinLabelStyle(NAME_DefaultPinLabelStyle)
		, _ButtonTextPadding(FMargin(0))
	{
	}

	SLATE_ARGUMENT(FName, PinLabelStyle)
		SLATE_ARGUMENT(bool, UsePinColorForText)
		SLATE_ATTRIBUTE(FMargin, ButtonTextPadding)
	SLATE_END_ARGS()

	SDefault_GraphPin();
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
protected:
	virtual FSlateColor GetPinTextColor() const override;
	virtual const FSlateBrush* GetPinIcon() const override;
	virtual FSlateColor GetPinColor() const override;
	const FSlateBrush* GetSecondaryPinIcon_New() const;
	FSlateColor GetSecondaryPinColor_New() const;
	virtual TSharedRef<SWidget> GetLabelWidget(const FName& InPinLabelStyle) override;
	virtual const FSlateBrush* GetPinStatusIcon() const override;
	const FSlateBrush* CachedImg_SetPin_Connected;
	const FSlateBrush* CachedImg_SetPin_Disconnected;
	const FSlateBrush* CachedImg_MapPin_Value_Connected;
	const FSlateBrush* CachedImg_MapPin_Value_Disconnected;
	FSlateColor DiffingColor;
	FSlateColor OrphanedColor;
	FSlateColor NormalColor;
	FSlateColor NonEditableDiffingColor;
	FSlateColor NonEditableOrphanedColor;
	FSlateColor NonEditableNormalColor;
	FLinearColor PinTypeColor;
	FLinearColor NonEditablePinTypeColor;
	FLinearColor SecPinTypeColor;
	FLinearColor NonEditableSecPinTypeColor;
	const FSlateBrush* CachedImg_WatchedPinIcon;
};

class SDefault_GraphPinCollisionProfile : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinCollisionProfile)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;

	void OnSelectionChanged(TSharedPtr<FName> NameItem, ESelectInfo::Type SelectInfo);
	void OnComboBoxOpening();

	TSharedPtr<FName> GetSelectedName() const;

	void SetPropertyWithName(const FName& Name);
	void GetPropertyAsName(FName& OutName) const;

protected:
	TArray<TSharedPtr<FName>> NameList;
	TSharedPtr<SDefault_NameComboBox> NameComboBox;
};

template <typename NumericType>
class SDefault_GraphPinNum : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinNum)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
	}

protected:
	// SGraphPin interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override
	{
		return SNew(SBox)
			.MinDesiredWidth(18)
			.MaxDesiredWidth(400)
		[
			SNew(SNumericEntryBox<NumericType>)
				.EditableTextBoxStyle(FEditorStyle::Get(), FPinRestyleStyles::Graph_EditableTextBox)
				.BorderForegroundColor(FSlateColor::UseForeground())
				.Visibility(this, &SDefault_GraphPinNum::GetDefaultValueVisibility)
				.IsEnabled(this, &SDefault_GraphPinNum::GetDefaultValueIsEditable)
				.Value(this, &SDefault_GraphPinNum::GetNumericValue)
				.OnValueCommitted(this, &SDefault_GraphPinNum::SetNumericValue)
		];
	}

	TOptional<NumericType> GetNumericValue() const
	{
		NumericType Num = NumericType();
		LexFromString(Num, *GraphPinObj->GetDefaultAsString());
		return Num;
	}

	void SetNumericValue(NumericType InValue, ETextCommit::Type CommitType)
	{
		if (GraphPinObj->IsPendingKill())
		{
			return;
		}

		const FString TypeValueString = LexToString(InValue);
		if (GraphPinObj->GetDefaultAsString() != TypeValueString)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeNumberPinValue",
			                                               "Change Number Pin Value"));
			GraphPinObj->Modify();

			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, *TypeValueString);
		}
	}
};

class SDefault_GraphPinInteger : public SDefault_GraphPinNum<int32>
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinInteger)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
protected:
	//~ Begin SGraphPinString Interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	//~ End SGraphPinString Interface
};

class SDefault_GraphPinObject : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinObject)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	virtual bool DoesWidgetHandleSettingEditingEnabled() const override { return true; }
	//~ End SGraphPin Interface

	/** Delegate to be called when the use current selected item in asset browser button is clicked */
	virtual FOnClicked GetOnUseButtonDelegate();
	/** Delegate to be called when the browse for item button is clicked */
	virtual FOnClicked GetOnBrowseButtonDelegate();

	/** Clicked Use button */
	virtual FReply OnClickUse();
	/** Clicked Browse button */
	virtual FReply OnClickBrowse();
	/** Get text tooltip for object */
	FText GetObjectToolTip() const;
	/** Get text tooltip for object */
	FString GetObjectToolTipAsString() const;
	/** Get string value for object */
	FText GetValue() const;
	/** Get name of the object*/
	FText GetObjectName() const;
	/** Get default text for the picker combo */
	virtual FText GetDefaultComboText() const;
	/** Allow self pin widget */
	virtual bool AllowSelfPinWidget() const { return true; }
	/** True if this specific pin should be treated as a self pin */
	virtual bool ShouldDisplayAsSelfPin() const;
	/** Generate asset picker window */
	virtual TSharedRef<SWidget> GenerateAssetPicker();
	/** Called to validate selection from picker window */
	virtual void OnAssetSelectedFromPicker(const struct FAssetData& AssetData);
	/** Called when enter is pressed when items are selected in the picker window */
	void OnAssetEnterPressedInPicker(const TArray<FAssetData>& InSelectedAssets);

	/** Used to update the combo button text */
	FText OnGetComboTextValue() const;
	/** Combo Button Color and Opacity delegate */
	FSlateColor OnGetComboForeground() const;
	/** Button Color and Opacity delegate */
	FSlateColor OnGetWidgetForeground() const;
	/** Button Color and Opacity delegate */
	FSlateColor OnGetWidgetBackground() const;

	/** Returns asset data of currently selected object, if bRuntimePath is true this will include _C for blueprint classes, for false it will point to UBlueprint instead */
	virtual const FAssetData& GetAssetData(bool bRuntimePath) const;

protected:
	/** Object manipulator buttons. */
	TSharedPtr<SButton> UseButton;
	TSharedPtr<SButton> BrowseButton;

	/** Menu anchor for opening and closing the asset picker */
	TSharedPtr<class SMenuAnchor> AssetPickerAnchor;

	/** Cached AssetData of object selected */
	mutable FAssetData CachedAssetData;
};

class SDefault_GraphPinClass : public SDefault_GraphPinObject
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinClass)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
	void SetAllowAbstractClasses(bool bAllow) { bAllowAbstractClasses = bAllow; }
protected:
	// Called when a new class was picked via the asset picker
	void OnPickedNewClass(UClass* ChosenClass);

	//~ Begin SGraphPinObject Interface
	virtual FReply OnClickUse() override;
	virtual bool AllowSelfPinWidget() const override { return false; }
	virtual TSharedRef<SWidget> GenerateAssetPicker() override;
	virtual FText GetDefaultComboText() const override;
	virtual FOnClicked GetOnUseButtonDelegate() override;
	virtual const FAssetData& GetAssetData(bool bRuntimePath) const override;
	//~ End SGraphPinObject Interface

	/** Cached AssetData without the _C */
	mutable FAssetData CachedEditorAssetData;

	/** Whether abstract classes should be filtered out in the class viewer */
	bool bAllowAbstractClasses;
};

class SDefault_GraphPinStruct : public SDefault_GraphPinObject
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinStruct)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	// Called when a new struct was picked via the asset picker
	void OnPickedNewStruct(const UScriptStruct* ChosenStruct);

	//~ Begin SGraphPinObject Interface
	virtual FReply OnClickUse() override;
	virtual bool AllowSelfPinWidget() const override { return false; }
	virtual TSharedRef<SWidget> GenerateAssetPicker() override;
	virtual FText GetDefaultComboText() const override;
	virtual FOnClicked GetOnUseButtonDelegate() override;
};

class SDefault_GraphPinEnum : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinEnum)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	/**
	 *	Function to create class specific widget.
	 *
	 *	@return Reference to the newly created widget object
	 */
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;

private:
	int32 GetSelectedEnum() const;
	/**
	 *	Function to get current string associated with the combo box selection
	 *
	 *	@return currently selected string
	 */
	FString OnGetText() const;

	/**
	 *	Function to generate the list of indexes from the enum object
	 *
	 *	@param OutComboBoxIndexes - Int array reference to store the list of indexes
	 */
	void GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes);

	/**
	 *	Function to set the newly selected index
	 *
	 * @param NewSelection The newly selected item in the combo box
	 * @param SelectInfo Provides context on how the selection changed
	 */
	void ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo);

	/**
	 * Returns the friendly name of the enum at index EnumIndex
	 *
	 * @param EnumIndex	- The index of the enum to return the friendly name for
	 */
	FText OnGetFriendlyName(int32 EnumIndex);

	/**
	 * Returns the tooltip of the enum at index EnumIndex
	 *
	 * @param EnumIndex	- The index of the enum to return the tooltip for
	 */
	FText OnGetTooltip(int32 EnumIndex);

	TSharedPtr<SDefault_IndexComboBox> ComboBox;
};

class SDefault_GraphPinIndex : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinIndex)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

	FEdGraphPinType OnGetPinType() const;
	void OnTypeChanged(const FEdGraphPinType& PinType);

protected:
	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	//~ End SGraphPin Interface
};

class SDefault_GraphPinKey : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinKey)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	/**
	 *	Function to create class specific widget.
	 *
	 *	@return Reference to the newly created widget object
	 */
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;

private:
	/** Gets the current Key being edited. */
	TOptional<FKey> GetCurrentKey() const;

	/** Updates the pin default when a new key is selected. */
	void OnKeyChanged(TSharedPtr<FKey> SelectedKey);

	FKey SelectedKey;
};

class SDefault_GraphPinText : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinText)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
};

class SDefault_GraphPinMaterialInput : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinMaterialInput)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	//~ Begin SGraphPin Interface
	virtual FSlateColor GetPinColor() const override;
	//~ End SGraphPin Interface
};

//class SDefault_GraphPinKnot : public SDefault_GraphPinKnot
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_GraphPinKnot) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};

class SDefault_GraphPinBool : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinBool)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	//~ End SGraphPin Interface

	/** Determine if the check box should be checked or not */
	ECheckBoxState IsDefaultValueChecked() const;

	/** Called when check box is changed */
	void OnDefaultValueCheckBoxChanged(ECheckBoxState InIsChecked);
};

class SDefault_GraphPinColor : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinColor)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

	/** Return the current color value stored in the pin */
	FLinearColor GetColor() const;

protected:
	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	//~ End SGraphPin Interface

	/** Called when clicking on the color button */
	FReply OnColorBoxClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

	/** Called when the color picker commits a color value */
	void OnColorCommitted(FLinearColor color);


private:
	/** Current selected color */
	FLinearColor SelectedColor;
	TSharedPtr<SWidget> DefaultValueWidget;
};

class SDefault_GraphPinExec : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinExec)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	virtual const FSlateBrush* GetPinIcon() const override;
	//~ End SGraphPin Interface

	void CachePinIcons();

	const FSlateBrush* CachedImg_Pin_ConnectedHovered;
	const FSlateBrush* CachedImg_Pin_DisconnectedHovered;
};

//
//class SDefault_GraphPinNum<NumericType> : public SDefault_GraphPinNum<NumericType>
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_GraphPinNum<NumericType>) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
class SDefault_GraphPinString : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinString)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	//~ End SGraphPin Interface

	FText GetTypeInValue() const;
	virtual void SetTypeInValue(const FText& NewTypeInValue, ETextCommit::Type CommitInfo);

	/** @return True if the pin default value field is read-only */
	bool GetDefaultValueIsReadOnly() const;
};

class SDefault_GraphPinStructInstance : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinStructInstance)
			: _StructEditWrapper(nullptr)
		{
		}

		SLATE_ARGUMENT(const UScriptStruct*, StructEditWrapper)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	//~ Begin SGraphPin Interface
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	//~ End SGraphPin Interface

	/** Parses the struct ata from the pin to fill in the struct instance */
	virtual void ParseDefaultValueData();

	/** Call to push changes from edit instance to pin */
	virtual void SaveDefaultValueData();

	/** Refreshes cached description and edit data after an edit change */
	virtual void RefreshCachedData();

	/** Creates widget used to edit the struct instance */
	virtual TSharedRef<SWidget> GetEditContent();

	/** Creates widget for displaying preview on the pin */
	virtual TSharedRef<SWidget> GetDescriptionContent();

	/** Slate accessor to shows cached description value */
	virtual FText GetCachedDescriptionText() const;

	/** Returns the base instance inside EditStruct, if null this is assumed to be a subclass that overrides other functions */
	virtual FPinStructEditWrapper* GetEditWrapper() const;

	/** Called when struct is modified by the details view */
	virtual void PropertyValueChanged(const FPropertyChangedEvent& PropertyChangedEvent);


	/** Combo Button widget used to show edit content */
	TSharedPtr<SComboButton> ComboButton;

	/** Instance of FPinStructEditWrapper that wraps what we actually want to edit */
	TSharedPtr<FStructOnScope> EditWrapperInstance;

	/** Details view that points into EditWrapperInstance */
	TSharedPtr<IStructureDetailsView> StructureDetailsView;

	/** Cached description text */
	FText CachedDescription;
};

class SDefault_GraphPinVector : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinVector)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
protected:
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
private:
	// Enum values to identify text boxes.
	enum ETextBoxIndex
	{
		TextBox_0,
		TextBox_1,
		TextBox_2,
	};

	FString GetCurrentValue_0() const;

	FString GetCurrentValue_1() const;

	FString GetCurrentValue_2() const;

	FString GetValue(ETextBoxIndex Index) const;

	void OnChangedValueTextBox_0(float NewValue, ETextCommit::Type CommitInfo);

	void OnChangedValueTextBox_1(float NewValue, ETextCommit::Type CommitInfo);

	void OnChangedValueTextBox_2(float NewValue, ETextCommit::Type CommitInfo);
	bool bIsRotator;
};

class SDefault_GraphPinVector2D : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinVector2D)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	/**
	 *	Function to create class specific widget.
	 *
	 *	@return Reference to the newly created widget object
	 */
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;

private:
	// Enum values to identify text boxes.
	enum ETextBoxIndex
	{
		TextBox_X,
		TextBox_Y
	};

	/*
	 *	Function to get current value in text box 0
	 *
	 *	@return current string value
	 */
	FString GetCurrentValue_X() const;

	/*
	 *	Function to get current value in text box 1
	 *
	 *	@return current string value
	 */
	FString GetCurrentValue_Y() const;

	/*
	 *	Function to getch current value based on text box index value
	 *
	 *	@param: Text box index
	 *
	 *	@return current string value
	 */
	FString GetValue(ETextBoxIndex Index) const;

	/*
	 *	Function to store value when text box 0 value in modified
	 *
	 *	@param 0: Updated Float Value
	 */
	void OnChangedValueTextBox_X(float NewValue, ETextCommit::Type CommitInfo);

	/*
	 *	Function to store value when text box 1 value in modified
	 *
	 *	@param 0: Updated Float Value
	 */
	void OnChangedValueTextBox_Y(float NewValue, ETextCommit::Type CommitInfo);
};

class SDefault_GraphPinVector4 : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinVector4)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:
	/**
	*	Function to create class specific widget.
	*
	*	@return Reference to the newly created widget object
	*/
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;

private:
	// Enum values to identify text boxes.
	enum ETextBoxIndex
	{
		TextBox_0,
		TextBox_1,
		TextBox_2,
		TextBox_3,
	};

	FString GetCurrentValue_0() const;
	FString GetCurrentValue_1() const;
	FString GetCurrentValue_2() const;
	FString GetCurrentValue_3() const;

	/*
	*	Function to getch current value based on text box index value
	*
	*	@param: Text box index
	*
	*	@return current string value
	*/
	FString GetValue(ETextBoxIndex Index) const;

	/*
	*	Function to store value when text box value in modified
	*
	*	@param 0: Updated Float Value
	*/
	void OnChangedValueTextBox_0(float NewValue, ETextCommit::Type CommitInfo);
	void OnChangedValueTextBox_1(float NewValue, ETextCommit::Type CommitInfo);
	void OnChangedValueTextBox_2(float NewValue, ETextCommit::Type CommitInfo);
	void OnChangedValueTextBox_3(float NewValue, ETextCommit::Type CommitInfo);

	static FVector4 ParseValue(FString Value);
private:
	/** Flag is true if the widget is used to represent a rotator; false otherwise */
	bool bIsRotator;
};
//
//class SDefault_GraphPinNameList : public SDefault_GraphPinNameList
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_GraphPinNameList) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
//
//class SDefault_PhysicsAssetGraphNodeOutputPin : public SPhysicsAssetGraphNodeOutputPin
//{
//public:
//	SLATE_BEGIN_ARGS(SDefault_PhysicsAssetGraphNodeOutputPin) {}
//	SLATE_END_ARGS()
//
//		void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
//};
