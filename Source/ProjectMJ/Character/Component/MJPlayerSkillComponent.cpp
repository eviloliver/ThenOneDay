// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJPlayerSkillComponent.h"

#include "ProjectMJ.h"

UMJPlayerSkillComponent::UMJPlayerSkillComponent()
{
}

void UMJPlayerSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// 기존 BeginPlay의 테스트 코드를 여기에 둡니다.
	LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.AirArrow")));
	EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.AirArrow")));

	LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.Catastrophe")));
	EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.Catastrophe")));
	LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.Catastrophe")));

	// TODO:일반 공격 슬롯 만들어야 함
	// 일반 공격 태그를 따로 만들어야 하나?
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
