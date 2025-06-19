// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MJCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Class Description: 캐릭터 어트리뷰트 세트
 * Author: 차태관
 * Created Date: 미상
 * Last Modified By: 신동민
 * Last Modified Date: 2025-06-19
 */
UCLASS()
class PROJECTMJ_API UMJCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UMJCharacterAttributeSet();

	// Level
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Level)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Experience)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, DropExperience)

	// Resource
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, HealthRegeneration)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Stamina)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, StaminaRegeneration)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, ManaRegeneration)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Focus)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, FocusRegeneration)

	// Attack / Ability
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, AttackDamage)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, AbilityPower)

	// Armor / Resistance
	//For future implementation
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Armor)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Resistance)

	// Attack Speed
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, AttackSpeed)

	// Skill Cooldown(Haste)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, SkillCooldown)

	// Critical
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, CriticalChance)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, CriticalDamage)

	// MovementSpeed
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MovementSpeed)

	// --- Max Stat ---

	// Level
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxLevel)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxExperience)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxDropExperience)

	// Resource
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxHealthRegeneration)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxStamina)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxStaminaRegeneration)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxMana)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxManaRegeneration)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxFocus)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxFocusRegeneration)

	// Attack / Ability
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxAttackDamage)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxAbilityPower)

	// Armor / Resistance
	// For future implementation
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxArmor)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxResistance)

	// Attack Speed
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxAttackSpeed)

	// Skill Cooldown(Haste)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxSkillCooldown)

	// Critical
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxCriticalChance)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxCriticalDamage)

	// MovementSpeed
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxMovementSpeed)

	// --- Damage ---
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Damage)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:

	// Level
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Level;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Experience;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData DropExperience;

	// Resource
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData HealthRegeneration;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StaminaRegeneration;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ManaRegeneration;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Focus;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData FocusRegeneration;

	// Attack / Ability
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Attack/Ability", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Attack/Ability", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AbilityPower;

	// Armor / Resistance
	// For future implementation
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Armor/Resistance", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Armor;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Armor/Resistance", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Resistance;

	// Attack Speed
	UPROPERTY(BlueprintReadOnly, Category = "Stat|AttackSpeed", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackSpeed;

	// Skill Cooldown(Haste)
	UPROPERTY(BlueprintReadOnly, Category = "Stat|SkillCooldown", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillCooldown;

	// Critical
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Critical", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CriticalChance;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Critical", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CriticalDamage;

	// MovementSpeed
	UPROPERTY(BlueprintReadOnly, Category = "Stat|MovementSpeed", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MovementSpeed;

	// Penetration
	// For future implementation

	// --- Max Stat ---

	// Level
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxLevel;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxExperience;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxDropExperience;

	// Resource
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealthRegeneration;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStaminaRegeneration;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxManaRegeneration;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxFocus;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxFocusRegeneration;

	// Attack / Ability
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Attack/Ability", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Attack/Ability", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAbilityPower;

	// Armor / Resistance
	// For future implementation
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Armor/Resistance", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxArmor;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Armor/Resistance", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxResistance;

	// Attack Speed
	UPROPERTY(BlueprintReadOnly, Category = "Stat|AttackSpeed", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackSpeed;

	// Skill Cooldown(Haste)
	UPROPERTY(BlueprintReadOnly, Category = "Stat|SkillCooldown", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillCooldown;

	// Critical
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Critical", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCriticalChance;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Critical", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCriticalDamage;

	// MovementSpeed
	UPROPERTY(BlueprintReadOnly, Category = "Stat|MovementSpeed", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMovementSpeed;

	// Penetration
	// For future implementation

	// --- Damage ---
	UPROPERTY(BlueprintReadOnly, Category = "Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;
};
