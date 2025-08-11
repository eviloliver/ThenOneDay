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

        // Cost
        { UMJCharacterSkillAttributeSet::GetCostStaminaAttribute(),          FName("Data.Skill.CostStamina") },
        { UMJCharacterSkillAttributeSet::GetCostManaAttribute(),             FName("Data.Skill.CostMana") },
        { UMJCharacterSkillAttributeSet::GetCostFocusAttribute(),            FName("Data.Skill.CostFocus") },

        // Damage / Scaling
        { UMJCharacterSkillAttributeSet::GetBaseDamageAttribute(),           FName("Data.Skill.BaseDamage") },
        { UMJCharacterSkillAttributeSet::GetHealingAttribute(),              FName("Data.Skill.Healing") },
        { UMJCharacterSkillAttributeSet::GetLifeStealAttribute(),            FName("Data.Skill.LifeSteal") },
        { UMJCharacterSkillAttributeSet::GetAttackDamageScalingAttribute(),  FName("Data.Skill.AttackDamageScaling") },
        { UMJCharacterSkillAttributeSet::GetAbilityPowerScalingAttribute(),  FName("Data.Skill.AbilityPowerScaling") },

        // Range
        { UMJCharacterSkillAttributeSet::GetSkillRadiusAttribute(),          FName("Data.Skill.SkillRadius") },
        { UMJCharacterSkillAttributeSet::GetSkillRangeAttribute(),           FName("Data.Skill.SkillRange") },
        { UMJCharacterSkillAttributeSet::GetSkillAttackLocationOffsetAttribute(), FName("Data.Skill.SkillAttackLocationOffset") },

        // Time
        { UMJCharacterSkillAttributeSet::GetCooldownAttribute(),             FName("Data.Skill.Cooldown") },
        { UMJCharacterSkillAttributeSet::GetMaxCooldownAttribute(),          FName("Data.Skill.MaxCooldown") },
        { UMJCharacterSkillAttributeSet::GetSkillAttackRateAttribute(),      FName("Data.Skill.SkillAttackRate") },
        { UMJCharacterSkillAttributeSet::GetMaxSkillAttackRateAttribute(),   FName("Data.Skill.MaxSkillAttackRate") },
        { UMJCharacterSkillAttributeSet::GetCastTimeAttribute(),             FName("Data.Skill.CastTime") },
        { UMJCharacterSkillAttributeSet::GetPreDelayAttribute(),             FName("Data.Skill.PreDelay") },
        { UMJCharacterSkillAttributeSet::GetPostDelayAttribute(),            FName("Data.Skill.PostDelay") },
        { UMJCharacterSkillAttributeSet::GetEffectDurationAttribute(),       FName("Data.Skill.EffectDuration") },

        // Status effect
        { UMJCharacterSkillAttributeSet::GetStatusEffectChanceAttribute(),   FName("Data.Skill.StatusEffectChance") },
        { UMJCharacterSkillAttributeSet::GetStatusEffectDurationAttribute(), FName("Data.Skill.StatusEffectDuration") },
        { UMJCharacterSkillAttributeSet::GetStatusBaseDamageAttribute(),     FName("Data.Skill.StatusBaseDamage") },
        { UMJCharacterSkillAttributeSet::GetStatusEffectADScalingAttribute(),FName("Data.Skill.StatusEffectADScaling") },
        { UMJCharacterSkillAttributeSet::GetStatusEffectAPScalingAttribute(), FName("Data.Skill.StatusEffectAPScaling") },
        { UMJCharacterSkillAttributeSet::GetStatusEffectMaxStackAttribute(), FName("Data.Skill.StatusEffectMaxStack") },
        { UMJCharacterSkillAttributeSet::GetMaxStatusEffectMaxStackAttribute(), FName("Data.Skill.MaxStatusEffectMaxStack") },
        { UMJCharacterSkillAttributeSet::GetStatusEffectPeriodAttribute(), FName("Data.Skill.StatusEffectPeriod") },
        { UMJCharacterSkillAttributeSet::GetStatusEffectSlowPercentAttribute(),FName("Data.Skill.StatusEffectSlowPercent") },

        // Projectile
        { UMJCharacterSkillAttributeSet::GetProjectileSpeedAttribute(),      FName("Data.Skill.ProjectileSpeed") },
        { UMJCharacterSkillAttributeSet::GetProjectileCountAttribute(),      FName("Data.Skill.ProjectileCount") },
        { UMJCharacterSkillAttributeSet::GetMaxProjectileCountAttribute(),   FName("Data.Skill.MaxProjectileCount") },
        { UMJCharacterSkillAttributeSet::GetProjectileLifeSpanAttribute(),   FName("Data.Skill.ProjectileLifeSpan") },
        { UMJCharacterSkillAttributeSet::GetProjectilePierceCountAttribute(),   FName("Data.Skill.ProjectilePierceCount") },
        { UMJCharacterSkillAttributeSet::GetMaxProjectilePierceCountAttribute(),   FName("Data.Skill.MaxProjectilePierceCount") },

    	// Explosion
        { UMJCharacterSkillAttributeSet::GetExplosionRadiusAttribute(), FName("Data.Skill.ExplosionRadius") },
        { UMJCharacterSkillAttributeSet::GetExplosionBaseDamageAttribute(), FName("Data.Skill.ExplosionBaseDamage") },
        { UMJCharacterSkillAttributeSet::GetExplosionADScalingAttribute(), FName("Data.Skill.ExplosionADScaling") },
        { UMJCharacterSkillAttributeSet::GetExplosionAPScalingAttribute(), FName("Data.Skill.ExplosionAPScaling") },

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
