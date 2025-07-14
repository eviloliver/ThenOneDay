// Fill out your copyright notice in the Description page of Project Settings.

#include "MJGameInstanceTG.h"

#include "GameFramework/GameUserSettings.h"

UMJGameInstanceTG::UMJGameInstanceTG()
{
	PlayerSessionData.CurrentDungeonMapNum = -1;

	

}

void UMJGameInstanceTG::Init()
{
	Super::Init();
}

void UMJGameInstanceTG::OnStart()
{
	Super::OnStart();

	// Apply Default Settings before Starting Level
	UGameUserSettings* CurrentGameUserSettings = GEngine->GetGameUserSettings();

	if (CurrentGameUserSettings)
	{
		CurrentGameUserSettings->SetFullscreenMode(EWindowMode::Type::Windowed);
		CurrentGameUserSettings->SetScreenResolution(FIntPoint(1280,720));
		CurrentGameUserSettings->SetOverallScalabilityLevel(1); // Medium

		CurrentGameUserSettings->ApplySettings(false);
		CurrentGameUserSettings->SaveSettings();
	}

}

FMJPlayerSessionData& UMJGameInstanceTG::GetPlayerSessionDataRef() 
{
	return PlayerSessionData;
}

TArray<FMJDungeonSessionData>& UMJGameInstanceTG::GetDungeonSessionDataRef()
{
	return DungeonSessionData;
}
