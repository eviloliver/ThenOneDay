#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "MJCharacterSkillAttributeSaveData.generated.h"

USTRUCT(BlueprintType)
struct FMJCharacterSkillAttributeSaveData
{
	GENERATED_BODY()

	// Level
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float SkillLevel;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxSkillLevel;

	// Cost
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float CostStamina;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxCostStamina;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float CostMana;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxCostMana;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float CostFocus;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxCostFocus;

	// Damage / Scaling
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float BaseDamage;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxBaseDamage;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Healing;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxHealing;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float LifeSteal;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxLifeSteal;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float AttackDamageScaling;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxAttackDamageScaling;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float AbilityPowerScaling;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxAbilityPowerScaling;

	// Range
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float SkillRadius;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxSkillRadius;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float SkillRange;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxSkillRange;

	// Time
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Cooldown;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxCooldown;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float SkillAttackRate;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxSkillAttackRate;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float CastTime;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxCastTime;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float PreDelay;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxPreDelay;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float PostDelay;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxPostDelay;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float EffectDuration;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxEffectDuration;

	// Status effect
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float StatusEffectChance;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxStatusEffectChance;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float StatusEffectDuration;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxStatusEffectDuration;

	// Projectile
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float ProjectileSpeed;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxProjectileSpeed;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float ProjectileCount;
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxProjectileCount;

	// Operator overload
	FMJCharacterSkillAttributeSaveData& operator=(const UMJCharacterSkillAttributeSet& AttributeSet);

	// Apply saved data
	void ApplyToAttributeSet(UMJCharacterSkillAttributeSet& AttributeSet) const;
};
