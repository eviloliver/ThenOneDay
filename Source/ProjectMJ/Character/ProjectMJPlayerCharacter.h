// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ProjectMJCharacterBase.h"
#include "ProjectMJPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class PROJECTMJ_API AProjectMJPlayerCharacter : public AProjectMJCharacterBase
{
	GENERATED_BODY()
	
public:
	AProjectMJPlayerCharacter();

protected:
	virtual void BeginPlay() override;


	virtual void PossessedBy(AController* NewController)override;

private:

#pragma region ComponentPart
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Camera",meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;
#pragma endregion
};
