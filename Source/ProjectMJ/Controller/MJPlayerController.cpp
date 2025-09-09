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
#include "Components/SphereComponent.h"
#include "UI/MJUIManagerSubsystem.h"
#include "Player/MJPlayerState.h"
#include "ProjectMJ.h"
#include "Character/Component/MJPlayerSkillComponent.h"
#include "Dialogue/MJDialogueWidget.h"
#include "Character/Component/MJPlayerStatComponent.h"
#include "Components/Button.h"
#include "DataTable/MJSkillDataRow.h"
#include "UI/Inventory/MJInventoryComponent.h"
#include "Item/MJItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "TG/UI/MJGameFlowHUDWidget.h"
#include "UI/MJHUDWidget.h"
#include "UI/Component/MJInteractComponent.h"
#include "UI/Skill/MJEquipedSkillWidget.h"
#include "UI/Skill/MJSkillWidget.h"
#include "UI/Store/MJMerchandiseSlot.h"
#include "UI/Store/MJPopupWidget.h"
#include "UI/Store/MJSalesSlot.h"
#include "UI/Store/MJStoreComponent.h"
#include "UI/Store/MJStoreWidget.h"
#include "UI/Skill/MJSkillSlotWidget.h"
#include "UI/Tutorial/MJTutorialCollision.h"
#include "UI/Tutorial/MJTutorialStartDialogueComponent.h"


// TODO: Input 관련한 로직들 Component로 따로 빼기 - 동민 - 

AMJPlayerController::AMJPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	bIsLMBPressed = false;
	bIsLMBHolding = false;
	LMBHoldTime = 0.0f;

	bIsRMBPressed = false;
	bIsRMBHolding = false;
	RMBHoldTime = 0.0f;

	bIsCharge = false;
	bShiftKeyDown = false;

	ChargeThreshold = 0.3f;
}

void AMJPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UIManager =	GetGameInstance()->GetSubsystem<UMJUIManagerSubsystem>();
	ensure(UIManager);
	
	AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn());
	if (MJChar)
	{
		MJChar->GetUITrigger()->OnComponentBeginOverlap.AddDynamic(this,&AMJPlayerController::OnTriggeredIn);
		MJChar->GetUITrigger()->OnComponentEndOverlap.AddDynamic(this,&AMJPlayerController::OnTriggeredOut);
		MJChar->GetUITrigger()->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnTriggeredItemIn);
	}
	
	GameFlowHUD = CastChecked<UMJGameFlowHUDWidget>(CreateWidget(this, GameFlowHUDWidgetClass));
	if (GameFlowHUD)
	{
		// TG : Do not change order of PC setter. 
		GameFlowHUD->SetPlayerController(this);
		GameFlowHUD->AddToViewport(1);
	}
	UMJPlayerStatComponent* MJPlayerStatComp = GetPawn()->FindComponentByClass<UMJPlayerStatComponent>();
	if (MJPlayerStatComp)
	{
		MJPlayerStatComp->OnDeath.AddDynamic(this,&AMJPlayerController::OnDead);
	}

	AMJPlayerState* State = GetPlayerState<AMJPlayerState>();
    if (State && MJPlayerStatComp)
    {
    	UIManager->ShowHUD(State, this, MJPlayerStatComp);
    	UIManager->GetHUDWidget()->GetStoreWidget()->SetStatComponent(MJPlayerStatComp);
    }
	
	TArray<UMJMerchandiseSlot*> MerSlot = UIManager->GetHUDWidget()->GetStoreWidget()->GetMerchandiseSlots();
	for (int i = 0; i < MerSlot.Num(); i++)
	{
		if (MerSlot[i])
		{
			MerSlot[i]->OnMerchandiseSlotEvent.AddDynamic(this, &AMJPlayerController::OnTryPurchase);
		}
	}

	if (UIManager->GetHUDWidget()->GetStoreWidget())
	{
		UIManager->GetHUDWidget()->GetStoreWidget()->OnClickedPurchaseYes.AddDynamic(this,&AMJPlayerController::OnPurchase);
		UIManager->GetHUDWidget()->GetStoreWidget()->OnClickedSellYes.AddDynamic(this,&AMJPlayerController::OnSell);
	}

	if (UMJPlayerSkillComponent* SkillComponent = MJChar->FindComponentByClass<UMJPlayerSkillComponent>())
	{
		SkillComponent->OnLearnSkillEvent.AddDynamic(this,&AMJPlayerController::UpdateSkillWidget);
	}

	for (int i = 0; i < 10; i++)
	{
		UIManager->GetHUDWidget()->GetSkillWidget()->GetSkillSlots()[i]->OnClickedEquipButton.AddDynamic(this,&AMJPlayerController::UpdateEquipedSkillWidget);
		UIManager->GetHUDWidget()->GetSkillWidget()->GetSkillSlots()[i]->GetEquipButton()->OnClicked.AddDynamic(this,&ThisClass::GetOwnedSkill);
	}

	const FString CurrentLevel = UGameplayStatics::GetCurrentLevelName(this, true);
	if (CurrentLevel.Equals(TEXT("Tutorial_StartStory")))
	{
		ChangeToIMCDialogue();
		bIsTutorialMode = true;
		UMJTutorialStartDialogueComponent* TutorialStartDialogue = MJChar->FindComponentByClass<UMJTutorialStartDialogueComponent>();
		if (!TutorialStartDialogue)
		{
			return;
		}
		TutorialStartDialogue->FloatLine();
		TutorialStartDialogue->OnTutorialStartDialogueEnd.AddDynamic(this,&ThisClass::TutorialDialogueEnd);
	}
}

void AMJPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputConfigDataAsset->GetDefaultMappingContext(), 0);
	}
	
	UMJInputComponent* MJInputComponent = CastChecked< UMJInputComponent>(InputComponent);

	MJInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AMJPlayerController::AbilityInputPressed, &AMJPlayerController::AbilityInputReleased);

	MJInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AMJPlayerController::ShiftPressed);
	MJInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AMJPlayerController::ShiftReleased);

	//Dialogue Input
	MJInputComponent->BindAction(ChangeIMCAction, ETriggerEvent::Triggered, this, &ThisClass::StartDialogue);
	MJInputComponent->BindAction(NextDialogueAction, ETriggerEvent::Triggered, this, &ThisClass::ProceedDialogue);
	
	
	MJInputComponent->BindAction(ShowBacklogAction, ETriggerEvent::Triggered, this, &ThisClass::ShowBacklog);

	// UI Input
	MJInputComponent->BindAction(ShowInventoryAction, ETriggerEvent::Triggered, this, &ThisClass::ShowInventory);
	MJInputComponent->BindAction(ShowStatPanelAction, ETriggerEvent::Triggered, this, &ThisClass::ShowStatPanel);
	MJInputComponent->BindAction(ShowSkillWidgetAction, ETriggerEvent::Triggered, this, &ThisClass::ShowSkillWidget);
	MJInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ThisClass::PauseGame);
}

void AMJPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bIsLMBPressed && !bIsLMBHolding)
	{
		bIsLMBHolding = true;
	}

	if (bIsLMBHolding)
	{
		LMBHoldTime += DeltaTime;
		HandleLeftMouseHold();
	}

	if (bIsRMBPressed && !bIsRMBHolding)
	{
		bIsRMBHolding = true;
	}

	if (bIsRMBHolding)
	{
		RMBHoldTime += DeltaTime;
		HandleRightMouseHold();
	}
}

void AMJPlayerController::OnLeftMousePressed()
{
	bIsLMBPressed = true;
	LMBHoldTime = 0.0f;
	bIsLMBHolding = false;

	if (bShiftKeyDown)
	{
		AMJPlayerCharacter* ControlledCharacter = Cast<AMJPlayerCharacter>(GetPawn());
		if (!ControlledCharacter)
		{
			return;
		}

		UMJPlayerSkillComponent* SkillComponent = ControlledCharacter->FindComponentByClass<UMJPlayerSkillComponent>();
		if (!SkillComponent)
		{
			return;
		}

		FGameplayTag BasicAttackTag = FGameplayTag::RequestGameplayTag(FName("Skill.Normal"));
		SkillComponent->ActivateSkillByInputTag(BasicAttackTag);
	}
}

