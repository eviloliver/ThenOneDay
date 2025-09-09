// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "MJPlayerController.generated.h"


class UMJGameFlowHUDWidget;
class UDataAsset_InputConfig;
class UInputAction;
class UMJUIManagerSubsystem;

/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: ?
 * Modified By: Lee Jisoo
 * Modified Date: 2025.06.25(BeginPlay에 ShowHUD 추가)
 * ---
 * Modified By: 신동민
 * Modified Date: 2025.07.14
 * Modified Description: 이동과 공격 관련 Input 
 */

UCLASS()
class PROJECTMJ_API AMJPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMJPlayerController();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

public:
	void OnLeftMousePressed();
	void OnLeftMouseReleased();
	void HandleLeftMouseHold();

	void OnRightMousePressed();
	void OnRightMouseReleased();
	void HandleRightMouseHold();

	void AttackOrMove(const FHitResult& HitResult);

	void AbilityInputPressed(FGameplayTag InInputTag);
	void AbilityInputReleased(FGameplayTag InInputTag);

	void ShiftPressed();
	void ShiftReleased();
private:
	bool bIsLMBPressed = false;
	bool bIsLMBHolding = false;
	float LMBHoldTime = 0.0f;

	bool bIsRMBPressed = false;
	bool bIsRMBHolding = false;
	float RMBHoldTime = 0.0f;

	bool bIsCharge = false;

	bool bShiftKeyDown = false;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float ChargeThreshold = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inpur", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;
#pragma region UIPart
private:
	bool bIsTutorialMode = false;
	
	bool IsInteracted = false;
	FGameplayTag PurchaseItemTag;
	int32 ItemPrice;
	int32 ItemQuantity;

	FGameplayTag SalesItemTag;
	int32 SalesPrice;
	int32 SalesQuantity;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> ChangeIMCAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> NextDialogueAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> ShowBacklogAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> ShowStatPanelAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> ShowInventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> ShowStoreAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> ShowSkillWidgetAction;
	
	UPROPERTY()
	TObjectPtr<UMJUIManagerSubsystem> UIManager;

	//Dialogue
	UFUNCTION()
	void StartDialogue();

	UFUNCTION()
	void ChangeToIMCDialogue();

	UFUNCTION()
	void ChangeToIMCDefault();
	

	UFUNCTION()
	void ProceedDialogue();
	
	UFUNCTION()
	void DialogueEnd();

	UFUNCTION()
	void TutorialDialogueEnd();
	
	// Store
	UFUNCTION()
	void ShowStore();
	UFUNCTION()
	void HideStore();
		
	// Show Widget
	UFUNCTION()
	void ShowBacklog();
	UFUNCTION()
	void ShowStatPanel();
	UFUNCTION()
	void ShowInventory();
	UFUNCTION()
	void ShowSkillWidget();
	UFUNCTION()
	void UpdateSkillWidget(FGameplayTag SkillTag,int32 Level);
	UFUNCTION()
	void UpdateEquipedSkillWidget(UTexture2D* Icon, ESkillType SkillType, FGameplayTag Tag);
	UFUNCTION()
	void GetOwnedSkill();

	FGameplayTag TempTag;
	
	UFUNCTION()
	void OnTriggeredIn(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggeredOut(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex);

	UFUNCTION()
	void OnTriggeredItemIn(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTryPurchase(FGameplayTag& ItemTag, int32 Price, int32 Quantity);

	UFUNCTION()
	void OnTrySell(FGameplayTag& ItemTag, int32 Price, int32 Quantity);

	UFUNCTION()
	void OnPurchase();

	UFUNCTION()
	void OnSell();
#pragma endregion


public:

	UFUNCTION(BlueprintCallable)
	UMJGameFlowHUDWidget* GetGameFlowHUD() {return GameFlowHUD; }

protected:
	UPROPERTY()
	TObjectPtr<UMJGameFlowHUDWidget> GameFlowHUD;
	
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUserWidget> GameFlowHUDWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	UInputAction* PauseAction;
	//
	UFUNCTION()
	void PauseGame();



protected:
	UFUNCTION()
	void OnDead(AActor* InEffectCauser);

};
