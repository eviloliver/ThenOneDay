// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MJPlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "DataAsset/DataAsset_StartDataBase.h"
#include "Component/MJPlayerCombatComponent.h"
#include "Component/MJPlayerSkillComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "UI/Inventory/MJInventoryComponent.h"
#include "Component/MJFadeObjectComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"

class UMJSaveGameSubsystem;

AMJPlayerCharacter::AMJPlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 800.0f;
	//CameraBoom->SocketOffset = FVector(0.0f, 55.0f, 65.0);
	CameraBoom->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bDoCollisionTest = false;

	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0;

	PlayerCombatComponent = CreateDefaultSubobject<UMJPlayerCombatComponent>(TEXT("PlayerCombatComponent"));

	//Add FadeComponent
	//FadeComponent = CreateDefaultSubobject<UMJFadeObjectComponent>(TEXT("FadeComponent"));
	// Minjin: AI Perception-캐릭터를 StimuliSource로 등록(AI가 감지)
	
	PerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));
	if (nullptr!= PerceptionStimuliSourceComponent)
	{
		// Sight, Damage, Hearing source 등록(명시적으로 나타내기 위함)
		PerceptionStimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());
		PerceptionStimuliSourceComponent->RegisterForSense(UAISense_Damage::StaticClass());
		PerceptionStimuliSourceComponent->RegisterForSense(UAISense_Hearing::StaticClass());
		
		// RegisterWithPerceptionSystem(): bAutoRegisterAsSource == true 해줌
		PerceptionStimuliSourceComponent->RegisterWithPerceptionSystem();
	}

	DialogueTarget = nullptr;

	DialogueTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("DialogueTrigger"));
	DialogueTrigger->SetupAttachment(RootComponent);
	DialogueTrigger->InitSphereRadius(120.f);
	DialogueTrigger->SetCollisionProfileName(TEXT("Trigger"));
	DialogueTrigger->SetGenerateOverlapEvents(true);
	DialogueTrigger->SetHiddenInGame(false);

	InventoryComponent = CreateDefaultSubobject<UMJInventoryComponent>(TEXT("InventoryComponent"));
	// Skill Component
	SkillComponent = CreateDefaultSubobject<UMJPlayerSkillComponent>(TEXT("SkillComponent"));
}

void AMJPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMJPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!CharacterStartData.IsNull())
	{
		if (UDataAsset_StartDataBase* LoadData = CharacterStartData.LoadSynchronous())
		{
			LoadData->GiveToAbilitySystemComponent(Cast<UMJAbilitySystemComponent>(GetAbilitySystemComponent()));
		}
	}
	// 로딩 데이터 있을 시 받아와서 AttributeSet에 적용
	// 없을 시엔 무시하고 기본 AttributeSet 으로 진행됩니다.


	
	// UMJGameInstanceTG* MJGI = Cast<UMJGameInstanceTG>(GetWorld()->GetGameInstance());
	//
	// if (MJGI)
	// {
	// 	UMJSaveGameSubsystem* MJSaveGameSubsystem = MJGI->GetSubsystem<UMJSaveGameSubsystem>();
	// 	if (MJSaveGameSubsystem)
	// 	{
	// 		MJSaveGameSubsystem->LoadSaveGame(this);
	// 	}
	// 	MJ_LOG(LogTG, Log, TEXT("player loaded health : %f"),  GetAbilitySystemComponent()->GetNumericAttribute(UMJCharacterAttributeSet::GetHealthAttribute()));
	// }
	
}

void AMJPlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	// if (UMJGameInstanceTG* MJGI = Cast<UMJGameInstanceTG>(GetGameInstance()))
	// {
	// 	UMJSaveGameSubsystem* MJSaveGameSubsystem = MJGI->GetSubsystem<UMJSaveGameSubsystem>();
	// 	if (MJSaveGameSubsystem)
	// 	{
	// 		MJSaveGameSubsystem->SaveGameToSlot(this);
	// 	}
	// 	MJ_LOG(LogTG,Log, TEXT("Character Attribute Saved"));
	// }

}