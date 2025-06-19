// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJPlayerGameplayAbility.h"
#include "Character/MJPlayerCharacter.h"
#include "Controller/MJPlayerController.h"
#include "Component/MJPlayerCombatComponent.h"

AMJPlayerCharacter* UMJPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<AMJPlayerCharacter>(CurrentActorInfo->AvatarActor);
	}


	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

AMJPlayerController* UMJPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<AMJPlayerController>(CurrentActorInfo->PlayerController);

	}

	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UMJPlayerCombatComponent* UMJPlayerGameplayAbility::GetPlayerCombatComponent()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}