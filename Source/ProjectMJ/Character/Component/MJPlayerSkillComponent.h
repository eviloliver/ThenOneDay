// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "MJPlayerSkillComponent.generated.h"

/**
 * Class Description: 스킬 컴포넌트
 * - 플레이어가 사용할 컴포넌트
 * Author: 신동민
 * Created Date: 2025.07.08
 * Modified Description: InputTag 를 그냥 유형으로 받아오기
 * Modified By: 신동민
 * Modified Date: 2025.07.15
 */

UCLASS(ClassGroup = (Skill), meta = (BlueprintSpawnableComponent))
class PROJECTMJ_API UMJPlayerSkillComponent : public UMJSkillComponentBase
{
	GENERATED_BODY()

public:
	UMJPlayerSkillComponent();

	virtual void BeginPlay() override;

	void ActivateSkillByInputTag(const FGameplayTag InputTag);

};
