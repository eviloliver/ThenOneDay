// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGameplayAbility.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "Component/MJCombatComponent.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "MJGameplayAbility.h"

void UMJGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
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

void UMJGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
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

UMJCombatComponent* UMJGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UMJCombatComponent>();
}

UMJAbilitySystemComponent* UMJGameplayAbility::GetAbilitySysteamComponent() const
{
	return Cast< UMJAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
	
}
