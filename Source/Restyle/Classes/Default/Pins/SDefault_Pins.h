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
#include "SDefault_Vector2DTextBox.h"
#include "SDefault_VectorTextBox.h"
#include "SDefault_Vector4TextBox.h"
//};
	
class SDefault_GraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPin)
		: _PinLabelStyle(NAME_DefaultPinLabelStyle)
		, _ButtonTextPadding(FMargin(0))
		, _UsePinColorForText(false)
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
	//virtual FSlateColor GetHighlightColor() const override;
	//virtual FSlateColor GetPinDiffColor() const override;
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
				.EditableTextBoxStyle(FAppStyle::Get(), FPinRestyleStyles::Graph_EditableTextBox)
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

		if (GetNumericValue() != InValue)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeNumberPinValue", "Change Number Pin Value"));
			GraphPinObj->Modify();

			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, *LexToString(InValue));
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
template <typename NumericType>
class SDefault_GraphPinVector : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinVector) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
	}

protected:

	/**
	 *	Function to create class specific widget.
	 *
	 *	@return Reference to the newly created widget object
	 */
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override
	{
		UScriptStruct* RotatorStruct = TBaseStructure<FRotator>::Get();
		bIsRotator = (GraphPinObj->PinType.PinSubCategoryObject == RotatorStruct) ? true : false;

		return	SNew(SDefault_VectorTextBox<NumericType>, bIsRotator)
			.VisibleText_0(this, &SDefault_GraphPinVector::GetCurrentValue_0)
			.VisibleText_1(this, &SDefault_GraphPinVector::GetCurrentValue_1)
			.VisibleText_2(this, &SDefault_GraphPinVector::GetCurrentValue_2)
			.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
			.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
			.OnNumericCommitted_Box_0(this, &SDefault_GraphPinVector::OnChangedValueTextBox_0)
			.OnNumericCommitted_Box_1(this, &SDefault_GraphPinVector::OnChangedValueTextBox_1)
			.OnNumericCommitted_Box_2(this, &SDefault_GraphPinVector::OnChangedValueTextBox_2);
	}

private:

	// Enum values to identify text boxes.
	enum ETextBoxIndex
	{
		TextBox_0,
		TextBox_1,
		TextBox_2,
	};

	using FVectorType = UE::Math::TVector<NumericType>;

	// Rotator is represented as X->Roll, Y->Pitch, Z->Yaw
	FString GetCurrentValue_0() const
	{
		// Text box 0: Rotator->Roll, Vector->X
		return GetValue(bIsRotator ? TextBox_2 : TextBox_0);
	}
	 
	FString GetCurrentValue_1() const
	{
		// Text box 1: Rotator->Pitch, Vector->Y
		return GetValue(bIsRotator ? TextBox_0 : TextBox_1);
	}

	FString GetCurrentValue_2() const
	{
		// Text box 2: Rotator->Yaw, Vector->Z
		return GetValue(bIsRotator ? TextBox_1 : TextBox_2);
	}
 
	TArray<FString> GetComponentArray() const
	{
		TArray<FString> VecComponentStrings;

		FString DefaultString = GraphPinObj->GetDefaultAsString();
		// Parse string to split its contents separated by ','
		DefaultString.TrimStartInline();
		DefaultString.TrimEndInline();
		DefaultString.ParseIntoArray(VecComponentStrings, TEXT(","), true);

		return VecComponentStrings;
	}
 
	FString GetValue(ETextBoxIndex Index) const
	{
		const TArray<FString> VecComponentStrings = GetComponentArray();

		if (Index < VecComponentStrings.Num())
		{
			return VecComponentStrings[Index];
		}
		else
		{
			return FString(TEXT("0"));
		}
	}
 
	void OnChangedValueTextBox_0(NumericType NewValue, ETextCommit::Type CommitInfo)
	{
		const EAxis::Type Axis = bIsRotator ? /* update roll */ EAxis::Z : EAxis::X;
		SetNewValueHelper(Axis, NewValue);
	}
	 
	void OnChangedValueTextBox_1(NumericType NewValue, ETextCommit::Type CommitInfo)
	{
		const EAxis::Type Axis = bIsRotator ? /* update pitch */ EAxis::X : EAxis::Y;
		SetNewValueHelper(Axis, NewValue);
	}
	 
	void OnChangedValueTextBox_2(NumericType NewValue, ETextCommit::Type CommitInfo)
	{
		const EAxis::Type Axis = bIsRotator ? /* update yaw */ EAxis::Y : EAxis::Z;
		SetNewValueHelper(Axis, NewValue);
	}

	void SetNewValueHelper(EAxis::Type Axis, NumericType NewValue)
	{
		if (GraphPinObj->IsPendingKill())
		{
			return;
		}

		FVectorType NewVector = ConvertDefaultValueStringToVector();
		const NumericType OldValue = NewVector.GetComponentForAxis(Axis);

		if (OldValue == NewValue)
		{
			return;
		}

		NewVector.SetComponentForAxis(Axis, NewValue);

		const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeVectorPinValue", "Change Vector Pin Value"));
		GraphPinObj->Modify();

		// Create the new value string
		FString DefaultValue = FString::Format(TEXT("{0},{1},{2}"), { NewVector.X, NewVector.Y, NewVector.Z });

		//Set new default value
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
	}
	 
	FVectorType ConvertDefaultValueStringToVector() const
	{
		const TArray<FString> VecComponentStrings = GetComponentArray();

		// Construct the vector from the string parts.
		FVectorType Vec = FVectorType::ZeroVector;
		TDefaultNumericTypeInterface<NumericType> NumericTypeInterface{};

		// If default string value contained a fully specified 3D vector, set the vector components, otherwise leave it zero'ed.
		if (VecComponentStrings.Num() == 3)
		{
			Vec.X = NumericTypeInterface.FromString(VecComponentStrings[0], 0).Get(0);
			Vec.Y = NumericTypeInterface.FromString(VecComponentStrings[1], 0).Get(0);
			Vec.Z = NumericTypeInterface.FromString(VecComponentStrings[2], 0).Get(0);
		}

		return Vec;
	}

