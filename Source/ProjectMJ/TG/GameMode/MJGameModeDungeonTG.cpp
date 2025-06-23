// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameModeDungeonTG.h"

#include "EngineUtils.h"
#include "ProjectMJ.h"
#include "TG/GameState/MJGameStateDungeonTG.h"
#include "TG/Struct/MJDungeonSessionDataStruct.h"

AMJGameModeDungeonTG::AMJGameModeDungeonTG()
{
	MJ_LOG(LogTG,Log,TEXT("New GameMode Instance Created"));
}

void AMJGameModeDungeonTG::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	

		GetGameState<AMJGameStateDungeonTG>()->SaveDungeonSessionDataToGameInstance();

	
}

bool AMJGameModeDungeonTG::TravelToMapByNode(const FString MapName, const uint8 NodeNum)
{
	
	return Super::TravelToMapByNode(MapName, NodeNum);
}

void AMJGameModeDungeonTG::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();

	
}
