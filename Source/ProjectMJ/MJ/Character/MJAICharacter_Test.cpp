// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJAICharacter_Test.h"
#include "MJ/AI/MJAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AMJAICharacter_Test::AMJAICharacter_Test()
{
	AIControllerClass = AMJAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	// RVO
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 100.0f;
}
