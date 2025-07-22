// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActor/MJTA_Trace.h"
#include "MJTA_SphereTrace.generated.h"

/**
 * Class Description: 구 모양 Trace
 * Author: 신동민
 * Created Date: 2025.07.18
 * Description of Change:
 * Modified By:
 * Modified Date: 
 */
UCLASS()
class PROJECTMJ_API AMJTA_SphereTrace : public AMJTA_Trace
{
	GENERATED_BODY()
public:
	AMJTA_SphereTrace();
protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;

};
