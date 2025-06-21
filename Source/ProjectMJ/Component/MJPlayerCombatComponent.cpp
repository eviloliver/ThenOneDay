// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MJPlayerCombatComponent.h"
#include "Character/Weapon/MJPlayerWeapon.h"

AMJPlayerWeapon* UMJPlayerCombatComponent::GetPlayerWeaponCarreidWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AMJPlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
