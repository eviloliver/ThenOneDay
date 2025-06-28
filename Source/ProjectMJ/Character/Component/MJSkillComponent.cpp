// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJSkillComponent.h"

#include "ProjectMJ.h"
#include "Character/MJCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
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
	EquipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.BasicMeleeAttack")));
	//UnequipSkill(FGameplayTag::RequestGameplayTag(FName("Skill.Instant.BasicMeleeAttack")));

	// TODO:일반 공격 슬롯 만들어야 함
	// 일반 공격 태그를 따로 만들어야 하나?

}


void UMJSkillComponent::LearnSkill(const FGameplayTag& NewSkill)
{
	// DongMin: - SkillTag == DefaultSkillTag == RowName(이건 자료형이 FName이긴 한데)
	//		    - SkillTag는 Skill.{Type}.{SkillName}
	if (OwnedSkillMap.Contains(NewSkill))
	{
		if (OwnedSkillMap[NewSkill].Level < 9)
		{
			++OwnedSkillMap[NewSkill].Level;
			// 장착중인 스킬이 레벨업 하면 GiveAbility 새로 해줘야함
			if (EquippedSkillMap.Contains(NewSkill))
			{
				GiveAbilityToASC(NewSkill);
			}
		}
	}
	else
	{
		UMJGameInstanceDM* GI = GetWorld()->GetGameInstance<UMJGameInstanceDM>();
		if (GI || GI->SkillDataTable)
		{
			return;
		}
		FName RowName = NewSkill.GetTagName();
		const FMJSkillDataRow* DataRow = GI->SkillDataTable->FindRow<FMJSkillDataRow>(RowName, TEXT(""));
		if (DataRow)
		{
			FSkillData NewSkillData;
			NewSkillData.SkillDefaultTag = NewSkill;
			NewSkillData.SkillTypeTag = NewSkill.GetGameplayTagParents().GetByIndex(1);
			OwnedSkillMap.Add(NewSkill, NewSkillData);
		}
		
	}
}

void UMJSkillComponent::EquipSkill(const FGameplayTag& EquippingSkill)
{
	// DongMin: 절대 일어나지 않을거 같지만 예외처리
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
	GiveAbilityToASC(EquippingSkill);
}

void UMJSkillComponent::UnequipSkill (const FGameplayTag& UnequippingSkill)
{
	// DongMin: 절대 일어나지 않을거 같지만 예외처리
	if (!OwnedSkillMap.Contains(UnequippingSkill))
	{
		return;
	}

	FGameplayTag SkillTypeTag = OwnedSkillMap[UnequippingSkill].SkillTypeTag;
	if (EquippedSkillMap.Contains(SkillTypeTag) && EquippedSkillMap[SkillTypeTag] == UnequippingSkill)
	{
		EquippedSkillMap.Remove(SkillTypeTag);
		RemoveAbility(UnequippingSkill);
	}
}

void UMJSkillComponent::ActivateSkill(const FGameplayTag& EquippedSlotSkill)
{
	// DongMin: 절대 일어나지 않을거 같지만 예외처리
	if (!OwnedSkillMap.Contains(EquippedSlotSkill))
	{
		return;
	}

	if (!GivenAbilityHandles.Contains(EquippedSlotSkill))
	{
		MJ_LOG(LogMJ, Log, TEXT("not exist GivenAbilityHandles(EquippedSlotSkill)"));
		return;
	}

	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Log, TEXT("not exist OwnerCharacter"));
		return;
	}

	UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());
	if (!MJASC)
	{
		MJ_LOG(LogMJ, Log, TEXT("not exist ASC"));
		return;
	}

	FGameplayTag SkillTypeTag = OwnedSkillMap[EquippedSlotSkill].SkillTypeTag;
	if (!EquippedSkillMap.Contains(SkillTypeTag))
	{
		return;
	}

	UMJGameInstanceDM* GI = GetWorld()->GetGameInstance<UMJGameInstanceDM>();
	if (!GI || !GI->SkillDataTable)
	{
		MJ_LOG(LogMJ, Log, TEXT("not exist GI or SkillDataTable"));
		return;
	}

	const FMJSkillDataRow* DataRow = GI->SkillDataTable->FindRow<FMJSkillDataRow>(EquippedSlotSkill.GetTagName(), TEXT("ActivateSkill"));
	if (!DataRow || !DataRow->SkillLevelDataTable)
	{
		return;
	}

	UCurveTable* CurveTable = DataRow->SkillLevelDataTable.LoadSynchronous();
	if (!CurveTable)
	{
		return;
	}

	const UMJCharacterSkillAttributeSet* SkillAttributeSet = MJASC->GetSet<UMJCharacterSkillAttributeSet>();
	if (!SkillAttributeSet)
	{
		return;
	}

}

// TODO:
void UMJSkillComponent::GiveAbilityToASC(const FGameplayTag& UpdateSkill)
{
	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Log, TEXT("not exist OwnerCharacter"));
		return;
	}
	UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());
	if (!MJASC)
	{
		MJ_LOG(LogMJ,Log,TEXT("not exist ASC"));
		return;
	}

	UMJGameInstanceDM* GI = GetWorld()->GetGameInstance<UMJGameInstanceDM>();
	if (!GI || !GI->SkillDataTable)
	{
		MJ_LOG(LogMJ, Log, TEXT("not exist GI or SkillDataTable"));
		return;
	}

	const FMJSkillDataRow* DataRow = GI->SkillDataTable->FindRow<FMJSkillDataRow>(UpdateSkill.GetTagName(), TEXT("GiveAbility"));
	if (DataRow && DataRow->SkillAbilityClass)
	{
		RemoveAbility(UpdateSkill);

		// DongmMin: 예외처리 안 한 이유는 이거가 들어가는 로직에 이미 OwnedSkillMap을 검증해서 인데
		// 그래도 예외처리 해주는게 좋은가?
		//if (!OwnedSkillMap.Contains(UpdateSkill))
		//{
		//	return;
		//}
		int32 SkillLevel = OwnedSkillMap[UpdateSkill].Level;

		FGameplayAbilitySpec AbilitySpec(DataRow->SkillAbilityClass, SkillLevel, INDEX_NONE, OwnerCharacter);

		FGameplayAbilitySpecHandle Handle = MJASC->GiveAbility(AbilitySpec);
		GivenAbilityHandles.Add(UpdateSkill, Handle);
	}
}

void UMJSkillComponent::RemoveAbility(const FGameplayTag& RemoveSkill)
{
	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Log, TEXT("not exist OwnerCharacter"));
		return;
	}
	UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());
	if (!MJASC)
	{
		MJ_LOG(LogMJ, Log, TEXT("not exist ASC"));
		return;
	}

	if (GivenAbilityHandles.Contains(RemoveSkill))
	{
		MJASC->ClearAbility(GivenAbilityHandles[RemoveSkill]);
		GivenAbilityHandles.Remove(RemoveSkill);
	}

}

