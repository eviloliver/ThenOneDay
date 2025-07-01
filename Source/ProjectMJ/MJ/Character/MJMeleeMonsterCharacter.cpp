// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJMeleeMonsterCharacter.h"

AMJMeleeMonsterCharacter::AMJMeleeMonsterCharacter()
{
}

float AMJMeleeMonsterCharacter::GetAIMaximumAttackRange()
{
	return 400.0f;
}

float AMJMeleeMonsterCharacter::GetAIMinimumAttackRange()
{
	return 200.0f;
}

void AMJMeleeMonsterCharacter::AttackByAI()
{
	/*
	 * Minjin
	 * TODO
	 * 공격
	 */
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Emerald, TEXT("MeleeMonster: 공격"));
}

void AMJMeleeMonsterCharacter::MeleeAttackByAI()
{
	/*
	 * Minjin
	 * TODO
	 * 근거리 공격
	 */
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Emerald, TEXT("MeleeMonster: 근거리 공격"));
}

void AMJMeleeMonsterCharacter::RangeAttackByAI()
{
	/*
	 * Minjin
	 * TODO
	 * 중거리 공격-돌진?
	 */
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Emerald, TEXT("MeleeMonster: 중거리 공격"));
}
