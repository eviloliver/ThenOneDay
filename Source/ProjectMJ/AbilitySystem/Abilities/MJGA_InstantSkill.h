// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "MJGA_InstantSkill.generated.h"

/**
 * Class Description: 플레이어의 스킬을 Instant, Charging, Passive로 구분
 * Instant는 우클릭 딸깍에 매칭하는 스킬 + 기본 공격
 * Author: 신동민
 * Created Date: 2025_06_24
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */

class UAnimMontage;
class UGameplayEffect;

UCLASS()
class PROJECTMJ_API UMJGA_InstantSkill : public UMJGA_GameplayAbility
{
	GENERATED_BODY()

public:
	UMJGA_InstantSkill();

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo);
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> SkillActionAnimMontage;

	// 
	UPROPERTY(EditDefaultsOnly, Category = "Cost")
	TSubclassOf<UGameplayEffect> CostGameplayEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Cooldown")
	TSubclassOf<UGameplayEffect> CooldownGameplayEffect;



};
