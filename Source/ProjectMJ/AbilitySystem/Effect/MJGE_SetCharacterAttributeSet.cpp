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

    // TODO: Max가 먼저 와야하는 문제
    const FAttributeSetter Attributes[] = {
        // Level
	    { UMJCharacterAttributeSet::GetMaxExperienceAttribute(),    FName("Data.Character.MaxExperience") },
        { UMJCharacterAttributeSet::GetExperienceAttribute(),       FName("Data.Character.Experience") },

		{ UMJCharacterAttributeSet::GetMaxDropExperienceAttribute(),    FName("Data.Character.MaxDropExperience") },
        { UMJCharacterAttributeSet::GetDropExperienceAttribute(),       FName("Data.Character.DropExperience") },

        // Resource
        { UMJCharacterAttributeSet::GetMaxHealthAttribute(),        FName("Data.Character.MaxHealth") },
        { UMJCharacterAttributeSet::GetHealthAttribute(),           FName("Data.Character.Health") },

        { UMJCharacterAttributeSet::GetHealthRegenerationAttribute(),   FName("Data.Character.HealthRegeneration") },

		{ UMJCharacterAttributeSet::GetMaxStaminaAttribute(),       FName("Data.Character.MaxStamina") },
        { UMJCharacterAttributeSet::GetStaminaAttribute(),          FName("Data.Character.Stamina") },

        { UMJCharacterAttributeSet::GetStaminaRegenerationAttribute(),  FName("Data.Character.StaminaRegeneration") },

		{ UMJCharacterAttributeSet::GetMaxManaAttribute(),          FName("Data.Character.MaxMana") },

        { UMJCharacterAttributeSet::GetManaAttribute(),             FName("Data.Character.Mana") },

        { UMJCharacterAttributeSet::GetManaRegenerationAttribute(),     FName("Data.Character.ManaRegeneration") },

		{ UMJCharacterAttributeSet::GetMaxFocusAttribute(),         FName("Data.Character.MaxFocus") },
        { UMJCharacterAttributeSet::GetFocusAttribute(),            FName("Data.Character.Focus") },

        { UMJCharacterAttributeSet::GetFocusRegenerationAttribute(),    FName("Data.Character.FocusRegeneration") },

        // Attack / Ability
        { UMJCharacterAttributeSet::GetAttackDamageAttribute(),     FName("Data.Character.AttackDamage") },

        { UMJCharacterAttributeSet::GetAbilityPowerAttribute(),     FName("Data.Character.AbilityPower") },

        // Armor / Resistance
        { UMJCharacterAttributeSet::GetArmorAttribute(),            FName("Data.Character.Armor") },

		{ UMJCharacterAttributeSet::GetMaxResistanceAttribute(),    FName("Data.Character.MaxResistance") },
        { UMJCharacterAttributeSet::GetResistanceAttribute(),       FName("Data.Character.Resistance") },

        // Attack Speed
        { UMJCharacterAttributeSet::GetMaxAttackSpeedAttribute(),   FName("Data.Character.MaxAttackSpeed") },
        { UMJCharacterAttributeSet::GetAttackSpeedAttribute(),      FName("Data.Character.AttackSpeed") },


        // Skill Cooldown
		{ UMJCharacterAttributeSet::GetMaxSkillCooldownAttribute(), FName("Data.Character.MaxSkillCooldown") },
        { UMJCharacterAttributeSet::GetSkillCooldownAttribute(),    FName("Data.Character.SkillCooldown") },

        // Critical
        { UMJCharacterAttributeSet::GetCriticalChanceAttribute(),   FName("Data.Character.CriticalChance") },

        { UMJCharacterAttributeSet::GetCriticalDamageAttribute(),   FName("Data.Character.CriticalDamage") },

        // MovementSpeed
		{ UMJCharacterAttributeSet::GetMaxMovementSpeedAttribute(), FName("Data.Character.MaxMovementSpeed") },
        { UMJCharacterAttributeSet::GetMovementSpeedAttribute(),    FName("Data.Character.MovementSpeed") },

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
