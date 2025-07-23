// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Bar/MJEnemyHPBar.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Components/ProgressBar.h"

void UMJEnemyHPBar::BindToAttributes(UMJAbilitySystemComponent* ASC, UMJCharacterAttributeSet* AttributeSet)
{
	if (!ASC || !AttributeSet)
	{
		return;
	}
	
	MaxHP = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetMaxHealthAttribute());
	CurrentHP = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetHealthAttribute());
	// 데이터가 실제로 변할 때마다, GAS가 자동 호출
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &UMJEnemyHPBar::OnHealthChanged);
	
	InitializeWidget();
}

void UMJEnemyHPBar::InitializeWidget()
{
	// 초기화
	CurrentPercent = (MaxHP > 0.f) ? CurrentHP / MaxHP : 0.f;
	TargetPercent = (MaxHP > 0.f) ? CurrentHP / MaxHP : 0.f;
	if (HPBar)
	{
		HPBar->SetPercent(CurrentPercent);
	}
}

void UMJEnemyHPBar::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	CurrentHP = Data.NewValue;
	TargetPercent = (MaxHP > 0.f) ? CurrentHP / MaxHP : 0.f;
}

void UMJEnemyHPBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (HPBar->GetPercent() >= 0.f) // 어차피 죽으면 tick도 멈출거 같긴 한데 일단 안전하게 넣어봅니다
	{
		Super::NativeTick(MyGeometry, InDeltaTime);
        
        if (FMath::Abs(CurrentPercent- TargetPercent) > KINDA_SMALL_NUMBER)
        {
        	CurrentPercent = FMath::FInterpTo(CurrentPercent, TargetPercent, InDeltaTime, LerpSpeed);
        	CurrentPercent = CurrentPercent < 0.f ? -0.0001f : CurrentPercent;
        	if (HPBar)
        	{
        		HPBar->SetPercent(CurrentPercent);
        	}
        }
	}
}
