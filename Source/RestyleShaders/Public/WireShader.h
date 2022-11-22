// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once
 
#include "GlobalShader.h"
struct FShaderParams;
class FRestyleVertexShader : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FRestyleVertexShader, Global, RESTYLESHADERS_API);
 
	//** Indicates that this shader should be cached */
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters) { return true; }
 
	RESTYLESHADERS_API FRestyleVertexShader();

	/** Constructor.  Binds all parameters used by the shader */
	RESTYLESHADERS_API FRestyleVertexShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer);

	void RESTYLESHADERS_API SetViewProjection(FRHICommandList& RHICmdList, const FMatrix44f& InViewProjection);

private:
	LAYOUT_FIELD(FShaderParameter, ViewProjection)
};

class FRestylePixelShader : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FRestylePixelShader, Global, RESTYLESHADERS_API);
	/** Indicates that this shader should be cached */
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
	}

	RESTYLESHADERS_API FRestylePixelShader();

	/** Constructor.  Binds all parameters used by the shader */
	RESTYLESHADERS_API FRestylePixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer);

	void RESTYLESHADERS_API SetShaderParams(FRHICommandList& RHICmdList, const FShaderParams& InShaderParams);
	 
private:
	LAYOUT_FIELD(FShaderParameter, ShaderParams);
	LAYOUT_FIELD(FShaderParameter, ShaderParams2);
};