void AMJPlayerController::OnLeftMouseReleased()
{
	if (!bIsLMBHolding)
	{
		FHitResult HitResult;
		if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
		{
			AttackOrMove(HitResult);
		}
	}

	bIsLMBPressed = false;
	bIsLMBHolding = false;
}

void AMJPlayerController::HandleLeftMouseHold()
{
	// 꾹 눌렀을 때는 몹 위에 마우스 있어도 이동이 맞음 - 동민 -
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		if (bShiftKeyDown)
		{
			AMJPlayerCharacter* ControlledCharacter = Cast<AMJPlayerCharacter>(GetPawn());
			if (!ControlledCharacter)
			{
				return;
			}

			UMJPlayerSkillComponent* SkillComponent = ControlledCharacter->FindComponentByClass<UMJPlayerSkillComponent>();
			if (!SkillComponent)
			{
				return;
			}

			FGameplayTag BasicAttackTag = FGameplayTag::RequestGameplayTag(FName("Skill.Normal"));
			SkillComponent->ActivateSkillByInputTag(BasicAttackTag);
			StopMovement();

		}
		else
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitResult.Location);

		}
	}
}

void AMJPlayerController::OnRightMousePressed()
{
	bIsRMBPressed = true;
	bIsRMBHolding = false;
	bIsCharge = false;
	RMBHoldTime = 0.0f;
}

void AMJPlayerController::OnRightMouseReleased()
{
	StopMovement();



	AMJPlayerCharacter* ControlledCharacter = Cast<AMJPlayerCharacter>(GetPawn());
	if (!ControlledCharacter)
	{
		return;
	}

	UMJPlayerSkillComponent* SkillComponent = ControlledCharacter->FindComponentByClass<UMJPlayerSkillComponent>();
	if (!SkillComponent)
	{
		return;
	}
	MJ_LOG(LogMJ, Warning, TEXT("%f"), RMBHoldTime);


	if (!bIsCharge)
	{
		
		FGameplayTag InstantSkillTag = FGameplayTag::RequestGameplayTag(FName("Skill.Instant"));
		SkillComponent->ActivateSkillByInputTag(InstantSkillTag);
	}
	else
	{
		FGameplayTag ChargeSkillTag = FGameplayTag::RequestGameplayTag(FName("Skill.Charge"));
		SkillComponent->ReleaseSkillByInputTag(ChargeSkillTag);
	}

	bIsRMBPressed = false;
	bIsRMBHolding = false;
	bIsCharge = false;
	RMBHoldTime = 0.f;
}

void AMJPlayerController::HandleRightMouseHold()
{
	if (!bIsCharge && RMBHoldTime >= ChargeThreshold)
	{
		bIsCharge = true;

		AMJPlayerCharacter* ControlledCharacter = Cast<AMJPlayerCharacter>(GetPawn());
		if (!ControlledCharacter)
		{
			return;
		}

		UMJPlayerSkillComponent* SkillComponent = ControlledCharacter->FindComponentByClass<UMJPlayerSkillComponent>();
		if (!SkillComponent)
		{
			return;
		}

		FGameplayTag ChargeSkillTag = FGameplayTag::RequestGameplayTag(FName("Skill.Charge"));
		SkillComponent->ActivateSkillByInputTag(ChargeSkillTag);
	}
}

