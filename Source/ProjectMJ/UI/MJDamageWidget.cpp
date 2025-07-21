// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MJDamageWidget.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimationEvents.h"

void UMJDamageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AnimFinishedDelegate.BindDynamic(this,&UMJDamageWidget::OnAnimFinished);
}


void UMJDamageWidget::SetDamage(float damage)
{
	// 이대로 몬스터에 박아넣으면 몬스터의 어택데미지가 들어갈 거 같음
	// 구현 후 확인할 것
	Damage->SetText(FText::AsNumber(damage));
}

void UMJDamageWidget::PlayAnim()
{
	if (DamageAnim)
	{
		PlayAnimation(DamageAnim);
	}
}

void UMJDamageWidget::OnAnimFinished()
{
	RemoveFromParent();
}



