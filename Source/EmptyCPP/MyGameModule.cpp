// Fill out your copyright notice in the Description page of Project Settings.

#include "EmptyCPP.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#
#include "Runtime/ShaderCore/Public/ShaderCore.h"
#include "Modules/ModuleManager.h"


class FMyGameModule : public FDefaultGameModuleImpl
{

	virtual void StartupModule() override
	{
		FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));
		AddShaderSourceDirectoryMapping("/Project", ShaderDirectory);
	}


};

IMPLEMENT_PRIMARY_GAME_MODULE(FMyGameModule, EmptyCPP, "EmptyCPP" );
