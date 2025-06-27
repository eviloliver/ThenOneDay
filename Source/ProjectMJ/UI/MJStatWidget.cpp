// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MJStatWidget.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Components/TextBlock.h"

void UMJStatWidget::BindToAttribute(UMJAbilitySystemComponent* ASC, UMJCharacterAttributeSet* AttributeSet)
{
	if (!ASC || !AttributeSet) 
	{
		return;
	}
	
	Level = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetMaxLevelAttribute());
	Health = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetMaxHealthAttribute());
	AttackPower = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetMaxAttackDamageAttribute());
	SpellPower = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetMaxAbilityPowerAttribute());
	Speed = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetMaxAbilityPowerAttribute());
	
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UMJStatWidget::UpdateStat);
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxAttackDamageAttribute()).AddUObject(this, &UMJStatWidget::UpdateStat);
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxAbilityPowerAttribute()).AddUObject(this, &UMJStatWidget::UpdateStat);
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxLevelAttribute()).AddUObject(this, &UMJStatWidget::UpdateStat);

	UpdateStat(FOnAttributeChangeData{});
}

void UMJStatWidget::UpdateStat(const FOnAttributeChangeData& Data) // settext
{
	// 지수 : 하나의 함수로 두는거 말고 UpdateLevelStat 이런식으로 여러개를 두는게 나을까?
	if (StatLevel)
	{
		StatLevel->SetText(FText::FromString(FString::SanitizeFloat(Level)));
	}
	
	if (StatHealth)
	{
		StatHealth->SetText(FText::FromString(FString::SanitizeFloat(Health)));
	}

	if (StatAttackPower)
	{
		StatAttackPower->SetText(FText::FromString(FString::SanitizeFloat(AttackPower)));
	}

	if (StatSpellPower)
	{
		StatSpellPower->SetText(FText::FromString(FString::SanitizeFloat(SpellPower)));
	}
}
