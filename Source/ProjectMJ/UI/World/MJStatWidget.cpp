// Fill out your copyright notice in the Description page of Project Settings.


#include "MJStatWidget.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Character/Component/MJPlayerStatComponent.h"
#include "Components/TextBlock.h"

void UMJStatWidget::BindToAttribute(UMJAbilitySystemComponent* ASC, UMJCharacterAttributeSet* AttributeSet, UMJPlayerStatComponent* Stat)
{
	if (!ASC || !AttributeSet) 
	{
		return;
	}

	this->AttributSet = AttributeSet;
	
	Health = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetMaxHealthAttribute());
	AttackPower = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetAttackDamageAttribute());
	SpellPower = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetAbilityPowerAttribute());
	Speed = ASC->GetNumericAttribute(UMJCharacterAttributeSet::GetAbilityPowerAttribute());

	Stat->OnLevelUp.AddDynamic(this, &UMJStatWidget::UpdateLevel);
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UMJStatWidget::UpdateStat);
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetAttackDamageAttribute()).AddUObject(this, &UMJStatWidget::UpdateStat);
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetAbilityPowerAttribute()).AddUObject(this, &UMJStatWidget::UpdateStat);
	ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxMovementSpeedAttribute()).AddUObject(this, &UMJStatWidget::UpdateStat);
	
	UpdateStat(FOnAttributeChangeData{});
}

void UMJStatWidget::UpdateLevel(int32 NewLevel)
{
	if (StatLevel)
 	{
 		StatLevel->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewLevel)));
 	}
}

void UMJStatWidget::UpdateStat(const FOnAttributeChangeData& Data) // settext
{
	FGameplayAttribute ChangedAttr = Data.Attribute;
	if (ChangedAttr == AttributSet->GetMaxHealthAttribute())
	{
		if (StatHealth)
        {
        	Health = Data.NewValue;
        	StatHealth->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
        }
	}

	if (ChangedAttr == AttributSet->GetAttackDamageAttribute())
	{
		if (StatAttackPower)
		{
			AttackPower = Data.NewValue;
			StatAttackPower->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), AttackPower)));
		}
	}
	if (ChangedAttr == AttributSet->GetAbilityPowerAttribute())
	{
		if (StatSpellPower)
        {
        	SpellPower = Data.NewValue;
        	StatSpellPower->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), SpellPower)));
        }
	}

	if (ChangedAttr == AttributSet->GetMaxMovementSpeedAttribute())
	{
		if (StatSpeed)
        {
        	Speed = Data.NewValue;
        	StatSpeed->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Speed)));
        }
	}

}
