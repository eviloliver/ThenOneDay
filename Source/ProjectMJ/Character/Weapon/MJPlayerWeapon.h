// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Weapon/MJWeaponBase.h"
#include "PlayerType/MJPlayerStructType.h"
#include "GameplayAbilitySpecHandle.h"
#include "MJPlayerWeapon.generated.h"

/**
 * Class Description: PlayerWeapon Data
 * Author: Lee JuHyeon
 * Created Date: 2025_06_18
 * Last Modified By: Add Weapon Ability
 * Last Modified Date:2025_06_23
 */
UCLASS()
class PROJECTMJ_API AMJPlayerWeapon : public AMJWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData")
	FMJPlayerWeaponData PlayerWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandle(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray< FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandle()const;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
