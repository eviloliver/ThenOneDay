// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "MJExperienceWidget.generated.h"

/**
 * Class Description: HUD 경험치 바
 * Author: 이지수
 * Created Date: 2025.06.26
 * Last Modified By: 
 * Last Modified Date: 
 */
class UProgressBar;
UCLASS()
class PROJECTMJ_API UMJExperienceWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ExpBar;

	float MaxExp;
	float CurrentExp;

	void OnExpChanged(const FOnAttributeChangeData& Data);
	
public:
	UFUNCTION()
	void BindToAttributes(class UMJAbilitySystemComponent* ASC, class UMJCharacterAttributeSet* AttributeSet);
};
