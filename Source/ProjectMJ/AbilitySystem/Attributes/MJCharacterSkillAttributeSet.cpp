// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

UMJCharacterSkillAttributeSet::UMJCharacterSkillAttributeSet() 
    : SkillLevel(1.0f)
    , MaxSkillLevel(5.0f)

    // Cost
    , CostStamina(0.0f)
    , MaxCostStamina(100.0f)
    , CostMana(0.0f)
    , MaxCostMana(100.0f)
    , CostFocus(0.0f)
    , MaxCostFocus(100.0f)

    // Damage / Scaling
    , BaseDamage(10.0f)
    , MaxBaseDamage(999.0f)
    , Healing(0.0f)
    , MaxHealing(999.0f)
    , LifeSteal(0.0f)
    , MaxLifeSteal(1.0f)
    , AttackDamageScaling(1.0f)
    , MaxAttackDamageScaling(10.0f)
    , AbilityPowerScaling(1.0f)
    , MaxAbilityPowerScaling(10.0f)

    // Range
    , SkillRadius(100.0f)
    , MaxSkillRadius(1000.0f)
    , SkillRange(500.0f)
    , MaxSkillRange(5000.0f)

    // Time
    , Cooldown(1.0f)
    , MaxCooldown(60.0f)
    , SkillAttackRate(1.0f)
    , MaxSkillAttackRate(10.0f)
    , CastTime(0.0f)
    , MaxCastTime(10.0f)
    , PreDelay(0.0f)
    , MaxPreDelay(5.0f)
    , PostDelay(0.0f)
    , MaxPostDelay(5.0f)
    , EffectDuration(0.0f)
    , MaxEffectDuration(60.0f)

    // Status effect
    , StatusEffectChance(0.0f)
    , MaxStatusEffectChance(1.0f)
    , StatusEffectDuration(0.0f)
    , MaxStatusEffectDuration(60.0f)

    // Projectile
    , ProjectileSpeed(1000.0f)
    , MaxProjectileSpeed(10000.0f)
    , ProjectileCount(1.0f)
    , MaxProjectileCount(10.0f)
{

}


void UMJCharacterSkillAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

    // TODO: 필요한  Attribute들 다 Clamp로 구간 잡아줘야 할거 같음

	if (Attribute == GetSkillRangeAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.1f, GetMaxSkillRange());
	}
	else if (Attribute == GetSkillAttackRateAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxSkillAttackRate());
	}

}

void UMJCharacterSkillAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,
	float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

bool UMJCharacterSkillAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UMJCharacterSkillAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
