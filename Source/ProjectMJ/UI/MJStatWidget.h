// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "MJStatWidget.generated.h"

/**
 * 
 */
class  UTextBlock;

UCLASS()
class PROJECTMJ_API UMJStatWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatLevel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatHealth;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatAttackPower;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatSpellPower;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatSpeed;

	float Level;
	float Health;
	float AttackPower;
	float SpellPower;
	float Speed;

public:
	void BindToAttribute(class UMJAbilitySystemComponent* ASC, class UMJCharacterAttributeSet* AttributeSet);
	void UpdateStat(const FOnAttributeChangeData& Data);
};
