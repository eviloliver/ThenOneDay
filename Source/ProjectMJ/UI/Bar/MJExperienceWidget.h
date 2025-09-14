// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "MJExperienceWidget.generated.h"

class UTextBlock;
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
	TObjectPtr<UProgressBar> ExpBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Percent;

	// 스르륵 게이지가 줄도록 하기 위한 변수
	float TargetPercent ;
	float CurrentPercent ;
	float LerpSpeed = 2.5f; // 보간 속도
	
	float MaxExp;
	float CurrentExp;
	
	
public:
	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	void InitializeWidget(float Current, float ExpForNextLevel);
	
	UFUNCTION()
	void OnExperienceChanged(float Current, float ExpForNextLevel);
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
