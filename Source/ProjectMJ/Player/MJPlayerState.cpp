// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MJPlayerState.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem//Attributes/MJCharacterAttributeSet.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"

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

FMJPlayerSessionData& AMJPlayerState::GetPlayerSessionData()
{
	return PlayerSessionData;
}

void AMJPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	AMJPlayerState* MJPS = Cast<AMJPlayerState>(PlayerState);
	
	if (MJPS)
	{
		
		MJPS->ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetHealthAttribute(),ASC->GetSet<UMJCharacterAttributeSet>()->GetHealth());
		MJPS->PlayerSessionData = PlayerSessionData;

		// TODO CharacterAttribute 프로퍼티 옮겨담기
		
		MJ_LOG(LogTG,Warning, TEXT("PlayerState Pointer Copied!!"));
		MJ_LOG(LogTG,Warning, TEXT("PlayerSessionData.DungeonNodeNum = %d"), MJPS->PlayerSessionData.CurrentDungeonMapNum);
	}

	
}
