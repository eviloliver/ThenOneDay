// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "MJGA_ChargeSkill.generated.h"

/**
 * Class Description: 플레이어의 스킬을 Instant, Charging, Passive로 구분
 * Charge는 우클릭을 길게 눌렀다 땠 을때 발동하는 스킬
 * Author: 신동민
 * Created Date: 2025.06.24
 * Description of Change: 차징 애니메이션 추가
 * Modified By: 신동민
 * Modified Date: 2025.08.06
 */

UCLASS()
class PROJECTMJ_API UMJGA_ChargeSkill : public UMJGA_GameplayAbility
{
	GENERATED_BODY()

public:
	UMJGA_ChargeSkill();

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

protected:

	virtual bool CalculateFinalCosts(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FSkillCost& OutCost) const;
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

protected:
	UPROPERTY(EditAnywhere, Category="Animation")
	TObjectPtr<UAnimMontage> SkillChargeAnimMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> SkillActionAnimMontage;

};
