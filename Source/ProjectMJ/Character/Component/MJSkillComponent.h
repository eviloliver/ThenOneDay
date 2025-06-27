// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "DataTable/MJSkillDataRow.h"
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

UENUM(BlueprintType)
enum class ESlotType : uint8
{
	None UMETA(Hidden),
	Instant UMETA(DisplayName = "Instant", ToolTip = "Instantly Action Skill"),
	Charge UMETA(DisplayName = "Charge", ToolTip = "Charging Action Skill"),
	Passive UMETA(DisplayName = "Passive", ToolTip = "Passive Skill"),
};

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
	FGameplayTagContainer SkillStateTags;
};

UCLASS( ClassGroup=(Skill), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMJSkillComponent();

public:
	void LearnSkill(const FGameplayTag& NewSkill);
	
	void EquipSkill(const FGameplayTag& EquippingSkill, ESlotType ActivateSlot);

	void UnequipSkill(const FGameplayTag& UnequippingSkill);

	void ActivateSkill(ESlotType ActivateSlot);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FSkillData> OwnedSkillMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<ESlotType, FSkillData> EquippedSkillMap;

};
