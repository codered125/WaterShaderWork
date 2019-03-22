// Fill out your copyright notice in the Description page of Project Settings.

#include "FMyTestVS.h"
#include "ShaderParameterUtils.h"
#include "RHIStaticStates.h"
#include "PixelShaderPrivatePCH.h"

//IMPLEMENT_SHADER_TYPE(, FMyTestVS, TEXT("Plugin/PixelShader/Shaders/TestShader.usf"),TEXT("MainVS"), SF_Vertex);
//IMPLEMENT_SHADER_TYPE(, FMyTestVS, TEXT("Plugin/PixelShader/Private/TestShader.USF"),TEXT("MainPS"), SF_Pixel);

//Needed to make sure the plugin works :)
IMPLEMENT_MODULE(FDefaultModuleImpl, PixelShader);
