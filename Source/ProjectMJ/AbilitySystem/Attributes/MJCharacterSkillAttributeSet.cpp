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
        ClampBaseToMax(GetCooldownAttribute(), GetMaxCooldownAttribute(), 0.f);
    }
    else if (Attribute == GetSkillAttackRateAttribute())
    {
        ClampBaseToMax(GetSkillAttackRateAttribute(), GetMaxSkillAttackRateAttribute(), 0.f);
    }
    else if (Attribute == GetStatusEffectMaxStackAttribute())
    {
        ClampBaseToMax(GetStatusEffectMaxStackAttribute(), GetMaxStatusEffectMaxStackAttribute(), 0.f);
    }
    else if (Attribute == GetProjectileCountAttribute())
    {
        ClampBaseToMax(GetProjectileCountAttribute(), GetMaxProjectileCountAttribute(), 0.f);
    }
    else if (Attribute == GetProjectilePierceCountAttribute())
    {
        ClampBaseToMax(GetProjectilePierceCountAttribute(), GetMaxProjectilePierceCountAttribute(), 0.f);
    }
}

void UMJCharacterSkillAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,
	float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if (Attribute == GetMaxCooldownAttribute())
    {
        ClampBaseToMax(GetCooldownAttribute(), GetMaxCooldownAttribute(), 0.f);
    }
    else if (Attribute == GetMaxSkillAttackRateAttribute())
    {
	    ClampBaseToMax(GetSkillAttackRateAttribute(), GetMaxSkillAttackRateAttribute(), 0.f);
    }
    else if (Attribute == GetMaxStatusEffectMaxStackAttribute())
    {
	    ClampBaseToMax(GetStatusEffectMaxStackAttribute(), GetMaxStatusEffectMaxStackAttribute(), 0.f);
    }
    else if (Attribute == GetMaxProjectileCountAttribute())
    {
	    ClampBaseToMax(GetProjectileCountAttribute(), GetMaxProjectileCountAttribute(), 0.f);
    }
    else if (Attribute == GetMaxProjectilePierceCountAttribute())
    {
	    ClampBaseToMax(GetProjectilePierceCountAttribute(), GetMaxProjectilePierceCountAttribute(), 0.f);
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
	    ClampBaseToMax(GetCooldownAttribute(), GetMaxCooldownAttribute(), 0.f);
    }
    else if (Data.EvaluatedData.Attribute == GetSkillAttackRateAttribute())
    {
	    ClampBaseToMax(GetSkillAttackRateAttribute(), GetMaxSkillAttackRateAttribute(), 0.f);
    }
    else if (Data.EvaluatedData.Attribute == GetStatusEffectMaxStackAttribute())
    {
	    ClampBaseToMax(GetStatusEffectMaxStackAttribute(), GetMaxStatusEffectMaxStackAttribute(), 0.f);
    }
    else if (Data.EvaluatedData.Attribute == GetProjectileCountAttribute())
    {
	    ClampBaseToMax(GetProjectileCountAttribute(), GetMaxProjectileCountAttribute(), 0.f);
    }
    else if (Data.EvaluatedData.Attribute == GetProjectilePierceCountAttribute())
    {
	    ClampBaseToMax(GetProjectilePierceCountAttribute(), GetMaxProjectilePierceCountAttribute(), 0.f);
    }
 }

void UMJCharacterSkillAttributeSet::ClampBaseToMax(const FGameplayAttribute& BaseAttribute,
	const FGameplayAttribute& MaxAttribute, float Min)
{
    UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(GetOwningAbilitySystemComponent());
    if (!ASC)
    {
        MJ_LOG(LogMJ, Warning, TEXT("Not Exist ASC"));
        return;
    }
    const float MaxValue = MaxAttribute.GetNumericValue(this);
    const float CurrentValue = BaseAttribute.GetNumericValue(this);
    const float Clamped = FMath::Clamp(CurrentValue, Min, MaxValue);
    if (!FMath::IsNearlyEqual(CurrentValue, Clamped))
    {
        ASC->ApplyModToAttributeUnsafe(BaseAttribute, EGameplayModOp::Additive, Clamped - CurrentValue);
    }
}
