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
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UMJCharacterSkillAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UMJCharacterSkillAttributeSet();

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, CostStamina);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, CostMana);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, CostFocus);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, BaseDamage);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, AttackDamageScaling);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, AbilityPowerScaling);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, EffectRadius);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, SkillRange);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, SkillLevel);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, Cooldown);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, SkillAttackRate);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, CastTime);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, EffectDuration);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, StatusEffectChance);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, ProjectileSpeed);

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxCostStamina);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxCostMana);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxCostFocus);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxBaseDamage);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxAttackDamageScaling);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxAbilityPowerScaling);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxEffectRadius);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxSkillRange);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxSkillLevel);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxCooldown);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxSkillAttackRate);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxCastTime);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxEffectDuration);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxStatusEffectChance);
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxProjectileSpeed);



	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CostStamina;		 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CostMana;		 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CostFocus;		 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseDamage;		 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackDamageScaling;
											 
	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AbilityPowerScaling;
											 
	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData EffectRadius;	 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillRange;		 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillLevel;		 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Cooldown;		 

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CastTime;		 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData EffectDuration;	 
											 
	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StatusEffectChance;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ProjectileSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCostStamina;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCostMana;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCostFocus;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxBaseDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackDamageScaling;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAbilityPowerScaling;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxEffectRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillRange;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillLevel;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCooldown;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCastTime;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxEffectDuration;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStatusEffectChance;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxProjectileSpeed;
};
