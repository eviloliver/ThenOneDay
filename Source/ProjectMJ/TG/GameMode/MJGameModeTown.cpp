// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameModeTown.h"

#include "ProjectMJ.h"
#include "Kismet/GameplayStatics.h"

AMJGameModeTown::AMJGameModeTown()
{
	MJ_LOG(LogTG,Log,TEXT("New GameMode Instance Created"));
}

void AMJGameModeTown::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* NewPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (NewPC)
	{
		UE_LOG(LogTemp, Warning, TEXT("PC After OpenLevel: %p"), NewPC);
	}
	
}
