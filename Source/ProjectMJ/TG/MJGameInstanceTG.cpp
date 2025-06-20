// Fill out your copyright notice in the Description page of Project Settings.

#include "MJGameInstanceTG.h"

#include <functional>

#include "MJDungeonGenerationSubSystem.h"
#include "MJHttpDownloadManager.h"
#include "MJSaveGame.h"
#include "MJSaveGameSubsystem.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/MJCharacterAttributeSet.h"
#include "Character/MJPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UMJGameInstanceTG::UMJGameInstanceTG()
{
	SavedDummyPos = FVector(0.0f,0.0f,0.0f);
	SavedMapNodeNum = -1;
}

void UMJGameInstanceTG::Init()
{
	Super::Init();

	// Generating DungeonGraph
	GetSubsystem<UMJDungeonGenerationSubSystem>()->GenerateDungeonGraph();
	
	// Google Sheet Load
	HttpDownloader = NewObject<UMJHttpDownloadManager>();
	HttpDownloader->FetchGoogleSheetData();
	
	UMJSaveGameSubsystem* SaveGameSubsystem = GetSubsystem<UMJSaveGameSubsystem>();
	if (!UGameplayStatics::DoesSaveGameExist(SaveGameSubsystem->GetSaveSlotName(), SaveGameSubsystem->GetUserIndex()))
	{
		SaveGameSubsystem->CreateSaveGame();
		MJ_LOG(LogTG,Log,TEXT("Create SaveGame File"));
	}
}

FVector UMJGameInstanceTG::GetSavedDummyPos()
{
	return SavedDummyPos;
}

uint8 UMJGameInstanceTG::GetSavedMapNodeNum()
{
	return SavedMapNodeNum;
}


void UMJGameInstanceTG::SetSavedMapNodeNum(uint8 Input)
{
	SavedMapNodeNum = Input;
}

void UMJGameInstanceTG::SetSavedDummyPos(FVector Input)
{
	SavedDummyPos = Input;
}

