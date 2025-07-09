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
/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: 2025_06_11
 * Last Modified By: Add CombatComponent Data
 * Last Modified Date: 2025_06_18
 */
UCLASS()
class PROJECTMJ_API UMJGA_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EMJAbilityActivationPolicy AbilityActivationPolicy = EMJAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category="Player|Combat")
	UMJCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Player|Combat")
	UMJAbilitySystemComponent* GetAbilitySysteamComponent() const;
};
