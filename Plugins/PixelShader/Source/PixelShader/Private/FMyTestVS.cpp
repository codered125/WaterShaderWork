// Fill out your copyright notice in the Description page of Project Settings.

#include "FMyTestVS.h"
#include "ModuleManager.h"


//IMPLEMENT_SHADER_TYPE(, FVertexShaderExample, TEXT("/Plugin/PixelShader/Private/PixelShaderExample.usf"),TEXT("MainVertexShader"), SF_Vertex);
//IMPLEMENT_SHADER_TYPE(, FPixelShaderDeclaration, TEXT("/Plugin/PixelShader/Private/PixelShaderExample.usf"),TEXT("MainPixelShader"), SF_Pixel);

//Needed to make sure the plugin works :)
IMPLEMENT_MODULE(FDefaultModuleImpl, PixelShader)
