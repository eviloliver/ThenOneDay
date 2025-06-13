// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MJDungeonGameState.generated.h"

/**
 * Class Description: 던전의 상태를 저장할 GameState
 * Author: 차태관
 * Created Date: 2025-06-13
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-13
 */
UCLASS()
class PROJECTMJ_API AMJDungeonGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AMJDungeonGameState();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
	UFUNCTION(BlueprintCallable)
	FVector GetDummyPos();

	UFUNCTION(BlueprintCallable)
	void SetDummyPos(FVector Input);

protected:

	UPROPERTY()
	FVector DummyPos;

	
};
