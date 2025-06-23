#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MJCharacterAttributeSet.h"
#include "MJCharacterAttributeSaveDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FCharacterAttributeSaveData
{
	GENERATED_BODY()

	// TODO 필요한 Attribute 만 담기
	
	// Stat | Level
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Level;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxLevel;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Experience;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxExperience;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float DropExperience;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxDropExperience;
	
	// Stat | Resource
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Health;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxHealth;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float HealthRegeneration;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxHealthRegeneration;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Stamina;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxStamina;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float StaminaRegeneration;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxStaminaRegeneration;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Mana;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxMana;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float ManaRegeneration;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxManaRegeneration;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Focus;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxFocus;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float FocusRegeneration;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxFocusRegeneration;
	
	// Attack / Ability
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float AttackDamage;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxAttackDamage;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float AbilityPower;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxAbilityPower;
	
	// Armor / Resistance
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Armor;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxArmor;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Resistance;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxResistance;
	
	// Attack Speed
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float AttackSpeed;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxAttackSpeed;
	
	// Skill Cooldown
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float SkillCooldown;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxSkillCooldown;
	
	// Critical
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float CriticalChance;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxCriticalChance;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float CriticalDamage;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxCriticalDamage;
	
	// MovementSpeed
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MovementSpeed;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float MaxMovementSpeed;
	
	// Damage
	UPROPERTY(BlueprintReadWrite, SaveGame)
	float Damage;

	// AttributeSet으로부터 값을 받아 저장
	FCharacterAttributeSaveData& operator=(const UMJCharacterAttributeSet& AttributeSet);

	// AttributeSet에 값을 덮어쓰기
	void ApplyToAttributeSet(UMJCharacterAttributeSet& AttributeSet) const;
	
	
};