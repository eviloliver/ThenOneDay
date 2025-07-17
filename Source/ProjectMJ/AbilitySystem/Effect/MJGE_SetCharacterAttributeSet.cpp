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
        { UMJCharacterAttributeSet::GetLevelAttribute(),            FName("Data.Character.Level") },
        { UMJCharacterAttributeSet::GetMaxLevelAttribute(),         FName("Data.Character.MaxLevel") },

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
        { UMJCharacterAttributeSet::GetMaxStaminaRegenerationAttribute(),FName("Data.Character.MaxStaminaRegeneration") },

        { UMJCharacterAttributeSet::GetManaAttribute(),             FName("Data.Character.Mana") },
        { UMJCharacterAttributeSet::GetMaxManaAttribute(),          FName("Data.Character.MaxMana") },

        { UMJCharacterAttributeSet::GetManaRegenerationAttribute(),     FName("Data.Character.ManaRegeneration") },
        { UMJCharacterAttributeSet::GetMaxManaRegenerationAttribute(),  FName("Data.Character.MaxManaRegeneration") },

        { UMJCharacterAttributeSet::GetFocusAttribute(),            FName("Data.Character.Focus") },
        { UMJCharacterAttributeSet::GetMaxFocusAttribute(),         FName("Data.Character.MaxFocus") },

        { UMJCharacterAttributeSet::GetFocusRegenerationAttribute(),    FName("Data.Character.FocusRegeneration") },
        { UMJCharacterAttributeSet::GetMaxFocusRegenerationAttribute(), FName("Data.Character.MaxFocusRegeneration") },

        // Attack / Ability
        { UMJCharacterAttributeSet::GetAttackDamageAttribute(),     FName("Data.Character.AttackDamage") },
        { UMJCharacterAttributeSet::GetMaxAttackDamageAttribute(),  FName("Data.Character.MaxAttackDamage") },

        { UMJCharacterAttributeSet::GetAbilityPowerAttribute(),     FName("Data.Character.AbilityPower") },
        { UMJCharacterAttributeSet::GetMaxAbilityPowerAttribute(),  FName("Data.Character.MaxAbilityPower") },

        // Armor / Resistance
        { UMJCharacterAttributeSet::GetArmorAttribute(),            FName("Data.Character.Armor") },
        { UMJCharacterAttributeSet::GetMaxArmorAttribute(),         FName("Data.Character.MaxArmor") },

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
        { UMJCharacterAttributeSet::GetMaxCriticalChanceAttribute(),FName("Data.Character.MaxCriticalChance") },

        { UMJCharacterAttributeSet::GetCriticalDamageAttribute(),   FName("Data.Character.CriticalDamage") },
        { UMJCharacterAttributeSet::GetMaxCriticalDamageAttribute(),FName("Data.Character.MaxCriticalDamage") },

        // MovementSpeed
        { UMJCharacterAttributeSet::GetMovementSpeedAttribute(),    FName("Data.Character.MovementSpeed") },
        { UMJCharacterAttributeSet::GetMaxMovementSpeedAttribute(), FName("Data.Character.MaxMovementSpeed") },

        // Damage
        { UMJCharacterAttributeSet::GetDamageAttribute(),           FName("Data.Character.Damage") }
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
