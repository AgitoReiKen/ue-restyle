// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "WireShader.h"
#include "ShaderParameterUtils.h"
#include "Rendering/RenderingCommon.h"
IMPLEMENT_SHADER_TYPE(, FRestyleVertexShader, TEXT("/Plugin/Restyle/Private/WireShader.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FRestylePixelShader, TEXT("/Plugin/Restyle/Private/WireShader.usf"), TEXT("MainPS"), SF_Pixel);


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
