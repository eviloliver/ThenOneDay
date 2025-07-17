// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Bar/MJManaBarWidget.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaAttribute()).AddUObject(this,&UMJManaBarWidget::OnManaChanged);

	InitializeWidget();
	//OnManaChanged(FOnAttributeChangeData{}); 
}

void UMJManaBarWidget::InitializeWidget()
{
	float Percentage = (MaxMana > 0.f) ? CurrentMana / MaxMana : 0.f;
	if (ManaBar)
	{
		ManaBar->SetPercent(Percentage);
	}
	if (Percent)
	{
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), CurrentMana, MaxMana)));
	}
}

void UMJManaBarWidget::OnManaChanged(const FOnAttributeChangeData& Data)
{
	CurrentMana = Data.NewValue;
	float Percentage = (MaxMana > 0.f) ? CurrentMana / MaxMana : 0.f;
	
	if (ManaBar)
	{
		ManaBar->SetPercent(Percentage);
	}
	if (Percent)
	{
		float curMP =  CurrentMana < 0.f ? 0.f : CurrentMana;
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), curMP, MaxMana)));
	}
	
}
