// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameInstanceTG.h"

#include "MJHttpDownloadManager.h"
#include "MJSaveGame.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/MJCharacterAttributeSet.h"
#include "Character/MJPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UMJGameInstanceTG::UMJGameInstanceTG()
{
	SavedDummyPos = FVector(0.0f,0.0f,0.0f);
	
}

void UMJGameInstanceTG::Init()
{
	Super::Init();

	// Google Sheet Load
	HttpDownloader = NewObject<UMJHttpDownloadManager>();
	HttpDownloader->FetchGoogleSheetData();
	
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		CreateSaveGame();
		MJ_LOG(LogTG,Log,TEXT("Create SaveGame File"));
	}

	
}

UMJSaveGame* UMJGameInstanceTG::GetSaveGameData()
{
	return SaveGameData;
}

void UMJGameInstanceTG::CreateSaveGame()
{
	SaveGameData = CastChecked<UMJSaveGame>(UGameplayStatics::CreateSaveGameObject(UMJSaveGame::StaticClass()));
	if (SaveGameData)
	{
		//SaveGameToSlot(nullptr);
	}
}

void UMJGameInstanceTG::LoadSaveGame(AMJPlayerCharacter* Player)
{
	if (!Player) return;
	
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		MJ_LOG(LogTG, Log, TEXT("No save found. Saving current character state as default."));

		SaveGameData = CastChecked<UMJSaveGame>(UGameplayStatics::CreateSaveGameObject(UMJSaveGame::StaticClass()));
		SaveGameToSlot(Player); // 현재 캐릭터의 기본값으로 저장
		return;
	}

	
	 SaveGameData = Cast<UMJSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (SaveGameData)
	 {
		if (Player)
	 	{
	 		UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(Player->GetAbilitySystemComponent());
	 		
	 		UMJCharacterAttributeSet* MJCAS = const_cast<UMJCharacterAttributeSet*>(MJASC->GetSet<UMJCharacterAttributeSet>());

	 		SaveGameData->GetAttributeSaveData().ApplyTo(MJASC);
	 		
	 		MJ_LOG(LogTG,Log,TEXT("loaded health : %f"), MJASC->GetNumericAttribute(UMJCharacterAttributeSet::GetHealthAttribute()));
	 	}
	 }
}

void UMJGameInstanceTG::SaveGameToSlot(AMJPlayerCharacter* Player)
{
	if (SaveGameData)
	{
		if (Player)
		{
			UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(Player->GetAbilitySystemComponent());
			UMJCharacterAttributeSet* MJCAS = const_cast<UMJCharacterAttributeSet*>(MJASC->GetSet<UMJCharacterAttributeSet>());

			SaveGameData->GetAttributeSaveData() = FCharacterAttributeSaveData::FromAttributeSet(MJCAS);
			
			MJ_LOG(LogTG,Log,TEXT("saved health : %f"), SaveGameData->GetAttributeSaveData().Health);
		}
		else
		{
			bool bSaved = false;
			MJ_LOG(LogTG, Log, TEXT("Character Info Save success: %s"), bSaved ? TEXT("true") : TEXT("false"));
		}
		
		bool bSaved = UGameplayStatics::SaveGameToSlot(SaveGameData, SaveSlotName, UserIndex);
		MJ_LOG(LogTG, Log, TEXT("Save success: %s"), bSaved ? TEXT("true") : TEXT("false"));
		
	}
}

void UMJGameInstanceTG::Shutdown()
{
	Super::Shutdown();
}

FVector UMJGameInstanceTG::GetSavedDummyPos()
{
	return SavedDummyPos;
}

void UMJGameInstanceTG::SetSavedDummyPos(FVector Input)
{
	SavedDummyPos = Input;
}
