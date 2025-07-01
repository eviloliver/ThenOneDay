// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJRangedMonsterCharacter.h"

AMJRangedMonsterCharacter::AMJRangedMonsterCharacter()
{
}

float AMJRangedMonsterCharacter::GetAIMaximumAttackRange()
{
	return 800.0f;
}

float AMJRangedMonsterCharacter::GetAIMinimumAttackRange()
{
	return 200.0f;
}

void AMJRangedMonsterCharacter::AttackByAI()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("RangedMonster: 공격"));
}

void AMJRangedMonsterCharacter::MeleeAttackByAI()
{
	/*
	 * Minjin
	 * TODO
	 * 근거리 공격
	 */
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("RangedMonster: 근거리공격"));
}

void AMJRangedMonsterCharacter::RangeAttackByAI()
{
	/*
	 * Minjin
	 * TODO
	 * 원거리 공격
	 */
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("RangedMonster: 원거리공격"));
}
