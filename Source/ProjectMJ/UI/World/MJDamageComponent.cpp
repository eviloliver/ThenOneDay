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

void UMJDamageComponent::SetDamageWidget(FVector CharacterLocation, float OffSet)
{
	// 기타 세팅
	SetWidgetSpace(EWidgetSpace::Screen);

	// // 1. 배 주변 랜덤 생성할 경우
	// float OffsetX = FMath::FRandRange(0.f, 100.f);
	// float OffsetZ= FMath::FRandRange(0.f, 100.f);
	// SetWorldLocation(CharacterLocation + FVector(OffsetX, 0, OffsetZ)); // 랜덤하게 뜨게 해보자 배 주변 와다닥

	// 2. 메이플스토리 마냥 위로 쌓이게 할라면?
	SetWorldLocation(CharacterLocation + FVector(0, 0, OffSet * 50));
	
	SetDrawSize(FVector2D(30.0f,30.0f));
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


