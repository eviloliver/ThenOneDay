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
#include "TG/SubSystem/MJDungeonGenerationSubSystem.h"


AMJGameStateDungeonTG::AMJGameStateDungeonTG()
{
	LoadedDungeonSessionData = FMJDungeonSessionData();
	LoadedDungeonNodeNum = 255;
	
	CurrentWaveNum = 1;
	SpawnAIMaxNum = 5;
	CurrentSpawnedAINum = 0;
}

void AMJGameStateDungeonTG::BeginPlay()
{
	Super::BeginPlay();

	UMJDungeonGenerationSubSystem* GS = GetGameInstance()->GetSubsystem<UMJDungeonGenerationSubSystem>();
	check(GS);
	if (GS)
	{
		EMJNodeType CurrentNodeType = GS->GetDungeonGraph().Nodes[LoadedDungeonSessionData.DungeonNodeNum].NodeType;

		switch (CurrentNodeType)
		{
			case EMJNodeType::Battle:
				Initialize_BattleNode();		
				break;
			
			case EMJNodeType::Boss:
				Initialize_BossNode();
				break;
			
			case EMJNodeType::Reward:
				Initialize_RewardNode();
				break;
		}
	}
}

void AMJGameStateDungeonTG::Initialize_BattleNode()
{
	if (LoadedDungeonSessionData.DungeonContext == EMJDungeonContext::InActive)
	{
		if (LoadedDungeonSessionData.AISpawnType == EMJAISpawnType::Static)
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(),AMJDungeonAISpawnPointActor::StaticClass(),StaticSpawnPointActors);
			
			for (auto& Iter : StaticSpawnPointActors)
			{
				FVector IterSpawnPoint = Iter->GetActorLocation();
	
				FNavLocation ResultLocation;
	
				UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	
				if (NavSys)
				{
					// hard coded for now
					for (int i = 0 ; i < 10 ; ++i)
					{
						bool bIsFound = NavSys->GetRandomPointInNavigableRadius(IterSpawnPoint, 1000.f,ResultLocation);
						if (bIsFound)
						{
							FActorSpawnParameters Params;
							AActor* NewAIActor = GetWorld()->SpawnActor<AMJDummyActorTG>(DummyActorBPClass,ResultLocation,FRotator(),Params);
							if (NewAIActor)
							{
								
								NewAIActor->OnDestroyed.AddDynamic(this, &AMJGameStateDungeonTG::OnAIDestroy);
								SpawnedActorRefs.Add(NewAIActor);
								++CurrentSpawnedAINum;
							}
						}
					}
				}
				//GetWorldTimerManager().SetTimer(StaticAIEndCheckTimerHandle, this, &AMJGameStateDungeonTG::CheckSpawnAICondition,  2.0f, true);
			}
		}
		else if (LoadedDungeonSessionData.AISpawnType == EMJAISpawnType::Wave)
		{
			GetWorldTimerManager().SetTimer(WaveAISpawn_ConditionCheckTimerHandle, this, &AMJGameStateDungeonTG::CheckSpawnAICondition,  2.0f, true);

			if (LoadedWaveDataTable)
			{
				GetWaveDataRowByIndex(CurrentWaveNum);
			}
		}

		LoadedDungeonSessionData.DungeonContext = EMJDungeonContext::Activated;
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, FString::Printf(TEXT("AISpawnType is %s"), *FDungeonNode::AISpawnTypeToString(LoadedDungeonSessionData.AISpawnType)));
		
}

void AMJGameStateDungeonTG::Initialize_BossNode()
{
	
}

void AMJGameStateDungeonTG::Initialize_RewardNode()
{
	
}

bool AMJGameStateDungeonTG::GetWaveDataRowByIndex(int32 InputWaveRowNum)
{
	// Hard coded wave name for now
	FName Name = *FString::Printf(TEXT("Wave%d"), InputWaveRowNum);
	FMJWaveDataRow* RowPtr = LoadedWaveDataTable->FindRow<FMJWaveDataRow>(Name, TEXT("FindRow is Failed"));
	
	if (RowPtr)
	{
		LoadedWaveDataRow.EnemyCount = RowPtr->EnemyCount;
		LoadedWaveDataRow.EnemyPool = RowPtr->EnemyPool;
		LoadedWaveDataRow.WaveNum = RowPtr->WaveNum;

		return true;
	}
	return false;
}



void AMJGameStateDungeonTG::CheckSpawnAICondition()
{
	if (LoadedDungeonSessionData.DungeonContext != EMJDungeonContext::Activated)
	{
		return;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, FString::Printf(TEXT("Check AISpawn Coniditon Call")));
	
	if (CurrentSpawnedAINum < SpawnAIMaxNum)
	{
		if (LoadedWaveDataRow.EnemyCount <= 0)
		{
			bool GetNextWave = GetWaveDataRowByIndex(++CurrentWaveNum);
			
			if (!GetNextWave)
			{
				GetWorldTimerManager().ClearTimer(WaveAISpawn_ConditionCheckTimerHandle);
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, FString::Printf(TEXT("Wave is end. Set Dungeon Context to Cleared")));

				LoadedDungeonSessionData.DungeonContext = EMJDungeonContext::Cleared;
				//GetWorldTimerManager().SetTimer(WaveAISpawn_ConditionCheckTimerHandle, this, &AMJGameStateDungeonTG::CheckSpawnAICondition,  2.0f, true);
				
			}
		}
		else
		{
			SpawnAI();
		}
	}
}

