// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MJCombatComponent.h"
#include "Character/Weapon/MJWeaponBase.h"

void UMJCombatComponent::RegisterSpawnedWeapon(FGameplayTag InPlayerTagToRegister, AMJWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	check(InWeaponToRegister)

		CharacterCarriedWeaponMap.Emplace(InPlayerTagToRegister, InWeaponToRegister);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InPlayerTagToRegister;
	}
	UE_LOG(LogTemp, Warning, TEXT("HI"));
}

AMJWeaponBase* UMJCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AMJWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
		
	}
		return nullptr;
}

AMJWeaponBase* UMJCombatComponent::GetCharacterCarriedEquippedWeapon() const
{
	return nullptr;
}
