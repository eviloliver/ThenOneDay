// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/ProjectMJPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "Component/Input/ProjectMJInputComponent.h"
#include "ProjectMJGamePlayTags.h"

AProjectMJPlayerController::AProjectMJPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AProjectMJPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	}
	UProjectMJInputComponent* ProjectMJInputComponent = CastChecked< UProjectMJInputComponent>(InputComponent);

	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, ProjectMJGameplayTags::Input_SetDestination_Click, ETriggerEvent::Started, this, &ThisClass::OnInputStarted);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, ProjectMJGameplayTags::Input_SetDestination_Click, ETriggerEvent::Triggered, this, &ThisClass::OnSetDestinationTriggered);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, ProjectMJGameplayTags::Input_SetDestination_Click, ETriggerEvent::Completed, this, &ThisClass::OnSetDestinationReleased);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, ProjectMJGameplayTags::Input_SetDestination_Click, ETriggerEvent::Canceled, this, &ThisClass::OnSetDestinationReleased);

	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, ProjectMJGameplayTags::Input_SetDestination_Touch, ETriggerEvent::Started, this, &ThisClass::OnInputStarted);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, ProjectMJGameplayTags::Input_SetDestination_Touch, ETriggerEvent::Triggered, this, &ThisClass::OnTouchTriggered);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, ProjectMJGameplayTags::Input_SetDestination_Touch, ETriggerEvent::Completed, this, &ThisClass::OnTouchReleased);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, ProjectMJGameplayTags::Input_SetDestination_Touch, ETriggerEvent::Canceled, this, &ThisClass::OnTouchReleased);


}

void AProjectMJPlayerController::OnInputStarted()
{
	StopMovement();
}

void AProjectMJPlayerController::OnSetDestinationTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
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

void AProjectMJPlayerController::OnSetDestinationReleased()
{
	FollowTime = 0.f;
}

void AProjectMJPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AProjectMJPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
