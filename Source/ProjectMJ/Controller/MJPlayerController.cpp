// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MJPlayerController.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "Component/Input/MJInputComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MJGamePlayTags.h"
#include "UI/Dialogue/MJDialogueComponent.h"
#include "Components/SphereComponent.h"
#include "UI/Dialogue/MJDialogueWidget.h"
#include "ProjectMJ.h"
#include "Character/MJPlayerCharacter.h"



AMJPlayerController::AMJPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	bIsTouch=false;
	DialogueSpeed = 0.08f;
}

void AMJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn());
	if (MJChar)
	{
		MJChar->GetDialogueTrigger()->OnComponentBeginOverlap.AddDynamic(this,&AMJPlayerController::OnTriggeredDialogueIn);
		MJChar->GetDialogueTrigger()->OnComponentEndOverlap.AddDynamic(this,&AMJPlayerController::OnTriggeredDialogueOut);
	}
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

	//Dialogue Input
	ProjectMJInputComponent->BindAction(BeginDialogueAction, ETriggerEvent::Triggered, this, &ThisClass::BeginDialogue);
	ProjectMJInputComponent->BindAction(NextDialogueAction, ETriggerEvent::Triggered, this, &ThisClass::OnNextDialogue);
	
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

void AMJPlayerController::OnDialogueStateChanged()
{
	MJ_LOG(LogTG,Log,TEXT("www"));
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (bIsDialogueActive) 
		{
			Subsystem->AddMappingContext(InputConfigDataAsset->DialogueMappingContext, 0);
			Subsystem->RemoveMappingContext(InputConfigDataAsset->DefaultMappingContext);
		}
		else
		{
			Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
			Subsystem->RemoveMappingContext(InputConfigDataAsset->DialogueMappingContext);
		}
	}
}

void AMJPlayerController::BeginDialogue()
{
	if (DialogueWidget && DialogueWidget->IsInViewport()) return; 

	if (IsTriggered)
	{
		bIsDialogueActive = true;
        OnDialogueStateChanged();
        
        AMJPlayerCharacter* MyChar = Cast<AMJPlayerCharacter>(GetPawn());
        if (!MyChar) return;
        AActor* DialogueTarget = MyChar->GetDialogueTarget();
        if (!DialogueTarget) return;
        UMJDialogueComponent* DialogueComp = DialogueTarget->GetComponentByClass<UMJDialogueComponent>();
        if (!DialogueComp) return;
        
        DialogueComp->StartDialogue();
        
        UE_LOG(LogTemp, Warning, TEXT("DialogueWidgetClass ptr: %s"), *GetNameSafe(DialogueWidgetClass));
        
        DialogueWidget = CreateWidget<UMJDialogueWidget>(GetWorld(), DialogueWidgetClass);
        if (!DialogueWidget) return;
        DialogueWidget->AddToViewport();
        
        if (const FMJDialogueRow* Row = DialogueComp->GetCurrentRow())
        {
        	DialogueWidget->ShowDialogue(*Row);
        	DialogueWidget->StartTyping(Row->Text, DialogueSpeed);
        }
	}
}

void AMJPlayerController::EndDialog()
{	
	bIsDialogueActive = false;
	OnDialogueStateChanged();

	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
		DialogueWidget = nullptr;
	}
}

void AMJPlayerController::OnNextDialogue()
{
	if (IsTriggered)
	{
		AMJPlayerCharacter* MyChar = Cast<AMJPlayerCharacter>(GetPawn());
        if (!MyChar)
        	return;
        AActor* DialogueTarget = MyChar->GetDialogueTarget();
        if (!DialogueTarget)
        	return;
        UMJDialogueComponent* DialogueComp = DialogueTarget->GetComponentByClass<UMJDialogueComponent>();
        if (!DialogueComp)
        	return;
		
        if (!DialogueComp || !DialogueWidget) return;
        
        DialogueComp->NextDialogue();
		
        if (DialogueComp->IsDialogueEnd())
        {
        	EndDialog();
        }
        else if (const FMJDialogueRow* Row = DialogueComp->GetCurrentRow())
        {
        	DialogueWidget->ShowDialogue(*Row);
        	DialogueWidget->StartTyping(Row->Text, DialogueSpeed);
        }
	}
}

void AMJPlayerController::OnTriggeredDialogueIn(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IsTriggered = true;
	
	UE_LOG(LogTemp, Log, TEXT("OnTriggerBegin"));
	AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn());
	if ( Other && Other->FindComponentByClass<UMJDialogueComponent>())
	{
		MJChar->SetDialogueTarget(Other);
	}
}

void AMJPlayerController::OnTriggeredDialogueOut(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	IsTriggered = false;

	AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn());
	if (MJChar->GetDialogueTarget()== Other)
	{
		MJChar->SetDialogueTarget(nullptr);	
	}
}
