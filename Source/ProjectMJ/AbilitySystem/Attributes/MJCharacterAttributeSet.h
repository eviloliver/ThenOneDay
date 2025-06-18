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
 * Last Modified Date: 2025-06-18
 */
UCLASS()
class PROJECTMJ_API UMJCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UMJCharacterAttributeSet();

	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, AttackPower);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxAttackPower);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, SpellPower);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxSpellPower);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, CriticalProbability);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxCriticalProbability);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, CriticalRate);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxCriticalRate);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, Speed);
	ATTRIBUTE_ACCESSORS(UMJCharacterAttributeSet, MaxSpeed);

	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UFUNCTION(BlueprintCallable)
	void UpHealth(float Input);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackPower;

	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackPower;

	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData SpellPower;
	
	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSpellPower;
	
	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CriticalProbability;

	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCriticalProbability;
	
	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CriticalRate;

	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxCriticalRate;
	
	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRate;
	
	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Speed;

	UPROPERTY(BlueprintReadOnly, Category="Stat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSpeed;
	
	
};
