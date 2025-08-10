// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJSkillComponentBase.h"

#include "ProjectMJ.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "AbilitySystem/Effect/MJGE_SetSkillAttributeSet.h"
#include "Character/MJCharacterBase.h"
#include "DataTable/MJSkillDataRow.h"
#include "DataTable/MJSkillLevelAbilityRow.h"

// Sets default values for this component's properties
UMJSkillComponentBase::UMJSkillComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMJSkillComponentBase::LearnSkill(const FGameplayTag& SkillTag)
{
	// DongMin: - SkillTag == DefaultSkillTag == RowName(이건 자료형이 FName이긴 한데)
	//		    - SkillTag는 Skill.{Type}.{SkillName}
	if (OwnedSkillMap.Contains(SkillTag))
	{
		if (OwnedSkillMap[SkillTag].Level < 9)
		{
			++OwnedSkillMap[SkillTag].Level;

			FGameplayTag SkillTypeTag = OwnedSkillMap[SkillTag].SkillTypeTag;

			if (EquippedSkillMap.Contains(SkillTypeTag))
			{
				GiveAbilityToASC(SkillTag);
			}
		}
	}
	else
	{
		FName RowName = SkillTag.GetTagName();
		UDataTable* SkillDataTable = GetSkillDataTable();
		const FMJSkillDataRow* DataRow = SkillDataTable->FindRow<FMJSkillDataRow>(RowName, TEXT(""));
		if (DataRow)
		{
			FSkillData NewSkillData;
			NewSkillData.SkillDefaultTag = SkillTag;
			int32 TagLength = SkillTag.GetGameplayTagParents().Num();
			if (TagLength < 2)
			{
				MJ_LOG(LogMJ, Warning, TEXT("Tag is too short"));
				return;
			}
			NewSkillData.SkillTypeTag = SkillTag.GetGameplayTagParents().GetByIndex(TagLength - 2);
			OwnedSkillMap.Add(SkillTag, NewSkillData);
		}
	}
}

void UMJSkillComponentBase::EquipSkill(const FGameplayTag& SkillTag)
{
	if (!OwnedSkillMap.Contains(SkillTag))
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnedSkillMap[SkillTag]"));
		return;
	}

	FGameplayTag SkillTypeTag = OwnedSkillMap[SkillTag].SkillTypeTag;
	if (EquippedSkillMap.Contains(SkillTypeTag))
	{
		FGameplayTag EquippedSkill = EquippedSkillMap[SkillTypeTag];
		UnequipSkill(EquippedSkill);
	}

	EquippedSkillMap.Add(SkillTypeTag, SkillTag);
	GiveAbilityToASC(SkillTag);
}

void UMJSkillComponentBase::UnequipSkill(const FGameplayTag& SkillTag)
{
	if (!OwnedSkillMap.Contains(SkillTag))
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnedSkillMap[SkillTag]"));
		return;
	}

	FGameplayTag SkillTypeTag = OwnedSkillMap[SkillTag].SkillTypeTag;
	if (EquippedSkillMap.Contains(SkillTypeTag) && EquippedSkillMap[SkillTypeTag] == SkillTag)
	{
		EquippedSkillMap.Remove(SkillTypeTag);
		RemoveAbility(SkillTag);
	}
}

void UMJSkillComponentBase::ActivateSkill(const FGameplayTag& SkillTag)
{
	if (!OwnedSkillMap.Contains(SkillTag))
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnedSkillMap[SkillTag]"));
		return;
	}

	if (!GivenActionAbilityHandles.Contains(SkillTag))
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist GivenActionAbilityHandles(EquippedSlotSkill)"));
		return;
	}

	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnerCharacter"));
		return;
	}

	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());
	if (!ASC)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist ASC"));
		return;
	}

	FGameplayTag SkillTypeTag = OwnedSkillMap[SkillTag].SkillTypeTag;
	if (!EquippedSkillMap.Contains(SkillTypeTag))
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist ASC"));
		return;
	}

	UDataTable* SkillDataTable = GetSkillDataTable();
	const FMJSkillDataRow* DataRow = SkillDataTable->FindRow<FMJSkillDataRow>(SkillTag.GetTagName(), TEXT("ActivateSkill"));
	if (!DataRow)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist DataRow"));
		return;
	}

	UCurveTable* CurveTable = DataRow->SkillLevelDataTable.LoadSynchronous();
	if (!CurveTable)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist SkillLevelDataTable"));
		return;
	}

	const UMJCharacterSkillAttributeSet* SkillAttributeSet = ASC->GetSet<UMJCharacterSkillAttributeSet>();
	if (!SkillAttributeSet)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist SkillAttributeSet"));
		return;
	}

	TSubclassOf<UGameplayEffect> EffectClass = UMJGE_SetSkillAttributeSet::StaticClass();

	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1.f, EffectContext);
	// Dongmin: 여기서 Attribute 덮어줌
	if (SpecHandle.IsValid())
	{
		// Dongmin: Skill은 SkillComponent의 SkillData에서 가져와서 쓰는걸로 그 레벨로 다른 데이터를 가져오는 방식
		float SkillLevel = OwnedSkillMap[SkillTag].Level;
		SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.SkillLevel")), SkillLevel);
		SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.MaxSkillLevel")), 9);

		for (auto& CurveTableRow : CurveTable->GetRowMap())
		{
			const FName& RowName = CurveTableRow.Key;
			FRealCurve* Curve = CurveTable->FindCurve(RowName, TEXT("FindCurve"));

			if (Curve)
			{
				float Value = Curve->Eval(SkillLevel);
				FString TagString = FString::Printf(TEXT("Data.Skill.%s"), *RowName.ToString());
				SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName(*TagString)), Value);

			}
		}
		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}

	FGameplayAbilitySpecHandle Handle = GivenActionAbilityHandles[SkillTag];
	ASC->TryActivateAbility(Handle);

}

