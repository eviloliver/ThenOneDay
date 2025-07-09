// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJSkillComponentBase.h"

#include "ProjectMJ.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "AbilitySystem/Effect/MJGE_SetSkillAttributeSet.h"
#include "Character/MJCharacterBase.h"
#include "DataTable/MJSkillDataRow.h"
#include "TG/MJGameInstanceTG.h"

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
		UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
		if (!GI || !GI->SkillDataTable)
		{
			return;
		}
		FName RowName = SkillTag.GetTagName();
		const FMJSkillDataRow* DataRow = GI->SkillDataTable->FindRow<FMJSkillDataRow>(RowName, TEXT(""));
		if (DataRow)
		{
			FSkillData NewSkillData;
			NewSkillData.SkillDefaultTag = SkillTag;
			NewSkillData.SkillTypeTag = SkillTag.GetGameplayTagParents().GetByIndex(1);
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

	if (!GivenAbilityHandles.Contains(SkillTag))
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist GivenAbilityHandles(EquippedSlotSkill)"));
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

	UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
	if (!GI || !GI->SkillDataTable)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist GI or SkillDataTable"));
		return;
	}

	const FMJSkillDataRow* DataRow = GI->SkillDataTable->FindRow<FMJSkillDataRow>(SkillTag.GetTagName(), TEXT("ActivateSkill"));
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

	FGameplayAbilitySpecHandle Handle = GivenAbilityHandles[SkillTag];
	ASC->TryActivateAbility(Handle);
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

	UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
	if (!GI || !GI->SkillDataTable)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist GI or SkillDataTable"));
		return;
	}

	const FMJSkillDataRow* DataRow = GI->SkillDataTable->FindRow<FMJSkillDataRow>(SkillTag.GetTagName(), TEXT("GiveAbility"));
	if (!DataRow || !DataRow->SkillAbilityClass)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist DataRow or SkillAbilityClass"));
		return;
	}

	RemoveAbility(SkillTag);

	int32 SkillLevel = OwnedSkillMap[SkillTag].Level;

	FGameplayAbilitySpec AbilitySpec(DataRow->SkillAbilityClass, SkillLevel, INDEX_NONE, OwnerCharacter);

	const FSkillAssetDataByLevel* FoundAssetData = nullptr;

	for (int32 i = DataRow->AssetTagDataByLevel.Num() - 1; i >= 0; --i)
	{
		const FSkillAssetDataByLevel& AssetData = DataRow->AssetTagDataByLevel[i];
		if (SkillLevel >= AssetData.MinimumLevel)
		{
			FoundAssetData = &AssetData;
			break;
		}
	}

	if (FoundAssetData)
	{
		// Dongmin: 이거도 투사체 처럼 바꿀까 고민
		if (FoundAssetData->AnimationTag.IsValid())
		{
			AbilitySpec.DynamicAbilityTags.AddTag(FoundAssetData->AnimationTag);
		}

		if (OwnedSkillMap.Contains(SkillTag))
		{
			OwnedSkillMap[SkillTag].ProjectileTag = FoundAssetData->ProjectileTag;
		}
	}
	else
	{

	}

	FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(AbilitySpec);
	GivenAbilityHandles.Add(SkillTag, Handle);
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

	if (GivenAbilityHandles.Contains(SkillTag))
	{
		ASC->ClearAbility(GivenAbilityHandles[SkillTag]);
		GivenAbilityHandles.Remove(SkillTag);
	}
}

