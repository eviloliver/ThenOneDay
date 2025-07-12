// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJStoneElementCharacter.h"

void AMJStoneElementCharacter::BeginPlay()
{
	Super::BeginPlay();

	SkillComponent->LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.StoneElementalMeleeAttack")));
	SkillComponent->EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.StoneElementalMeleeAttack")));
	
}

void AMJStoneElementCharacter::AttackByAI()
{
	SkillComponent->ActivateSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.StoneElementalMeleeAttack")));
}
