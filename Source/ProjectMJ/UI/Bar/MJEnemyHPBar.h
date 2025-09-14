// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "MJEnemyHPBar.generated.h"

class UMJCharacterAttributeSet;
class UMJAbilitySystemComponent;
class UProgressBar;
/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJEnemyHPBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HPBar;

	UPROPERTY()
	float MaxHP;

	UPROPERTY()
	float CurrentHP;

	float TargetPercent ;
	float CurrentPercent ;
	float LerpSpeed = 2.5f; // 보간 속도

public:
	UFUNCTION()
	void BindToAttributes(UMJAbilitySystemComponent* ASC, UMJCharacterAttributeSet* AttributeSet);
	void InitializeWidget();

	void OnHealthChanged(const FOnAttributeChangeData& Data);
	void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
