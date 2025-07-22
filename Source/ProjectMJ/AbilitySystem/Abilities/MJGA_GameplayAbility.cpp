// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "Component/MJCombatComponent.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "MJGA_GameplayAbility.h"

#include "ProjectMJ.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

void UMJGA_GameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (AbilityActivationPolicy == EMJAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UMJGA_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void UMJGA_GameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EMJAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UMJCombatComponent* UMJGA_GameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UMJCombatComponent>();
}

UMJAbilitySystemComponent* UMJGA_GameplayAbility::GetAbilitySysteamComponent() const
{
	return Cast< UMJAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
	
}

void UMJGA_GameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (!CostGameplayEffect)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist CostGameplayEffect"));
		return;
	}

	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
	if (!ASC)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist ASC"));
		return;
	}

	const UMJCharacterSkillAttributeSet* SkillAttributeSet = ASC->GetSet<UMJCharacterSkillAttributeSet>();
	if (!SkillAttributeSet)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist SkillAttributeSet"));
		return;
	}

	FGameplayEffectSpecHandle CostSpecHandle = MakeOutgoingGameplayEffectSpec(CostGameplayEffect, 1.0f);
	if (!CostSpecHandle.Data)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist CostSpecHandle.Data"));
		return;
	}

	CostSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostStamina")), SkillAttributeSet->GetCostStamina());
	CostSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostMana")), SkillAttributeSet->GetCostMana());
	CostSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Skill.CostFocus")), SkillAttributeSet->GetCostFocus());

	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, CostSpecHandle);
}

void UMJGA_GameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
}
