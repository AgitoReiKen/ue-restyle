// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "DefaultGraphPanelPinFactory.h"

#include "AnimationGraphSchema.h"
#include "AnimationStateMachineSchema.h"
#include "Restyle.h"

#include "Animation/AnimNodeBase.h"

#include "MaterialGraph/MaterialGraphSchema.h"
#include "MaterialPins/SGraphPinMaterialInput.h"
#include "Pins/SDefault_Pins.h"
#include "Themes/Default/PinRestyleDefault.h"
#include "Utils/Private_EdGraphUtilities.h"

TSharedPtr<SGraphPin> FDefaultGraphPanelPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	if (!InPin || !InPin->GetSchema()) return nullptr;

	// ReSharper disable once CppJoinDeclarationAndAssignment
	TSharedPtr<SGraphPin> Result;

	Result = TryAnimation(InPin);
	if (Result) return Result;

	Result = TryMaterial(InPin);
	if (Result) return Result;

	auto& PinFactories = access_private_static::FEdGraphUtilities::VisualPinFactories();

	for (int i = 0; i < PinFactories.Num(); i++)
	{
		TSharedPtr<FGraphPanelPinFactory> FactoryPtr = PinFactories[i];
		if (FactoryPtr.IsValid() && FactoryPtr.Get() != this)
		{
			TSharedPtr<SGraphPin> ResultVisualPin = FactoryPtr->CreatePin(InPin);
			if (ResultVisualPin.IsValid())
			{
				return ResultVisualPin;
			}
		}
	}

	// TryKismet contain default widget style for UEdGraphSchema_K2 pins,
	// UEdGraphSchema_K2 also base class not only for blueprints
	Result = TryKismet(InPin);
	if (Result) return Result;

	return nullptr;
}

