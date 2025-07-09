// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "MJPlayerGameplayAbility.generated.h"


class AMJPlayerCharacter;
class AMJPlayerController;
class UMJPlayerCombatComponent;
/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: 2025_06_18
 * Last Modified By:HelpFunc
 * Last Modified Date: 2025-06_20
 */
UCLASS()
class PROJECTMJ_API UMJPlayerGameplayAbility : public UMJGA_GameplayAbility
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
