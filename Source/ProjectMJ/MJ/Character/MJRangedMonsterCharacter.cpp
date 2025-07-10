// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJRangedMonsterCharacter.h"

AMJRangedMonsterCharacter::AMJRangedMonsterCharacter()
{
}

void AMJRangedMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Minjin: 기본 원거리 공격 스킬 추가
	SkillComponent->LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.Catastrophe")));
	SkillComponent->EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.Catastrophe")));
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
	// Minjin: Skill 공격
	SkillComponent->ActivateSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.Catastrophe")));

	
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
