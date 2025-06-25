// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerType/MJPlayerStructType.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"

bool FPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
