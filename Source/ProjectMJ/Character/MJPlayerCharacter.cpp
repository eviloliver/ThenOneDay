// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MJPlayerCharacter.h"

#include "MJGameInstanceTG.h"
#include "MJSaveGame.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

}

void AMJPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMJPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	Cast<UMJGameInstanceTG>(GetWorld()->GetGameInstance())->LoadSaveGame();
	
	UE_LOG(LogTemp,Log,TEXT("player loaded health : %f"), 
	GetAbilitySystemComponent()->GetNumericAttribute(UMJCharacterAttributeSet::GetHealthAttribute()));
}

void AMJPlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (UMJGameInstanceTG* GI = Cast<UMJGameInstanceTG>(GetGameInstance()))
	{
		GI->SaveGameToSlot(this); // 캐릭터 자신 넘겨줌
	}

	UE_LOG(LogTemp,Log,TEXT("Character :: Saved"));
}