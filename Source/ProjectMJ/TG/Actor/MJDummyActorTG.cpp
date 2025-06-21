// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/MJDummyActorTG.h"
#include "MJGameStateDungeonTG.h"
#include "ProjectMJ.h"
#include "Kismet/GameplayStatics.h"

AMJDummyActorTG::AMJDummyActorTG()
{
 	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	SetActorLocation(FVector(970.f, 250.f, -450.f));
}

void AMJDummyActorTG::BeginPlay()
{
	Super::BeginPlay();

	MJ_LOG(LogTG, Warning, TEXT(" "));
	
	ApplySavedPosition();
	
}

void AMJDummyActorTG::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MJ_LOG(LogTG, Warning, TEXT(" "));

}

void AMJDummyActorTG::ApplySavedPosition()
{
	if (AMJGameStateDungeonTG* GS = Cast<AMJGameStateDungeonTG>(UGameplayStatics::GetGameState(this)))
	{
		FVector SavedPos = GS->GetDummyPos();

		// 기본값: 저장된 DummyPos가 0,0,0이라면, 초기 위치로 복원
		if (SavedPos.IsNearlyZero()) // 또는 SavedPos == FVector::ZeroVector
		{
			SavedPos = FVector(970.f, 250.f, -450.f);
		}

		SetActorLocation(SavedPos);

		MJ_LOG(LogTemp, Warning, TEXT("Applied DummyPos: %s"), *SavedPos.ToString());
	}
}

void AMJDummyActorTG::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AMJGameStateDungeonTG* GS = Cast<AMJGameStateDungeonTG>(UGameplayStatics::GetGameState(this));
	if (GS)
	{
		GS->SetDummyPos(GetActorLocation());
	}
	
}
