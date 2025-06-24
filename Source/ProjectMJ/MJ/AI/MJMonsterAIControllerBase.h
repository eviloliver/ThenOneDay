// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "MJMonsterAIControllerBase.generated.h"

class UBehaviorTree;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
/**
 * Class Description: MonsterAIControllerBase: Perception-Sight,Affiliation 포함
 * Author: Kim Minjin
 * Created Date: 2025.06.20.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API AMJMonsterAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AMJMonsterAIControllerBase();

	virtual void BeginPlay() override;
	
	void RunAI();
	void StopAI();

	// AI Affiliation
	virtual FGenericTeamId GetGenericTeamId() const override {return TeamId;}

protected:
	virtual void OnPossess(APawn* InPawn) override;

	// AI Perception
	UPROPERTY()
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	// Sight
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AI|Perception")
	TObjectPtr<UAISenseConfig_Sight> AISenseConfig_Sight;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="AI|Perception")
	FAISenseAffiliationFilter DetectionByAffiliation;
	
	// AI Affiliation
	FGenericTeamId TeamId;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="AI|BehaviorTree")
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
