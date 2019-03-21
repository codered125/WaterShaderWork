// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/ShaderCore/Public/GlobalShader.h"

/**
 * 
 */
class FMyTestVS : public FGlobalShader
{

	DECLARE_EXPORTED_SHADER_TYPE(FMyTestVS, Global,  /*MYMODULE_API*/);
	FMyTestVS()
	{

	};

	FMyTestVS(const ShaderMetaType::CompiledShaderInitializerType & Initializer) : FGlobalShader(Initializer)
	{

	};
	~FMyTestVS()
	{
	
	};
	
	static bool ShouldCache(EShaderPlatform Platform)
	{
		return true;
	};

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters & Parameters)
	{
		return true;
	};

};
