// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/MJCombatComponent.h"
#include "Character/Weapon/MJPlayerWeapon.h"
#include "MJPlayerCombatComponent.generated.h"


class AMJPlayerWeapon;
/**
 * Class Description: Find Weapon by Tag
 * Author: Lee JuHyeon
 * Created Date: 2025_06_19
 * Last Modified By: Lee JuHyeon
 * Last Modified Date: 
 */
UCLASS()
class PROJECTMJ_API UMJPlayerCombatComponent : public UMJCombatComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category="Warrior|Combat")
	AMJPlayerWeapon* GetPlayerWeaponCarreidWeaponByTag(FGameplayTag InWeaponTag) const;
};
