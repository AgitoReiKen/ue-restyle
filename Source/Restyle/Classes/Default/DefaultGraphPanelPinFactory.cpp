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
	const auto* Settings = UPinRestyleSettings::Get();
	const auto& Disabled = Settings->DisabledWidgets.Kismet;
	const auto& PinCategory = InPin->PinType.PinCategory;
	const auto& PinSubCategory = InPin->PinType.PinSubCategory;
	auto PinSubCategoryObject = InPin->PinType.PinSubCategoryObject;
	if (InPin->GetSchema()->IsA<UEdGraphSchema_K2>())
	{
		if (PinCategory == UEdGraphSchema_K2::PC_Boolean)
		{
			if (Disabled[EKismetPinClass::Boolean]) return nullptr;
			return SNew(SDefault_GraphPinBool, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Text)
		{
			if (Disabled[EKismetPinClass::Text]) return nullptr;
			return SNew(SDefault_GraphPinText, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Exec)
		{
			if (Disabled[EKismetPinClass::Exec]) return nullptr;
			return SNew(SDefault_GraphPinExec, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Object)
		{
			const UClass* ObjectMetaClass = Cast<UClass>(PinSubCategoryObject.Get());
			if (ObjectMetaClass && ObjectMetaClass->IsChildOf<UScriptStruct>())
			{
				if (Disabled[EKismetPinClass::Struct]) return nullptr;
				return SNew(SDefault_GraphPinStruct, InPin);
			}
			else
			{
				if (Disabled[EKismetPinClass::Object]) return nullptr;
				return SNew(SDefault_GraphPinObject, InPin);
			}
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Interface)
		{
			if (Disabled[EKismetPinClass::Interface]) return nullptr;
			return SNew(SDefault_GraphPinObject, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_SoftObject)
		{
			if (Disabled[EKismetPinClass::SoftObject]) return nullptr;
			return SNew(SDefault_GraphPinObject, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Class)
		{
			if (Disabled[EKismetPinClass::Class]) return nullptr;
			return SNew(SDefault_GraphPinClass, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_SoftClass)
		{
			if (Disabled[EKismetPinClass::SoftClass]) return nullptr;
			return SNew(SDefault_GraphPinClass, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Int)
		{
			if (Disabled[EKismetPinClass::Int]) return nullptr;
			return SNew(SDefault_GraphPinInteger, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Int64)
		{
			if (Disabled[EKismetPinClass::Int64]) return nullptr;
			return SNew(SDefault_GraphPinNum<int64>, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Real)
		{
			if (Disabled[EKismetPinClass::Real]) return nullptr;
			return SNew(SDefault_GraphPinNum<double>, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_String)
		{
			if (Disabled[EKismetPinClass::String]) return nullptr;
			return SNew(SDefault_GraphPinString, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Name)
		{
			if (Disabled[EKismetPinClass::Name]) return nullptr;
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
				if (Disabled[EKismetPinClass::Color]) return nullptr;
				return SNew(SDefault_GraphPinColor, InPin);
			}
			if (PinSubCategoryObject == VectorStruct)
			{
				if (Disabled[EKismetPinClass::Vector]) return nullptr;
				return SNew(SDefault_GraphPinVector<double>, InPin);
			}
			if (PinSubCategoryObject == Vector3fStruct)
			{
				if (Disabled[EKismetPinClass::Vector3f]) return nullptr;
				return SNew(SDefault_GraphPinVector<double>, InPin);
			}
			if (PinSubCategoryObject == RotatorStruct)
			{
				if (Disabled[EKismetPinClass::Rotator]) return nullptr;
				return SNew(SDefault_GraphPinVector<double>, InPin);
			}
			if (PinSubCategoryObject == Vector2DStruct)
			{
				if (Disabled[EKismetPinClass::Vector2d]) return nullptr;
				return SNew(SDefault_GraphPinVector2D<double>, InPin);
			}

			if (PinSubCategoryObject == FKey::StaticStruct())
			{
				if (Disabled[EKismetPinClass::Key]) return nullptr;
				return SNew(SDefault_GraphPinKey, InPin);
			}
			if (PinSubCategoryObject == FCollisionProfileName::StaticStruct())
			{
				if (Disabled[EKismetPinClass::CollisionProfile]) return nullptr;
				return SNew(SDefault_GraphPinCollisionProfile, InPin);
			}
		}
		if (PinCategory == UEdGraphSchema_K2::PC_Byte)
		{
			// Check for valid enum object reference
			if ((PinSubCategoryObject != NULL) && (PinSubCategoryObject->IsA(
				UEnum::StaticClass())))
			{
				if (Disabled[EKismetPinClass::Enum]) return nullptr;
				return SNew(SDefault_GraphPinEnum, InPin);
			}
			else
			{
				if (Disabled[EKismetPinClass::Byte]) return nullptr;
				return SNew(SDefault_GraphPinInteger, InPin);
			}
		}
		if ((PinCategory == UEdGraphSchema_K2::PC_Wildcard) && (PinSubCategory ==
			UEdGraphSchema_K2::PSC_Index))
		{
			if (Disabled[EKismetPinClass::Wildcard]) return nullptr;
			return SNew(SDefault_GraphPinIndex, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_MCDelegate)
		{
			if (Disabled[EKismetPinClass::MCDelegate]) return nullptr;
			return SNew(SDefault_GraphPinString, InPin);
		}
		if (PinCategory == UEdGraphSchema_K2::PC_FieldPath)
		{
			if (Disabled[EKismetPinClass::String]) return nullptr;
			return SNew(SDefault_GraphPinString, InPin);
		}
		if (Disabled[EKismetPinClass::Base]) return nullptr;
		return SNew(SDefault_GraphPin, InPin);
	}
	return nullptr;
}

TSharedPtr<SGraphPin> FDefaultGraphPanelPinFactory::TryMaterial(UEdGraphPin* InPin) const
{
	const auto* Settings = UPinRestyleSettings::Get();
	const auto& Disabled = Settings->DisabledWidgets.Material;
	const auto& PinCategory = InPin->PinType.PinCategory;
	const auto& PinSubCategory = InPin->PinType.PinSubCategory;
	auto PinSubCategoryObject = InPin->PinType.PinSubCategoryObject;
	if (const UMaterialGraphSchema* MaterialGraphSchema = Cast<const UMaterialGraphSchema>(InPin->GetSchema()))
	{

		if (PinCategory == MaterialGraphSchema->PC_Exec)
		{
			if (Disabled[EMaterialPinClass::Exec]) return nullptr;
			return SNew(SDefault_GraphPinExec, InPin);
		}
		else if (PinCategory == MaterialGraphSchema->PC_MaterialInput)
		{
			if (Disabled[EMaterialPinClass::MaterialInput]) return nullptr;
			return SNew(SDefault_GraphPinMaterialInput, InPin);
		}
		else
		{
			if (PinSubCategory == MaterialGraphSchema->PSC_Red)
			{
				if (Disabled[EMaterialPinClass::Red]) return nullptr;
				return SNew(SDefault_GraphPinNum<double>, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_Float)
			{
				if (Disabled[EMaterialPinClass::Float]) return nullptr;
				return SNew(SDefault_GraphPinNum<double>, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_RG)
			{
				if (Disabled[EMaterialPinClass::RG]) return nullptr;
				return SNew(SDefault_GraphPinVector2D<float>, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_RGB)
			{
				if (Disabled[EMaterialPinClass::RGB]) return nullptr;
				return SNew(SDefault_GraphPinVector<float>, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_RGBA)
			{
				if (Disabled[EMaterialPinClass::RGBA]) return nullptr;
				return SNew(SDefault_GraphPinColor, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_Vector4)
			{
				if (Disabled[EMaterialPinClass::Vector4]) return nullptr;
				return SNew(SDefault_GraphPinVector4<float>, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_Int)
			{
				if (Disabled[EMaterialPinClass::Int]) return nullptr;
				return SNew(SDefault_GraphPinInteger, InPin);
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_Byte)
			{
				// Check for valid enum object reference
				if ((PinSubCategoryObject != NULL) && (InPin->PinType.PinSubCategoryObject->IsA(UEnum::StaticClass())))
				{
					if (Disabled[EMaterialPinClass::Enum]) return nullptr;
					return SNew(SDefault_GraphPinEnum, InPin);
				}
				else
				{
					if (Disabled[EMaterialPinClass::Byte]) return nullptr;
					return SNew(SDefault_GraphPinInteger, InPin);
				}
			}
			else if (PinSubCategory == MaterialGraphSchema->PSC_Bool)
			{
				if (Disabled[EMaterialPinClass::Bool]) return nullptr;
				return SNew(SDefault_GraphPinBool, InPin);
			}
			if (Disabled[EMaterialPinClass::Base]) return nullptr;
			return SNew(SDefault_GraphPin, InPin);
		}
	}
	return nullptr;
}

TSharedPtr<SGraphPin> FDefaultGraphPanelPinFactory::TryAnimation(UEdGraphPin* InPin) const
{
	const auto* Settings = UPinRestyleSettings::Get();
	const auto& Disabled = Settings->DisabledWidgets.Animation;
	/* @TODO SGraphPinPose must be Widget->GetType() == "SGraphPinPose" in Animation Connection shit*/
	if (InPin->GetSchema()->IsA<UAnimationGraphSchema>() && InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		if ((InPin->PinType.PinSubCategoryObject == FPoseLink::StaticStruct()) || (InPin->PinType.PinSubCategoryObject == FComponentSpacePoseLink::StaticStruct()))
		{
			auto Restyle = FModuleManager::GetModuleChecked<FRestyleModule>(TEXT("Restyle"));
			if (Restyle.IsSubjectProviderRegistered("Default", ERestyleSubject::PinConnection)) 
			{
				if (Disabled[EAnimationPinClass::Pose]) return nullptr;
				return SNew(SDefault_GraphPinPose, InPin);
			}
		}
	}
	if (InPin->GetSchema()->IsA<UAnimationStateMachineSchema>() && InPin->PinType.PinCategory == UAnimationStateMachineSchema::PC_Exec)
	{
		if (Disabled[EAnimationPinClass::Exec]) return nullptr;
		return SNew(SDefault_GraphPinExec, InPin);
	}
	return nullptr;
}