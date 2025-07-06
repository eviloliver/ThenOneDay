// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "DataTable/MJSkillDataRow.h"
#include "GameplayAbilitySpec.h"
#include "MJSkillComponent.generated.h"

/**
 * Class Description: 스킬 컴포넌트
 * 역할
 * - 보유 스킬을 가질 수 있고, 장착 할 수 있음
 * - 
 * -
 * Author: 신동민
 * Created Date: 2025_06_27
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
class PROJECTMJ_API UMJSkillComponent : public UActorComponent
{
	GENERATED_BODY() 

public:	
	// Sets default values for this component's properties
	UMJSkillComponent();

	virtual void BeginPlay() override;

public:
	void LearnSkill(const FGameplayTag& NewSkill);
	
	void EquipSkill(const FGameplayTag& EquippingSkill);

	void UnequipSkill(const FGameplayTag& UnequippingSkill);

	void ActivateSkill(const FGameplayTag& EquippedSlotSkill);

	void GiveAbilityToASC(const FGameplayTag& AddSkill);

	void RemoveAbility(const FGameplayTag& RemoveSkill);

	void ActivateSkillByInputTag(const FGameplayTag& InputTag);

	FGameplayTag ConvertInputTagToTypeTag(const FGameplayTag& InputTag);

	// Getter
	TMap<FGameplayTag, FSkillData> GetOwnedSkillMap() const { return OwnedSkillMap; };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FSkillData> OwnedSkillMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayTag> EquippedSkillMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayTag> InputTagToSkillTagMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> GivenAbilityHandles;
};
