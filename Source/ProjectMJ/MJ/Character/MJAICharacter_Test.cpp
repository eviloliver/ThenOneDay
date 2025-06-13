// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJAICharacter_Test.h"

#include "MJ/AI/MJAIController.h"

AMJAICharacter_Test::AMJAICharacter_Test()
{
	AIControllerClass = AMJAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
