// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "DefaultGraphPanelPinFactory.h"

#include "AnimationGraphSchema.h"
#include "Restyle.h"

#include "Animation/AnimNodeBase.h"

#include "MaterialGraph/MaterialGraphSchema.h"
#include "MaterialPins/SGraphPinMaterialInput.h"
#include "Pins/SDefault_Pins.h"
#include "Themes/Default/PinRestyleDefault.h"
#include "Utils/Privates.h"

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
			const UClass* ObjectMetaClass = Cast<UClass>(InPin->PinType.PinSubCategoryObject.Get());
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
				if (InPin->PinType.PinSubCategoryObject == Vector4Struct)
				{
					return SNew(SDefault_GraphPinVector4, InPin);
				}
			}
			if (InPin->PinType.PinSubCategoryObject == ColorStruct)
			{
				return SNew(SDefault_GraphPinColor, InPin);
			}
			if ((InPin->PinType.PinSubCategoryObject == VectorStruct) || (InPin->PinType.PinSubCategoryObject ==
				Vector3fStruct) || (InPin->PinType.PinSubCategoryObject == RotatorStruct))
			{
				return SNew(SDefault_GraphPinVector, InPin);
			}
			if (InPin->PinType.PinSubCategoryObject == Vector2DStruct)
			{
				return SNew(SDefault_GraphPinVector2D, InPin);
			}

			if (InPin->PinType.PinSubCategoryObject == FKey::StaticStruct())
			{
				return SNew(SDefault_GraphPinKey, InPin);
			}
			if (InPin->PinType.PinSubCategoryObject == FCollisionProfileName::StaticStruct())
			{
				return SNew(SDefault_GraphPinCollisionProfile, InPin);
			}
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Byte)
		{
			// Check for valid enum object reference
			if ((InPin->PinType.PinSubCategoryObject != NULL) && (InPin->PinType.PinSubCategoryObject->IsA(
				UEnum::StaticClass())))
			{
				return SNew(SDefault_GraphPinEnum, InPin);
			}
			else
			{
				return SNew(SDefault_GraphPinInteger, InPin);
			}
		}
		if ((PinCategory == UEdGraphSchema_K2::PC_Wildcard) && (InPin->PinType.PinSubCategory ==
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
	if (const UMaterialGraphSchema* MaterialGraphSchema = Cast<const UMaterialGraphSchema>(InPin->GetSchema()))
	{
		if (PinCategory == MaterialGraphSchema->PC_MaterialInput)
		{
			return SNew(SDefault_GraphPinMaterialInput, InPin);
		}
		return SNew(SDefault_GraphPin, InPin);
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
	return nullptr;
}
