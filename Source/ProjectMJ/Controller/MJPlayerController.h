// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "MJPlayerController.generated.h"

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
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

public:
	void OnLeftMousePressed();
	void OnLeftMouseReleased();
	void HandleLeftMouseHold();

	void OnRightMousePressed();
	void OnRightMouseReleased();

	void AttackOrMove(const FHitResult& HitResult);

	void AbilityInputPressed(FGameplayTag InInputTag);
	void AbilityInputReleased(FGameplayTag InInputTag);

private:
	bool bIsLMBPressed = false;
	bool bIsLMBHolding = false;
	float LMBHoldTime = 0.0f;

	bool bIsRMBPressed = false;
	float RMBHoldTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float HoldThreshold = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float ChargeThreshold = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inpur", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

#pragma region UIPart
private:
	bool IsTriggered = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ChangeIMCAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* NextDialogueAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ShowBacklogAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ShowStatPanelAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ShowInventoryAction;
	
	UPROPERTY()
	UMJUIManagerSubsystem* UIManager;
	
	void ChangeToIMCDialogue();
	void ChangeToIMCDefault();
	void ProceedDialogue();
	
	void ShowBacklog();
	void ShowStatPanel();
	void ShowInventory();
	
	UFUNCTION()
	void OnTriggeredDialogueIn(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggeredDialogueOut(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex);

	UFUNCTION()
	void OnTriggeredItemIn(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
#pragma endregion


};
