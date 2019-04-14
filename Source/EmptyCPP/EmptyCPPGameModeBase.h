// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "EmptyCPPGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FSnapSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FTransform LeftHand = FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector);

	UPROPERTY(BlueprintReadWrite)
	FTransform RightHand = FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector);

	UPROPERTY(BlueprintReadWrite)
	FString Name = "Item3";

};

UCLASS()
class EMPTYCPP_API AEmptyCPPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEmptyCPPGameModeBase();

	static FORCEINLINE FString VerifyOrCreateDirectory(const FString& Dir)
	{
			FString output = ReturnRelativePath() + *Dir;
			IPlatformFile & PF = FPlatformFileManager::Get().GetPlatformFile();
			if (!PF.DirectoryExists(*output))
			{
				PF.CreateDirectory(*output);
				if (!PF.DirectoryExists(*output))
				{
					GEngine->AddOnScreenDebugMessage(0, 60, FColor::Red, "Directory Failed : " + output);
					return FString();
				}
			}
		return output;
	}

	static FORCEINLINE FString ReturnRelativePath()
	{
		FString RelativePath = FPaths::GameContentDir();
		return RelativePath;
	}

	UFUNCTION(BlueprintCallable)
	virtual void DeleteFile(const FString& Dir);

	UFUNCTION(BlueprintPure)
	virtual FString ReadFile(const FString& Dir);
	
	UFUNCTION(BlueprintCallable)
	virtual void WriteToFile(const FString& Dir);

	virtual const TArray<TSharedPtr<class FJsonValue>> WriteToJson(TSharedPtr<FJsonObject> serialisedObj,TArray<TSharedPtr<class FJsonValue>> arr, const FSnapSettings & val);

	UFUNCTION(BlueprintPure)
	FSnapSettings GetSnapSettings(const FString& Dir, const FString & Accessor);

};