private:
	bool bIsRotator;
};
 

template<typename NumericType>
class SDefault_GraphPinVector2D : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinVector2D){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
	}

protected:
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override
	{
		//Create widget
		return SNew(SDefault_Vector2DTextBox<NumericType>)
			.VisibleText_X(this, &SDefault_GraphPinVector2D::GetCurrentValue_X)
			.VisibleText_Y(this, &SDefault_GraphPinVector2D::GetCurrentValue_Y)
			.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
			.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
			.OnNumericCommitted_Box_X(this, &SDefault_GraphPinVector2D::OnChangedValueTextBox_X)
			.OnNumericCommitted_Box_Y(this, &SDefault_GraphPinVector2D::OnChangedValueTextBox_Y);
	}

private:

	static FString MakeVector2DString(NumericType X, NumericType Y)
	{
		return FString::Format(TEXT("(X={0},Y={1})"), { X, Y });
	}
	// Enum values to identify text boxes.
	enum ETextBoxIndex
	{
		TextBox_X,
		TextBox_Y
	};
 
	FString GetCurrentValue_X() const
	{
		return FString::Printf(TEXT("%f"), GetValue().X);
	}
	FString GetCurrentValue_Y() const
	{
		return FString::Printf(TEXT("%f"), GetValue().Y);
	}
	FVector2D GetValue() const
	{
		const FString& DefaultString = GraphPinObj->GetDefaultAsString();

		FVector2D Value;
		Value.InitFromString(DefaultString);

		return Value;
	}
	void OnChangedValueTextBox_X(NumericType NewValue, ETextCommit::Type CommitInfo)
	{
		if (GraphPinObj->IsPendingKill())
		{
			return;
		}

		const FVector2D OldValue = GetValue();
		if (NewValue != OldValue.X)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeVectorPinValue", "Change Vector Pin Value"));
			GraphPinObj->Modify();

			const FString Vector2DString = MakeVector2DString(NewValue, OldValue.Y);
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, Vector2DString);
		}
	}
	void OnChangedValueTextBox_Y(NumericType NewValue, ETextCommit::Type CommitInfo)
	{
		if (GraphPinObj->IsPendingKill())
		{
			return;
		}

		const FVector2D OldValue = GetValue();
		if (NewValue != OldValue.Y)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeVectorPinValue", "Change Vector Pin Value"));
			GraphPinObj->Modify();

			const FString Vector2DString = MakeVector2DString(OldValue.X, NewValue);
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, Vector2DString);
		}
	} 
};
template<typename NumericType>
class SDefault_GraphPinVector4 : public SDefault_GraphPin
{
public:
	SLATE_BEGIN_ARGS(SDefault_GraphPinVector4)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SDefault_GraphPin::Construct(SDefault_GraphPin::FArguments(), InGraphPinObj);
	}

