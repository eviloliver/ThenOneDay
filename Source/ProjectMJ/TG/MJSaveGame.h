// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MJCharacterAttributeSet.h"
#include "GameFramework/SaveGame.h"
#include "MJSaveGame.generated.h"

struct FGameplayAttributeData;
class UMJCharacterAttributeSet;
/**
 * Class Description: 게임을 저장할 데이터들을 모아놓은 USaveGame 클래스
 * Author: 차태관
 * Created Date: 2025-06-11
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-11
 */

USTRUCT(BlueprintType)
struct FCharacterAttributeSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float Health;

	UPROPERTY(BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite)
	float AttackPower;

	UPROPERTY(BlueprintReadWrite)
	float MaxAttackPower;

	UPROPERTY(BlueprintReadWrite)
	float SpellPower;

	UPROPERTY(BlueprintReadWrite)
	float MaxSpellPower;

	UPROPERTY(BlueprintReadWrite)
	float CriticalProbability;

	UPROPERTY(BlueprintReadWrite)
	float MaxCriticalProbability;

	UPROPERTY(BlueprintReadWrite)
	float CriticalRate;

	UPROPERTY(BlueprintReadWrite)
	float MaxCriticalRate;

	UPROPERTY(BlueprintReadWrite)
	float AttackRate;

	UPROPERTY(BlueprintReadWrite)
	float MaxAttackRate;

	UPROPERTY(BlueprintReadWrite)
	float Speed;

	UPROPERTY(BlueprintReadWrite)
	float MaxSpeed;

	static FCharacterAttributeSaveData FromAttributeSet(const UMJCharacterAttributeSet* AttrSet)
	{
		FCharacterAttributeSaveData Data;

		if (!AttrSet) return Data;

		Data.Health = AttrSet->GetHealth();
		Data.MaxHealth = AttrSet->GetMaxHealth();

		Data.AttackPower = AttrSet->GetAttackPower();
		Data.MaxAttackPower = AttrSet->GetMaxAttackPower();

		Data.SpellPower = AttrSet->GetSpellPower();
		Data.MaxSpellPower = AttrSet->GetMaxSpellPower();

		Data.CriticalProbability = AttrSet->GetCriticalProbability();
		Data.MaxCriticalProbability = AttrSet->GetMaxCriticalProbability();

		Data.CriticalRate = AttrSet->GetCriticalRate();
		Data.MaxCriticalRate = AttrSet->GetMaxCriticalRate();

		Data.AttackRate = AttrSet->GetAttackRate();
		Data.MaxAttackRate = AttrSet->GetMaxAttackRate();

		Data.Speed = AttrSet->GetSpeed();
		Data.MaxSpeed = AttrSet->GetMaxSpeed();

		return Data;
	}

	void ApplyTo(UAbilitySystemComponent* ASC) const
	{
		if (!ASC) return;

		// Health
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetHealthAttribute(), Health);
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetMaxHealthAttribute(), MaxHealth);

		// AttackPower
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetAttackPowerAttribute(), AttackPower);
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetMaxAttackPowerAttribute(), MaxAttackPower);

		// SpellPower
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetSpellPowerAttribute(), SpellPower);
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetMaxSpellPowerAttribute(), MaxSpellPower);

		// CriticalProbability
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetCriticalProbabilityAttribute(), CriticalProbability);
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetMaxCriticalProbabilityAttribute(), MaxCriticalProbability);

		// CriticalRate
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetCriticalRateAttribute(), CriticalRate);
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetMaxCriticalRateAttribute(), MaxCriticalRate);

		// AttackRate
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetAttackRateAttribute(), AttackRate);
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetMaxAttackRateAttribute(), MaxAttackRate);

		// Speed
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetSpeedAttribute(), Speed);
		ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetMaxSpeedAttribute(), MaxSpeed);
	}

	
};

UCLASS()
class PROJECTMJ_API UMJSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UMJSaveGame();

	FCharacterAttributeSaveData& GetAttributeSaveData();
	
protected:
	
	UPROPERTY()
	FCharacterAttributeSaveData AttributeSaveData;
	

	
	
};
