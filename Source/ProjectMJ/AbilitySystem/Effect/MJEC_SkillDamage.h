// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "MJEC_SkillDamage.generated.h"

/**
 * Class Description: 데미지 계산을 하는 이펙트
 * Author: 신동민
 * Created Date: 2025.07.07
 * Last Modified By: 김민진
 * Last Modified Date: (25.08.08.) 데미지 태그 부여
 */

UCLASS()
class PROJECTMJ_API UMJEC_SkillDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UMJEC_SkillDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
