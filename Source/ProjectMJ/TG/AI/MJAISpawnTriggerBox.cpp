// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/AI/MJAISpawnTriggerBox.h"

#include "ProjectMJ.h"
#include "EnvironmentQuery/EnvQueryManager.h"

AMJAISpawnTriggerBox::AMJAISpawnTriggerBox()
{
	
	
}

void AMJAISpawnTriggerBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

void AMJAISpawnTriggerBox::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan,TEXT("overlapped"));
	if (EQSQuery)
	{
		FEnvQueryRequest Request(EQSQuery,SpawnCenterActor);
		Request.Execute(EEnvQueryRunMode::AllMatching, this, &AMJAISpawnTriggerBox::OnQueryFininshed);
	}
}

void AMJAISpawnTriggerBox::OnQueryFininshed(TSharedPtr<FEnvQueryResult> Result)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan,TEXT("Query Executed"));

    	TArray<FVector> Locations;
    	Result->GetAllAsLocations(Locations);
    
    	for (const FVector& Loc : Locations)
    	{
    		FActorSpawnParameters SpawnParams;
    		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    		GetWorld()->SpawnActor<AActor>(SpawnTargetActor, Loc, FRotator(0.0f,90.f,0.0f), SpawnParams);
    	}

	if (Destroy())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan,TEXT("Spawner Destroyed"));
	}
	
}

