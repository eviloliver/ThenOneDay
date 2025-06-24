// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameplayTags.h"

namespace MJGameplayTags
{
	/*Input_Tag*/
	UE_DEFINE_GAMEPLAY_TAG(Input_SetDestination_Click, "Input.SetDestination.Click");
	UE_DEFINE_GAMEPLAY_TAG(Input_SetDestination_Touch, "Input.SetDestination.Touch");
	UE_DEFINE_GAMEPLAY_TAG(Input_Equip_Weapon, "Input.Equip.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Input_UnEquip_Weapon, "Input.UnEquip.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Input_Attack_Normal, "Input.Attack.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Input_Attack_Press, "Input.Attack.Press");


	/*Weapon_Tag*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");

	/*State_Tag*/
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Equip_Sword, "Player.State.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Unequip_Sword, "Player.State.Unequip.Sword");
	/*Ability_Tag*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Sword, "Player.Ability.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Sword, "Player.Ability.Unequip.Sword");
	
	/*Attack_Tag*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Attack_Normal_Sword, "Player.Attack.Normal.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Attack_Press_Sword, "Player.Attack.Press.Sword");
}
