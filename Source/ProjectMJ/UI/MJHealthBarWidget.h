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

class UProgressBar;

UCLASS()
class PROJECTMJ_API UMJHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	float MaxHealth;
	float CurrentHealth;

	void OnHealthChanged(const FOnAttributeChangeData& Data);
	
public:
	UFUNCTION()
	void BindToAttributes(class UMJAbilitySystemComponent* ASC, class UMJCharacterAttributeSet* AttributeSet);
};
