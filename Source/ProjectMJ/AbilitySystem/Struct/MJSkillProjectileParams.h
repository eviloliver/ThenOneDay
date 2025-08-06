#pragma once

#include "CoreMinimal.h"
#include "MJSkillProjectileParams.generated.h"

/**
* Class Description : Projectile Param
* Author : 신동민
* Created Date : 2025.07.31
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
    // Target
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TargetLocation = FVector::ZeroVector;

	// Damage/Scaling
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseDamage = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackDamageScaling = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AbilityPowerScaling = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LifeSteal = 0.0f;

    // Range
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillRadius = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillRange = 0.0f;

    // Status Effect
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatusEffectChance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatusEffectDuration = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatusEffectBaseDamage = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatusEffectADScaling = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatusEffectAPScaling = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatusEffectMaxStack = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatusEffectPeriod = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatusEffectSlowPercent = 0.f;

    // Explosion
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ExplosionRadius = 0.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ExplosionBaseDamage = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ExplosionADScaling = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ExplosionAPScaling = 0.f;

    // Projectile
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ProjectileSpeed = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ProjectileCount = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LifeSpan = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PierceCount = 0;

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayEffect> ExplosionDamageGameplayEffectClass;

};