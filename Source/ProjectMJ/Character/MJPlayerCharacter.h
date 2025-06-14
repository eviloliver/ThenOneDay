// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MJCharacterBase.h"
#include "MJPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USphereComponent;
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
protected:
 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Trigger")
 	USphereComponent* DialogueTrigger;

 	UPROPERTY()
 	AActor* DialogueTarget;

public:
	void SetDialogueTarget(AActor* NewTarget) { DialogueTarget = NewTarget; }
	
	AActor* GetDialogueTarget() {return DialogueTarget;}
	USphereComponent* GetDialogueTrigger() {return DialogueTrigger;}
#pragma endregion
};
