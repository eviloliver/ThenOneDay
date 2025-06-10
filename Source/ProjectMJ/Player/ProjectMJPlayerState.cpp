// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ProjectMJPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ProjectMJCharacterAttributeSet.h"

AProjectMJPlayerState::AProjectMJPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	CharacterAttributeSet = CreateDefaultSubobject<UProjectMJCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
}

\
class UAbilitySystemComponent* AProjectMJPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}