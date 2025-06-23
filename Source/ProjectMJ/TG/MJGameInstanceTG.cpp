// Fill out your copyright notice in the Description page of Project Settings.

#include "MJGameInstanceTG.h"
#include "SubSystem/MJDungeonGenerationSubSystem.h"

class UMJSaveGameSubsystem;
class UMJDungeonGenerationSubSystem;

UMJGameInstanceTG::UMJGameInstanceTG()
{
	PlayerSessionData.CurrentDungeonMapNum = -1;
}

void UMJGameInstanceTG::Init()
{
	Super::Init();

	// Generating DungeonGraph
	GetSubsystem<UMJDungeonGenerationSubSystem>()->GenerateDungeonGraph();
	
	// Google Sheet Load
	//HttpDownloader = NewObject<UMJHttpDownloadManager>();
	//HttpDownloader->FetchGoogleSheetData();
	
	// UMJSaveGameSubsystem* SaveGameSubsystem = GetSubsystem<UMJSaveGameSubsystem>();
	// if (!UGameplayStatics::DoesSaveGameExist(SaveGameSubsystem->GetSaveSlotName(), SaveGameSubsystem->GetUserIndex()))
	// {
	// 	SaveGameSubsystem->CreateSaveGame();
	// 	MJ_LOG(LogTG,Log,TEXT("Create SaveGame File"));
	// }
}

FMJPlayerSessionData& UMJGameInstanceTG::GetPlayerSessionDataRef() 
{
	return PlayerSessionData;
}

TArray<FMJDungeonSessionData>& UMJGameInstanceTG::GetDungeonSessionDataRef()
{
	return DungeonSessionData;
}
