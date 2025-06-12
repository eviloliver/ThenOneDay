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
	else
	{
		LoadSaveGame();
		
		UE_LOG(LogTemp,Log,TEXT("loadsavegame"));
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
		//SaveGameToSlot();
	}
}

void UMJGameInstanceTG::LoadSaveGame()
{
	
	 SaveGameData = Cast<UMJSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (SaveGameData)
	 {
		 AMJPlayerCharacter* MJPlayer = Cast<AMJPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
	 	if (MJPlayer)
	 	{
	 		UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(MJPlayer->GetAbilitySystemComponent());
	 		
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
			
			bool bSaved = UGameplayStatics::SaveGameToSlot(SaveGameData, SaveSlotName, UserIndex);
			UE_LOG(LogTemp, Log, TEXT("Save success: %s"), bSaved ? TEXT("true") : TEXT("false"));
		}
		else
		{
			bool bSaved = false;
			UE_LOG(LogTemp, Log, TEXT("Save success: %s"), bSaved ? TEXT("true") : TEXT("false"));
		}
		
	}
}

void UMJGameInstanceTG::Shutdown()
{
	Super::Shutdown();
}
