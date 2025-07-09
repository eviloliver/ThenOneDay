// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MJManaBarWidget.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Components/ProgressBar.h"

void UMJManaBarWidget::BindToAttributes(class UMJAbilitySystemComponent* ASC,
	class UMJCharacterAttributeSet* AttributeSet)
{
	if (!ASC || !AttributeSet)
	{
		return;
	}
	
	MaxMana = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetMaxManaAttribute());
	CurrentMana= ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetManaAttribute());
	// 데이터가 실제로 변할 때마다, GAS가 자동 호출
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this,&UMJManaBarWidget::OnManaChanged);

	OnManaChanged(FOnAttributeChangeData{}); 
	
}

void UMJManaBarWidget::OnManaChanged(const FOnAttributeChangeData& Data)
{
	float Percentage = (MaxMana > 0.f) ? CurrentMana / MaxMana : 0.f;
	
	if (ManaBar)
	{
		ManaBar->SetPercent(Percentage);
	}
}