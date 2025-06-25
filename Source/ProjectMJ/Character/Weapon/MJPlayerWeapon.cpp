// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Weapon/MJPlayerWeapon.h"

void AMJPlayerWeapon::AssignGrantedAbilitySpecHandle(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AMJPlayerWeapon::GetGrantedAbilitySpecHandle() const
{
	return GrantedAbilitySpecHandles;
}
