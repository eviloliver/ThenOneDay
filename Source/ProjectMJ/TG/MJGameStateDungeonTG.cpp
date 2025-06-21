// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/MJGameStateDungeonTG.h"

#include "MJGameInstanceTG.h"
#include "ProjectMJ.h"
#include "Kismet/GameplayStatics.h"


AMJGameStateDungeonTG::AMJGameStateDungeonTG()
{
	DummyPos = FVector(0.0f,0.0f, 0.0f);
	CurrentNodeNum = -1;
}

void AMJGameStateDungeonTG::BeginPlay()
{
	Super::BeginPlay();


	MJ_LOG(LogTG, Warning, TEXT(" "));
	
}

void AMJGameStateDungeonTG::PostInitializeComponents()
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

	UMJGameInstanceTG* MJGI = GetGameInstance<UMJGameInstanceTG>();

	if (MJGI)
	{
		CurrentNodeNum = MJGI->GetSavedMapNodeNum();
		//GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,FString::Printf(TEXT("Your CurrentMapNodeNum == %d"),CurrentNodeNum));
	}
}

void AMJGameStateDungeonTG::EndPlay(const EEndPlayReason::Type EndPlayReason)
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

FVector AMJGameStateDungeonTG::GetDummyPos()
{
	return DummyPos;
}

void AMJGameStateDungeonTG::SetDummyPos(FVector Input)
{
	DummyPos = Input;
	
	MJ_LOG(LogTG,Warning,TEXT("Dummy Pos : %f %f %f "), DummyPos.X,DummyPos.Y,DummyPos.Z);
}
void AMJGameStateDungeonTG::SetCurrentNodeNum(uint8 InputNodeNum)
{
	CurrentNodeNum = InputNodeNum;
}
