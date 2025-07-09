// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MJGameModeBase.h"

#include "ProjectMJ.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MJPlayerState.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/GameState/MJGameStateDungeonTG.h"

AMJGameModeBase::AMJGameModeBase()
{
	MJ_LOG(LogTG,Warning,TEXT("Ptr : %p"),this);

}

bool AMJGameModeBase::TravelToMap(const FString MapName)
{
	bool bAbsolute = false;
	if (CanServerTravel(MapName, bAbsolute))
	{
		GetWorld()->ServerTravel(MapName, bAbsolute);
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
		AMJPlayerState* PS = Cast<AMJPlayerState>(UGameplayStatics::GetPlayerState(this,0));
		if (PS)
		{
			PS->GetPlayerSessionDataRef().CurrentDungeonMapNum = NodeNum;
			PS->SaveToInstancedPlayerSessionData();
		}
		MJGI->bIsPlayerStateDirty = true;
		
	}

	if (TravelToMap(MapName))
	{
		return true;
	}

	return false;
}
