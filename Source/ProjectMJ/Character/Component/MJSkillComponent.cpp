// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJSkillComponent.h"

// Sets default values for this component's properties
UMJSkillComponent::UMJSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	LearnSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.BasicMeleeAttack")));

}


void UMJSkillComponent::LearnSkill(const FGameplayTag& NewSkill)
{
	if (OwnedSkillMap.Contains(NewSkill))
	{
		if (OwnedSkillMap[NewSkill].Level < 10)
		{
			++OwnedSkillMap[NewSkill].Level;
		}
	}
	else
	{
		FSkillData NewSkillData;
		NewSkillData.SkillDefaultTag = NewSkill;
		NewSkillData.SkillStateTags.AddTag(FGameplayTag::RequestGameplayTag("Skill.State.Learned"));
		// TODO: 나머지 GameInstant에서 DT 가져와서 할 것
		//OwnedSkillMap.Add(NewSkill, );
	}
}

void UMJSkillComponent::EquipSkill(const FGameplayTag& EquippingSkill, ESlotType ActivateSlot)
{
	// TODO: 
    if (!OwnedSkillMap.Contains(EquippingSkill))
    {
	    return;
    }

    OwnedSkillMap[EquippingSkill].SkillStateTags.AddTag(FGameplayTag::RequestGameplayTag("Skill.State.Equipped"));
}

void UMJSkillComponent::UnequipSkill (const FGameplayTag& UnequippingSkill)
{

}

void UMJSkillComponent::ActivateSkill(ESlotType ActivateSlot)
{
	// TODO: 
	if (EquippedSkillMap.Contains(ActivateSlot))
	{

		FGameplayTag SkillTag = EquippedSkillMap[ActivateSlot].SkillDefaultTag;
	}
}

