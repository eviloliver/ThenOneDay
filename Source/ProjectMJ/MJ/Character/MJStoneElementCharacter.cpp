// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJStoneElementCharacter.h"

void AMJStoneElementCharacter::BeginPlay()
{
	Super::BeginPlay();
	AttackTag = FGameplayTag::RequestGameplayTag(FName("Skill.Instant.StoneElementalMeleeAttack"));
	SkillComponent->LearnSkill(AttackTag);
	SkillComponent->EquipSkill(AttackTag);
	
}

void AMJStoneElementCharacter::AttackByAI()
{
	SkillComponent->ActivateSkill(AttackTag);
}
