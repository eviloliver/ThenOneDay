// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MJPlayerState.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/MJCharacterAttributeSet.h"

AMJPlayerState::AMJPlayerState()
{
	ASC = CreateDefaultSubobject<UMJAbilitySystemComponent>(TEXT("ASC"));
	CharacterAttributeSet = CreateDefaultSubobject<UMJCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
}


UAbilitySystemComponent* AMJPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}