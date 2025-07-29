// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "MJStaminaBar.generated.h"

/**
 * 
 */
class UTextBlock;
class UProgressBar;
UCLASS()
class PROJECTMJ_API UMJStaminaBar : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Percent;

	float TargetPercent;
	float CurrentPercent;
	float LerpSpeed = 2.5f;
	
	float MaxStamina;
	float CurrentStamina;


public:
	UFUNCTION()
	void BindToAttributes(class UMJAbilitySystemComponent* ASC, class UMJCharacterAttributeSet* AttributeSet);
	void InitializeWidget();
	void OnStaminaChanged(const FOnAttributeChangeData& Data);
	void OnMaxStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
