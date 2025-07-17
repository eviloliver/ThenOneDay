// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Bar/MJStaminaBar.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Math/UnitConversion.h"


void UMJStaminaBar::BindToAttributes(class UMJAbilitySystemComponent* ASC, class UMJCharacterAttributeSet* AttributeSet)
{
	if (!ASC || !AttributeSet)
	{
		return;
	}
	
	MaxStamina = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetMaxStaminaAttribute());
	CurrentStamina = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetStaminaAttribute());
	// 데이터가 실제로 변할 때마다, GAS가 자동 호출
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddUObject(this,&UMJStaminaBar::OnStaminaChanged);

	InitializeWidget();
}

void UMJStaminaBar::InitializeWidget()
{
	float Percentage = (MaxStamina > 0.f) ? CurrentStamina / MaxStamina : 0.f;
	if (StaminaBar)
	{
		StaminaBar->SetPercent(Percentage);
	}
	if (Percent)
	{
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), CurrentStamina, MaxStamina)));
	}
}

void UMJStaminaBar::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	CurrentStamina = Data.NewValue;
	float Percentage = (MaxStamina > 0.f) ? CurrentStamina / MaxStamina : 0.f;

	if (StaminaBar)
	{
		StaminaBar->SetPercent(Percentage);
	}
	if (Percent)
	{
		float curStamina =   CurrentStamina< 0.f ? 0.f : CurrentStamina;
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), curStamina, MaxStamina)));
	}
}