void AMJPlayerController::AttackOrMove(const FHitResult& HitResult)
{
	if (bShiftKeyDown)
	{
		// Shift + Left Click은 OnLeftMousePressed에서 처리되므로 여기서는 아무것도 하지 않습니다.
		return;
	}

	AMJPlayerCharacter* ControlledCharacter = Cast<AMJPlayerCharacter>(GetPawn());
	if (!ControlledCharacter)
	{
		return;
	}

	UMJPlayerSkillComponent* SkillComponent = ControlledCharacter->FindComponentByClass<UMJPlayerSkillComponent>();
	if (!SkillComponent)
	{
		return;
	}

	AMJCharacterBase* TargetCharacter = Cast<AMJCharacterBase>(HitResult.GetActor());
	if (!TargetCharacter)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitResult.Location);;
	}
	else if (TargetCharacter != ControlledCharacter && TargetCharacter->GetGenericTeamId() != ControlledCharacter->GetGenericTeamId())
	{
		MJ_LOG(LogMJ, Warning, TEXT("NormalAttack"));
		FGameplayTag LeftClickInputTag = FGameplayTag::RequestGameplayTag(FName("Skill.Normal"));
		SkillComponent->ActivateSkillByInputTag(LeftClickInputTag);
	}
	else
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitResult.Location);
	}
}

void AMJPlayerController::AbilityInputPressed(FGameplayTag InInputTag)
{
	AMJPlayerCharacter* ControlledCharacter = Cast<AMJPlayerCharacter>(GetPawn());
	if (!ControlledCharacter)
	{
		return;
	}

	UMJPlayerSkillComponent* SkillComponent = ControlledCharacter->FindComponentByClass<UMJPlayerSkillComponent>();
	if (!SkillComponent)
	{
		return;
	}

	if (InInputTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input.Mouse.Left.Pressed"))))
	{
		OnLeftMousePressed();
	}
	else if (InInputTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input.Mouse.Right.Pressed"))))
	{
		OnRightMousePressed();
	}
	else
	{
		
	}
}

void AMJPlayerController::AbilityInputReleased(FGameplayTag InInputTag)
{
	if (InInputTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input.Mouse.Left.Released"))))
	{
		OnLeftMouseReleased();
	}
	else if (InInputTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input.Mouse.Right.Released"))))
	{
		OnRightMouseReleased();
	}
	else
	{
		
	}
}

void AMJPlayerController::ShiftPressed()
{
	bShiftKeyDown = true;
}

void AMJPlayerController::ShiftReleased()
{
	bShiftKeyDown = false;
}

void AMJPlayerController::StartDialogue()// x키를 눌렀을 때 실행되는 함수
{
	if (!IsInteracted) return; 
	
	AMJPlayerCharacter* MyChar = Cast<AMJPlayerCharacter>(GetPawn());
	if (!MyChar) return;
	
	if (UMJInteractComponent* InteractComp = MyChar->GetUITarget()->FindComponentByClass<UMJInteractComponent>())
	{		
		InteractComp->StartInteraction();
		switch (InteractComp->CurrentType)
		{
		case EMJInteractionType::Dialogue:
			ChangeToIMCDialogue();
			UIManager->SetDialogueVisibility();
			break;

		case EMJInteractionType::Store:
			ChangeToIMCDialogue();
			UIManager->SetDialogueVisibility();
			break;

		default:
			break;
		}
	}

	if (bIsTutorialMode)
	{
		UIManager->GetHUDWidget()->SetInstructionWidgetVisibility();
	}
}

void AMJPlayerController::ChangeToIMCDialogue()
{
	StopMovement();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
		Subsystem->AddMappingContext(InputConfigDataAsset->GetDialogueMappingContext(), 0);
   		Subsystem->RemoveMappingContext(InputConfigDataAsset->GetDefaultMappingContext());
    }
}

void AMJPlayerController::ChangeToIMCDefault() 
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputConfigDataAsset->GetDefaultMappingContext(), 0);
		Subsystem->RemoveMappingContext(InputConfigDataAsset->GetDialogueMappingContext());
	}
}

