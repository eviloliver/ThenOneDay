// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/MJTA_Trace.h"

AMJTA_Trace::AMJTA_Trace()
{
}

void AMJTA_Trace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
}

void AMJTA_Trace::ConfirmTargetingAndContinue()
{
	Super::ConfirmTargetingAndContinue();
}

FGameplayAbilityTargetDataHandle AMJTA_Trace::MakeTargetData() const
{
	return FGameplayAbilityTargetDataHandle();
}
