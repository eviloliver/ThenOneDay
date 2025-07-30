// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "GameplayTagContainer.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Effects")
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Effects")
	TSubclassOf<UGameplayEffect> StatusGameplayEffectClass;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<AMJTA_Trace> TargetActorClass;

	UPROPERTY(EditAnywhere, Category = "GameplayCue" , meta = (Categories = "GameplayCue"))
	FGameplayTag GameplayCueTag;
};