void AMJPlayerController::ProceedDialogue()
{
	AMJPlayerCharacter* MyChar = Cast<AMJPlayerCharacter>(GetPawn());
	if (!MyChar)
	{
		return;
	}
	if (MyChar->GetUITarget())
	{
		UMJInteractComponent* InteractComp = MyChar->GetUITarget()->FindComponentByClass<UMJInteractComponent>();
        if (InteractComp)
        {
        	InteractComp->ProceedInteraction();
        	return;
        }
	}
	if (bIsTutorialMode)
	{
		UMJTutorialStartDialogueComponent* TutorialStartDialogue = MyChar->FindComponentByClass<UMJTutorialStartDialogueComponent>();
		TutorialStartDialogue->ProceedStory();
	}
}

void AMJPlayerController::DialogueEnd()
{
	ChangeToIMCDefault();
	UIManager->SetDialogueVisibility();
	if (bIsTutorialMode)
	{
		UIManager->GetHUDWidget()->SetMouseVisibility();
		UIManager->GetHUDWidget()->SetInstructionWidgetVisibility();
		UIManager->GetHUDWidget()->ShowShift();
		UIManager->GetHUDWidget()->SetInstructionText("Move right and defeat the monster. Hold Shift and left-click to execute a basic attack.");
	}
}

void AMJPlayerController::TutorialDialogueEnd() // Tutorial 시작 다이어로그가 끝나면
{
	ChangeToIMCDefault();
	UIManager->SetDialogueVisibility();
	UIManager->GetHUDWidget()->SetLeftMouse();
	UIManager->GetHUDWidget()->SetInstructionWidgetVisibility();
	UIManager->GetHUDWidget()->SetInstructionText("Click the left mouse button to move the map. Move to your sister.");
}

void AMJPlayerController::ShowStore()
{
	UIManager->SetDialogueVisibility();
 	UIManager->ShowStore();
}

void AMJPlayerController::HideStore()
{
	UIManager->ShowStore();
	ChangeToIMCDefault();
	UE_LOG(LogTemp, Display, TEXT("AMJPlayerController::HideStore"));
}

void AMJPlayerController::ShowBacklog()
{
	UIManager->GetHUDWidget()->GetDialogueWidget()->ShowBacklog();
}

void AMJPlayerController::ShowStatPanel()
{
	UIManager->ShowStatPanel();
}

void AMJPlayerController::ShowInventory()
{
	UIManager->ShowInventory();
}

void AMJPlayerController::ShowSkillWidget()
{
	UIManager->SetSkillWidgetVisibility();
}

void AMJPlayerController::UpdateSkillWidget(FGameplayTag SkillTag,int32 Level)
{
	UIManager->GetHUDWidget()->GetSkillWidget()->UpdateSkillSlots(SkillTag,Level);
}

void AMJPlayerController::UpdateEquipedSkillWidget(UTexture2D* Icon, ESkillType SkillType, FGameplayTag Tag)
{
	if (SkillType == ESkillType::Instant)
	{
		UIManager->GetHUDWidget()->GetEquipedSkillWidget()->SetInstantImage(Icon);
	}
	if (SkillType == ESkillType::Passive)
	{
		UIManager->GetHUDWidget()->GetEquipedSkillWidget()->SetPassiveImage(Icon);
	}
	if (SkillType == ESkillType::Charge)
	{
		UIManager->GetHUDWidget()->GetEquipedSkillWidget()->SetChargingImage(Icon);
	}

	TempTag = Tag;
}

void AMJPlayerController::GetOwnedSkill()
{
	AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn());
	if (UMJPlayerSkillComponent* SkillComponent = MJChar->FindComponentByClass<UMJPlayerSkillComponent>())
	{
		SkillComponent->EquipSkill(TempTag);
		UE_LOG(LogTemp,Error,TEXT("AMJPlayerController::GetOwnedSkill, %s"),*TempTag.ToString());
	}
}


