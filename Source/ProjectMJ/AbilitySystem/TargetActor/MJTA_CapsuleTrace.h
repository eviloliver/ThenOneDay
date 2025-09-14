// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActor/MJTA_Trace.h"
#include "MJTA_CapsuleTrace.generated.h"

/**
 * Class Description: 캡슐 모양 Trace
 * Author: 신동민
 * Created Date: 2025.07.18
 * Description of Change: 같은 클래스끼리 공격 못하도록 수정
 * Modified By: 김민진
 * Modified Date: 2025.07.27.
 * Description of Change: Trace 위치 오프셋 추가
 * Modified By: 김민진
 * Modified Date: 2025.08.05.
 */
UCLASS()
class PROJECTMJ_API AMJTA_CapsuleTrace : public AMJTA_Trace
{
	GENERATED_BODY()

public:
	AMJTA_CapsuleTrace();
protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;
};
