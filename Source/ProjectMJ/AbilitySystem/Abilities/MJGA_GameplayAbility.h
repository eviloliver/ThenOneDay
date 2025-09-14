// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MJGA_GameplayAbility.generated.h"

class UMJCombatComponent;
class UMJAbilitySystemComponent;

UENUM(BlueprintType)
enum class EMJAbilityActivationPolicy :uint8
{
	OnTriggered,
	OnGiven
};

struct FSkillCost
{
	float StaminaCost = 0.0f;
	float ManaCost = 0.0f;
	float FocusCost = 0.0f;
};

/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: 2025_06_11
 * Description of Change: 자원 소모 쿨타임 감소 추가
 * Modified By: 신동민	
 * Modified Date: 2025.07.23
 */
UCLASS()
class PROJECTMJ_API UMJGA_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EMJAbilityActivationPolicy AbilityActivationPolicy = EMJAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category="Player|Combat")
	UMJCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Player|Combat")
	UMJAbilitySystemComponent* GetAbilitySysteamComponent() const;

	
};
