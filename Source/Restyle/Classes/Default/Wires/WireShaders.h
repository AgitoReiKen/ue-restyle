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

class FRestyleVertexDeclaration : public FRenderResource
{
public:
	FVertexDeclarationRHIRef VertexDeclarationRHI;

	virtual ~FRestyleVertexDeclaration()
	{
	}

	/** Initializes the vertex declaration RHI resource */
	virtual void InitRHI() override
	{
		FVertexDeclarationElementList Elements;
		uint32 Stride = sizeof(FSlateVertex);
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FSlateVertex, TexCoords), VET_Float4, 0, Stride));
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FSlateVertex, MaterialTexCoords), VET_Float2, 1, Stride));
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FSlateVertex, Position), VET_Float2, 2, Stride));
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FSlateVertex, Color), VET_Color, 3, Stride));
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FSlateVertex, SecondaryColor), VET_Color, 4, Stride));
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FSlateVertex, PixelSize), VET_UShort2, 5, Stride));

		VertexDeclarationRHI = PipelineStateCache::GetOrCreateVertexDeclaration(Elements);
	}

	/** Releases the vertex declaration RHI resource */
	virtual void ReleaseRHI() override
	{
		VertexDeclarationRHI.SafeRelease();
	}
};

TGlobalResource<FRestyleVertexDeclaration> GRestyleVertexDeclaration;
//class FRestyleVertexShader : public FGlobalShader
//{
//	DECLARE_SHADER_TYPE(FRestyleVertexShader, Global);
//public:
//	/** Indicates that this shader should be cached */
//	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters) { return true; }
//
//	/** Constructor.  Binds all parameters used by the shader */
//	FRestyleVertexShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
//	{
//		ViewProjection.Bind(Initializer.ParameterMap, TEXT("ViewProjection"));
//		VertexShaderParams.Bind(Initializer.ParameterMap, TEXT("VertexShaderParams"));
//	}
//
//	FRestyleVertexShader() {}
//
//	/**
//	 * Sets the view projection parameter
//	 *
//	 * @param InViewProjection	The ViewProjection matrix to use when this shader is bound
//	 */
//	void SetViewProjection(FRHICommandList& RHICmdList, const FMatrix44f& InViewProjection)
//	{
//		SetShaderValue(RHICmdList, RHICmdList.GetBoundVertexShader(), ViewProjection, InViewProjection);
//	}
//
//	/**
//	 * Sets shader parameters for use in this shader
//	 *
//	 * @param ShaderParams	The shader params to be used
//	 */
//	void SetShaderParameters(FRHICommandList& RHICmdList, const FVector4f& ShaderParams)
//	{
//		SetShaderValue(RHICmdList, RHICmdList.GetBoundVertexShader(), VertexShaderParams, ShaderParams);
//	}
//
//	 
//
//	/** Serializes the shader data */
//	//virtual bool Serialize( FArchive& Ar ) override;
//
//private:
//	/** ViewProjection parameter used by the shader */
//	LAYOUT_FIELD(FShaderParameter, ViewProjection)
//	/** Shader parmeters used by the shader */
//	LAYOUT_FIELD(FShaderParameter, VertexShaderParams)
//
//};
//class FRestylePixelShader : public FGlobalShader
//{
//	DECLARE_SHADER_TYPE(FRestylePixelShader, Global);
//	/** Indicates that this shader should be cached */
//	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
//	{
//		return true;
//	}
//
//	FRestylePixelShader()
//	{
//	}
//
//	/** Constructor.  Binds all parameters used by the shader */
//	FRestylePixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
//		: FGlobalShader(Initializer)
//	{
//		ShaderParams.Bind(Initializer.ParameterMap, TEXT("ShaderParams"));
//		//ShaderParams2.Bind(Initializer.ParameterMap, TEXT("ShaderParams2"));
//	}
//
//	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
//	{
//		//static const auto CVar = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.HDR.Display.OutputDevice"));
//		//OutEnvironment.SetDefine(TEXT("USE_709"), CVar ? (CVar->GetValueOnGameThread() == 1) : 1);
//	}
//
//	/**
//	 * Sets shader params used by the shader
//	 *
//	 * @param InShaderParams Shader params to use
//	 */
//	void SetShaderParams(FRHICommandList& RHICmdList, const FShaderParams& InShaderParams)
//	{
//		SetShaderValue(RHICmdList, RHICmdList.GetBoundPixelShader(), ShaderParams, (FVector4f)InShaderParams.PixelParams);
//		//SetShaderValue(RHICmdList, RHICmdList.GetBoundPixelShader(), ShaderParams2, (FVector4f)InShaderParams.PixelParams2);
//	}
//
//	 
//
//private:
//
//	LAYOUT_FIELD(FShaderParameter, ShaderParams);
//	/*LAYOUT_FIELD(FShaderParameter, ShaderParams2);*/
//};

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
	///** Indicates that this shader should be cached */
	//static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	//{
	//	return true;
	//}

	FRestylePixelShader()
	{
	}

	/** Constructor.  Binds all parameters used by the shader */
	FRestylePixelShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
		TextureParameter.Bind(Initializer.ParameterMap, TEXT("ElementTexture"));
		TextureParameterSampler.Bind(Initializer.ParameterMap, TEXT("ElementTextureSampler"));
		ShaderParams.Bind(Initializer.ParameterMap, TEXT("ShaderParams"));
		ShaderParams2.Bind(Initializer.ParameterMap, TEXT("ShaderParams2"));
	}

	void SetShaderParams(FRHICommandList& RHICmdList, const FShaderParams& InShaderParams)
	{
		SetShaderValue(RHICmdList, RHICmdList.GetBoundPixelShader(), ShaderParams, (FVector4f)InShaderParams.PixelParams);
		SetShaderValue(RHICmdList, RHICmdList.GetBoundPixelShader(), ShaderParams2, (FVector4f)InShaderParams.PixelParams2);
	}
	void SetTexture(FRHICommandList& RHICmdList, FRHITexture* InTexture, const FSamplerStateRHIRef SamplerState)
	{
		SetTextureParameter(RHICmdList, RHICmdList.GetBoundPixelShader(), TextureParameter, TextureParameterSampler, SamplerState, InTexture);
	}
	//static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	//{
	//	//static const auto CVar = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.HDR.Display.OutputDevice"));
	//	//OutEnvironment.SetDefine(TEXT("USE_709"), CVar ? (CVar->GetValueOnGameThread() == 1) : 1);
	//} 


private:
	LAYOUT_FIELD(FShaderResourceParameter, TextureParameter);
	LAYOUT_FIELD(FShaderResourceParameter, TextureParameterSampler);
	LAYOUT_FIELD(FShaderParameter, ShaderParams);
	LAYOUT_FIELD(FShaderParameter, ShaderParams2);
};
