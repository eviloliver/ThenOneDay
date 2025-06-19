// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MJCharacterBase.h"
#include "GenericTeamAgentInterface.h"
#include "MJPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAIPerceptionStimuliSourceComponent;
/**
 * Class Description:
 * Author: Lee JuHyeon
 * Created Date: 2025_06_11
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: add GameInstance SubSystem Logic
 */
UCLASS()
class PROJECTMJ_API AMJPlayerCharacter : public AMJCharacterBase, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AMJPlayerCharacter();

	// GenericTeamAgentInterface 구현
	/*
	 * TODO
	 * CharacterBase에 해야 할지 고민: TeamId는 플레이어 뿐만 아니라 모든 캐릭터들이 있어야 할 것 같음.
	 */
	virtual FGenericTeamId GetGenericTeamId() const override {return TeamId;}
	/*
	 * TODO
	 * SetTeamId 만들어서 에디터상에서 편집이 가능하게 할까 고민
	 */
protected:
	virtual void BeginPlay() override;


	virtual void PossessedBy(AController* NewController)override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// AI Perception
	UPROPERTY()
	TObjectPtr<UAIPerceptionStimuliSourceComponent> PerceptionStimuliSourceComponent;
	
	FGenericTeamId TeamId;
	
private:

#pragma region ComponentPart
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Camera",meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;
#pragma endregion
};
