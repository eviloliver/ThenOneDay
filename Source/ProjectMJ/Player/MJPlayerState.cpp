// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MJPlayerState.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem//Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "TG/MJGameInstanceTG.h"

AMJPlayerState::AMJPlayerState()
{
	ASC = CreateDefaultSubobject<UMJAbilitySystemComponent>(TEXT("ASC"));
	CharacterAttributeSet = CreateDefaultSubobject<UMJCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
	MJ_LOG(LogTG,Log, TEXT("Ptr : %p"),this);
	
	CharacterSkillAttributeSet = CreateDefaultSubobject<UMJCharacterSkillAttributeSet>(TEXT("CharacterSkillAttributeSet"));
}


UAbilitySystemComponent* AMJPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

UMJCharacterAttributeSet* AMJPlayerState::GetCharacterAttributeSet() const
{
	return CharacterAttributeSet;
}

FMJPlayerSessionData& AMJPlayerState::GetPlayerSessionDataRef()
{
	return PlayerSessionData;
}

void AMJPlayerState::SaveToInstancedPlayerSessionData()
{
	PlayerSessionData.CharacterAttribute = *CharacterAttributeSet;
	PlayerSessionData.CharacterSkillAttribute = *CharacterSkillAttributeSet;
	GetGameInstance<UMJGameInstanceTG>()->GetPlayerSessionDataRef() = PlayerSessionData;
	
	MJ_LOG(LogTG,Warning, TEXT("PlayerState Copied!!"));

}

void AMJPlayerState::LoadFromInstancedPlayerSessionData()
{
	PlayerSessionData = GetGameInstance<UMJGameInstanceTG>()->GetPlayerSessionDataRef();
	PlayerSessionData.CharacterAttribute.ApplyToAttributeSet(*CharacterAttributeSet);
	PlayerSessionData.CharacterSkillAttribute.ApplyToAttributeSet(*CharacterSkillAttributeSet);
}

