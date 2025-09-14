// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "MJStatWidget.generated.h"

class UMJCharacterAttributeSet;
class UMJAttributeSet;
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
	TObjectPtr<UTextBlock> StatLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StatHealth;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StatAttackPower;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StatSpellPower;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StatSpeed;

	UPROPERTY()
	TObjectPtr<UMJCharacterAttributeSet> AttributSet;
	
	float Health;
	float AttackPower;
	float SpellPower;
	float Speed;

public:
	UFUNCTION()
	void BindToAttribute(class UMJAbilitySystemComponent* ASC, class UMJCharacterAttributeSet* AttributeSet, class UMJPlayerStatComponent* Stat);

	UFUNCTION()
	void UpdateLevel(int32 NewLevel);
	void UpdateStat(const FOnAttributeChangeData& Data);
};
