// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "WireShader.h"
#include "Shader.h"
IMPLEMENT_SHADER_TYPE(, FRestyleVertexShader, TEXT("/Plugin/Restyle/Private/WireShader.usf"), TEXT("MainVS"),
                        SF_Vertex);


FRestyleVertexShader::FRestyleVertexShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
	ViewProjection.Bind(Initializer.ParameterMap, TEXT("ViewProjection"));
}

FRestyleVertexShader::FRestyleVertexShader()
{
}

void FRestyleVertexShader::SetViewProjection(FRHICommandList& RHICmdList, const FMatrix44f& InViewProjection)
{
	SetShaderValue(RHICmdList, RHICmdList.GetBoundVertexShader(), ViewProjection, InViewProjection);
}

void FRestylePixelShader::InternalDestroy(void* Object, const FTypeLayoutDesc&, const FPointerTableBase* PtrTable,
                                          bool bIsFrozen)
{
	Freeze::DestroyObject(static_cast<FRestylePixelShader*>(Object), PtrTable, bIsFrozen);
}

FTypeLayoutDesc& FRestylePixelShader::StaticGetTypeLayout()
{
	static_assert(TValidateInterfaceHelper<FRestylePixelShader, InterfaceType>::Value, "Invalid interface for "
		"FRestylePixelShader");
	alignas(FTypeLayoutDesc) static uint8 TypeBuffer[sizeof(FTypeLayoutDesc)] = {0};
	FTypeLayoutDesc& TypeDesc = *(FTypeLayoutDesc*)TypeBuffer;
	if (!TypeDesc.IsInitialized)
	{
		TypeDesc.IsInitialized = true;
		TypeDesc.Name = L"FRestylePixelShader";
		TypeDesc.WriteFrozenMemoryImageFunc = TGetFreezeImageHelper<FRestylePixelShader>::Do();
		TypeDesc.UnfrozenCopyFunc = &Freeze::DefaultUnfrozenCopy;
		TypeDesc.AppendHashFunc = &Freeze::DefaultAppendHash;
		TypeDesc.GetTargetAlignmentFunc = &Freeze::DefaultGetTargetAlignment;
		TypeDesc.ToStringFunc = &Freeze::DefaultToString;
		TypeDesc.DestroyFunc = &InternalDestroy;
		TypeDesc.Size = sizeof(FRestylePixelShader);
		TypeDesc.Alignment = alignof(FRestylePixelShader);
		TypeDesc.Interface = InterfaceType;
		TypeDesc.SizeFromFields = ~0u;
		TypeDesc.GetDefaultObjectFunc = &TGetDefaultObjectHelper<FRestylePixelShader, InterfaceType>::Do;
		InternalLinkType<1>::Initialize(TypeDesc);
		InternalInitializeBases<FRestylePixelShader>(TypeDesc);
		FTypeLayoutDesc::Initialize(TypeDesc);
	}
	return TypeDesc;
};
const FTypeLayoutDesc& FRestylePixelShader::GetTypeLayout() const { return StaticGetTypeLayout(); };
FRestylePixelShader::ShaderMetaType FRestylePixelShader::StaticType(FRestylePixelShader::StaticGetTypeLayout(),
                                                                    L"FRestylePixelShader",
                                                                    L"/Plugin/Restyle/Private/WireShader.usf",
                                                                    L"MainPS", SF_Pixel,
                                                                    FRestylePixelShader::FPermutationDomain::PermutationCount,
                                                                    FRestylePixelShader::ConstructSerializedInstance,
                                                                    FRestylePixelShader::ConstructCompiledInstance,
                                                                    FRestylePixelShader::ModifyCompilationEnvironmentImpl,
                                                                    FRestylePixelShader::ShouldCompilePermutationImpl,
                                                                    FRestylePixelShader::ValidateCompiledResult,
                                                                    sizeof(FRestylePixelShader),
                                                                    FRestylePixelShader::GetRootParametersMetadata());;

FRestylePixelShader::FRestylePixelShader()
{
}

FRestylePixelShader::FRestylePixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
	ShaderParams.Bind(Initializer.ParameterMap, TEXT("ShaderParams"));
	ShaderParams2.Bind(Initializer.ParameterMap, TEXT("ShaderParams2"));
}

void FRestylePixelShader::SetShaderParams(FRHICommandList& RHICmdList, const FShaderParams& InShaderParams)
{
	SetShaderValue(RHICmdList, RHICmdList.GetBoundPixelShader(), ShaderParams, (FVector4f)InShaderParams.PixelParams);
	SetShaderValue(RHICmdList, RHICmdList.GetBoundPixelShader(), ShaderParams2, (FVector4f)InShaderParams.PixelParams2);
}
