// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGameplayAbility.h"
#include "MJPlayerGameplayAbility.generated.h"


class AMJPlayerCharacter;
class AMJPlayerController;
class UMJPlayerCombatComponent;
/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJPlayerGameplayAbility : public UMJGameplayAbility
{
	GENERATED_BODY()

public:
	
	UFUNCTION(blueprintPure, Category="Player|Ability")
	AMJPlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(blueprintPure, Category = "Player|Ability")
	AMJPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(blueprintPure, Category = "Player|Ability")
	UMJPlayerCombatComponent* GetPlayerCombatComponent();

private:

	TWeakObjectPtr<AMJPlayerCharacter> CachedPlayerCharacter;

	TWeakObjectPtr <AMJPlayerController> CachedPlayerController;
};
