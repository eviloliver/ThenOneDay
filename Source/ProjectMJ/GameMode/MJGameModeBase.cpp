// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MJGameModeBase.h"

#include "ProjectMJ.h"
#include "Internationalization/StringTableRegistry.h"

AMJGameModeBase::AMJGameModeBase()
{
	// static ConstructorHelpers::FObjectFinder<UStringTable> MapNamesRef(TEXT("/Script/Engine.StringTable'/Game/Blueprint/GameData/TG_MapNames.TG_MapNames'"));
	// if (MapNamesRef.Object)
	// {
	// 	MapNames = MapNamesRef.Object;
	// }

	//MapNames = FStringTableRegistry::Get().FindStringTable(FName(TEXT("/Script/Engine.StringTable'/Game/Blueprint/GameData/TG_MapNames.TG_MapNames'")));
}

FString AMJGameModeBase::GetCurrentMapName()
{
	return CurrentMapName;
}

bool AMJGameModeBase::TravelToMap(const FString MapName)
{
	bool bAbsolute = false;
	if (CanServerTravel(MapName, bAbsolute))
	{
		if (GetWorld()->ServerTravel(MapName))
		{
			CurrentMapName = MapName;
		}
	}
	else
	{
		MJ_LOG(LogTemp,Warning,TEXT("Can`t Travel to %s"), *MapName);
	}

	return false;
}
