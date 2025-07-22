// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "MJGA_PassiveSkill.generated.h"

/**
 * Class Description: 플레이어의 스킬을 Instant, Charging, Passive로 구분
 * Passive는 항상 영향을 주는 버프 또는 디버프 같은 스킬, 기본 지속 효과 라고도 함
 * Author: 신동민
 * Created Date: 2025_06_24
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UMJGA_PassiveSkill : public UMJGA_GameplayAbility
{
	GENERATED_BODY()

public:
	UMJGA_PassiveSkill();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Passive")
	TArray<TSubclassOf<UGameplayEffect>> PassiveEffects;

};
