// Fill out your copyright notice in the Description page of Project Settings.

#include "EmptyCPPGameModeBase.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"
#include "Kismet/KismetStringLibrary.h"
#include "Json.h"

AEmptyCPPGameModeBase::AEmptyCPPGameModeBase()
{
}

void AEmptyCPPGameModeBase::DeleteFile(const FString & Dir)
{
}

FString AEmptyCPPGameModeBase::ReadFile(const FString & Dir)
{
	FString SaveDirectory = VerifyOrCreateDirectory(Dir);
	FString FileName = FString("RotationLog.json");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString result;
	FString FilePathAbs = SaveDirectory + "/" + FileName;
	FFileHelper::LoadFileToString(result, *FilePathAbs);
	return result;
}

void AEmptyCPPGameModeBase::WriteToFile(const FString & Dir)
{
	FString SaveDirectory = VerifyOrCreateDirectory(Dir);
	FString FileName = FString("RotationLog.json");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.CreateDirectoryTree(*SaveDirectory))
	{
		FString URL = SaveDirectory + "/" + FileName;
		FString JSonString;
		FFileHelper::LoadFileToString(JSonString, *URL);
		TSharedPtr<FJsonObject> JsonParsed;
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(*JSonString);
		if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
		{	
			TArray <TSharedPtr<FJsonValue>> Items = JsonParsed->GetArrayField("Items");
			FSnapSettings empty;
			JsonParsed->SetArrayField("Items", WriteToJson(JsonParsed, Items, empty));

			FString OutputString;
			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(JsonParsed.ToSharedRef(), Writer);
			FFileHelper::SaveStringToFile(OutputString, *URL);
		}
	}
}

const TArray<TSharedPtr<class FJsonValue>> AEmptyCPPGameModeBase::WriteToJson(TSharedPtr<FJsonObject> serialisedObj,TArray<TSharedPtr<class FJsonValue>> arr, const FSnapSettings & val)
{	
	TSharedPtr< FJsonObject > JsonObj = MakeShareable(new FJsonObject);
	JsonObj->SetStringField("Name", val.Name);
	for (int i = 0; i < 2; i++)
	{
		bool isLeft = i == 0;
		FTransform t = isLeft ? val.LeftHand : val.RightHand;
		JsonObj->SetStringField(isLeft ? "LeftRotation" : "RightRotation", t.GetRotation().ToString());
		JsonObj->SetStringField(isLeft ? "LeftLocation" : "RightLocation", t.GetLocation().ToString());
		JsonObj->SetStringField(isLeft ? "LeftScale" : "RightScale", t.GetScale3D().ToString());
	}

	TSharedRef< FJsonValueObject > JsonValue = MakeShareable(new FJsonValueObject(JsonObj));
	
	for (int ArrayIndex = 0; ArrayIndex != arr.Num(); ArrayIndex++)
	{
		TSharedPtr<FJsonObject> inst = arr[ArrayIndex]->AsObject();
		if (inst->GetStringField("Name") == val.Name)
		{
			arr[ArrayIndex] = JsonValue;
			return arr;
		}
	}

	arr.Add(JsonValue);
	return arr;
}


FSnapSettings AEmptyCPPGameModeBase::GetSnapSettings(const FString & Dir, const FString & Accessor)
{
	TSharedPtr<FJsonObject> JsonParsed;
	FSnapSettings result;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Dir);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		TArray <TSharedPtr<FJsonValue>> ItemArr = JsonParsed->GetArrayField("Items");
		for (int ArrayIndex = 0; ArrayIndex != ItemArr.Num(); ArrayIndex++)
		{
			TSharedPtr<FJsonObject> inst = ItemArr[ArrayIndex]->AsObject();
			FString InstanceName = inst->GetStringField("Name");
			if (InstanceName == Accessor)
			{
				for (int i = 0; i < 2; i++)
				{
					FRotator Rot;
					FVector Loc; FVector Scale;
					bool success; 
					bool isLeft = i == 0;
					UKismetStringLibrary::Conv_StringToRotator(inst->GetStringField(isLeft ? "LeftRotation" : "RightRotation"), Rot, success);
					UKismetStringLibrary::Conv_StringToVector(inst->GetStringField(isLeft ? "LeftLocation" : "RightLocation"), Loc, success);
					UKismetStringLibrary::Conv_StringToVector(inst->GetStringField(isLeft ? "LeftScale" : "RightScale"), Scale, success);
					isLeft == true ? result.LeftHand = FTransform(Rot, Loc, Scale) : result.RightHand = FTransform(Rot, Loc, Scale);
					GEngine->AddOnScreenDebugMessage(i, 60, FColor::Red, Loc.ToString());
				}
			}
		}
	}
	return result;
}
