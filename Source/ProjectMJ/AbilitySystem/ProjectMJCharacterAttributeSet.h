// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ProjectMJCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UProjectMJCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UProjectMJCharacterAttributeSet();

	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, AttackPower);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, MaxAttackPower);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, SpellPower);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, MaxSpellPower);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, CriticalProbability);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, MaxCriticalProbability);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, CriticalRate);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, MaxCriticalRate);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, Speed);
	ATTRIBUTE_ACCESSORS(UProjectMJCharacterAttributeSet, MaxSpeed);

	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	

	
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
