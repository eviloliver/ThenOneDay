// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Actor/MJProjectileBase.h"

// Sets default values
AMJProjectileBase::AMJProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMJProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}