void UMJSkillComponentBase::ReleaseSkill(const FGameplayTag& SkillTag)
{
	if (!OwnedSkillMap.Contains(SkillTag))
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnedSkillMap[SkillTag]"));
		return;
	}

	if (!GivenActionAbilityHandles.Contains(SkillTag))
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist GivenActionAbilityHandles(EquippedSlotSkill)"));
		return;
	}

	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnerCharacter"));
		return;
	}

	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());
	if (!ASC)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist ASC"));
		return;
	}

	FGameplayAbilitySpecHandle Handle = GivenActionAbilityHandles[SkillTag];
	FGameplayAbilitySpec* SpecPtr = ASC->FindAbilitySpecFromHandle(Handle);
	if (SpecPtr)
	{
		ASC->AbilitySpecInputReleased(*SpecPtr);
	}
}

void UMJSkillComponentBase::GiveAbilityToASC(const FGameplayTag& SkillTag)
{
	if (!OwnedSkillMap.Contains(SkillTag))
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnedSkillMap[SkillTag]"));
		return;
	}

	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnerCharacter"));
		return;
	}
	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());
	if (!ASC)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist ASC"));
		return;
	}

	UDataTable* SkillDataTable = GetSkillDataTable();
	const FMJSkillDataRow* DataRow = SkillDataTable->FindRow<FMJSkillDataRow>(SkillTag.GetTagName(), TEXT("GiveAbility"));
	if (!DataRow)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist DataRow"));
		return;
	}

	RemoveAbility(SkillTag);

	int32 SkillLevel = OwnedSkillMap[SkillTag].Level;
	FName RowName = FName(*FString::FromInt(SkillLevel));
	// Minjin TODO: SkillLevelAbilityTable 넣어주기.
	UDataTable* SkillLevelAbilityTable = DataRow->SkillLevelAbilityTable.LoadSynchronous();
	if (!SkillLevelAbilityTable)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist SkillLevelAbilityTable"));
		return;
	}

	const FMJSkillLevelAbilityRow* LevelAbilityRow = SkillLevelAbilityTable->FindRow<FMJSkillLevelAbilityRow>(RowName, TEXT("SkillLevelAbility"));
	
	if (LevelAbilityRow->ActionSkillAbilityClass)
	{
		FGameplayAbilitySpec ActionAbilitySpec(LevelAbilityRow->ActionSkillAbilityClass, SkillLevel, INDEX_NONE, OwnerCharacter);
		FGameplayAbilitySpecHandle ActionHandle = ASC->GiveAbility(ActionAbilitySpec);
		GivenActionAbilityHandles.Add(SkillTag, ActionHandle);
	}

	if (LevelAbilityRow->SkillAbilityClass)
	{
		FGameplayAbilitySpec SkillAbilitySpec(LevelAbilityRow->SkillAbilityClass, SkillLevel, INDEX_NONE, OwnerCharacter);

		FGameplayAbilitySpecHandle SkillHandle = ASC->GiveAbility(SkillAbilitySpec);
		GivenSkillAbilityHandles.Add(SkillTag, SkillHandle);
	}

	if (LevelAbilityRow->PassiveSkillAbilityClass)
	{
		FGameplayAbilitySpec PassiveSkillAbilitySpec(LevelAbilityRow->PassiveSkillAbilityClass, SkillLevel, INDEX_NONE, OwnerCharacter);
		FGameplayAbilitySpecHandle PassiveSkillHandle = ASC->GiveAbility(PassiveSkillAbilitySpec);
		GivenPassiveAbilityHandles.Add(SkillTag, PassiveSkillHandle);
	}

	if (LevelAbilityRow->DrawMarkerAbilityClass)
	{
		FGameplayAbilitySpec DrawMarkerAbilitySpec(LevelAbilityRow->DrawMarkerAbilityClass, SkillLevel, INDEX_NONE, OwnerCharacter);
		FGameplayAbilitySpecHandle PassiveSkillHandle = ASC->GiveAbility(DrawMarkerAbilitySpec);
		GivenPassiveAbilityHandles.Add(SkillTag, PassiveSkillHandle);
	}
}

void UMJSkillComponentBase::RemoveAbility(const FGameplayTag& SkillTag)
{
	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnerCharacter"));
		return;
	}
	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent());
	if (!ASC)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist ASC"));
		return;
	}

	if (GivenActionAbilityHandles.Contains(SkillTag))
	{
		ASC->ClearAbility(GivenActionAbilityHandles[SkillTag]);
		GivenActionAbilityHandles.Remove(SkillTag);
	}

	if (GivenSkillAbilityHandles.Contains(SkillTag))
	{
		ASC->ClearAbility(GivenSkillAbilityHandles[SkillTag]);
		GivenSkillAbilityHandles.Remove(SkillTag);
	}

	if (GivenPassiveAbilityHandles.Contains(SkillTag))
	{
		ASC->ClearAbility(GivenSkillAbilityHandles[SkillTag]);
		GivenPassiveAbilityHandles.Remove(SkillTag);
	}

	if (GivenDrawMarkerAbilityHandles.Contains(SkillTag))
	{
		ASC->ClearAbility(GivenDrawMarkerAbilityHandles[SkillTag]);
		GivenDrawMarkerAbilityHandles.Remove(SkillTag);
	}
}

