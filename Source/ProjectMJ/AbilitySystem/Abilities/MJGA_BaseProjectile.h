// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "AbilitySystem/Struct/MJSkillProjectileParams.h"
#include "MJGA_BaseProjectile.generated.h"

/**
 * Class Description: Spawn Projectile Ability
 * Author: 신동민
 * Created Date: 2025.07.03
 * Last Modified By:
 * Last Modified Date:
 */

class AMJProjectileBase;

UCLASS()
class PROJECTMJ_API UMJGA_BaseProjectile : public UMJGA_GameplayAbility
{
	GENERATED_BODY()

public:
	UMJGA_BaseProjectile();


protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AMJProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile");
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffectClasses;

};
