// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MJHealthBarWidget.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Components/ProgressBar.h"


void UMJHealthBarWidget::BindToAttributes(class UMJAbilitySystemComponent* ASC,
                                         class UMJCharacterAttributeSet* AttributeSet)
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

	OnHealthChanged(FOnAttributeChangeData{}); // 데이터가 변하기 전까지는 위 방식으로 호출되지 않음. 그러므로 처음 세팅을 위해 직접 한번 호출
}

void UMJHealthBarWidget::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	// CurrentHealth = Data.NewValue; // 바뀐 데이터로 갱신할 수 있는? 근데 이게 있으면 currentHealth가 0이 되넴
	
	// 0으로 나누기 방지
	float Percentage = (MaxHealth > 0.f) ? CurrentHealth / MaxHealth : 0.f;
	
	// ex) 100 + (-20)
	// ex) 100 + (+20)
	if (HealthBar)
	{
		HealthBar->SetPercent(Percentage);
		UE_LOG(LogTemp,Warning,TEXT("Health Bar Value: %f, maxHealth : %f, currentHealth : %f"),Percentage, MaxHealth, CurrentHealth);
	}
}