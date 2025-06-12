// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameInstanceTG.h"

#include "MJSaveGame.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/MJCharacterAttributeSet.h"
#include "Character/MJPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UMJGameInstanceTG::UMJGameInstanceTG()
{
	
}

void UMJGameInstanceTG::Init()
{
	Super::Init();
	
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		CreateSaveGame();
		UE_LOG(LogTemp,Log,TEXT("createsavegame"));
	 
	}
	// else
	// {
	// 	LoadSaveGame();
	// 	
	// 	UE_LOG(LogTemp,Log,TEXT("loadsavegame"));
	// }
	
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
		UE_LOG(LogTemp, Log, TEXT("No save found. Saving current character state as default."));

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
	 		
	 		UE_LOG(LogTemp,Log,TEXT("loaded health : %f"), 
	 		MJASC->GetNumericAttribute(UMJCharacterAttributeSet::GetHealthAttribute()));
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
			
			UE_LOG(LogTemp,Log,TEXT("saved health : %f"), SaveGameData->GetAttributeSaveData().Health);
		}
		else
		{
			bool bSaved = false;
			UE_LOG(LogTemp, Log, TEXT("Character Info Save success: %s"), bSaved ? TEXT("true") : TEXT("false"));
		}
		
		bool bSaved = UGameplayStatics::SaveGameToSlot(SaveGameData, SaveSlotName, UserIndex);
		UE_LOG(LogTemp, Log, TEXT("Save success: %s"), bSaved ? TEXT("true") : TEXT("false"));
		
	}
}

void UMJGameInstanceTG::Shutdown()
{
	Super::Shutdown();
}
