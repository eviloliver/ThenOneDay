// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Bar/MJExperienceWidget.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMJExperienceWidget::BindToAttributes(UMJAbilitySystemComponent* ASC, UMJCharacterAttributeSet* AttributeSet)
{
	if (!ASC || !AttributeSet)
	{
		return;
	}
	
	MaxExp = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetMaxExperienceAttribute());
	CurrentExp = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetExperienceAttribute());
	// 데이터가 실제로 변할 때마다, GAS가 자동 호출
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetExperienceAttribute()).AddUObject(this,&UMJExperienceWidget::OnExpChanged);

	InitializeWidget();
}

void UMJExperienceWidget::InitializeWidget()
{
	// 초기화
	CurrentPercent= (MaxExp > 0.f) ? CurrentExp / MaxExp : 0.f;
	TargetPercent = (MaxExp > 0.f) ? CurrentExp / MaxExp : 0.f;
	if (ExpBar)
	{
		ExpBar->SetPercent(CurrentPercent);
	}
	if (Percent)
	{
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), CurrentExp, MaxExp)));
	}
}

void UMJExperienceWidget::OnExpChanged(const FOnAttributeChangeData& Data)
{
	CurrentExp = Data.NewValue;
	float Percentage = (MaxExp > 0.f) ? CurrentExp / MaxExp : 0.f;

	if (ExpBar)
	{
		ExpBar->SetPercent(Percentage);
	}
	if (Percent)
	{
		float curExp = CurrentExp < 0.f ? 0.f : CurrentExp;
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), curExp, MaxExp)));
	}
}

void UMJExperienceWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (FMath::Abs(CurrentPercent- TargetPercent) > KINDA_SMALL_NUMBER)
	{
		CurrentPercent = FMath::FInterpTo(CurrentPercent, TargetPercent, InDeltaTime, LerpSpeed);
		if (ExpBar)
		{
			ExpBar->SetPercent(CurrentPercent);
		}
	}
}