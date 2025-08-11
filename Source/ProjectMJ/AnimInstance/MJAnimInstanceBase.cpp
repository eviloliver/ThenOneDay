// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/MJAnimInstanceBase.h"
#include "MJAnimInstanceBase.h"
#include "Character/MJCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMJAnimInstanceBase::NativeInitializeAnimation()
{
	
	OwningCharacter = Cast<AMJCharacterBase>(TryGetPawnOwner());
	
	if (OwningCharacter)
	{
		OwningCharacterMovementComponent = OwningCharacter->GetCharacterMovement();

	}
}

void UMJAnimInstanceBase::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningCharacterMovementComponent)
	{
		return;
	}
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	if (GroundSpeed > 0.0f)
	{
		bHasAcceleration = true;
	}
	else
	{
		bHasAcceleration = false;
	}

	const float BaseRunSpeed = 600.f; // 기본 속도

	MoveAnimPlayRate = FMath::Max(GroundSpeed / BaseRunSpeed, 0.2f);
}
