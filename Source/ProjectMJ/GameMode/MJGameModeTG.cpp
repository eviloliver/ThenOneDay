// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MJGameModeTG.h"

#include "ProjectMJ.h"
#include "Internationalization/StringTableRegistry.h"

AMJGameModeTG::AMJGameModeTG()
{
	CurrentMapName = FText::FromStringTable(FName("TG_MapNames"),TEXT("Town")).ToString();
}

bool AMJGameModeTG::TravelToMap(const FString MapName)
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
		UE_LOG(LogTemp,Warning,TEXT("Can`t Travel to %s"), *MapName);
	}

	return false;
}

