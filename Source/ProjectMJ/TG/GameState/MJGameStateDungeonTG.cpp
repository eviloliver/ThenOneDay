// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameStateDungeonTG.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MJPlayerState.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/Actor/MJDummyActorTG.h"


AMJGameStateDungeonTG::AMJGameStateDungeonTG()
{
	CurrentDungeonSessionData = FMJDungeonSessionData();
	CurrentDungeonNodeNum = 255;
}

void AMJGameStateDungeonTG::BeginPlay()
{
	Super::BeginPlay();
}

void AMJGameStateDungeonTG::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	UMJGameInstanceTG* MJGI = GetGameInstance<UMJGameInstanceTG>();

	if (MJGI)
	{
		AMJPlayerState* MJPS = Cast<AMJPlayerState>(UGameplayStatics::GetPlayerState(this,0));

		if (MJPS)
		{
			CurrentDungeonNodeNum = MJPS->GetPlayerSessionData().CurrentDungeonMapNum;
		}
		
		SetDungeonSessionData(MJGI->GetDungeonSessionDataRef()[CurrentDungeonNodeNum]);

		for (auto iter : CurrentDungeonSessionData.SpawnInfos)
		{
			if (iter.ActorClass->ImplementsInterface(UMJInstancedActorInterface::StaticClass()))
			{
				FActorSpawnParameters Params;
				GetWorld()->SpawnActor<AActor>(iter.ActorClass.Get(),iter.Transform,Params);	
			}
		}
	}
}

void AMJGameStateDungeonTG::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMJGameStateDungeonTG::SetDungeonSessionData(FMJDungeonSessionData& DungeonSessionData)
{
	CurrentDungeonSessionData = DungeonSessionData;
}

void AMJGameStateDungeonTG::SaveDungeonSessionDataToGameInstance()
{
	UMJGameInstanceTG* MJGI = GetGameInstance<UMJGameInstanceTG>();

	if (MJGI)
	{
		for (TActorIterator<AActor> Iter(GetWorld()); Iter ; ++Iter)
		{
			if (Iter->Implements<UMJInstancedActorInterface>())
			{
				
				AActor* Actor = *Iter;
				FMJDungeonActorInfo Info;
				Info.ActorClass = Actor->GetClass();
				Info.Transform = Actor->GetActorTransform();
				CurrentDungeonSessionData.SpawnInfos.Add(Info);	
			}
		}
		
		MJGI->GetDungeonSessionDataRef()[CurrentDungeonNodeNum] = CurrentDungeonSessionData;
	} 
}