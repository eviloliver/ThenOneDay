// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Weapon/MJWeaponBase.h"
#include "Components/BoxComponent.h"
// Sets default values
AMJWeaponBase::AMJWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetupAttachment(GetRootComponent());
	WeaponCollision->InitBoxExtent(FVector(20.0f));
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


