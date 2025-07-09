// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MJCharacterBase.h"

#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "Component/MJSkillComponent.h"
#include "Components/CapsuleComponent.h"
#include "Physics/MJCollision.h"
#include "Player/MJPlayerState.h"

// Sets default values
AMJCharacterBase::AMJCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->bReceivesDecals = false;
	ASC = nullptr;
		
	SkillComponent = CreateDefaultSubobject<UMJSkillComponent>(TEXT("SkillComponent"));

	// Capsule Component Collision Profile
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_MJCAPSULE);
}

UAbilitySystemComponent* AMJCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

void AMJCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// TeamId 설정 - 적/중립/아군 구별용
	TeamId = FGenericTeamId(static_cast<uint8>(ID));
	UE_LOG(LogTemp, Log, TEXT("Selected Team Enum: %d"), TeamId.GetId());
}

void AMJCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AMJPlayerState* PS = GetPlayerState<AMJPlayerState>();
	
	if (PS)
	{
		ASC = Cast<UMJAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		if (ASC)
		{
			ASC->InitAbilityActorInfo(PS, this);
		
			MJ_LOG(LogTG, Warning,TEXT("Player Health %f"),GetAbilitySystemComponent()->GetNumericAttribute(UMJCharacterAttributeSet::GetHealthAttribute()));

		}
		/// This line continues peaking so annotated - TaeGawn - 
		//ensureMsgf(!CharacterStartData.IsNull(), TEXT("Forgot to assign start data to %s"), *GetName());
	}

}




