// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MJPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemComponent.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "Component/Input/MJInputComponent.h"
#include "Character/MJPlayerCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "MJGamePlayTags.h"

AMJPlayerController::AMJPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	bIsTouch=false;
}

void AMJPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	}
	UMJInputComponent* ProjectMJInputComponent = CastChecked< UMJInputComponent>(InputComponent);

	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, MJGameplayTags::Input_SetDestination_Click, ETriggerEvent::Started, this, &ThisClass::OnInputStarted);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, MJGameplayTags::Input_SetDestination_Click, ETriggerEvent::Triggered, this, &ThisClass::OnSetDestinationTriggered);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, MJGameplayTags::Input_SetDestination_Click, ETriggerEvent::Completed, this, &ThisClass::OnSetDestinationReleased);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, MJGameplayTags::Input_SetDestination_Click, ETriggerEvent::Canceled, this, &ThisClass::OnSetDestinationReleased);

	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, MJGameplayTags::Input_SetDestination_Touch, ETriggerEvent::Started, this, &ThisClass::OnInputStarted);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, MJGameplayTags::Input_SetDestination_Touch, ETriggerEvent::Triggered, this, &ThisClass::OnTouchTriggered);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, MJGameplayTags::Input_SetDestination_Touch, ETriggerEvent::Completed, this, &ThisClass::OnTouchReleased);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, MJGameplayTags::Input_SetDestination_Touch, ETriggerEvent::Canceled, this, &ThisClass::OnTouchReleased);

	ProjectMJInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AMJPlayerController::Input_AbilityInputPressed, &AMJPlayerController::Input_AbilityInputReleased);
}

void AMJPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (bIsTouch)
	{
		MoveToMouseCurser();
	}
}

void AMJPlayerController::OnInputStarted()
{
	StopMovement();
}

void AMJPlayerController::OnSetDestinationTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AMJPlayerController::OnSetDestinationReleased()
{
	FollowTime = 0.f;
}

void AMJPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
}

void AMJPlayerController::OnTouchReleased()
{
	bIsTouch = false;
}

void AMJPlayerController::SetNewDestination(const FVector DestLocation)
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		float const Distance = FVector::Dist(DestLocation, ControlledPawn->GetActorLocation());

		if (Distance > 30.0f)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AMJPlayerController::MoveToMouseCurser()
{
	FHitResult Hit;

	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (Hit.bBlockingHit)
	{
		SetNewDestination(Hit.ImpactPoint);
	}
}

void AMJPlayerController::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	AMJPlayerCharacter* ControlledPawn = Cast<AMJPlayerCharacter>(GetPawn());
	if (ControlledPawn)
	{
		if (UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(ControlledPawn->GetAbilitySystemComponent()))
		{
			MJASC->OnAbilityInputPressed(InInputTag);
		}
	}
	
}

void AMJPlayerController::Input_AbilityInputReleased(FGameplayTag InInputTag)
{

}
