// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJSkillComponent.h"

#include "AudioMixerDevice.h"
#include "ProjectMJ.h"
#include "DM/MJGameInstanceDM.h"

// Sets default values for this component's properties
UMJSkillComponent::UMJSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMJSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// Dongmin: 테스트용 시작하자 마자 스킬 획득
	LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.BasicMeleeAttack")));
}


void UMJSkillComponent::LearnSkill(const FGameplayTag& NewSkill)
{
	// DongMin: SkillTag == DefaultSkillTag == RowName(이건 자료형이 FName이긴 한데)

	if (OwnedSkillMap.Contains(NewSkill))
	{
		if (OwnedSkillMap[NewSkill].Level < 9)
		{
			++OwnedSkillMap[NewSkill].Level;
		}
	}
	else
	{
		auto* GI = GetWorld()->GetGameInstance<UMJGameInstanceDM>();
		if (GI && GI->SkillDataTable)
		{
			FName RowName = NewSkill.GetTagName();
			const FMJSkillDataRow* DT = GI->SkillDataTable->FindRow<FMJSkillDataRow>(RowName, TEXT(""));
			if (DT)
			{
				FSkillData NewSkillData;
				NewSkillData.SkillDefaultTag = NewSkill;
				NewSkillData.SkillTypeTag = NewSkill.GetGameplayTagParents().Last();
				OwnedSkillMap.Add(NewSkill, NewSkillData);
			}
		}
	}
}

void UMJSkillComponent::EquipSkill(const FGameplayTag& EquippingSkill)
{
	// DM: 절대 일어나지 않을거 같지만 예외처리
	if (!OwnedSkillMap.Contains(EquippingSkill))
	{
		return;
	}

	FGameplayTag SkillTypeTag = OwnedSkillMap[EquippingSkill].SkillTypeTag;
	if (EquippedSkillMap.Contains(SkillTypeTag))
	{
		FGameplayTag EquippedSkill = EquippedSkillMap[SkillTypeTag];
		UnequipSkill(EquippedSkill);
	}

	EquippedSkillMap.Add(SkillTypeTag, EquippingSkill);

}

void UMJSkillComponent::UnequipSkill (const FGameplayTag& UnequippingSkill)
{
	// DM: 절대 일어나지 않을거 같지만 예외처리
	if (!OwnedSkillMap.Contains(UnequippingSkill))
	{
		return;
	}

	FGameplayTag SkillTypeTag = OwnedSkillMap[UnequippingSkill].SkillTypeTag;
	if (EquippedSkillMap.Contains(SkillTypeTag) && EquippedSkillMap[SkillTypeTag] == UnequippingSkill)
	{
		EquippedSkillMap.Remove(SkillTypeTag);
	}
}

void UMJSkillComponent::ActivateSkill(const FGameplayTag& EquippedSlotSkill)
{
	if (!OwnedSkillMap.Contains(EquippedSlotSkill))
	{
		return;
	}

	FGameplayTag SkillTypeTag = OwnedSkillMap[EquippedSlotSkill].SkillTypeTag;
	if (EquippedSkillMap.Contains(SkillTypeTag))
	{
		EquippedSkillMap[SkillTypeTag];
	}
	else
	{
		MJ_LOG(LogMJ, Log, TEXT("No Equipped Skill"));
		return;
	}
}

