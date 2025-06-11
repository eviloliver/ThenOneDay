// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ProjectMJCharacterBase.h"
#include "AbilitySystem/ProjectMJAbilitySystemComponent.h"
#include "Player/ProjectMJPlayerState.h"

// Sets default values
AProjectMJCharacterBase::AProjectMJCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->bReceivesDecals = false;
	ASC = nullptr;
}

UAbilitySystemComponent* AProjectMJCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

void AProjectMJCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AProjectMJPlayerState* PS = GetPlayerState<AProjectMJPlayerState>();
	if (PS)
	{
		ASC = CastChecked<UProjectMJAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		ASC->InitAbilityActorInfo(PS, this);
	}
}



