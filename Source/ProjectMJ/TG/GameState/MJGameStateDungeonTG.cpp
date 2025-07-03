// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameStateDungeonTG.h"

#include "EngineUtils.h"
#include "NavigationSystem.h"
#include "Character/MJPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/Actor/MJDummyActorTG.h"
#include "TG/Actor/MJDungeonAISpawnPointActor.h"


AMJGameStateDungeonTG::AMJGameStateDungeonTG()
{
	LoadedDungeonSessionData = FMJDungeonSessionData();
	LoadedDungeonNodeNum = 255;

	static ConstructorHelpers::FClassFinder<AMJDummyActorTG> Actor(TEXT("/Game/TG/Actor/BP_DummyActor_TG.BP_DummyActor_TG_C"));
	if (Actor.Succeeded())
	{
		DummyActorBPClass = Actor.Class;
	}
}

void AMJGameStateDungeonTG::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
	
}

void AMJGameStateDungeonTG::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, FString::Printf(TEXT("AISpawnType is %s"), *FDungeonNode::AISpawnTypeToString(LoadedDungeonSessionData.AISpawnType)));

	// Case Static

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AMJDungeonAISpawnPointActor::StaticClass(),StaticSpawnPointActors);
	
	for (auto& Iter : StaticSpawnPointActors)
	{
		FVector IterSpawnPoint = Iter->GetActorLocation();

		FNavLocation ResultLocation;

		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

		if (NavSys)
		{
			for (int i = 0 ; i < 10 ; ++i)
			{
				bool bIsFound = NavSys->GetRandomPointInNavigableRadius(IterSpawnPoint, 1000.f,ResultLocation);
				if (bIsFound)
				{
					FActorSpawnParameters Params;
					GetWorld()->SpawnActor<AMJDummyActorTG>(DummyActorBPClass,ResultLocation,FRotator(),Params);
				}
			}
		}
		
	}

	// Case Wave

	
	
	
	
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

void AMJGameStateDungeonTG::PublishOnBossHealthChanged(float Delta)
{
	
	OnAIBossHealthChanged.Broadcast(Delta);
}

void AMJGameStateDungeonTG::PublishOnBossSpawned(float Health)
{
	OnAIBossSpawned.Broadcast(Health);
}
