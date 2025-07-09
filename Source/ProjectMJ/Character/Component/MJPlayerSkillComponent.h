// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "MJPlayerSkillComponent.generated.h"

/**
 * Class Description: 스킬 컴포넌트
 * - 플레이어가 사용할 컴포넌트
 * - input과 매핑하며 장착한 스킬을 발동
 * Author: 신동민
 * Created Date: 2025.07.08
 * Last Modified By:
 * Last Modified Date:
 */

UCLASS(ClassGroup = (Skill), meta = (BlueprintSpawnableComponent))
class PROJECTMJ_API UMJPlayerSkillComponent : public UMJSkillComponentBase
{
	GENERATED_BODY()

public:
	UMJPlayerSkillComponent();

	virtual void BeginPlay() override;

	void ActivateSkillByInputTag(const FGameplayTag InputTag);

	FGameplayTag ConvertInputTagToTypeTag(const FGameplayTag& InputTag);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayTag> InputTagToSkillTagMap;

};
