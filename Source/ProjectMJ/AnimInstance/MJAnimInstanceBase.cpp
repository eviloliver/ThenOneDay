// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/MJAnimInstanceBase.h"
#include "MJAnimInstanceBase.h"
#include "Character/MJPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMJAnimInstanceBase::NativeInitializeAnimation()
{
	
	OwningCharacter = Cast<AMJPlayerCharacter>(TryGetPawnOwner());
	
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
}
