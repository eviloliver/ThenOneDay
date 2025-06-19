// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MJAIController.generated.h"

/**
 * Class Description: AIController-기본 작동
 * Author: Kim Minjin
 * Created Date: 2025.06.13.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */

class UAIPerceptionComponent;

UCLASS()
class PROJECTMJ_API AMJAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMJAIController();

	void RunAI();
	void StopAI();

	// AI Affiliation
	virtual FGenericTeamId GetGenericTeamId() const override {return TeamId;}

protected:
	virtual void OnPossess(APawn* InPawn) override;

	// AI Perception
	UPROPERTY()
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionComponent;
	
	UFUNCTION()
	 void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	// Sight
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UAISenseConfig_Sight> AISenseConfig_Sight;

	// AI Affiliation
	FGenericTeamId TeamId;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
};
