// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MJCharacterBase.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "Player/MJPlayerState.h"

// Sets default values
AMJCharacterBase::AMJCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->bReceivesDecals = false;
	ASC = nullptr;
}

UAbilitySystemComponent* AMJCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

void AMJCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AMJPlayerState* PS = GetPlayerState<AMJPlayerState>();
	if (PS)
	{
		ASC = CastChecked<UMJAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		ASC->InitAbilityActorInfo(PS, this);
		
		ensureMsgf(!CharacterStartData.IsNull(), TEXT("Forgot to assign start data to %s"), *GetName());
	}
}



