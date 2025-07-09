// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

UMJCharacterSkillAttributeSet::UMJCharacterSkillAttributeSet() 
    : SkillLevel(0.0f)
    , MaxSkillLevel(0.0f)

    // Cost
    , CostStamina(0.0f)
    , MaxCostStamina(0.0f)
    , CostMana(0.0f)
    , MaxCostMana(0.0f)
    , CostFocus(0.0f)
    , MaxCostFocus(0.0f)

    // Damage / Scaling
    , BaseDamage(0.0f)
    , MaxBaseDamage(0.0f)
    , Healing(0.0f)
    , MaxHealing(0.0f)
    , LifeSteal(0.0f)
    , MaxLifeSteal(0.0f)
    , AttackDamageScaling(0.0f)
    , MaxAttackDamageScaling(0.0f)
    , AbilityPowerScaling(0.0f)
    , MaxAbilityPowerScaling(0.0f)

    // Range
    , SkillRadius(0.0f)
    , MaxSkillRadius(0.0f)
    , SkillRange(0.0f)
    , MaxSkillRange(0.0f)

    // Time
    , Cooldown(0.0f)
    , MaxCooldown(0.0f)
    , SkillAttackRate(0.0f)
    , MaxSkillAttackRate(0.0f)
    , CastTime(0.0f)
    , MaxCastTime(0.0f)
    , PreDelay(0.0f)
    , MaxPreDelay(0.0f)
    , PostDelay(0.0f)
    , MaxPostDelay(0.0f)
    , EffectDuration(0.0f)
    , MaxEffectDuration(0.0f)

    // Status effect
    , StatusEffectChance(0.0f)
    , MaxStatusEffectChance(0.0f)
    , StatusEffectDuration(0.0f)
    , MaxStatusEffectDuration(0.0f)

    // Projectile
    , ProjectileSpeed(0.0f)
    , MaxProjectileSpeed(0.0f)
    , ProjectileCount(0.0f)
    , MaxProjectileCount(0.0f)
{

}


void UMJCharacterSkillAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

    // TODO: 필요한  Attribute들 다 Clamp로 구간 잡아줘야 할거 같음

	//if (Attribute == GetSkillRangeAttribute())
	//{
	//	NewValue = FMath::Clamp(NewValue, 0.1f, GetMaxSkillRange());
	//}
	//else if (Attribute == GetSkillAttackRateAttribute())
	//{
	//	NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxSkillAttackRate());
	//}

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
