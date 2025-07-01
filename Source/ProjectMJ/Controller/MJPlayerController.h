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
 * Last Modified By: Lee Jisoo
 * Last Modified Date: 2025.06.25(BeginPlay에 ShowHUD 추가)
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
	
	virtual void PlayerTick(float DeltaTime)override;
#pragma region Inputs
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

	void SetNewDestination(const FVector DestLocation);
	void MoveToMouseCurser();

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
#pragma endregion 
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed


	
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
