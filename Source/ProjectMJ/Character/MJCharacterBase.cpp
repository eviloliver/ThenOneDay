// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MJCharacterBase.h"

#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Physics/MJCollision.h"
#include "Player/MJPlayerState.h"
#include "MotionWarpingComponent.h"
#include "Component/MJAbilityContextComponent.h"
#include "DataAsset/MJStateAbilityDataAsset.h"
#include "TG/Component/MJMiniMapIconMeshComponent.h"
#include "UI/World/MJDamageComponent.h"
#include "UI/World/MJDamageWidget.h"


// Sets default values
AMJCharacterBase::AMJCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->bReceivesDecals = false;
	ASC = nullptr;

	// Capsule Component Collision Profile
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_MJCAPSULE);

	// MotionWarpingComponent Section
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));

	// AbilityContextComponent Section
	AbilityContextComponent = CreateDefaultSubobject<UMJAbilityContextComponent>(TEXT("AbilityContextComponent"));

	// TG : MiniMapIconMeshComponent 
	MiniMapIconMeshComponent = CreateDefaultSubobject<UMJMiniMapIconMeshComponent>(TEXT("MiniMapIconMeshComponent"));
	MiniMapIconMeshComponent->SetupAttachment(GetMesh());
  
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

	/*
	 * Minjin
	 * StateAbilityDataAsset 설정 - Player는 캐릭터 BP에서, Enemy는 DataTable을 통해서
	*/
	if(StateAbilityDataAsset)
	{
		// Minjin: State Ability 부여
		FGameplayAbilitySpec AppearAbilitySpec(StateAbilityDataAsset->ActionAppearanceAbilityClass);
		ASC->GiveAbility(AppearAbilitySpec);

		FGameplayAbilitySpec DamageAbilitySpec(StateAbilityDataAsset->ActionDamageAbilityClass);
		ASC->GiveAbility(DamageAbilitySpec);

		FGameplayAbilitySpec DeathAbilitySpec(StateAbilityDataAsset->ActionDeathAbilityClass);
		ASC->GiveAbility(DeathAbilitySpec);
	}
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

void AMJCharacterBase::FloatDamage(float Magnitude, bool bIsCritical, EOwnerType type)
{
	UMJDamageComponent* NewComp = NewObject<UMJDamageComponent>(this);
	NewComp->RegisterComponent();
	NewComp->SetDamageWidget(this->GetActorLocation(), OffSet);
	NewComp->SetVisibility(true);
	DamageComponents.Add(NewComp);

	if (UMJDamageWidget* Widget =Cast<UMJDamageWidget>(NewComp->GetUserWidgetObject()) )
	{
		Widget->SetDamage(-Magnitude, bIsCritical, type);
		Widget->PlayAnim();
	}

	OffSet ++;
	if (OffSet > 5)
	{
		OffSet = 0;
	}
}




