// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effect/MJGE_AttackDamage.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"

UMJGE_AttackDamage::UMJGE_AttackDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
}
