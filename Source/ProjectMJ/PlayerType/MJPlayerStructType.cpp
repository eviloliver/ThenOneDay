// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerType/MJPlayerStructType.h"
#include "AbilitySystem/Abilities/MJGameplayAbility.h"

bool FPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
