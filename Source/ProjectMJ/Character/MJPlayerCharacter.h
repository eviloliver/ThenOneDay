// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MJCharacterBase.h"

#include "UI/Dialogue/MJDialogueWidget.h"
#include "Components/SphereComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "MJPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: 2025_06_11
 * Last Modified By: Lee JuHyeon
 * Last Modified Date: Delete CameraBoom Sockect
 */
UCLASS()
class PROJECTMJ_API AMJPlayerCharacter : public AMJCharacterBase
{
	GENERATED_BODY()
	
public:
	AMJPlayerCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController)override;

private:

#pragma region ComponentPart
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Camera",meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;
#pragma endregion
	

#pragma region DialoguePart	
	public:
	// Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BeginDialogueAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* NextDialogueAction;
	
	UPROPERTY()
	UMJDialogueWidget* DialogueWidget;

	UPROPERTY(EditAnywhere, Category = "Dialogue")
	TSubclassOf<UMJDialogueWidget> DialogueWidgetClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Trigger")
	USphereComponent* DialogueTrigger;

	UPROPERTY()
	AActor* DialogueTarget;

	//
	UFUNCTION()
	void OnTriggerBegin(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerEnd(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void BeginDialogue();
	void EndDialog();
	void OnNextDialogue();
	
#pragma endregion
};
