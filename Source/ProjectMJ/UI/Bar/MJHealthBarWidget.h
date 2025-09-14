// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "MJHealthBarWidget.generated.h"

/**
* Class Description: HUD 체력바
 * Author: 이지수
 * Created Date: 2025.06.26
 * Last Modified By: 
 * Last Modified Date: 
 */

class UTextBlock;
class UProgressBar;

UCLASS()
class PROJECTMJ_API UMJHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Percent;

	float TargetPercent;
	float CurrentPercent;
	float LerpSpeed = 2.5f; // 보간 속도
	
	float MaxHealth;
	float CurrentHealth;

public:
	UFUNCTION()
	void BindToAttributes(class UMJAbilitySystemComponent* ASC, class UMJCharacterAttributeSet* AttributeSet);
	void InitializeWidget();
	
	void OnHealthChanged(const FOnAttributeChangeData& Data);
	void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
