// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJMeleeMonsterCharacter.h"


AMJMeleeMonsterCharacter::AMJMeleeMonsterCharacter()
{
}

void AMJMeleeMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Minjin: 기본 공격 스킬 추가
	SkillComponent->LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.BasicMeleeAttack")));
	SkillComponent->EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.BasicMeleeAttack")));

	
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
	// Minjin: Skill 공격
	SkillComponent->ActivateSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.BasicMeleeAttack")));

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
