// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

UMJCharacterSkillAttributeSet::UMJCharacterSkillAttributeSet() 
    : CostStamina(0.f)
    , CostMana(0.f)
    , CostFocus(0.f)
    , BaseDamage(0.f)
    , AttackDamageScaling(1.f)
    , AbilityPowerScaling(1.f)
    , EffectRadius(100.f)
    , SkillRange(300.f)
    , SkillLevel(1.f)
    , Cooldown(1.f)
    , SkillAttackRate(1.f)
    , CastTime(0.f)
    , EffectDuration(0.f)
    , StatusEffectChance(0.f)
    , ProjectileSpeed(600.f)

    , MaxCostStamina(100.f)
    , MaxCostMana(100.f)
    , MaxCostFocus(100.f)
    , MaxBaseDamage(9999.f)
    , MaxAttackDamageScaling(10.f)
    , MaxAbilityPowerScaling(10.f)
    , MaxEffectRadius(5000.f)
    , MaxSkillRange(5000.f)
    , MaxSkillLevel(10.f)
    , MaxCooldown(30.f)
    , MaxSkillAttackRate(5.f)
    , MaxCastTime(10.f)
    , MaxEffectDuration(60.f)
    , MaxStatusEffectChance(100.f)
    , MaxProjectileSpeed(3000.f)
{

}


void UMJCharacterSkillAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetSkillRangeAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.1f, GetMaxSkillRange());
	}
	else if (Attribute == GetSkillAttackRateAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxSkillAttackRate());
	}
}
