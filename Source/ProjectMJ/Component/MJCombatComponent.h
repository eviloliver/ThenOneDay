// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/MJExtensionComponent.h"
#include "GameplayTagContainer.h"
#include "MJCombatComponent.generated.h"

class AMJWeaponBase;
/**
 * Class Description: PlayerBattle relate Class
 * Author: Lee JuHyeon
 * Created Date: 2025_06_19
 * Last Modified By: Lee JuHyeon
 * Last Modified Date: Add Using Func from BP 
 */
UCLASS()
class PROJECTMJ_API UMJCombatComponent : public UMJExtensionComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Player|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InPlayerTagToRegister, AMJWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	AMJWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet)const;

	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	AMJWeaponBase* GetCharacterCarriedEquippedWeapon()const;

	UPROPERTY(BlueprintReadWrite,Category="Player|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

private:
	TMap<FGameplayTag, AMJWeaponBase*> CharacterCarriedWeaponMap;
};
