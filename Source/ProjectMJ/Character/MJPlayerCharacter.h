// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MJCharacterBase.h"
#include "MJPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
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
};
