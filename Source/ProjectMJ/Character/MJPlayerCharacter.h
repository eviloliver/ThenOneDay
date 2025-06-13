// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MJCharacterBase.h"

#include "Components/SphereComponent.h"
#include "MJPlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestDialogue);

class USpringArmComponent;
class UCameraComponent;
/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: 2025_06_11
 * Last Modified By: Lee Jisoo
 * Last Modified Date: Delete CameraBoom Sockect, 2025.06.13(Delete Dialogue Input)
 */
UCLASS()
class PROJECTMJ_API AMJPlayerCharacter : public AMJCharacterBase
{
	GENERATED_BODY()
	
public:
	AMJPlayerCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController)override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

#pragma region ComponentPart
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Camera",meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;
#pragma endregion
	

#pragma region DialoguePart	
public:
 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Trigger")
 	USphereComponent* DialogueTrigger;

 	UPROPERTY()
 	AActor* DialogueTarget;

	UPROPERTY(BlueprintAssignable)
	FOnRequestDialogue OnRequestDialogueIn;

	UPROPERTY(BlueprintAssignable)
	FOnRequestDialogue OnRequestDialogueOut;

 	UFUNCTION()
 	void OnTriggerBegin(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

 	UFUNCTION()
 	void OnTriggerEnd(UPrimitiveComponent* Overlapped, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion
};
