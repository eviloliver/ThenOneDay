// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameStateDungeonTG.h"

#include "EngineUtils.h"
#include "NavigationSystem.h"
#include "Character/MJPlayerCharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/GameplayStatics.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/Actor/MJDummyActorTG.h"
#include "TG/Actor/MJDungeonAISpawnPointActor.h"


AMJGameStateDungeonTG::AMJGameStateDungeonTG()
{
	LoadedDungeonSessionData = FMJDungeonSessionData();
	LoadedDungeonNodeNum = 255;
	
	CurrentWaveNum = 1;
	SpawnAIMaxNum = 5;
	CurrSpawnedAINum = 0;

	
}

void AMJGameStateDungeonTG::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

void AMJGameStateDungeonTG::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, FString::Printf(TEXT("AISpawnType is %s"), *FDungeonNode::AISpawnTypeToString(LoadedDungeonSessionData.AISpawnType)));


	//GetWorldTimerManager().SetTimer(WaveAISpawnTimerHandle, this, &AMJGameStateDungeonTG::SpawnAI, 3.0f);

	GetWorldTimerManager().SetTimer(WaveAISpawnConditionCheckTimerHandle, this, &AMJGameStateDungeonTG::CheckSpawnAICondition,  2.0f, true);

	if (LoadedWaveDataTable)
	{
		FName Name = *FString::Printf(TEXT("Wave%d"),CurrentWaveNum);
		FMJWaveDataRow* RowPtr = LoadedWaveDataTable->FindRow<FMJWaveDataRow>(Name, TEXT(""));

		if (RowPtr)
		{
			LoadedWaveDataRow.EnemyCount = RowPtr->EnemyCount;
			LoadedWaveDataRow.EnemyPool = RowPtr->EnemyPool;
			LoadedWaveDataRow.WaveNum = RowPtr->WaveNum;
		}
		
	}
	
	// if (LoadedDungeonSessionData.AISpawnType == EAISpawnType::Static)
	// {
	// 	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AMJDungeonAISpawnPointActor::StaticClass(),StaticSpawnPointActors);
	//
	// 	for (auto& Iter : StaticSpawnPointActors)
	// 	{
	// 		FVector IterSpawnPoint = Iter->GetActorLocation();
	//
	// 		FNavLocation ResultLocation;
	//
	// 		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	//
	// 		if (NavSys)
	// 		{
	// 			for (int i = 0 ; i < 10 ; ++i)
	// 			{
	// 				bool bIsFound = NavSys->GetRandomPointInNavigableRadius(IterSpawnPoint, 1000.f,ResultLocation);
	// 				if (bIsFound)
	// 				{
	// 					FActorSpawnParameters Params;
	// 					GetWorld()->SpawnActor<AMJDummyActorTG>(DummyActorBPClass,ResultLocation,FRotator(),Params);
	// 				}
	// 			}
	// 		}
	// 	
	// 	}
	// }
	// else if (LoadedDungeonSessionData.AISpawnType == EAISpawnType::Wave)
	// {
	// 
	// }
	
	
}
void AMJGameStateDungeonTG::SpawnAI()
{
	
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this,0);
	if (Player)
	{
		FEnvQueryRequest Request(EQSQuery, Player);
		
		Request.Execute(EEnvQueryRunMode::AllMatching, FQueryFinishedSignature::CreateLambda([this, Player](TSharedPtr<FEnvQueryResult> Result)
				   {
					   if (Result->IsSuccessful())
					   {

					   		TArray<FVector> AllLocations;

						   	AllLocations.Reserve(Result->Items.Num());
	
					   		Result->GetAllAsLocations(AllLocations);

					   		int i = 0;
					   		while (CurrSpawnedAINum < SpawnAIMaxNum)
					   		{
					   			SpawnedActorRefs.Add(GetWorld()->SpawnActor<AActor>(GetActorFromPool(), AllLocations[i],FRotator()));

					   			CurrSpawnedAINum++;
					   			i++;
					   		}
					   }
				   }));
	}
}

void AMJGameStateDungeonTG::CheckSpawnAICondition()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, FString::Printf(TEXT("Check AISpawn Coniditon Call")));
	
	if (CurrSpawnedAINum < SpawnAIMaxNum)
	{
		SpawnAI();
	}
}

TSubclassOf<AActor> AMJGameStateDungeonTG::GetActorFromPool()
{
	TArray<TSubclassOf<AActor>> Keys;
	LoadedWaveDataRow.EnemyPool.GetKeys(Keys);

	if (Keys.Num() == 0)
	{
		return nullptr;
	}
	
	const int32 RandomIndex = FMath::RandRange(0,Keys.Num() - 1);
	
	return Keys[RandomIndex];
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
