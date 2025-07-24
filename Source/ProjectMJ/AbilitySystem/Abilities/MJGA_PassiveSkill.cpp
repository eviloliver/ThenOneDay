// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGA_PassiveSkill.h"

UMJGA_PassiveSkill::UMJGA_PassiveSkill()
{
	
}

void UMJGA_PassiveSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

