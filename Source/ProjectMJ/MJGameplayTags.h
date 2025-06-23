// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include"NativeGameplayTags.h"

/**
 * Class Description: Player Tag
 * Author: Lee JuHyeon
 * Created Date: 2025_06_12
 * Last Modified By: Add GameplayTag
 * Last Modified Date: 2025_06_21
 */

namespace MJGameplayTags
{
	/*Input_Tag*/
	PROJECTMJ_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_SetDestination_Click);
	PROJECTMJ_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_SetDestination_Touch);
	PROJECTMJ_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Equip_Weapon);
	PROJECTMJ_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_UnEquip_Weapon);

	/*Weapon_Tag*/
	PROJECTMJ_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);
	/*State_Tag*/
	PROJECTMJ_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Equip_Sword);
	PROJECTMJ_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Unequip_Sword);

	PROJECTMJ_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Abiliy_Equip_Sword);
	PROJECTMJ_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Abiliy_Unequip_Sword);

}