void AMJGameStateDungeonTG::SpawnAI()
{
	if (LoadedDungeonSessionData.DungeonContext != EMJDungeonContext::Activated)
	{
		return;
	}
	
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this,0);

	if (Player)
	{
		FEnvQueryRequest Request(EQSQuery_WaveRandomSpawn, Player);

		// Async Call Lamda func
		Request.Execute(EEnvQueryRunMode::AllMatching, FQueryFinishedSignature::CreateLambda([this, Player](TSharedPtr<FEnvQueryResult> Result)
				   {
					   if (Result->IsSuccessful())
					   {
							   TArray<FVector> AllLocations;

							   AllLocations.Reserve(Result->Items.Num());
	
							   Result->GetAllAsLocations(AllLocations);

							   int i = 0;
							   while (CurrentSpawnedAINum < SpawnAIMaxNum)
							   {

								   AActor* NewAIActor = GetWorld()->SpawnActor<AActor>(GetActorFromPool(), AllLocations[i],FRotator());
								   if (NewAIActor)
								   {
									   // Add Delegate when it`s spawned by GameState
									   NewAIActor->OnDestroyed.AddDynamic(this, &AMJGameStateDungeonTG::OnAIDestroy);
									   SpawnedActorRefs.Add(NewAIActor);
									   ++CurrentSpawnedAINum;
									   --LoadedWaveDataRow.EnemyCount;
									   ++i;
								   }
								   else
								   {
									   GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("AISpawn Failed!!")));
								   }
							   }
					   }
				   }));
	}
}

void AMJGameStateDungeonTG::OnAIDestroy(AActor* DestroyedActor)
{
	if (DestroyedActor->IsPendingKillPending())
	{
		--CurrentSpawnedAINum;

		if (LoadedDungeonSessionData.AISpawnType == EMJAISpawnType::Static &&
			LoadedDungeonSessionData.DungeonContext == EMJDungeonContext::Activated &&
			CurrentSpawnedAINum <= 0)
		{
			LoadedDungeonSessionData.DungeonContext = EMJDungeonContext::Cleared;
			
			GetWorldTimerManager().SetTimer(EndPortalSpawnTimerHandle, this, &AMJGameStateDungeonTG::SpawnEndPortal, 2.0f, false);
		}
		else if (LoadedDungeonSessionData.AISpawnType == EMJAISpawnType::Wave &&
			LoadedDungeonSessionData.DungeonContext == EMJDungeonContext::Activated &&
			CurrentSpawnedAINum <= 0
			)
		{
			
				//LoadedDungeonSessionData.DungeonContext = EMJDungeonContext::Cleared;
				GetWorldTimerManager().SetTimer(EndPortalSpawnTimerHandle, this, &AMJGameStateDungeonTG::SpawnEndPortal, 2.0f, false);
			
		}
	}
}

TSubclassOf<AActor> AMJGameStateDungeonTG::GetActorFromPool()
{
	// pick Actor class randomly
	TArray<TSubclassOf<AActor>> Keys;
	LoadedWaveDataRow.EnemyPool.GetKeys(Keys);

	if (Keys.Num() == 0)
	{
		return nullptr;
	}
	
	const int32 RandomIndex = FMath::RandRange(0,Keys.Num() - 1);
	
	return Keys[RandomIndex];
}

void AMJGameStateDungeonTG::SpawnEndPortal()
{
	if (LoadedDungeonSessionData.DungeonContext != EMJDungeonContext::Cleared)
	{
		return;
	}

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this,0);
	if (Player)
	{
		FEnvQueryRequest Request(EQSQuery_WaveRandomSpawn, Player);

		Request.Execute(EEnvQueryRunMode::AllMatching, FQueryFinishedSignature::CreateLambda([this, Player](TSharedPtr<FEnvQueryResult> Result)
		{
			if (Result->IsSuccessful())
			{
				FVector Location;
				
				Location = Result->GetItemAsLocation(0);

				FActorSpawnParameters Params;
				AActor* Portal = GetWorld()->SpawnActor<AActor>(PortalActor,Location,FRotator(),Params);
				if (Portal)
				{
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, FString::Printf(TEXT("PortalActor is Successfully Spawned")));

				}
			}
		}));
		
	}
}

void AMJGameStateDungeonTG::SetDungeonSessionData(FMJDungeonSessionData& DungeonSessionData)
{
	LoadedDungeonSessionData = DungeonSessionData;
}

void AMJGameStateDungeonTG::SaveToInstancedDungeonSessionData(uint8 SaveToNum)
{
	UMJGameInstanceTG* MJGI = GetGameInstance<UMJGameInstanceTG>();

	FMJDungeonSessionData NewDungeonSessionData = LoadedDungeonSessionData;

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
					NewDungeonSessionData.SpawnInfos.Add(Info);	
			}
		}
		
		MJGI->GetDungeonSessionDataRef()[SaveToNum] = NewDungeonSessionData;
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
