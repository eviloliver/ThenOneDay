// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effect/MJGE_SetSkillAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

UMJGE_SetSkillAttributeSet::UMJGE_SetSkillAttributeSet()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

    struct FAttributeSetter
    {
        FGameplayAttribute Attribute;
        FName TagName;
    };

    const FAttributeSetter Attributes[] = {
        // Level
        { UMJCharacterSkillAttributeSet::GetSkillLevelAttribute(),           FName("Data.Skill.SkillLevel") },
        { UMJCharacterSkillAttributeSet::GetMaxSkillLevelAttribute(),        FName("Data.Skill.MaxSkillLevel") },

        // Cost
        { UMJCharacterSkillAttributeSet::GetCostStaminaAttribute(),          FName("Data.Skill.CostStamina") },
        { UMJCharacterSkillAttributeSet::GetMaxCostStaminaAttribute(),       FName("Data.Skill.MaxCostStamina") },
        { UMJCharacterSkillAttributeSet::GetCostManaAttribute(),             FName("Data.Skill.CostMana") },
        { UMJCharacterSkillAttributeSet::GetMaxCostManaAttribute(),          FName("Data.Skill.MaxCostMana") },
        { UMJCharacterSkillAttributeSet::GetCostFocusAttribute(),            FName("Data.Skill.CostFocus") },
        { UMJCharacterSkillAttributeSet::GetMaxCostFocusAttribute(),         FName("Data.Skill.MaxCostFocus") },

        // Damage / Scaling
        { UMJCharacterSkillAttributeSet::GetBaseDamageAttribute(),           FName("Data.Skill.BaseDamage") },
        { UMJCharacterSkillAttributeSet::GetMaxBaseDamageAttribute(),        FName("Data.Skill.MaxBaseDamage") },
        { UMJCharacterSkillAttributeSet::GetHealingAttribute(),              FName("Data.Skill.Healing") },
        { UMJCharacterSkillAttributeSet::GetMaxHealingAttribute(),           FName("Data.Skill.MaxHealing") },
        { UMJCharacterSkillAttributeSet::GetLifeStealAttribute(),            FName("Data.Skill.LifeSteal") },
        { UMJCharacterSkillAttributeSet::GetMaxLifeStealAttribute(),         FName("Data.Skill.MaxLifeSteal") },
        { UMJCharacterSkillAttributeSet::GetAttackDamageScalingAttribute(),  FName("Data.Skill.AttackDamageScaling") },
        { UMJCharacterSkillAttributeSet::GetMaxAttackDamageScalingAttribute(), FName("Data.Skill.MaxAttackDamageScaling") },
        { UMJCharacterSkillAttributeSet::GetAbilityPowerScalingAttribute(),  FName("Data.Skill.AbilityPowerScaling") },
        { UMJCharacterSkillAttributeSet::GetMaxAbilityPowerScalingAttribute(), FName("Data.Skill.MaxAbilityPowerScaling") },

        // Range
        { UMJCharacterSkillAttributeSet::GetSkillRadiusAttribute(),          FName("Data.Skill.SkillRadius") },
        { UMJCharacterSkillAttributeSet::GetMaxSkillRadiusAttribute(),       FName("Data.Skill.MaxSkillRadius") },
        { UMJCharacterSkillAttributeSet::GetSkillRangeAttribute(),           FName("Data.Skill.SkillRange") },
        { UMJCharacterSkillAttributeSet::GetMaxSkillRangeAttribute(),        FName("Data.Skill.MaxSkillRange") },

        // Time
        { UMJCharacterSkillAttributeSet::GetCooldownAttribute(),             FName("Data.Skill.Cooldown") },
        { UMJCharacterSkillAttributeSet::GetMaxCooldownAttribute(),          FName("Data.Skill.MaxCooldown") },
        { UMJCharacterSkillAttributeSet::GetSkillAttackRateAttribute(),      FName("Data.Skill.SkillAttackRate") },
        { UMJCharacterSkillAttributeSet::GetMaxSkillAttackRateAttribute(),   FName("Data.Skill.MaxSkillAttackRate") },
        { UMJCharacterSkillAttributeSet::GetCastTimeAttribute(),             FName("Data.Skill.CastTime") },
        { UMJCharacterSkillAttributeSet::GetMaxCastTimeAttribute(),          FName("Data.Skill.MaxCastTime") },
        { UMJCharacterSkillAttributeSet::GetPreDelayAttribute(),             FName("Data.Skill.PreDelay") },
        { UMJCharacterSkillAttributeSet::GetMaxPreDelayAttribute(),          FName("Data.Skill.MaxPreDelay") },
        { UMJCharacterSkillAttributeSet::GetPostDelayAttribute(),            FName("Data.Skill.PostDelay") },
        { UMJCharacterSkillAttributeSet::GetMaxPostDelayAttribute(),         FName("Data.Skill.MaxPostDelay") },
        { UMJCharacterSkillAttributeSet::GetEffectDurationAttribute(),       FName("Data.Skill.EffectDuration") },
        { UMJCharacterSkillAttributeSet::GetMaxEffectDurationAttribute(),    FName("Data.Skill.MaxEffectDuration") },

        // Status effect
        { UMJCharacterSkillAttributeSet::GetStatusEffectChanceAttribute(),   FName("Data.Skill.StatusEffectChance") },
        { UMJCharacterSkillAttributeSet::GetMaxStatusEffectChanceAttribute(), FName("Data.Skill.MaxStatusEffectChance") },
        { UMJCharacterSkillAttributeSet::GetStatusEffectDurationAttribute(), FName("Data.Skill.StatusEffectDuration") },
        { UMJCharacterSkillAttributeSet::GetMaxStatusEffectDurationAttribute(), FName("Data.Skill.MaxStatusEffectDuration") },

        // Projectile
        { UMJCharacterSkillAttributeSet::GetProjectileSpeedAttribute(),      FName("Data.Skill.ProjectileSpeed") },
        { UMJCharacterSkillAttributeSet::GetMaxProjectileSpeedAttribute(),   FName("Data.Skill.MaxProjectileSpeed") },
        { UMJCharacterSkillAttributeSet::GetProjectileCountAttribute(),      FName("Data.Skill.ProjectileCount") },
        { UMJCharacterSkillAttributeSet::GetMaxProjectileCountAttribute(),   FName("Data.Skill.MaxProjectileCount") }
    };

    for (const auto& Iter : Attributes)
    {
        FGameplayModifierInfo ModifierInfo;
        ModifierInfo.Attribute = Iter.Attribute;
        ModifierInfo.ModifierOp = EGameplayModOp::Override;

        FSetByCallerFloat SetByCaller;
        SetByCaller.DataTag = FGameplayTag::RequestGameplayTag(Iter.TagName);
        ModifierInfo.ModifierMagnitude = SetByCaller;
        Modifiers.Add(ModifierInfo);
    }

}
