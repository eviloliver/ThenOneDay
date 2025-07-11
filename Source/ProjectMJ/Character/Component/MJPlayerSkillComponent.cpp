// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJPlayerSkillComponent.h"

#include "ProjectMJ.h"

UMJPlayerSkillComponent::UMJPlayerSkillComponent()
{
	// TODO: 현재 테스트 용 Input 태그를 사용해서 매핑했으므로 나중에 태그 정리와 함께 할 것
	// 하드 코딩 개선 하고 싶음
	InputTagToSkillTagMap.Add(FGameplayTag::RequestGameplayTag(TEXT("Input.Test.Q")), FGameplayTag::RequestGameplayTag(TEXT("Skill.Instant")));
	InputTagToSkillTagMap.Add(FGameplayTag::RequestGameplayTag(TEXT("Input.Test.W")), FGameplayTag::RequestGameplayTag(TEXT("Skill.Charge")));
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
	if (!InputTagToSkillTagMap.Contains(InputTag))
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist InputTag in InputTagToSkillTagMap"));
		return;
	}
	FGameplayTag SkillTypeTag = InputTagToSkillTagMap[InputTag];

	if (!EquippedSkillMap.Contains(SkillTypeTag))
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist SkillTag in EquippedSkillMap"));
		return;
	}

	FGameplayTag EquippedSkill = EquippedSkillMap[SkillTypeTag];
	ActivateSkill(EquippedSkill);
}

FGameplayTag UMJPlayerSkillComponent::ConvertInputTagToTypeTag(const FGameplayTag& InputTag)
{
	if (InputTagToSkillTagMap.Contains(InputTag))
	{
		return InputTagToSkillTagMap[InputTag];
	}
	return FGameplayTag();
}
