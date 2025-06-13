// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameModeTG.h"

#include "MJDungeonGameState.h"
#include "MJGameInstanceTG.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/MJCharacterAttributeSet.h"
#include "Character/MJPlayerCharacter.h"
#include "Controller/MJPlayerController.h"
#include "Internationalization/StringTableCore.h"
#include "Internationalization/StringTableRegistry.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MJPlayerState.h"

AMJGameModeTG::AMJGameModeTG()
{
	CurrentMapName = TEXT("");
	MJ_LOG(LogTG,Log,TEXT("New GameMode Instance Created"));
}

void AMJGameModeTG::BeginPlay()
{
	Super::BeginPlay();
	
	//CurrentMapName = FStringTableRegistry::Get().FindStringTable(FName("TG_MapNames"))->GetSourceString()
	//우선 하드코딩 하겠습니다.
}

FString AMJGameModeTG::GetCurrentMapName()
{
	return CurrentMapName;
}


void AMJGameModeTG::HandleTownLogic()
{
}

void AMJGameModeTG::HandleeDungeonLogic()
{
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