protected:
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override
	{
		return SNew(SDefault_Vector4TextBox<NumericType>)
			.VisibleText_0(this, &SDefault_GraphPinVector4::GetCurrentValue_0)
			.VisibleText_1(this, &SDefault_GraphPinVector4::GetCurrentValue_1)
			.VisibleText_2(this, &SDefault_GraphPinVector4::GetCurrentValue_2)
			.VisibleText_3(this, &SDefault_GraphPinVector4::GetCurrentValue_3)
			.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
			.IsEnabled(this, &SGraphPin::GetDefaultValueIsEditable)
			.OnNumericCommitted_Box_0(this, &SDefault_GraphPinVector4::OnChangedValueTextBox_0)
			.OnNumericCommitted_Box_1(this, &SDefault_GraphPinVector4::OnChangedValueTextBox_1)
			.OnNumericCommitted_Box_2(this, &SDefault_GraphPinVector4::OnChangedValueTextBox_2)
			.OnNumericCommitted_Box_3(this, &SDefault_GraphPinVector4::OnChangedValueTextBox_3);
	}

private:
	enum ETextBoxIndex
	{
		TextBox_0,
		TextBox_1,
		TextBox_2,
		TextBox_3,
	};
	FString GetCurrentValue_0() const
	{
		// Text box 0: Rotator->Roll, Vector->X
		return GetValue(TextBox_0);
	}

	FString GetCurrentValue_1() const
	{
		// Text box 1: Rotator->Pitch, Vector->Y
		return GetValue(TextBox_1);
	}

	FString GetCurrentValue_2() const
	{
		// Text box 2: Rotator->Yaw, Vector->Z
		return GetValue(TextBox_2);
	}

	FString GetCurrentValue_3() const
	{
		// Text box 3: Vector->W
		return GetValue(TextBox_3);
	}

	/*
	*	Function to getch current value based on text box index value
	*
	*	@param: Text box index
	*
	*	@return current string value
	*/
	FString GetValue(ETextBoxIndex Index) const
	{
		FString DefaultString = GraphPinObj->GetDefaultAsString();
		TArray<FString> ResultString;

		// Parse string to split its contents separated by ','
		DefaultString.TrimStartAndEndInline();
		DefaultString.ParseIntoArray(ResultString, TEXT(","), true);

		if (Index < ResultString.Num())
		{
			return ResultString[Index];
		}
		else
		{
			return FString(TEXT("0"));
		}
	}

	/*
	*	Function to store value when text box value in modified
	*
	*	@param 0: Updated numeric value
	*/
	void OnChangedValueTextBox_0(NumericType NewValue, ETextCommit::Type CommitInfo)
	{
		const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);

		FString DefaultValue;
		// Update X value
		DefaultValue = ValueStr + FString(TEXT(",")) + GetValue(TextBox_1) + FString(TEXT(",")) + GetValue(TextBox_2) + FString(TEXT(",")) + GetValue(TextBox_3);

		if (GraphPinObj->GetDefaultAsString() != DefaultValue)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeVector4PinValue", "Change Vector4 Pin Value"));
			GraphPinObj->Modify();

			// Set new default value
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
		}
	}

	void OnChangedValueTextBox_1(NumericType NewValue, ETextCommit::Type CommitInfo)
	{
		const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);

		FString DefaultValue;
		// Update Y value
		DefaultValue = GetValue(TextBox_0) + FString(TEXT(",")) + ValueStr + FString(TEXT(",")) + GetValue(TextBox_2) + FString(TEXT(",")) + GetValue(TextBox_3);

		if (GraphPinObj->GetDefaultAsString() != DefaultValue)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeVector4PinValue", "Change Vector4 Pin Value"));
			GraphPinObj->Modify();

			// Set new default value
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
		}
	}

	void OnChangedValueTextBox_2(NumericType NewValue, ETextCommit::Type CommitInfo)
	{
		const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);

		FString DefaultValue;
		// Update Z value
		DefaultValue = GetValue(TextBox_0) + FString(TEXT(",")) + GetValue(TextBox_1) + FString(TEXT(",")) + ValueStr + FString(TEXT(",")) + GetValue(TextBox_3);

		if (GraphPinObj->GetDefaultAsString() != DefaultValue)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeVector4PinValue", "Change Vector4 Pin Value"));
			GraphPinObj->Modify();

			// Set new default value
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
		}
	}

	void OnChangedValueTextBox_3(NumericType NewValue, ETextCommit::Type CommitInfo)
	{
		const FString ValueStr = FString::Printf(TEXT("%f"), NewValue);

		FString DefaultValue;
		// Update W value
		DefaultValue = GetValue(TextBox_0) + FString(TEXT(",")) + GetValue(TextBox_1) + FString(TEXT(",")) + GetValue(TextBox_2) + FString(TEXT(",")) + ValueStr;

		if (GraphPinObj->GetDefaultAsString() != DefaultValue)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeVector4PinValue", "Change Vector4 Pin Value"));
			GraphPinObj->Modify();

			// Set new default value
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, DefaultValue);
		}
	}
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
 