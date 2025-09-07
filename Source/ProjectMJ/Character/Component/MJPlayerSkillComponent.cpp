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

	for (auto Iter : LoadedOwnedSkillMap)
	{
		LearnSkill(Iter.Key);
		EquipSkill(Iter.Key);
	}

	if (EquippedSkillMap.IsEmpty()) {}
	if (OwnedSkillMap.IsEmpty()){}
	
	
	//
	// LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.PoisonSlash")));
	// EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.PoisonSlash")));
	//
	//
	// LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.AlphaStrike")));
	// EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Charge.AlphaStrike")));
	//
	// LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Normal.MeleeAttack")));
	// EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Normal.MeleeAttack")));
	//
	// LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Passive.DamageUp")));
	// EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Passive.DamageUp")));

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
