// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MJPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJCharacterAttributeSet.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TG/MJGameInstanceTG.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

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

	DialogueTarget = nullptr;
	
	DialogueTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("DialogueTrigger"));
	DialogueTrigger->SetupAttachment(RootComponent);
	DialogueTrigger->InitSphereRadius(120.f);
	DialogueTrigger->SetCollisionProfileName(TEXT("Trigger"));
	DialogueTrigger->SetGenerateOverlapEvents(true);
	DialogueTrigger->SetHiddenInGame(false);
}

void AMJPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	DialogueTrigger->OnComponentBeginOverlap.AddDynamic(this,&AMJPlayerCharacter::OnTriggerBegin);
	DialogueTrigger->OnComponentEndOverlap.AddDynamic(this,&AMJPlayerCharacter::OnTriggerEnd);
}

void AMJPlayerCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMJPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// 로딩 데이터 있을 시 받아와서 AttributeSet에 적용
	// 없을 시엔 무시하고 기본 AttributeSet 으로 진행됩니다.

	
	UMJGameInstanceTG* MJGI = Cast<UMJGameInstanceTG>(GetWorld()->GetGameInstance());
	if (MJGI)
	{
		MJGI->LoadSaveGame(this);

		MJ_LOG(LogTG, Log, TEXT("player loaded health : %f"),  GetAbilitySystemComponent()->GetNumericAttribute(UMJCharacterAttributeSet::GetHealthAttribute()));
	}
	
}

void AMJPlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (UMJGameInstanceTG* GI = Cast<UMJGameInstanceTG>(GetGameInstance()))
	{
		GI->SaveGameToSlot(this);
		UE_LOG(LogTemp,Log,TEXT("Character :: Saved"));
	}

}

void AMJPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(BeginDialogueAction, ETriggerEvent::Triggered, this, &AMJPlayerCharacter::BeginDialogue);
		EnhancedInputComponent->BindAction(NextDialogueAction, ETriggerEvent::Triggered, this, &AMJPlayerCharacter::OnNextDialogue);
	}
}

void AMJPlayerCharacter::OnTriggerBegin(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
                                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("OnTriggerBegin"));
	if ( Other && Other->FindComponentByClass<UMJDialogueComponent>())
	{
		DialogueTarget = Other;
	}
}

void AMJPlayerCharacter::OnTriggerEnd(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (DialogueTarget == Other)
	{
		DialogueTarget = nullptr;
	}
}

void AMJPlayerCharacter::BeginDialogue()
{
	if (DialogueWidget && DialogueWidget->IsInViewport())
		return; 
	
	if (DialogueTarget)
	{
		UE_LOG(LogTemp, Log, TEXT("와"));
		UMJDialogueComponent* DialogueComp = DialogueTarget->GetComponentByClass<UMJDialogueComponent>();
		if (!DialogueComp) return;
        
		DialogueComp->StartDialogue();
		
		DialogueWidget = CreateWidget<UMJDialogueWidget>(GetWorld(), DialogueWidgetClass);
		DialogueWidget->AddToViewport();

		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC)
		{
			PC->SetIgnoreLookInput(true);
			PC->SetIgnoreMoveInput(true);
			//PC->SetInputMode(FInputModeUIOnly());
			//PC->bShowMouseCursor = true; // 원래 TRUE임;
		}
        
		if (const FMJDialogueRow* Row = DialogueComp->GetCurrentRow())
		{
			DialogueWidget->ShowDialogue(*Row);
		}
	}
}

void AMJPlayerCharacter::EndDialog()
{
	if (DialogueTarget)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(this,0);
		if (PC)
		{
			PC->SetIgnoreLookInput(false);
			PC->SetIgnoreMoveInput(false);
			//PC->SetInputMode(FInputModeGameOnly());
		}
       
		if (DialogueWidget)
		{
			DialogueWidget->RemoveFromParent();
			DialogueWidget = nullptr;
		}
	}
}

void AMJPlayerCharacter::OnNextDialogue()
{
	if (DialogueTarget)
	{
		UMJDialogueComponent* DialogueComp = DialogueTarget->GetComponentByClass<UMJDialogueComponent>();
		if (!DialogueComp) return;
		
		UE_LOG(LogTemp, Warning, TEXT("CurrentIndex is %d"), DialogueComp->CurrentIndex);
		if (!DialogueComp || !DialogueWidget)
			return;

		DialogueComp->NextDialogue();
	
		if (DialogueComp->IsDialogueEnd())
		{
			EndDialog();
		}
		else if (const FMJDialogueRow* Row = DialogueComp->GetCurrentRow())
		{
			DialogueWidget->ShowDialogue(*Row);
		}
	}
}
