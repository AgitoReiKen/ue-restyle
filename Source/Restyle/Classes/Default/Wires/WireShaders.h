// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "CoreMinimal.h"
#include "RenderResource.h"
#include "ShaderParameters.h"
#include "Shader.h"
#include "GlobalShader.h"
#include "ShaderParameterUtils.h"
#include "Rendering/RenderingCommon.h"
#include "RHIStaticStates.h"
#include "TextureResource.h"
#include "RenderUtils.h"
 
class FRestyleVertexShader : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FRestyleVertexShader, Global);
public:
	//** Indicates that this shader should be cached */
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters) { return true; }

	/** Constructor.  Binds all parameters used by the shader */
	FRestyleVertexShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
	{
		ViewProjection.Bind(Initializer.ParameterMap, TEXT("ViewProjection"));
	}

	FRestyleVertexShader()
	{
	}
	void SetViewProjection(FRHICommandList& RHICmdList, const FMatrix44f& InViewProjection)
	{
		SetShaderValue(RHICmdList, RHICmdList.GetBoundVertexShader(), ViewProjection, InViewProjection);
	}

private:
	LAYOUT_FIELD(FShaderParameter, ViewProjection)
};

class FRestylePixelShader : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FRestylePixelShader, Global);
	/** Indicates that this shader should be cached */
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
	}

	FRestylePixelShader()
	{
	}

	/** Constructor.  Binds all parameters used by the shader */
	FRestylePixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
		ShaderParams.Bind(Initializer.ParameterMap, TEXT("ShaderParams"));
		ShaderParams2.Bind(Initializer.ParameterMap, TEXT("ShaderParams2"));
	}

	void SetShaderParams(FRHICommandList& RHICmdList, const FShaderParams& InShaderParams)
	{
		SetShaderValue(RHICmdList, RHICmdList.GetBoundPixelShader(), ShaderParams, (FVector4f)InShaderParams.PixelParams);
		SetShaderValue(RHICmdList, RHICmdList.GetBoundPixelShader(), ShaderParams2, (FVector4f)InShaderParams.PixelParams2);
	} 
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		//static const auto CVar = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.HDR.Display.OutputDevice"));
		//OutEnvironment.SetDefine(TEXT("USE_709"), CVar ? (CVar->GetValueOnGameThread() == 1) : 1);
	}


private:
	LAYOUT_FIELD(FShaderParameter, ShaderParams);
	LAYOUT_FIELD(FShaderParameter, ShaderParams2);
};
