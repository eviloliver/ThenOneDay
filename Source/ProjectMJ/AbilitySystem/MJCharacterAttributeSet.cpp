// Fill out your copyright notice in the Description page of Project Settings.


#include "MJCharacterAttributeSet.h"

UMJCharacterAttributeSet::UMJCharacterAttributeSet() :
	Health(100.f),
	MaxHealth(100.f),
	AttackPower(20.f),
	MaxAttackPower(20.f),
	SpellPower(1.0f),
	MaxSpellPower(1.0f),
	CriticalProbability(1.0f),
	MaxCriticalProbability(1.0f),
	CriticalRate(0.0f),
	MaxCriticalRate(0.0f),
	AttackRate(1.0f),
	MaxAttackRate(1.0f),
	Speed(500.0f),
	MaxSpeed(800.f)
{
	
	
}

bool UMJCharacterAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
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
	


	
}
