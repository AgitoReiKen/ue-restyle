// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "RenderResource.h"
#include "ShaderParameters.h"
#include "Shader.h"
#include "GlobalShader.h"
#include "ShaderParameterUtils.h"
#include "Rendering/RenderingCommon.h"
#include "RHIStaticStates.h"
#include "RenderUtils.h"

class RESTYLESHADERS_API FRestyleVertexShader : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FRestyleVertexShader, Global);
public:
	//** Indicates that this shader should be cached */
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters) { return true; }

	FRestyleVertexShader();

	/** Constructor.  Binds all parameters used by the shader */
	FRestyleVertexShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer);

	void SetViewProjection(FRHICommandList& RHICmdList, const FMatrix44f& InViewProjection);

private:
	LAYOUT_FIELD(FShaderParameter, ViewProjection)
};

class RESTYLESHADERS_API FRestylePixelShader : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FRestylePixelShader, Global);
	/** Indicates that this shader should be cached */
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
	}

	FRestylePixelShader();

	/** Constructor.  Binds all parameters used by the shader */
	FRestylePixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer);


	void SetShaderParams(FRHICommandList& RHICmdList, const FShaderParams& InShaderParams);
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		//static const auto CVar = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.HDR.Display.OutputDevice"));
		//OutEnvironment.SetDefine(TEXT("USE_709"), CVar ? (CVar->GetValueOnGameThread() == 1) : 1);
	}


private:
	LAYOUT_FIELD(FShaderParameter, ShaderParams);
	LAYOUT_FIELD(FShaderParameter, ShaderParams2);
};
