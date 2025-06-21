// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/MJMeleeMonsterAIController.h"

#include "AIPerceptionInfo.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GenericTeamAgentInterface.h"

AMJMeleeMonsterAIController::AMJMeleeMonsterAIController()
{
	/*
	 * TODO
	 * AIPerception 하드코딩 변경하기
	 */
	// AIPerception
	// Sense-Sight
	// AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("AISenseConfig_Sight");
	// AISenseConfig_Sight->SightRadius = 1000.0f;
	// AISenseConfig_Sight->LoseSightRadius = 1500.0f;
	// AISenseConfig_Sight->PeripheralVisionAngleDegrees = 60.0f;

	/*
	 * How To: 적, 중립, 아군 감지 여부
	 */
	/*
	 * TODO
	 * 설정 안 바뀌고 있음
	 */
	// DetectionByAffiliation.bDetectEnemies = true;
	// DetectionByAffiliation.bDetectNeutrals = true;
	// DetectionByAffiliation.bDetectFriendlies = false;
	// AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);


}

void AMJMeleeMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
}
