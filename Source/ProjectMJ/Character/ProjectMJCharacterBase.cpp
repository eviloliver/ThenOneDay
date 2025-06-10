// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ProjectMJCharacterBase.h"
#include "AbilitySystem/ProjectMJAttributeSet.h"
#include "AbilitySystem/ProjectyMJAbilitySystemComponent.h"

// Sets default values
AProjectMJCharacterBase::AProjectMJCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
	ProjectyMJAbilitySystemComponent = CreateDefaultSubobject<UProjectyMJAbilitySystemComponent>(TEXT("ProjectMJAbilitySystemComponent"));
	ProjectMJAttributeSet = CreateDefaultSubobject<UProjectMJAttributeSet>(TEXT("ProjectMJAttributeSet"));
}

UAbilitySystemComponent* AProjectMJCharacterBase::GetAbilitySystemComponent() const
{
	return GetProjectMJAbilitySystemComponent();
}

void AProjectMJCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ProjectyMJAbilitySystemComponent)
	{
		ProjectyMJAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}



