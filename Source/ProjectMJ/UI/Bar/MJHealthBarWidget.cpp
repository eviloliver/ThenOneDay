// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Bar/MJHealthBarWidget.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMJHealthBarWidget::BindToAttributes(UMJAbilitySystemComponent* ASC, UMJCharacterAttributeSet* AttributeSet)
{
	if (!ASC || !AttributeSet)
	{
		return;
	}

	// Max는 base & current 같다.
	MaxHealth = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetMaxHealthAttribute());
	CurrentHealth = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetHealthAttribute());
	// 데이터가 실제로 변할 때마다, GAS가 자동 호출
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this,&UMJHealthBarWidget::OnHealthChanged);
	
	InitializeWidget();
}

void UMJHealthBarWidget::InitializeWidget()
{
	float per = (MaxHealth > 0.f) ? (CurrentHealth / MaxHealth) : 0.f;
	// CurrentPercent = (MaxHealth > 0.f) ? (CurrentHealth / MaxHealth) : 0.f;
	// CurrentPercent 대신 per를 쓰면 게임 시작할때 체력이 빠르게 차오르는 꼴을 볼 수 있다
	// 이유 : CurrentPercent = 0 이라서 NativeTick에서 0->TargetPercent까지 차오르는 거임
	// 이게 더 예뻐보여서 이렇게 했는데, 처음부터 꽉 찬 상태로 시작하고 싶으면 currentPercent 쓰면 된다.

	TargetPercent = (MaxHealth > 0.f) ? CurrentHealth / MaxHealth : 0.f;
	if (HealthBar)
	{
		HealthBar->SetPercent(per);
	}
	if (Percent)
	{
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), CurrentHealth, MaxHealth)));
	}
}

void UMJHealthBarWidget::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	CurrentHealth = Data.NewValue; // 바뀐 데이터로 갱신할 수 있는? 근데 이게 있으면 시작할 땐 currentHealth가 0이 되넴
	
	TargetPercent = (MaxHealth > 0.f) ? CurrentHealth / MaxHealth : 0.f; // 바 퍼센트 갱신

	if (Percent)
	{
		CurrentHealth = CurrentHealth < 0.f ? 0.f : CurrentHealth;
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), CurrentHealth, MaxHealth)));
	}
}

void UMJHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (HealthBar->GetPercent() >= 0.f) // 더이상 tick이 돌지않도록 가라로..
	{
		Super::NativeTick(MyGeometry, InDeltaTime);
		if (FMath::Abs(CurrentPercent- TargetPercent) > KINDA_SMALL_NUMBER)
		{
			CurrentPercent = FMath::FInterpTo(CurrentPercent, TargetPercent, InDeltaTime, LerpSpeed);
			CurrentPercent = CurrentPercent < 0.f ? -0.0001f : CurrentPercent;
			if (HealthBar)
			{
				HealthBar->SetPercent(CurrentPercent);
			}
		}
	}
}
