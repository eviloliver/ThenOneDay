// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/World/MJDamageWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimationEvents.h"

void UMJDamageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}


void UMJDamageWidget::SetDamage(float damage, bool IsCritical)
{
	Damage->SetText(FText::AsNumber(damage));

	if (IsCritical)
	{
		Damage->SetColorAndOpacity( FSlateColor(FLinearColor::Yellow));
	}
	else
	{
		Damage->SetColorAndOpacity( FSlateColor(FLinearColor::White));
	}
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
	// jisoo : 컴포넌트가 사라지면 어차피 widget도 사라지기는 하는데,
	// 이렇게 하면 나중에 몹이 많을 때 메모리 차지 심해질까봐 그냥 애니메이션 끝나면 위젯 죽어라 하는중입니다.
	RemoveFromParent(); 
}



