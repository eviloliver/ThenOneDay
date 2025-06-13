// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/MJDungeonGameState.h"

#include "MJGameInstanceTG.h"
#include "ProjectMJ.h"
#include "Kismet/GameplayStatics.h"


AMJDungeonGameState::AMJDungeonGameState()
{
	DummyPos = FVector(0.0f,0.0f, 0.0f);
}

void AMJDungeonGameState::BeginPlay()
{
	Super::BeginPlay();


	MJ_LOG(LogTG, Warning, TEXT(" "));
	
}

void AMJDungeonGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	MJ_LOG(LogTG, Warning, TEXT(" "));

	if (UGameplayStatics::GetCurrentLevelName(this,true) == "Dungeon_Chunk_Battle01")
	{
		SetDummyPos(GetGameInstance<UMJGameInstanceTG>()->GetSavedDummyPos());
		
		MJ_LOG(LogTG, Warning, TEXT("DUNGEON  !!!!"));
		MJ_LOG(LogTG,Warning,TEXT("Dummy Pos : %f %f %f "), DummyPos.X,DummyPos.Y,DummyPos.Z);
	}
	else
	{
		MJ_LOG(LogTG, Warning, TEXT("This level is not a dungeon! "));
	}
		
	
}

void AMJDungeonGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	MJ_LOG(LogTG,Warning,TEXT("Dummy Pos : %f %f %f "), DummyPos.X,DummyPos.Y,DummyPos.Z);

	if (UGameplayStatics::GetCurrentLevelName(this,true) == "Dungeon_Chunk_Battle01")
	{
		GetGameInstance<UMJGameInstanceTG>()->SetSavedDummyPos(DummyPos);
	
		MJ_LOG(LogTG, Warning, TEXT("DUNGEON END  !!!!"));
		MJ_LOG(LogTG,Warning,TEXT("Dummy Pos : %f %f %f "), DummyPos.X,DummyPos.Y,DummyPos.Z);
	}
	
	
	
}

FVector AMJDungeonGameState::GetDummyPos()
{
	return DummyPos;
}

void AMJDungeonGameState::SetDummyPos(FVector Input)
{
	DummyPos = Input;
	
	MJ_LOG(LogTG,Warning,TEXT("Dummy Pos : %f %f %f "), DummyPos.X,DummyPos.Y,DummyPos.Z);
}
