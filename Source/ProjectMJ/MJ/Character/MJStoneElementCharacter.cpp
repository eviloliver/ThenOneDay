// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Character/MJStoneElementCharacter.h"

AMJStoneElementCharacter::AMJStoneElementCharacter()
{
}

void AMJStoneElementCharacter::BeginPlay()
{
	Super::BeginPlay();
	AttackTag = FGameplayTag::RequestGameplayTag(FName("Skill.Instant.StoneElementalMeleeAttack"));
	
}

void AMJStoneElementCharacter::AttackByAI()
{
	SkillComponent->ActivateSkill(AttackTag);
}
