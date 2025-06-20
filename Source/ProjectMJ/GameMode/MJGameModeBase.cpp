// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MJGameModeBase.h"

#include "ProjectMJ.h"
#include "Internationalization/StringTableRegistry.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/MJGameStateDungeonTG.h"

AMJGameModeBase::AMJGameModeBase()
{
	// static ConstructorHelpers::FObjectFinder<UStringTable> MapNamesRef(TEXT("/Script/Engine.StringTable'/Game/Blueprint/GameData/TG_MapNames.TG_MapNames'"));
	// if (MapNamesRef.Object)
	// {
	// 	MapNames = MapNamesRef.Object;
	// }

	//MapNames = FStringTableRegistry::Get().FindStringTable(FName(TEXT("/Script/Engine.StringTable'/Game/Blueprint/GameData/TG_MapNames.TG_MapNames'")));
}


bool AMJGameModeBase::TravelToMap(const FString MapName)
{
	bool bAbsolute = false;
	if (CanServerTravel(MapName, bAbsolute))
	{
		GetWorld()->ServerTravel(MapName);
	}
	else
	{
		MJ_LOG(LogTemp,Warning,TEXT("Can`t Travel to %s"), *MapName);
	}

	return false;
}

bool AMJGameModeBase::TravelToMapByNode(const FString MapName, const uint8 NodeNum)
{

	UMJGameInstanceTG* MJGI = GetGameInstance<UMJGameInstanceTG>();
	if (MJGI)
	{
		MJGI->SetSavedMapNodeNum(NodeNum);
	}
	
	// AMJGameStateDungeonTG* MJGS = GetGameState<AMJGameStateDungeonTG>();
	// if (MJGS)
	// {
	// 	
	// 	MJGS->SetCurrentNodeNum(NodeNum);
	// 	
	// }	

	if (TravelToMap(MapName))
	{
		return true;
	}
	else
	{
		return false;
	}
}