void AMJPlayerController::OnTriggeredIn(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
                                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other)
	{
		if (UMJInteractComponent* InteractComp = Other->FindComponentByClass<UMJInteractComponent>())
		{
			IsInteracted = true;
			InteractComp->OnBeginInteract();
			
			InteractComp->OndialogueEnd.RemoveDynamic(this, &AMJPlayerController::DialogueEnd);
			InteractComp->OndialogueEnd.AddDynamic(this, &AMJPlayerController::DialogueEnd);
			
			InteractComp->OnstoreOpen.RemoveDynamic(this, &AMJPlayerController::ShowStore);
			InteractComp->OnstoreOpen.AddDynamic(this, &AMJPlayerController::ShowStore);
			
			InteractComp->OnstoreClose.RemoveDynamic(this, &AMJPlayerController::HideStore);
			InteractComp->OnstoreClose.AddDynamic(this, &AMJPlayerController::HideStore);
			
			if (AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn()))
			{
				MJChar->SetUITarget(Other);
				if (InteractComp->GetStoreComponent())
				{
					InteractComp->GetStoreComponent()->SetItemData(MJChar->GetInventoryComponent()->GetItemTags(),MJChar->GetInventoryComponent()->GetItemTags().Num(),MJChar->GetInventoryComponent());
				}
			}

			if (bIsTutorialMode && !UIManager->GetbHasRun())
			{
				UIManager->GetHUDWidget()->SetMouseVisibility(); // OFF
				UIManager->GetHUDWidget()->SetInstructionText("Interaction is possible with F key. Press F key to talk with your sister.");
				UIManager->SetbHasRun(true);
			}
		}
		
		if (AMJTutorialCollision* TutorialCollision = Cast<AMJTutorialCollision>(Other))
		{
			// if (TutorialCollision->GetCollisionType() == ECollisionType::AttackTutorial)
			// {
			// 	UIManager->GetHUDWidget()->ShowShift();
			// 	UIManager->GetHUDWidget()->SetInstructionText(TutorialCollision->GetInstructionText());
			// }

			if (TutorialCollision->GetCollisionType() == ECollisionType::InstantSkillTutorial)
			{
				UIManager->GetHUDWidget()->HideShift();
				UIManager->GetHUDWidget()->SetRightMouse();
				UIManager->GetHUDWidget()->SetInstructionText(TutorialCollision->GetInstructionText());
				TutorialCollision->Hide();
			}

			if (TutorialCollision->GetCollisionType() == ECollisionType::ChargeSkillTutorial)
			{
				UIManager->GetHUDWidget()->SetRightPressMouse();
				UIManager->GetHUDWidget()->SetInstructionText(TutorialCollision->GetInstructionText());
				TutorialCollision->Hide();
			}
		}
	}
}

void AMJPlayerController::OnTriggeredOut(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (Other)
	{
		if (UMJInteractComponent* InteractComp = Other->FindComponentByClass<UMJInteractComponent>())
		{
			IsInteracted = false;
			InteractComp->OnEndInteract();

			if (AMJPlayerCharacter* MJChar = Cast<AMJPlayerCharacter>(GetPawn()))
			{
				MJChar->SetUITarget(nullptr);
			}
		}
	}
}

void AMJPlayerController::OnTriggeredItemIn(UPrimitiveComponent* Overlapped, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMJItemBase* Item = Cast<AMJItemBase>(Other);
	if (!Item) return;
	UE_LOG(LogTemp,Error,TEXT("AMJPlayerController::OnTriggeredItemIn"));
	AMJPlayerCharacter* MyChar = Cast<AMJPlayerCharacter>(GetPawn());
	if (!MyChar) return;
	
	UMJInventoryComponent* InventoryComp = MyChar->GetInventoryComponent();
	 if (InventoryComp)
	 {
	 	InventoryComp->PickUpItem(Item->GetItemTag(), 1, UIManager->GetHUDWidget()->GetStoreWidget());
	 	
	 	TArray<UMJSalesSlot*> SalesSlot = UIManager->GetHUDWidget()->GetStoreWidget()->GetInventorySlots();
	 	for (int i = 0; i < SalesSlot.Num(); i++)
	 	{
	 		if (SalesSlot[i])
	 		{
	 			SalesSlot[i]->OnMerchandiseSlotEvent.RemoveDynamic(this, &AMJPlayerController::OnTrySell);
	 			SalesSlot[i]->OnMerchandiseSlotEvent.AddDynamic(this, &AMJPlayerController::OnTrySell);
	 			UE_LOG(LogTemp,Error,TEXT("%d개의 슬롯에 델리게이트 연결됨"),SalesSlot.Num());
	 		}
	 	}

	 	Item->Destroy();
	 }
}

