// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effect/MJGE_AttackDamage.h"
#include "AbilitySystem/Effect/MJEC_SkillDamage.h"

UMJGE_AttackDamage::UMJGE_AttackDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayEffectExecutionDefinition ExecutionDefinition;
    ExecutionDefinition.CalculationClass = UMJEC_SkillDamage::StaticClass();

    Executions.Add(ExecutionDefinition);
}
