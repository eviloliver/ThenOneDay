// Fill out your copyright notice in the Description page of Project Settings.


#include "MJTestHealthUpActorTG.h"

#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Character/MJPlayerCharacter.h"

// Sets default values
AMJTestHealthUpActorTG::AMJTestHealthUpActorTG()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
}

void AMJTestHealthUpActorTG::BeginPlay()
{
	Super::BeginPlay();

	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::UpHealth);
	
}

void AMJTestHealthUpActorTG::UpHealth(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AMJPlayerCharacter* Player = Cast<AMJPlayerCharacter>(OtherActor);
	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(Player->GetAbilitySystemComponent());

	UMJCharacterAttributeSet* MJCAS = const_cast<UMJCharacterAttributeSet*>(ASC->GetSet<UMJCharacterAttributeSet>());

	
	MJCAS->UpHealth(30);
	MJ_LOG(LogTG,Log,TEXT("AMJTestHealthUpActorTG ::UpHealth /  loaded health : %f"), MJCAS->GetHealth());

}


