// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MJCharacterBase.h"
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


	virtual void PossessedBy(AController* NewController)override;

private:

#pragma region ComponentPart
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Camera",meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;
#pragma endregion
};
