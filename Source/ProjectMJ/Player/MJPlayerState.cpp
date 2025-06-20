// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MJPlayerState.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem//Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

AMJPlayerState::AMJPlayerState()
{
	ASC = CreateDefaultSubobject<UMJAbilitySystemComponent>(TEXT("ASC"));
	CharacterAttributeSet = CreateDefaultSubobject<UMJCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
	CharacterSkillAttributeSet = CreateDefaultSubobject<UMJCharacterSkillAttributeSet>(TEXT("CharacterSkillAttributeSet"));
}


UAbilitySystemComponent* AMJPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}