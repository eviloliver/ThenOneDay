// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MJPlayerState.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem//Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "Character/Component/MJPlayerStatComponent.h"
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
	FMJPlayerSessionData& MJGIPlayerSessionData = GetGameInstance<UMJGameInstanceTG>()->GetPlayerSessionDataRef();
	
	MJGIPlayerSessionData.CharacterAttribute = *CharacterAttributeSet;
	MJGIPlayerSessionData.CharacterSkillAttribute = *CharacterSkillAttributeSet;
	UMJPlayerStatComponent* PlayerStatComp = GetPawn()->FindComponentByClass<UMJPlayerStatComponent>();
	if (PlayerStatComp)
	{
		MJGIPlayerSessionData.PlayerLevel = PlayerStatComp->GetPlayerLevel();
		MJGIPlayerSessionData.PlayerExp = PlayerStatComp->GetTotalCumulativeExperience();
	}

}

void AMJPlayerState::LoadFromInstancedPlayerSessionData()
{
	PlayerSessionData = GetGameInstance<UMJGameInstanceTG>()->GetPlayerSessionDataRef();
	PlayerSessionData.CharacterAttribute.ApplyToAttributeSet(*CharacterAttributeSet);
	PlayerSessionData.CharacterSkillAttribute.ApplyToAttributeSet(*CharacterSkillAttributeSet);
	PlayerSessionData.PlayerLevel =  GetGameInstance<UMJGameInstanceTG>()->GetPlayerSessionDataRef().PlayerLevel;
	PlayerSessionData.PlayerExp = GetGameInstance<UMJGameInstanceTG>()->GetPlayerSessionDataRef().PlayerExp;

	GetPawn()->FindComponentByClass<UMJPlayerStatComponent>()->SetPlayerLevel(PlayerSessionData.PlayerLevel);
	GetPawn()->FindComponentByClass<UMJPlayerStatComponent>()->SetTotalCumulativeExperience(PlayerSessionData.PlayerExp);
	GetPawn()->FindComponentByClass<UMJPlayerStatComponent>()->InitializeStat();
}

void AMJPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//FCoreDelegates::GetApplicationWillTerminateDelegate().AddUObject(this, &ThisClass::OnUserEndPlay);
}

void AMJPlayerState::BeginPlay()
{
	Super::BeginPlay();

	LoadFromInstancedPlayerSessionData();
}

void AMJPlayerState::OnUserEndPlay()
{
	//SaveToInstancedPlayerSessionData();
}

