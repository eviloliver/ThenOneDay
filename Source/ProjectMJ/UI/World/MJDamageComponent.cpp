// Fill out your copyright notice in the Description page of Project Settings.


#include "MJDamageComponent.h"

#include "UI/World/MJDamageWidget.h"

UMJDamageComponent::UMJDamageComponent()
{
	static ConstructorHelpers::FClassFinder<UMJDamageWidget> DamageWidgetRef(TEXT("/Game/UI/WBP/World/WBP_Damage.WBP_Damage_C"));

	if (DamageWidgetRef.Class)
	{
		SetWidgetClass(DamageWidgetRef.Class);
	}
}

void UMJDamageComponent::SetDamageWidget()
{
	// 기타 세팅
	SetRelativeLocation(FVector(0.0f, 0.0f, 220.0f));
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawSize(FVector2D(20.0f,20.0f));
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetVisibility(false);
}


