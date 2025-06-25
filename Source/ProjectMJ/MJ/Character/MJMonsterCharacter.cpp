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

float AMJMonsterCharacter::GetAIPatrolRadius()
{
	return 800.0f;
}

float AMJMonsterCharacter::GetAITurnSpeed()
{
	return 2.0f;
}

float AMJMonsterCharacter::GetAIAttackRange()
{
	/*
	 * TODO
	 * 우선 하드코딩. 스탯 기반으로 바꾸기
	 */
	//return Stat->GetTotalStat().AttackRange + Stat->GetAttackRadius()*2;
	return 200.0f;
}

float AMJMonsterCharacter::GetAISight_SightRadius()
{
	return 800.0f;
}

float AMJMonsterCharacter::GetAISight_LoseSightRadius()
{
	return 1000.0f;
}

float AMJMonsterCharacter::GetAISight_PeripheralVisionAngleDegrees()
{
	return 60.0f;
}

void AMJMonsterCharacter::AttackByAI()
{
	/*
	 * TODO
	 * 공격
	 */
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Attack"));
}
