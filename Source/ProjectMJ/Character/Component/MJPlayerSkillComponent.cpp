// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJPlayerSkillComponent.h"

#include "ProjectMJ.h"
#include "DataTable/MJSkillDataRow.h"
#include "TG/MJGameInstance.h"

UMJPlayerSkillComponent::UMJPlayerSkillComponent()
{
}

void UMJPlayerSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// Beginplay 시마다 스킬들을 저장된 정보에 따라 다시 배우고 장착
	// 맨 처음 기본 스킬 -> MJNewGamePopUpWidget.cpp Line:78 참고
	OwnedSkillMap.Empty();
	for (auto Iter : LoadedOwnedSkillMap)
	{
		LearnSkill(Iter.Key);
	}
	
	EquippedSkillMap.Empty();
	for (auto Iter : LoadedEquippedSkillMap)
	{
		EquipSkill(Iter.Value);
		OnLearnSkillEvents.Broadcast(Iter.Value);
	}


	
	// For Debug
	if (EquippedSkillMap.IsEmpty()) {}
	if (OwnedSkillMap.IsEmpty()){}
}

UDataTable* UMJPlayerSkillComponent::GetSkillDataTable() const
{
	UMJGameInstance* GI = GetWorld()->GetGameInstance<UMJGameInstance>();
	if (!GI)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist GI"));
		return nullptr;
	}
	UDataTable* SkillDataTable = GI->PlayerSkillDataTable;
	if (!SkillDataTable)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist SkillDataTable"));
		return nullptr;
	}
	return SkillDataTable;
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

void UMJPlayerSkillComponent::ReleaseSkillByInputTag(const FGameplayTag InputTag)
{
	if (EquippedSkillMap.Contains(InputTag))
	{
		FGameplayTag EquippedSkill = EquippedSkillMap[InputTag];
		ReleaseSkill(EquippedSkill);
	}
	else
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Equipped Skill Tag"))

	}
}
