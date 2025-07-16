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
#include "Player/MJPlayerState.h"
#include "ProjectMJ.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/MJPlayerCharacter.h"
#include "Character/Component/MJPlayerSkillComponent.h"
#include "Compression/lz4.h"
#include "UI/Inventory/MJInventoryComponent.h"
#include "Item/MJItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "TG/UI/MJPauseMenuWidget.h"
#include "TG/UI/MJSettingsWidget.h"
#include "UI/MJHUDWidget.h"
#include "UI/Inventory/MJInventoryWidget.h"


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
	
	AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn());
	if (MJChar)
	{
		MJChar->GetDialogueTrigger()->OnComponentBeginOverlap.AddDynamic(this,&AMJPlayerController::OnTriggeredDialogueIn);
		MJChar->GetDialogueTrigger()->OnComponentEndOverlap.AddDynamic(this,&AMJPlayerController::OnTriggeredDialogueOut);
		MJChar->GetDialogueTrigger()->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnTriggeredItemIn);
	}

	AMJPlayerState* State = GetPlayerState<AMJPlayerState>();
	if (State)
	{
		UIManager->ShowHUD(State, this);
	}
	
	PauseWidget = CreateWidget(this, PauseWidgetClass);
	PauseWidget->AddToViewport(1);
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	
			
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

	// UI Input
	ProjectMJInputComponent->BindAction(ShowInventoryAction, ETriggerEvent::Triggered, this, &ThisClass::ShowInventory);
	ProjectMJInputComponent->BindAction(ShowStatPanelAction, ETriggerEvent::Triggered, this, &ThisClass::ShowStatPanel);

	ProjectMJInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ThisClass::PauseGame);
	
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
	const float TraceOffsetZ = 10.0f;
	const float TraceDepthZ = 1000.0;


	if (!bIsHolding)
	{
		FHitResult Hit;
		
		FVector WorldOrigin, WorldDirection;

		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			if (DeprojectMousePositionToWorld(WorldOrigin, WorldDirection))
			{
				FVector TraceStart = WorldOrigin;
				FVector TraceEnd = TraceStart + WorldDirection * 10000.0f;

				TArray<FHitResult> HitResults;
				FCollisionQueryParams TraceParams;
				TraceParams.AddIgnoredActor(GetPawn()); 
				
				bool bHit = GetWorld()->LineTraceMultiByChannel(
					HitResults,
					TraceStart,
					TraceEnd,
					ECC_Visibility,
					TraceParams
				);
				DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.5f);
				for (const FHitResult& Hits : HitResults)
				{
					UE_LOG(LogTemp, Warning, TEXT("%d"), HitResults.Num());
					AActor* HitActor = Hits.GetActor();
					if (!HitActor)
					{
						continue;
					}
			
					if (HitActor->ActorHasTag("BlockClick"))
					{
						continue;
					}
				
					if (HitActor->ActorHasTag("Ground") || Hits.Component->GetCollisionObjectType() == ECC_WorldStatic)
					{
						UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hits.ImpactPoint);
						break;
					}
				}
			}

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

void AMJPlayerController::ChangeToIMCDefault() 
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
		
		if (DialogueComp->IsDialogueEnd()) 
		{
			ChangeToIMCDefault();
		}
	}
}

void AMJPlayerController::ShowBacklog()
{
	UIManager->ShowBacklog();
}

void AMJPlayerController::ShowStatPanel()
{
	UIManager->ShowStatPanel();
}

void AMJPlayerController::ShowInventory()
{
	UIManager->ShowInventory();
}

void AMJPlayerController::OnTriggeredDialogueIn(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
                                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ( Other && Other->FindComponentByClass<UMJDialogueComponent>())
	{
		UE_LOG(LogTemp, Log, TEXT("OnTriggerBegin"));
		AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn());
		if (MJChar)
		{
			MJChar->SetDialogueTarget(Other);
            IsTriggered = true;
		}
	}
}

void AMJPlayerController::OnTriggeredDialogueOut(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (Other && Other->FindComponentByClass<UMJDialogueComponent>())
	{
		AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn());
		if (MJChar)
		{
			if (MJChar->GetDialogueTarget() == Other)
			{
				MJChar->SetDialogueTarget(nullptr);
				IsTriggered = false;
			}

		}
	}
}

void AMJPlayerController::OnTriggeredItemIn(UPrimitiveComponent* Overlapped, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMJItemBase* Item = Cast<AMJItemBase>(Other);
	if (!Item) return;
	
	AMJPlayerCharacter* MyChar = Cast<AMJPlayerCharacter>(GetPawn());
	if (!MyChar) return;
	
	UMJInventoryComponent* InventoryComp = MyChar->GetInventoryComponent();
	 if (InventoryComp)
	 {
	 	InventoryComp->PickUpItem(Item->GetItemName());
	 	Item->Destroy();
	 }
}


void AMJPlayerController::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	MJ_LOG(LogMJ, Warning, TEXT("Input Pressed: %s"), *InInputTag.ToString())
	AMJPlayerCharacter* ControlledPawn = Cast<AMJPlayerCharacter>(GetPawn());
	if (ControlledPawn)
	{
		if (UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(ControlledPawn->GetAbilitySystemComponent()))
		{
			
			MJASC->OnAbilityInputPressed(InInputTag);
			if (UMJPlayerSkillComponent* SkillComponent = ControlledPawn->FindComponentByClass<UMJPlayerSkillComponent>())
			{
				SkillComponent->ActivateSkillByInputTag(InInputTag);
			}
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

void AMJPlayerController::PauseGame()
{
	if (IsPaused())
	{
		if (UMJSettingsWidget* SettingsWidget = Cast<UMJSettingsWidget>((Cast<UMJPauseMenuWidget>(PauseWidget)->GetSettingsWidget())))
		{
			if (SettingsWidget->GetVisibility() == ESlateVisibility::Visible)
			{
				SettingsWidget->GetParentWidget()->SetVisibility(ESlateVisibility::Visible);
				SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				PauseWidget->SetVisibility(ESlateVisibility::Hidden);
				SetPause(false);		
			}
		}
	}
	else
	{
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
		SetPause(true);
	}
}

UUserWidget* AMJPlayerController::GetPauseWidget()
{
	return PauseWidget;
}
