// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/MJMeleeMonsterAIController.h"

#include "AIPerceptionInfo.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GenericTeamAgentInterface.h"

AMJMeleeMonsterAIController::AMJMeleeMonsterAIController()
{
}

void AMJMeleeMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	// 이러면 설정이 바뀌긴 함
	// DetectionByAffiliation.bDetectEnemies = true;
	// DetectionByAffiliation.bDetectNeutrals = true;
	// DetectionByAffiliation.bDetectFriendlies = false;
	// AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
}
