// Fill out your copyright notice in the Description page of Project Settings.


#include "MJDummyActorTG.h"

AMJDummyActorTG::AMJDummyActorTG()
{
 	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

void AMJDummyActorTG::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void AMJDummyActorTG::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}


void AMJDummyActorTG::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	
	
}
