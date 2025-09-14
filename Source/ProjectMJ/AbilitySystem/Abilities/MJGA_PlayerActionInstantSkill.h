// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_InstantSkill.h"
#include "MJGA_PlayerActionInstantSkill.generated.h"

/**
 * Class Description: AM 을 실행시키는 어빌리티. 플레이어는 마우스 방향을 바라보고 스킬을 사용한다
 * Author: 신동민
 * Created Date: 2025.07.18
 * Description of Change: 
 * Modified By:
 * Modified Date: 
 */
UCLASS()
class PROJECTMJ_API UMJGA_PlayerActionInstantSkill : public UMJGA_InstantSkill
{
	GENERATED_BODY()

public:
	UMJGA_PlayerActionInstantSkill();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UFUNCTION()
	void OnMousePositionReady(const FVector& MouseLocation);

	UFUNCTION()
	void OnMousePositionFailed(const FVector& IgnoreLocation);

	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void OnInterruptedCallback();
	
};
