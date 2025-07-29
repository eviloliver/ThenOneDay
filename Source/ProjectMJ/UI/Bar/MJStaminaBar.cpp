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
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxStaminaAttribute()).AddUObject(this,&UMJStaminaBar::OnMaxStaminaChanged);
	
	InitializeWidget();
}

void UMJStaminaBar::InitializeWidget()
{
	// 아래 두줄 추가한 이유 : 무작정 1.f로 해놓으면 나중에 게임 다시 켰을 때 체력이 자동회복되어있을까봐
	float per = (MaxStamina > 0.f) ? CurrentStamina / MaxStamina : 0.f;
	TargetPercent = (MaxStamina > 0.f) ? CurrentStamina / MaxStamina : 0.f;
	if (StaminaBar)
	{
		StaminaBar->SetPercent(per);
	}
	if (Percent)
	{
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), CurrentStamina, MaxStamina)));
	}
}

void UMJStaminaBar::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	CurrentStamina = Data.NewValue;
	
	TargetPercent = (MaxStamina > 0.f) ? CurrentStamina / MaxStamina : 0.f;
	
	if (Percent)
	{
		CurrentStamina = CurrentStamina < 0.f ? 0.f : CurrentStamina;
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), CurrentStamina, MaxStamina)));
	}
}

void UMJStaminaBar::OnMaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	MaxStamina = Data.NewValue;
	
	TargetPercent = (MaxStamina > 0.f) ? CurrentStamina / MaxStamina : 0.f;
	
	if (Percent)
	{
		CurrentStamina = CurrentStamina < 0.f ? 0.f : CurrentStamina;
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), CurrentStamina, MaxStamina)));
	}
}

void UMJStaminaBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (StaminaBar->GetPercent() >= 0.f)
	{
		Super::NativeTick(MyGeometry, InDeltaTime);

		if (FMath::Abs(CurrentPercent- TargetPercent) > KINDA_SMALL_NUMBER)
		{
			CurrentPercent = FMath::FInterpTo(CurrentPercent, TargetPercent, InDeltaTime, LerpSpeed);
			CurrentPercent = CurrentPercent < 0.f ? -0.0001f : CurrentPercent;
			if (StaminaBar)
			{
				StaminaBar->SetPercent(CurrentPercent);
			}
		}
	}
}
