#pragma once

#include "CoreMinimal.h"
#include "MJSkillProjectileParams.generated.h"

/**
* Class Description : Projectile Param
* Author : 신동민
* Created Date : 2025.07.03
* Last Modified By :
* Last Modified Date :
*/

class UAbilitySystemComponent;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FMJSkillProjectileParams
{
	GENERATED_BODY()

	FMJSkillProjectileParams() {};

	// Damage/Scaling
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseDamage = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackDamageScaling = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AbilityPowerScaling = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LifeSteal = 0.f;

    // Range
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillRadius = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillRange = 0.f;

    // Status Effect
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatusEffectChance = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatusEffectDuration = 0.f;

    // Projectile
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ProjectileSpeed = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ProjectileCount = 1.0f;

    // ASC
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAbilitySystemComponent> SourceASC = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;

	// Effects
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayEffect> DamageGameplayEffectClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayEffect> StatusGameplayEffectClass;

};