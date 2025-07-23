// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameModeDungeonTG.h"

#include "ProjectMJ.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MJPlayerState.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/GameState/MJGameStateDungeonTG.h"


AMJGameModeDungeonTG::AMJGameModeDungeonTG()
{
}

void AMJGameModeDungeonTG::BeginPlay()
{
	Super::BeginPlay();
	
	AMJPlayerState* MJPS = Cast<AMJPlayerState>(UGameplayStatics::GetPlayerState(this,0));

	if (MJPS)
	{
		MJPS->LoadFromInstancedPlayerSessionData();
	}
	
}

bool AMJGameModeDungeonTG::TravelToMapByNode(const FString MapName, const uint8 NodeNum)
{

	UMJGameInstanceTG* MJGI = GetGameInstance<UMJGameInstanceTG>();
	if (MJGI)
	{
		AMJPlayerState* PS = Cast<AMJPlayerState>(UGameplayStatics::GetPlayerState(this,0));
		
		MJGI->GetPlayerSessionDataRef().CurrentDungeonMapNum = NodeNum;
		
		AMJGameStateDungeonTG* MJGS = GetGameState<AMJGameStateDungeonTG>();
		
		if (MJGS )
		{
			MJGS->SaveToInstancedDungeonSessionData(PS->GetPlayerSessionDataRef().CurrentDungeonMapNum);
		}
		
		MJGI->GetPlayerSessionDataRef().CurrentDungeonMapNum = NodeNum;
		
	}
	
	return Super::TravelToMapByNode(MapName, NodeNum);

	
}

