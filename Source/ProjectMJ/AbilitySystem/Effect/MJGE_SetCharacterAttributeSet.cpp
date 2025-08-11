// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effect/MJGE_SetCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"

UMJGE_SetCharacterAttributeSet::UMJGE_SetCharacterAttributeSet()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

    struct FAttributeSetter
    {
        FGameplayAttribute Attribute;
        FName TagName;
    };

    const FAttributeSetter Attributes[] = {
        // Level
        { UMJCharacterAttributeSet::GetExperienceAttribute(),       FName("Data.Character.Experience") },
        { UMJCharacterAttributeSet::GetMaxExperienceAttribute(),    FName("Data.Character.MaxExperience") },

        { UMJCharacterAttributeSet::GetDropExperienceAttribute(),       FName("Data.Character.DropExperience") },
        { UMJCharacterAttributeSet::GetMaxDropExperienceAttribute(),    FName("Data.Character.MaxDropExperience") },

        // Resource
        { UMJCharacterAttributeSet::GetHealthAttribute(),           FName("Data.Character.Health") },
        { UMJCharacterAttributeSet::GetMaxHealthAttribute(),        FName("Data.Character.MaxHealth") },

        { UMJCharacterAttributeSet::GetHealthRegenerationAttribute(),   FName("Data.Character.HealthRegeneration") },
        { UMJCharacterAttributeSet::GetMaxHealthRegenerationAttribute(),FName("Data.Character.MaxHealthRegeneration") },

        { UMJCharacterAttributeSet::GetStaminaAttribute(),          FName("Data.Character.Stamina") },
        { UMJCharacterAttributeSet::GetMaxStaminaAttribute(),       FName("Data.Character.MaxStamina") },

        { UMJCharacterAttributeSet::GetStaminaRegenerationAttribute(),  FName("Data.Character.StaminaRegeneration") },

        { UMJCharacterAttributeSet::GetManaAttribute(),             FName("Data.Character.Mana") },
        { UMJCharacterAttributeSet::GetMaxManaAttribute(),          FName("Data.Character.MaxMana") },

        { UMJCharacterAttributeSet::GetManaRegenerationAttribute(),     FName("Data.Character.ManaRegeneration") },

        { UMJCharacterAttributeSet::GetFocusAttribute(),            FName("Data.Character.Focus") },
        { UMJCharacterAttributeSet::GetMaxFocusAttribute(),         FName("Data.Character.MaxFocus") },

        { UMJCharacterAttributeSet::GetFocusRegenerationAttribute(),    FName("Data.Character.FocusRegeneration") },

        // Attack / Ability
        { UMJCharacterAttributeSet::GetAttackDamageAttribute(),     FName("Data.Character.AttackDamage") },

        { UMJCharacterAttributeSet::GetAbilityPowerAttribute(),     FName("Data.Character.AbilityPower") },

        // Armor / Resistance
        { UMJCharacterAttributeSet::GetArmorAttribute(),            FName("Data.Character.Armor") },

        { UMJCharacterAttributeSet::GetResistanceAttribute(),       FName("Data.Character.Resistance") },
        { UMJCharacterAttributeSet::GetMaxResistanceAttribute(),    FName("Data.Character.MaxResistance") },

        // Attack Speed
        { UMJCharacterAttributeSet::GetAttackSpeedAttribute(),      FName("Data.Character.AttackSpeed") },
        { UMJCharacterAttributeSet::GetMaxAttackSpeedAttribute(),   FName("Data.Character.MaxAttackSpeed") },

        // Skill Cooldown
        { UMJCharacterAttributeSet::GetSkillCooldownAttribute(),    FName("Data.Character.SkillCooldown") },
        { UMJCharacterAttributeSet::GetMaxSkillCooldownAttribute(), FName("Data.Character.MaxSkillCooldown") },

        // Critical
        { UMJCharacterAttributeSet::GetCriticalChanceAttribute(),   FName("Data.Character.CriticalChance") },

        { UMJCharacterAttributeSet::GetCriticalDamageAttribute(),   FName("Data.Character.CriticalDamage") },

        // MovementSpeed
        { UMJCharacterAttributeSet::GetMovementSpeedAttribute(),    FName("Data.Character.MovementSpeed") },
        { UMJCharacterAttributeSet::GetMaxMovementSpeedAttribute(), FName("Data.Character.MaxMovementSpeed") },

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
