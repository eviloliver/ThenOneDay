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
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, MJGameplayTags::Input_SetDestination_Click, ETriggerEvent::Started, this, &ThisClass::OnTouchStart);
	ProjectMJInputComponent->BindNativeInputAction(InputConfigDataAsset, MJGameplayTags::Input_SetDestination_Click, ETriggerEvent::Completed, this, &ThisClass::OnTouchReleased);
	
	ProjectMJInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AMJPlayerController::Input_AbilityInputPressed, &AMJPlayerController::Input_AbilityInputReleased);
	
	//Dialogue Input
	ProjectMJInputComponent->BindAction(ChangeIMCAction, ETriggerEvent::Triggered, this, &ThisClass::ChangeToIMCDialogue);
	ProjectMJInputComponent->BindAction(NextDialogueAction, ETriggerEvent::Triggered, this, &ThisClass::ProceedDialogue);
	ProjectMJInputComponent->BindAction(ShowBacklogAction, ETriggerEvent::Triggered, this, &ThisClass::ShowBacklog);
}
void AMJPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (bIspressed && !bIsHolding)
	{
		PressTimed += DeltaTime;
		if (PressTimed >= HoldThresHold)
		{
			bIsHolding = true;
			StopMove();
		}
	}
	if (bIsHolding)
	{
		HoldingMove();
	}
}

void AMJPlayerController::StopMove()
{
		StopMovement();	
}


void AMJPlayerController::HoldingMove()
{
	//FollowTime = 0.f;
	FHitResult Hit;

	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		FVector MoveDir = Hit.ImpactPoint - GetPawn()->GetActorLocation();
		MoveDir.Z = 0;
		MoveDir.Normalize();

		if (!MoveDir.IsNearlyZero())
		{
			GetPawn()->AddMovementInput(MoveDir, 1.0f);
		}
	}
}

void AMJPlayerController::OnTouchStart()
{
	//bIsTouch = true;
	bIspressed = true;
	bIsHolding = false;
	PressTimed = 0.0f;
}

void AMJPlayerController::OnTouchReleased()
{
	//bIsTouch = false;

	if (!bIsHolding)
	{
		FHitResult Hit;
		
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.Location;

			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		}
	}
	else
	{
		StopMove();
	}

	bIspressed = false;
	bIsHolding = false;
	PressTimed = 0.0f;
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
