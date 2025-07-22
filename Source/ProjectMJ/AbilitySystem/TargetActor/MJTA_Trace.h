// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "MJTA_Trace.generated.h"

/**
 * Class Description: 충돌을 확인하는 Target Actor
 * Author: 신동민
 * Created Date: 2025.06.18
 * Description of Change: 추상화 후 자식에서 구체화 하도록 구조 변경
 * Modified By: 신동민
 * Modified Date: 2025.07.18
 */
UCLASS()
class PROJECTMJ_API AMJTA_Trace : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AMJTA_Trace();

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;
	void SetShowDebug(bool isShowDebug) { bShowDebug = isShowDebug; }

protected:

	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const;

	bool bShowDebug = false;
};
