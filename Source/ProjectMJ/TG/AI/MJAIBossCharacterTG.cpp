// Fill out your copyright notice in the Description page of Project Settings.


#include "TG/AI/MJAIBossCharacterTG.h"

AMJAIBossCharacterTG::AMJAIBossCharacterTG()
{

}

void AMJAIBossCharacterTG::BeginPlay()
{
	Super::BeginPlay();
	// @fixme : change based on design	
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void AMJAIBossCharacterTG::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}
