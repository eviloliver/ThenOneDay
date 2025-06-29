// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameStateDungeonTG.h"

#include "EngineUtils.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/Actor/MJDummyActorTG.h"


AMJGameStateDungeonTG::AMJGameStateDungeonTG()
{
	LoadedDungeonSessionData = FMJDungeonSessionData();
	LoadedDungeonNodeNum = 255;
}

void AMJGameStateDungeonTG::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

void AMJGameStateDungeonTG::BeginPlay()
{
	Super::BeginPlay();
}

void AMJGameStateDungeonTG::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMJGameStateDungeonTG::SetDungeonSessionData(FMJDungeonSessionData& DungeonSessionData)
{
	LoadedDungeonSessionData = DungeonSessionData;
}

void AMJGameStateDungeonTG::SaveToInstancedDungeonSessionData(uint8 SaveToNum)
{
	UMJGameInstanceTG* MJGI = GetGameInstance<UMJGameInstanceTG>();

	FMJDungeonSessionData NewDungeonSessionData;
	if (MJGI && !MJGI->bIsDungeonGameStateDirty) 
	{
		for (TActorIterator<AActor> Iter(GetWorld()); Iter ; ++Iter)
		{
			if (Iter->Implements<UMJInstancedActorInterface>())
			{

					AActor* Actor = *Iter;
					FMJDungeonActorInfo Info;
					Info.ActorClass = Actor->GetClass();
					Info.Transform = Actor->GetActorTransform();
					NewDungeonSessionData.SpawnInfos.Add(Info);	
				
			}
		}
		


		MJGI->GetDungeonSessionDataRef()[SaveToNum] = NewDungeonSessionData;
		MJGI->bIsDungeonGameStateDirty = true;
	} 
}

void AMJGameStateDungeonTG::LoadFromInstancedDungeonSessionData(uint8 LoadFromNum)
{
	UMJGameInstanceTG* MJGI = GetGameInstance<UMJGameInstanceTG>();

	if (MJGI)
	{
		
		SetDungeonSessionData(MJGI->GetDungeonSessionDataRef()[LoadFromNum]);

		for (auto iter : LoadedDungeonSessionData.SpawnInfos)
		{
			if (iter.ActorClass->ImplementsInterface(UMJInstancedActorInterface::StaticClass()))
			{
				iter.ActorClass.LoadSynchronous();
				UClass* LoadedClass = iter.ActorClass.Get();
				FActorSpawnParameters Params;
				GetWorld()->SpawnActor<AActor>(LoadedClass,iter.Transform,Params);	
			}
		}
	}
}

void AMJGameStateDungeonTG::PublishOnBossHealthChanged(float Delta, float OldHealth, float NewHealth)
{
	
	OnAIBossHealthChanged.Broadcast(Delta, OldHealth, NewHealth);
}

void AMJGameStateDungeonTG::PublishOnBossSpawned(float Health)
{
	OnAIBossSpawned.Broadcast(Health);
}
