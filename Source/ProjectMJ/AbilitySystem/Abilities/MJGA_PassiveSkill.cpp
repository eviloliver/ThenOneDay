// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGA_PassiveSkill.h"

#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"

UMJGA_PassiveSkill::UMJGA_PassiveSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMJGA_PassiveSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UMJGA_PassiveSkill::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	if (!ASC)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist ASC"));
		return;
	}

	for (TSubclassOf<UGameplayEffect> EffectClass : PassiveEffects)
	{
		MJ_LOG(LogMJ, Error, TEXT("AAAAA"));

		if (EffectClass)
		{
			FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1.0f, EffectContext);
			if (SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				if (ActiveGameplayEffectHandle.WasSuccessfullyApplied())
				{
					AppliedEffects.Add(ActiveGameplayEffectHandle);
				}
			}
		}
	}

}

void UMJGA_PassiveSkill::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	if (!ASC)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist ASC"));
		return;
	}

	for (FActiveGameplayEffectHandle ActiveHandle : AppliedEffects)
	{
		if (ActiveHandle.IsValid())
		{
			ASC->RemoveActiveGameplayEffect(ActiveHandle);
		}
	}
	
	AppliedEffects.Empty();

	Super::OnRemoveAbility(ActorInfo, Spec);

}

