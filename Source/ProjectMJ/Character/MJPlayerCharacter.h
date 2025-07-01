// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MJCharacterBase.h"
#include "MJPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMJPlayerCombatComponent;
class UAIPerceptionStimuliSourceComponent;
class USphereComponent;
class UMJInventoryComponent;

/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: 2025_06_11
 * Last Modified By: Add Combat Component 
 * Last Modified Date: 2025_06_18
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

	// AI Perception
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> PerceptionStimuliSourceComponent;
	
private:

#pragma region ComponentPart
public:
	FORCEINLINE UMJPlayerCombatComponent* GetPlayerCombatComponent() { return PlayerCombatComponent; }
	

#pragma region DialoguePart	
protected:
 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Trigger")
 	USphereComponent* DialogueTrigger;

 	UPROPERTY()
 	AActor* DialogueTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UMJInventoryComponent* InventoryComponent;

public:
	void SetDialogueTarget(AActor* NewTarget) { DialogueTarget = NewTarget; }
	
	AActor* GetDialogueTarget() {return DialogueTarget;}
	USphereComponent* GetDialogueTrigger() {return DialogueTrigger;}
	UMJInventoryComponent* GetInventoryComponent() {return InventoryComponent;}
	
#pragma endregion
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Camera",meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMJPlayerCombatComponent>PlayerCombatComponent;
#pragma endregion
};
