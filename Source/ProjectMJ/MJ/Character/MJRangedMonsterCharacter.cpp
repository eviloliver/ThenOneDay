// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJRangedMonsterCharacter.h"

AMJRangedMonsterCharacter::AMJRangedMonsterCharacter()
{
}

void AMJRangedMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Minjin: 기본 원거리 공격 스킬 추가
	// SkillComponent->LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.Catastrophe")));
	// SkillComponent->EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.Catastrophe")));
	//
	// // Minjin: 근거리 공격 스킬 추가
	// SkillComponent->LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.BasicMeleeAttack")));
	// SkillComponent->EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.BasicMeleeAttack")));
}