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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageDelegate, float, Data, bool, IsCritical);

/**
 * Class Description: 캐릭터 어트리뷰트 세트
 * Author: 차태관
 * Created Date: 미상
 * Last Modified By: 신동민
 * Last Modified Date: 2025-06-19
 * Last Modified By: 김민진
 * Last Modified Date: (2025.07.22.) FOnDeathDelegate EffectCauser를 전달하게 수정
 */
UCLASS()
class PROJECTMJ_API UMJCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UMJCharacterAttributeSet();

	// Level
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Experience)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxExperience)

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, DropExperience)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxDropExperience)

	// Resource
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxHealth)

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, HealthRegeneration)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxHealthRegeneration)

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Stamina)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxStamina)

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, StaminaRegeneration)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxStaminaRegeneration)

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxMana)

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, ManaRegeneration)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxManaRegeneration)

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Focus)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxFocus)

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, FocusRegeneration)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxFocusRegeneration)

	// Attack / Ability
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, AttackDamage)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxAttackDamage)

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, AbilityPower)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxAbilityPower)

	// Armor / Resistance (for future)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Armor)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxArmor)

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Resistance)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxResistance)

	// Attack Speed
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, AttackSpeed)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxAttackSpeed)

	// Skill Cooldown(Haste)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, SkillCooldown)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxSkillCooldown)

	// Critical
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, CriticalChance)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxCriticalChance)

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, CriticalDamage)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxCriticalDamage)

	// MovementSpeed
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MovementSpeed)
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxMovementSpeed)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


	// mutable FOnDeathDelegate OnDeath;
	mutable FOnDamageDelegate OnDamage;
	

	// EC에서 접근하게 해주기 위해서
	// 이거 아니면 접근지정자를 public으로 하는건데 Aura는 Public, 보통은 캡슐화를 위해서 protected(friend 하긴 하지만 그래도 최소한의 캡슐화)
	friend struct FMJEC_SkillDamageStatics;
	friend struct FMJEC_DamageOverTimeStatics;
	friend struct FMJEC_MovementSpeedModifierStatics;

protected:

	// Level
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Experience;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxExperience;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData DropExperience;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxDropExperience;

	// Resource
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData HealthRegeneration;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealthRegeneration;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Stamina;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StaminaRegeneration;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStaminaRegeneration;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mana;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ManaRegeneration;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxManaRegeneration;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Focus;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxFocus;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData FocusRegeneration;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxFocusRegeneration;

	// Attack / Ability
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Attack/Ability", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackDamage;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Attack/Ability", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Attack/Ability", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AbilityPower;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Attack/Ability", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAbilityPower;

	// Armor / Resistance
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Armor/Resistance", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Armor;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Armor/Resistance", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxArmor;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Armor/Resistance", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Resistance;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Armor/Resistance", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxResistance;

	// Attack Speed
	UPROPERTY(BlueprintReadOnly, Category = "Stat|AttackSpeed", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|AttackSpeed", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackSpeed;

	// Skill Cooldown(Haste)
	UPROPERTY(BlueprintReadOnly, Category = "Stat|SkillCooldown", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillCooldown;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|SkillCooldown", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillCooldown;

	// Critical
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Critical", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CriticalChance;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Critical", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCriticalChance;

	UPROPERTY(BlueprintReadOnly, Category = "Stat|Critical", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CriticalDamage;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|Critical", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCriticalDamage;

	// MovementSpeed
	UPROPERTY(BlueprintReadOnly, Category = "Stat|MovementSpeed", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MovementSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "Stat|MovementSpeed", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMovementSpeed;

	// Penetration (For future implementation)
};
