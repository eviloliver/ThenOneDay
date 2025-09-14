// Fill out your copyright notice in the Description page of Project Settings.

#include "MJGameInstance.h"

#include "GameFramework/GameUserSettings.h"

UMJGameInstance::UMJGameInstance()
{
	PlayerSessionData.CurrentDungeonMapNum = -1;

	

}

void UMJGameInstance::Init()
{
	Super::Init();
}

void UMJGameInstance::OnStart()
{
	Super::OnStart();

	// Apply Default Settings before Starting Level
	UGameUserSettings* CurrentGameUserSettings = GEngine->GetGameUserSettings();

	if (CurrentGameUserSettings)
	{
		CurrentGameUserSettings->SetFullscreenMode(EWindowMode::Type::Windowed);
		CurrentGameUserSettings->SetScreenResolution(FIntPoint(1600,900));
		CurrentGameUserSettings->SetOverallScalabilityLevel(1); // Medium

		CurrentGameUserSettings->ApplySettings(false);
		CurrentGameUserSettings->SaveSettings();
	}

}

FMJPlayerSessionData& UMJGameInstance::GetPlayerSessionDataRef() 
{
	return PlayerSessionData;
}

TArray<FMJDungeonSessionData>& UMJGameInstance::GetDungeonSessionDataRef()
{
	return DungeonSessionData;
}