void AMJPlayerController::OnTryPurchase(FGameplayTag& ItemTag, int32 Price, int32 Quantity) // GET Item Data
{
	UE_LOG(LogTemp,Error,TEXT("AMJPlayerController::OnTryPurchase"));
	PurchaseItemTag = ItemTag;
	ItemPrice = Price;
	ItemQuantity = Quantity;
}

void AMJPlayerController::OnTrySell(FGameplayTag& ItemTag, int32 Price, int32 Quantity)
{
	UE_LOG(LogTemp,Error,TEXT("AMJPlayerController::OnTrySell"));
	SalesItemTag = ItemTag;
	SalesPrice = Price;
	SalesQuantity = Quantity;
}

void AMJPlayerController::OnPurchase()
{
	AMJPlayerCharacter* MyChar = Cast<AMJPlayerCharacter>(GetPawn());
    if (!MyChar) return;
	
   	UMJPlayerStatComponent* StatComp = GetPawn()->FindComponentByClass<UMJPlayerStatComponent>();
	UMJInventoryComponent* InventoryComp = MyChar->GetInventoryComponent();
	
	if (StatComp && InventoryComp)
   	{
   		if (StatComp->GetGold() >= ItemQuantity * ItemPrice)
   		{
   			InventoryComp->PickUpItem(PurchaseItemTag, ItemQuantity, UIManager->GetHUDWidget()->GetStoreWidget()); // 인벤토리 내 수량증가
   			UMJStoreComponent* StoreComp = MyChar->GetUITarget()->FindComponentByClass<UMJStoreComponent>();
   			StoreComp->SetItemData(MyChar->GetInventoryComponent()->GetItemTags(),MyChar->GetInventoryComponent()->GetItemTags().Num(),InventoryComp);
   			StatComp->SpendGold(ItemQuantity * ItemPrice);
   			for (auto* Slot : UIManager->GetHUDWidget()->GetStoreWidget()->GetMerchandiseSlots())
   			{
   				if (Slot)
   				{
   					Slot->InitializeQuantity(); // 구매 완료 후 구매 희망수량 초기화
   				}
   			}
   		}
   		else
   		{
   			// storewidget이 잔액 부족을 띄우게 한다.
   			return;
   		}
   	}
}

void AMJPlayerController::OnSell()
{
	AMJPlayerCharacter* MyChar = Cast<AMJPlayerCharacter>(GetPawn());
	if (!MyChar) return;
	
	UMJPlayerStatComponent* StatComp = GetPawn()->FindComponentByClass<UMJPlayerStatComponent>();
	UMJInventoryComponent* InventoryComp = MyChar->GetInventoryComponent();
	UMJStoreComponent* StoreComp = MyChar->GetUITarget()->FindComponentByClass<UMJStoreComponent>();
	if (StatComp && InventoryComp)
	{
		if (InventoryComp->GetItemInInventory()[SalesItemTag].ItemCount > SalesQuantity)
		{ 
			StatComp->GainGold(SalesQuantity * SalesPrice);
		}
		
		InventoryComp->DropItem(SalesItemTag,SalesQuantity);
		StoreComp->UpdateInventory(InventoryComp);

		for (auto* Slot : UIManager->GetHUDWidget()->GetStoreWidget()->GetInventorySlots())
		{
			if (Slot)
			{
				Slot->InitializeQuantity(); // 판매 완료 후 판매 수량 초기화
			}
		}
	}
}

void AMJPlayerController::PauseGame()
{
	GameFlowHUD->PauseGame(); 
}

void AMJPlayerController::OnDead(AActor* InEffectCauser)
{
	// TODO 태관 : StatComponent에서 델리게이트 로 호출해서 입력 막고 UI 띄울 예정 
	DisableInput(this);
	SetPause(true);
}