TSharedPtr<SGraphPin> FDefaultGraphPanelPinFactory::TryKismet(UEdGraphPin* InPin) const
{
	const auto& PinCategory = InPin->PinType.PinCategory;
	const auto& PinSubCategory = InPin->PinType.PinSubCategory;
	auto PinSubCategoryObject = InPin->PinType.PinSubCategoryObject;
	if (InPin->GetSchema()->IsA<UEdGraphSchema_K2>())
	{
		if (PinCategory == UEdGraphSchema_K2::PC_Boolean)
		{
			return SNew(SDefault_GraphPinBool, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Text)
		{
			return SNew(SDefault_GraphPinText, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Exec)
		{
			return SNew(SDefault_GraphPinExec, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Object)
		{
			const UClass* ObjectMetaClass = Cast<UClass>(PinSubCategoryObject.Get());
			if (ObjectMetaClass && ObjectMetaClass->IsChildOf<UScriptStruct>())
			{
				return SNew(SDefault_GraphPinStruct, InPin);
			}
			else
			{
				return SNew(SDefault_GraphPinObject, InPin);
			}
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Interface)
		{
			return SNew(SDefault_GraphPinObject, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_SoftObject)
		{
			return SNew(SDefault_GraphPinObject, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Class)
		{
			return SNew(SDefault_GraphPinClass, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_SoftClass)
		{
			return SNew(SDefault_GraphPinClass, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Int)
		{
			return SNew(SDefault_GraphPinInteger, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Int64)
		{
			return SNew(SDefault_GraphPinNum<int64>, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Real)
		{
			return SNew(SDefault_GraphPinNum<double>, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_String || PinCategory == UEdGraphSchema_K2::PC_Name)
		{
			return SNew(SDefault_GraphPinString, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Struct)
		{
			// If you update this logic you'll probably need to update UEdGraphSchema_K2::ShouldHidePinDefaultValue!
			UScriptStruct* ColorStruct = TBaseStructure<FLinearColor>::Get();
			UScriptStruct* VectorStruct = TBaseStructure<FVector>::Get();
			UScriptStruct* Vector3fStruct = TVariantStructure<FVector3f>::Get();
			UScriptStruct* Vector2DStruct = TBaseStructure<FVector2D>::Get();
			UScriptStruct* RotatorStruct = TBaseStructure<FRotator>::Get();
			UScriptStruct* Vector4Struct = TBaseStructure<FVector4>::Get();

			if (UPinRestyleSettings::Get()->CustomPins.bVector4)
			{
				if (PinSubCategoryObject == Vector4Struct)
				{
					return SNew(SDefault_GraphPinVector4<double>, InPin);
				}
			}
			if (PinSubCategoryObject == ColorStruct)
			{
				return SNew(SDefault_GraphPinColor, InPin);
			}
			if ((PinSubCategoryObject == VectorStruct) || (PinSubCategoryObject ==
				Vector3fStruct) || (PinSubCategoryObject == RotatorStruct))
			{
				return SNew(SDefault_GraphPinVector<double>, InPin);
			}
			if (PinSubCategoryObject == Vector2DStruct)
			{
				return SNew(SDefault_GraphPinVector2D<double>, InPin);
			}

			if (PinSubCategoryObject == FKey::StaticStruct())
			{
				return SNew(SDefault_GraphPinKey, InPin);
			}
			if (PinSubCategoryObject == FCollisionProfileName::StaticStruct())
			{
				return SNew(SDefault_GraphPinCollisionProfile, InPin);
			}
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Byte)
		{
			// Check for valid enum object reference
			if ((PinSubCategoryObject != NULL) && (PinSubCategoryObject->IsA(
				UEnum::StaticClass())))
			{
				return SNew(SDefault_GraphPinEnum, InPin);
			}
			else
			{
				return SNew(SDefault_GraphPinInteger, InPin);
			}
		}
		if ((PinCategory == UEdGraphSchema_K2::PC_Wildcard) && (PinSubCategory ==
			UEdGraphSchema_K2::PSC_Index))
		{
			return SNew(SDefault_GraphPinIndex, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_MCDelegate)
		{
			return SNew(SDefault_GraphPinString, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_FieldPath)
		{
			return SNew(SDefault_GraphPinString, InPin);
		}
		return SNew(SDefault_GraphPin, InPin);
	}
	return nullptr;
}

TSharedPtr<SGraphPin> FDefaultGraphPanelPinFactory::TryMaterial(UEdGraphPin* InPin) const
{
	const auto& PinCategory = InPin->PinType.PinCategory;
	const auto& PinSubCategory = InPin->PinType.PinSubCategory;
	auto PinSubCategoryObject = InPin->PinType.PinSubCategoryObject;
	if (const UMaterialGraphSchema* MaterialGraphSchema = Cast<const UMaterialGraphSchema>(InPin->GetSchema()))
	{

		if (PinCategory == MaterialGraphSchema->PC_Exec)
		{
			return SNew(SDefault_GraphPinExec, InPin);
		}
		else if (PinCategory == MaterialGraphSchema->PC_MaterialInput)
		{
			return SNew(SDefault_GraphPinMaterialInput, InPin);
		}
		else
		{
			if (PinSubCategory == MaterialGraphSchema->PSC_Red || PinSubCategory == MaterialGraphSchema->PSC_Float)
			{
				return SNew(SDefault_GraphPinNum<double>, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_RG)
			{
				return SNew(SDefault_GraphPinVector2D<float>, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_RGB)
			{
				return SNew(SDefault_GraphPinVector<float>, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_RGBA)
			{
				return SNew(SDefault_GraphPinColor, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_Vector4)
			{
				return SNew(SDefault_GraphPinVector4<float>, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_Int)
			{
				return SNew(SDefault_GraphPinInteger, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_Byte)
			{
				// Check for valid enum object reference
				if ((PinSubCategoryObject != NULL) && (InPin->PinType.PinSubCategoryObject->IsA(UEnum::StaticClass())))
				{
					return SNew(SDefault_GraphPinEnum, InPin);
				}
				else
				{
					return SNew(SDefault_GraphPinInteger, InPin);
				}
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_Bool)
			{
				return SNew(SDefault_GraphPinBool, InPin);
			}
			return SNew(SDefault_GraphPin, InPin);
		}
	}
	return nullptr;
}
TSharedPtr<SGraphPin> FDefaultGraphPanelPinFactory::TryAnimation(UEdGraphPin* InPin) const
{
	/* @TODO SGraphPinPose must be Widget->GetType() == "SGraphPinPose" in Animation Connection shit*/
	if (InPin->GetSchema()->IsA<UAnimationGraphSchema>() && InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		if ((InPin->PinType.PinSubCategoryObject == FPoseLink::StaticStruct()) || (InPin->PinType.PinSubCategoryObject == FComponentSpacePoseLink::StaticStruct()))
		{
			auto Restyle = FModuleManager::GetModuleChecked<FRestyleModule>(TEXT("Restyle"));
			if (Restyle.IsSubjectProviderRegistered("Default", ERestyleSubject::PinConnection))
				return SNew(SDefault_GraphPinPose, InPin);
		}
	}
	if (InPin->GetSchema()->IsA<UAnimationStateMachineSchema>() && InPin->PinType.PinCategory == UAnimationStateMachineSchema::PC_Exec)
	{
		return SNew(SDefault_GraphPinExec, InPin);
	}
	return nullptr;
}