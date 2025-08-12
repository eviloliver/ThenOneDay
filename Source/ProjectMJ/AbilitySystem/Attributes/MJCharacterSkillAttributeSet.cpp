// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"

UMJCharacterSkillAttributeSet::UMJCharacterSkillAttributeSet()
    : 
    // Cost
    CostStamina(0.0f)
	, CostMana(0.0f)
    , CostFocus(0.0f)

    // Damage / Scaling
    , BaseDamage(0.0f)
    , Healing(0.0f)
    , LifeSteal(0.0f)
    , AttackDamageScaling(0.0f)
    , AbilityPowerScaling(0.0f)

    // Range
    , SkillRadius(0.0f)
    , SkillRange(0.0f)
	, SkillAttackLocationOffset(0.0f)

    // Time
    , Cooldown(0.0f)
    , MaxCooldown(0.0f)
    , SkillAttackRate(0.0f)
    , MaxSkillAttackRate(0.0f)
    , CastTime(0.0f)
    , PreDelay(0.0f)
    , PostDelay(0.0f)
    , EffectDuration(0.0f)

    // Status Effect
    , StatusEffectChance(0.0f)
    , StatusEffectDuration(0.0f)
    , StatusEffectADScaling(0.0f)
    , StatusEffectAPScaling(0.0f)
    , StatusEffectMaxStack(0.0f)
    , MaxStatusEffectMaxStack(0.0f)
    , StatusEffectPeriod(0.0f)
    , StatusEffectSlowPercent(0.0f)

    // Projectile
    , ProjectileSpeed(0.0f)
    , ProjectileCount(0.0f)
    , MaxProjectileCount(0.0f)
	, ProjectileLifeSpan(0.0f)
    , ProjectilePierceCount(0.0f)
    , MaxProjectilePierceCount(0.0f)

    // Explosion
	, ExplosionRadius(0.0f)
    , ExplosionBaseDamage(0.0f)
    , ExplosionADScaling(0.0f)
    , ExplosionAPScaling(0.0f)
{

}


void UMJCharacterSkillAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetCooldownAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxCooldown());
    }
    else if (Attribute == GetSkillAttackRateAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxSkillAttackRate());
    }
    else if (Attribute == GetStatusEffectMaxStackAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStatusEffectMaxStack());
    }
    else if (Attribute == GetProjectileCountAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxProjectileCount());
    }
    else if (Attribute == GetProjectilePierceCountAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxProjectilePierceCount());
    }
}

void UMJCharacterSkillAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,
	float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if (Attribute == GetMaxCooldownAttribute())
    {
        SetCooldown(FMath::Clamp(GetCooldown(), 0.f, GetMaxCooldown()));
    }
    else if (Attribute == GetMaxSkillAttackRateAttribute())
    {
        SetSkillAttackRate(FMath::Clamp(GetSkillAttackRate(), 0.f, GetMaxSkillAttackRate()));
    }
    else if (Attribute == GetMaxStatusEffectMaxStackAttribute())
    {
        SetStatusEffectMaxStack(FMath::Clamp(GetStatusEffectMaxStack(), 0.f, GetMaxStatusEffectMaxStack()));
    }
    else if (Attribute == GetMaxProjectileCountAttribute())
    {
        SetProjectileCount(FMath::Clamp(GetProjectileCount(), 0.f, GetMaxProjectileCount()));
    }
    else if (Attribute == GetMaxProjectilePierceCountAttribute())
    {
        SetProjectilePierceCount(FMath::Clamp(GetProjectilePierceCount(), 0.f, GetMaxProjectilePierceCount()));
    }

}

bool UMJCharacterSkillAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UMJCharacterSkillAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
    if (Data.EvaluatedData.Attribute == GetCooldownAttribute())
    {
        SetCooldown(FMath::Clamp(GetCooldown(), 0.f, GetMaxCooldown()));
    }
    else if (Data.EvaluatedData.Attribute == GetSkillAttackRateAttribute())
    {
        SetSkillAttackRate(FMath::Clamp(GetSkillAttackRate(), 0.f, GetMaxSkillAttackRate()));
    }
    else if (Data.EvaluatedData.Attribute == GetStatusEffectMaxStackAttribute())
    {
        SetStatusEffectMaxStack(FMath::Clamp(GetStatusEffectMaxStack(), 0.f, GetMaxStatusEffectMaxStack()));
    }
    else if (Data.EvaluatedData.Attribute == GetProjectileCountAttribute())
    {
        SetProjectileCount(FMath::Clamp(GetProjectileCount(), 0.f, GetMaxProjectileCount()));
    }
    else if (Data.EvaluatedData.Attribute == GetProjectilePierceCountAttribute())
    {
        SetProjectilePierceCount(FMath::Clamp(GetProjectilePierceCount(), 0.f, GetMaxProjectilePierceCount()));
    }
 }