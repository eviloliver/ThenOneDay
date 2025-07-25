// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJPlayerSkillComponent.h"

#include "ProjectMJ.h"

UMJPlayerSkillComponent::UMJPlayerSkillComponent()
{
}

void UMJPlayerSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.AirArrow")));
	EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.AirArrow")));

	LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.Catastrophe")));
	EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.Catastrophe")));
	LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.Catastrophe")));

	LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Normal.MeleeAttack")));
	EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Normal.MeleeAttack")));

	LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Passive.Test")));
	EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Passive.Test")));

}

void UMJPlayerSkillComponent::ActivateSkillByInputTag(const FGameplayTag InputTag)
{
	if (EquippedSkillMap.Contains(InputTag))
	{
		FGameplayTag EquippedSkill = EquippedSkillMap[InputTag];
		ActivateSkill(EquippedSkill);
	}
	else
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Equipped Skill Tag"))
	}
}
