// Fill out your copyright notice in the Description page of Project Settings.


#include "MJCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "ProjectMJ.h"

UMJCharacterAttributeSet::UMJCharacterAttributeSet()
    :Level(1.0f)
	, MaxLevel(99.0f)
	, Experience(0.0f)
	, MaxExperience(999999.0f)
	, DropExperience(0.0f)
	, MaxDropExperience(999.0f)

	, Health(100.0f)
	, MaxHealth(100.0f)
	, HealthRegeneration(0.0f)
	, MaxHealthRegeneration(100.0f)
	, Stamina(100.0f)
	, MaxStamina(100.0f)
	, StaminaRegeneration(0.0f)
	, MaxStaminaRegeneration(100.0f)
	, Mana(100.0f)
	, MaxMana(100.0f)
	, ManaRegeneration(0.0f)
	, MaxManaRegeneration(100.0f)
	, Focus(100.0f)
	, MaxFocus(100.0f)
	, FocusRegeneration(0.0f)
	, MaxFocusRegeneration(100.0f)

	, AttackDamage(10.0f)
	, MaxAttackDamage(999.0f)
	, AbilityPower(10.0f)
	, MaxAbilityPower(999.0f)
	, Armor(0.0f)
	, MaxArmor(999.0f)
	, Resistance(0.0f)
	, MaxResistance(999.0f)

	, AttackSpeed(1.0f)
	, MaxAttackSpeed(10.0f)
	, SkillCooldown(1.0f)
	, MaxSkillCooldown(0.0f)

	, CriticalChance(0.0f)
	, MaxCriticalChance(100.0f)
	, CriticalDamage(0.0f)
	, MaxCriticalDamage(500.0f)

	, MovementSpeed(600.0f)
	, MaxMovementSpeed(1200.0f)

	, Damage(0.0f)
{
	InitHealth(GetMaxHealth());
	InitStamina(GetMaxStamina());
	InitMana(GetMaxMana());
	InitFocus(GetMaxFocus());
}

void UMJCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UMJCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

}

bool UMJCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	return true;
		
}

void UMJCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	// Effect 적용 후

	if (GetHealth() <= 0)
	{
		// Minjin: 데미지를 입힌 상대 전달
		OnDeath.Broadcast(Data.EffectSpec.GetEffectContext().GetEffectCauser());
	}

}