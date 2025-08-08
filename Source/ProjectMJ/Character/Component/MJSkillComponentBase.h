// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpec.h"

#include "MJSkillComponentBase.generated.h"

/**
 * Class Description: 스킬 컴포넌트 베이스
 * - 플레이어와 AI가 사용하는 공통 스킬 컴포넌트
 * - *더 구체적으로 분류한다면, AI가 스킬을 여러개 사용 + 장착을 안 하는 개념으로 더 추상화 가능*
 * Author: 신동민
 * Created Date: 2025.07.08
 * Last Modified By:
 * Last Modified Date:
 */

USTRUCT(BlueprintType)
struct FSkillData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag SkillDefaultTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag SkillTypeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ProjectileTag;
};

UCLASS( ClassGroup=(Skill), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJSkillComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMJSkillComponentBase();
	
	virtual void LearnSkill(const FGameplayTag& SkillTag);

	virtual void EquipSkill(const FGameplayTag& SkillTag);

	virtual void UnequipSkill(const FGameplayTag& SkillTag);

	virtual void ActivateSkill(const FGameplayTag& SkillTag);

	virtual void ReleaseSkill(const FGameplayTag& SkillTag);

	void GiveAbilityToASC(const FGameplayTag& SkillTag);

	void RemoveAbility(const FGameplayTag& SkillTag);

	// Getter
	TMap<FGameplayTag, FSkillData> GetOwnedSkillMap() const { return OwnedSkillMap; }
	TMap<FGameplayTag, FGameplayTag> GetEquippedSkillMap() const {return EquippedSkillMap;}

	virtual UDataTable* GetSkillDataTable() const PURE_VIRTUAL(UMJSkillComponentBase::GetSkillDataTable, return nullptr;);


protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FSkillData> OwnedSkillMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayTag> EquippedSkillMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> GivenActionAbilityHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> GivenSkillAbilityHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> GivenPassiveAbilityHandles;
	
};
