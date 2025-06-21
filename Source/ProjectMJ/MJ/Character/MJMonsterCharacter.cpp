// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJMonsterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AMJMonsterCharacter::AMJMonsterCharacter()
{
	//AIControllerClass = AMJAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	// RVO
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 100.0f;
}
