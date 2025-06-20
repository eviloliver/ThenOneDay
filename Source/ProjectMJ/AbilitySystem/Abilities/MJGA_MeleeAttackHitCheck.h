// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "MJGA_MeleeAttackHitCheck.generated.h"

/**
 * Class Description: 근접 공격을 할 때, 공격에 충돌했는지 확인하는 어빌리티
	여기서 Trace_AT와 Trace_TA를 확인,
	AnimNotify와 연동(보통 근접공격을 할 때는 Notify에서 충돌검사를 해서)
 * Author: 신동민
 * Created Date: 2025_06_19
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */

class UGameplayEffect;
class AMJTA_Trace;

UCLASS()
class PROJECTMJ_API UMJGA_MeleeAttackHitCheck : public UMJGA_GameplayAbility
{
	GENERATED_BODY()

public:
	UMJGA_MeleeAttackHitCheck();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
protected:

	UFUNCTION()
	void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<UGameplayEffect> AttackDamageEffect;

	// 사용할 어빌리티들 적용을 해야하나
	// 버프/디버프 등

	// 데이터로 따로 관리할 가능성이 높음
	// 그래서 추후 사용할지도
	// 명시 안해주면 1.f긴 함
	// float CurrentLevel;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<AMJTA_Trace> TargetActorClass;

};
