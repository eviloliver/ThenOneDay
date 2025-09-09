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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLearnSkillEvent, FGameplayTag, SkillTag, int32, Level);
class UMJUIManagerSubsystem;
class UMJSkillWidget;

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

	void SetOwnedSkillMap(TMap<FGameplayTag, FSkillData> InputOwnedSkillMap);
	void SetEquippedSkillMap(TMap<FGameplayTag, FGameplayTag> InputEquippedSkillMap);

	virtual UDataTable* GetSkillDataTable() const PURE_VIRTUAL(UMJSkillComponentBase::GetSkillDataTable, return nullptr;);

	FOnLearnSkillEvent OnLearnSkillEvent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FSkillData> OwnedSkillMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayTag> EquippedSkillMap;

	// PlayerSessionData 에서 로딩된 데이터는 여기에 담겨 다시 Learn 함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FSkillData> LoadedOwnedSkillMap;

	// PlayerSessionData 에서 로딩된 데이터는 여기에 담겨 다시 Equip 함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayTag> LoadedEquippedSkillMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> GivenActionAbilityHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> GivenSkillAbilityHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> GivenPassiveAbilityHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> GivenDrawMarkerAbilityHandles;


	// 시간관계상 구조를 생각하지 않고.. 임시로 갖고 있겠다...
};
