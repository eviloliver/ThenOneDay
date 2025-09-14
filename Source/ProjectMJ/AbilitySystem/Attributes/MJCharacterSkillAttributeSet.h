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
 * Created Date: 2025.06.18
 * Description of Change: 상태이상 값 추가
 * Modified By: 신동민
 * Modified Date: 2025.07.28
 * * Description of Change: 투사체 값 추가
 * Modified By: 신동민
 * Modified Date: 2025.07.31
 * Description of Change: 트레이스 위치 오프셋 값 추가
 * Modified By: 김민진
 * Modified Date: 2025.08.05.
 * Description of Change: 안쓰는 Max 지우기
 * Modified By: 신동민
 * Modified Date: 2025.08.11
 */
UCLASS()
class PROJECTMJ_API UMJCharacterSkillAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	public:
	UMJCharacterSkillAttributeSet();

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

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, SkillAttackLocationOffset)
	
	// Time
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, Cooldown)
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxCooldown)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, SkillAttackRate)
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxSkillAttackRate)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, CastTime)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, PreDelay)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, PostDelay)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, EffectDuration)

	// Status effect
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, StatusEffectChance)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, StatusEffectDuration)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, StatusBaseDamage)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, StatusEffectADScaling)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, StatusEffectAPScaling)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, StatusEffectMaxStack)
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxStatusEffectMaxStack)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, StatusEffectPeriod)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, StatusEffectSlowPercent);

	// Projectile
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, ProjectileSpeed)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, ProjectileCount)
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxProjectileCount)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, ProjectileLifeSpan)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, ProjectilePierceCount)
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, MaxProjectilePierceCount)

	// Explosion
	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, ExplosionRadius)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, ExplosionBaseDamage)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, ExplosionADScaling)

	ATTRIBUTE_ACCESSORS(UMJCharacterSkillAttributeSet, ExplosionAPScaling)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:

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

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Range", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillAttackLocationOffset;

	// Time
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Cooldown;
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCooldown;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SkillAttackRate;
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Time", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSkillAttackRate;

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

	UPROPERTY(BlueprintReadOnly, Category = "Skill|StatusEffect", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StatusEffectADScaling;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|StatusEffect", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StatusBaseDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|StatusEffect", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StatusEffectAPScaling;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|StatusEffect", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StatusEffectMaxStack;
	UPROPERTY(BlueprintReadOnly, Category = "Skill|StatusEffect", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStatusEffectMaxStack;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|StatusEffect", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StatusEffectPeriod;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|StatusEffect", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StatusEffectSlowPercent;

	// Projectile
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Projectile", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ProjectileSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Projectile", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ProjectileCount;
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Projectile", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxProjectileCount;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Projectile", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ProjectileLifeSpan;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Projectile", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ProjectilePierceCount;
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Projectile", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxProjectilePierceCount;

	// Explosion
	UPROPERTY(BlueprintReadOnly, Category = "Skill|Explosion", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ExplosionRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Explosion", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ExplosionBaseDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Explosion", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ExplosionADScaling;

	UPROPERTY(BlueprintReadOnly, Category = "Skill|Explosion", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ExplosionAPScaling;

};
