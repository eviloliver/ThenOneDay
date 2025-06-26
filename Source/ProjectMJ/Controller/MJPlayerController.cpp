// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MJPlayerController.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemComponent.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "Component/Input/MJInputComponent.h"
#include "Character/MJPlayerCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "MJGamePlayTags.h"
#include "Dialogue/MJDialogueComponent.h"
#include "Components/SphereComponent.h"
#include "UI/MJUIManagerSubsystem.h"
#include "ProjectMJ.h"
#include "Character/MJPlayerCharacter.h"
#include "Compression/lz4.h"


AMJPlayerController::AMJPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	bIsTouch=false;
}

void AMJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UIManager =	GetGameInstance()->GetSubsystem<UMJUIManagerSubsystem>();
	ensure(UIManager);
	// 언리얼 엔진의 초기화 순서 : GameInstance > GameMode > Actor
	// 그러므로 GetSubsystem 시 nullptr 을 반환할 일은 없지만, !
	// 혹시 모를 상황(모듈 누락, 이상한 호출 타이밍, 비동기 로직 중 접근 등)에 대비하여 ensure() 또는 UE_LOG 찍기
	
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

	ProjectMJInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AMJPlayerController::Input_AbilityInputPressed, &AMJPlayerController::Input_AbilityInputReleased);
	
	//Dialogue Input
	ProjectMJInputComponent->BindAction(ChangeIMCAction, ETriggerEvent::Triggered, this, &ThisClass::ChangeToIMCDialogue);
	ProjectMJInputComponent->BindAction(NextDialogueAction, ETriggerEvent::Triggered, this, &ThisClass::ProceedDialogue);
	ProjectMJInputComponent->BindAction(ShowBacklogAction, ETriggerEvent::Triggered, this, &ThisClass::ShowBacklog);
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

void AMJPlayerController::ChangeToIMCDialogue()
{
	if (IsTriggered)
	{
		AMJPlayerCharacter* MyChar = Cast<AMJPlayerCharacter>(GetPawn());
		if (!MyChar) return;
		AActor* DialogueTarget = MyChar->GetDialogueTarget();
		if (!DialogueTarget) return;
		UMJDialogueComponent* DialogueComp = DialogueTarget->GetComponentByClass<UMJDialogueComponent>();
		if (!DialogueComp) return;
		
		UIManager->ShowDialogue(DialogueComp);
		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
        {
        		Subsystem->AddMappingContext(InputConfigDataAsset->DialogueMappingContext, 0);
        		Subsystem->RemoveMappingContext(InputConfigDataAsset->DefaultMappingContext);
        }
	}
}

void AMJPlayerController::ChangeToIMCDefault() // showDialogue 마지막에 들어가야 함
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
		Subsystem->RemoveMappingContext(InputConfigDataAsset->DialogueMappingContext);
	}
}

void AMJPlayerController::ProceedDialogue() 
{
	if (IsTriggered)
	{
		AMJPlayerCharacter* MyChar = Cast<AMJPlayerCharacter>(GetPawn());
		if (!MyChar) return;
		AActor* DialogueTarget = MyChar->GetDialogueTarget();
		if (!DialogueTarget) return;
		UMJDialogueComponent* DialogueComp = DialogueTarget->GetComponentByClass<UMJDialogueComponent>();
		if (!DialogueComp) return;

		UIManager->NextDialogue(DialogueComp);
		
		if (DialogueComp->IsDialogueEnd()) // 마지막 대사라면 imc 전환
		{
			ChangeToIMCDefault();
		}
	}
}

void AMJPlayerController::ShowBacklog()
{
	UIManager->ShowBacklog();
}

void AMJPlayerController::OnTriggeredDialogueIn(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
                                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("OnTriggerBegin"));
	AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn());
	if ( Other && Other->FindComponentByClass<UMJDialogueComponent>())
	{
		MJChar->SetDialogueTarget(Other);
		IsTriggered = true;
	}
}

void AMJPlayerController::OnTriggeredDialogueOut(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn());
	if (MJChar->GetDialogueTarget()== Other)
	{
		MJChar->SetDialogueTarget(nullptr);
		IsTriggered = false;
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
	AMJPlayerCharacter* ControlledPawn = Cast<AMJPlayerCharacter>(GetPawn());
	if (ControlledPawn)
	{
		if (UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(ControlledPawn->GetAbilitySystemComponent()))
		{

			MJASC->OnAbilityInputReleased(InInputTag);
		}
	}
}
