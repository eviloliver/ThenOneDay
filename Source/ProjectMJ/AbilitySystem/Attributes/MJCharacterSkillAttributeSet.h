// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MJCharacterSkillAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Class Description: 스킬 어트리뷰트 세트
 * Author: 신동민
 * Created Date: 2025_06_18
 * Last Modified By: 신동민
 * Last Modified Date: 2025_06_19
 */
UCLASS()
class PROJECTMJ_API UMJCharacterSkillAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UMJCharacterSkillAttributeSet();

	// Level
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, SkillLevel)

		// Cost
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, CostStamina)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, CostMana)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, CostFocus)

		// Damage / Scaling
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, BaseDamage)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, Healing)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, LifeSteal)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, AttackDamageScaling)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, AbilityPowerScaling)

		// Range
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, SkillRadius)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, SkillRange)

		// Time
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, Cooldown)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, SkillAttackRate)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, CastTime)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, PreDelay)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, PostDelay)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, EffectDuration)

		// Status effect
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, StatusEffectChance)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, StatusEffectDuration)

		// Projectile
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, ProjectileSpeed)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, ProjectileCount)


		// --- Max Skill ---

		// Level
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxSkillLevel)

		// Cost
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxCostStamina)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxCostMana)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxCostFocus)

		// Damage / Scaling
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxBaseDamage)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxHealing)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxLifeSteal)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxAttackDamageScaling)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxAbilityPowerScaling)

		// Range
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxSkillRadius)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxSkillRange)

		// Time
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxCooldown)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxSkillAttackRate)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxCastTime)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxPreDelay)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxPostDelay)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxEffectDuration)

		// Status effect
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxStatusEffectChance)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxStatusEffectDuration)

		// Projectile
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxProjectileSpeed)
		ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxProjectileCount)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	// Level
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillLevel;

	// Cost
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Cost", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CostStamina;		 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Cost", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CostMana;		 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Cost", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CostFocus;		 

	// Damage / Scaling
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Healing;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData LifeSteal;
											 
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackDamageScaling;
											 
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AbilityPowerScaling;

	// Range
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Range", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillRadius;	 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Range", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillRange;

	// Time
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Cooldown;		 

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CastTime;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData PreDelay;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData PostDelay;
											 
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData EffectDuration;	 

	// Status effect
	UPROPERTY(BlueprintReadOnly, Category = "Skill|StatusEffect", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StatusEffectChance;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|StatusEffect", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StatusEffectDuration;
	// Projectile
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Projectile", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ProjectileSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Projectile", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ProjectileCount;

	// --- Max Ability ---
	// Level
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Level", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillLevel;

	// Cost
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Cost", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCostStamina;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Cost", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCostMana;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Cost", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCostFocus;

	// Damage / Scaling
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxBaseDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealing;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxLifeSteal;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackDamageScaling;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAbilityPowerScaling;

	// Range
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Range", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Range", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillRange;

	// Time
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCooldown;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCastTime;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxPreDelay;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxPostDelay;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxEffectDuration;

	// Status effect
	UPROPERTY(BlueprintReadOnly, Category = "Skill|StatusEffect", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStatusEffectChance;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|StatusEffect", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStatusEffectDuration;

	// Projectile
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Projectile", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxProjectileSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Projectile", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxProjectileCount;

};
