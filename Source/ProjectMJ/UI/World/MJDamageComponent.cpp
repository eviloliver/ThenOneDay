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

void UMJDamageComponent::SetDamageWidget(FVector CharacterLocation)
{
	// 기타 세팅
	SetWidgetSpace(EWidgetSpace::Screen);
	SetWorldLocation(CharacterLocation + FVector(0, 0, 220));
	SetDrawSize(FVector2D(30.0f,30.0f));
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


