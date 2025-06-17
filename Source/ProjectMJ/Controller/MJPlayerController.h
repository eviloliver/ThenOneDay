// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MJPlayerController.generated.h"

class UDataAsset_InputConfig;
class UInputAction;
class UMJDialogueWidget;
class UMJBacklogWidget;
/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: 
 * Last Modified By: Lee Jisoo
 * Last Modified Date: 2025.06.13(Add Dialogue Input)
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
#pragma endregion 
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed


	
#pragma region DialoguePart
private:
	bool bIsDialogueActive = false;
	bool IsTriggered = false;
	float DialogueSpeed;

	void OnDialogueStateChanged();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* BeginDialogueAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* NextDialogueAction;

	UPROPERTY()
	UMJDialogueWidget* DialogueWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<UMJDialogueWidget> DialogueWidgetClass;


	void BeginDialogue();
	void EndDialog();
	void NextDialogue();

	UFUNCTION()
	void OnTriggeredDialogueIn(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggeredDialogueOut(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex);

	
#pragma endregion
	
};
