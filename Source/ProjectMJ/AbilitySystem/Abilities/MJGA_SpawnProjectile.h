// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "AbilitySystem/Struct/MJSkillProjectileParams.h"
#include "MJGA_SpawnProjectile.generated.h"

/**
 * Class Description: Spawn Projectile Ability
 * Author: 신동민
 * Created Date: 2025.07.03
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

class UMJProjectileMovementBehaviorBase;
class UMJProjectileReactionBehaviorBase;
class AMJProjectileBase;

UCLASS()
class PROJECTMJ_API UMJGA_SpawnProjectile : public UMJGA_GameplayAbility
{
	GENERATED_BODY()

public:
	UMJGA_SpawnProjectile();

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Effects")
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Effects")
	TSubclassOf<UGameplayEffect> StatusGameplayEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Effects")
	TSubclassOf<UGameplayEffect> ExplosionDamageGameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AMJProjectileBase> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior")
	TSubclassOf<UMJProjectileMovementBehaviorBase> MovementBehavior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior")
	TArray<TSubclassOf<UMJProjectileReactionBehaviorBase>> ReactionBehaviors;
};
