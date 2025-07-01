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
class UAISenseConfig_Damage;
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

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	
	UFUNCTION(BlueprintCallable)
	void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	// AI Affiliation
	FGenericTeamId TeamId;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	// Minjin: Handle AI Sense
	// 자식 클래스에서 오버라이드해서 각 감각별로 다른 처리 진행
	UFUNCTION()
	virtual void HandleSight_Detected(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	virtual void HandleDamage_Detected(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	virtual void HandleSight_Lost(AActor* Actor, FAIStimulus Stimulus);
	
	UFUNCTION()
	virtual void HandleDamage_Lost(AActor* Actor, FAIStimulus Stimulus);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="AI|BehaviorTree")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	
};
