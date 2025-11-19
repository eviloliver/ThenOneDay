// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
//#include "Perception/AIPerceptionComponent.h"
#include "MJMonsterAIControllerBase.generated.h"

class UBehaviorTreeComponent;
class UAIPerceptionComponent;

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

	// Minjin: BehaviorTree Component
	UPROPERTY(EditDefaultsOnly, Category="AI|BehaviorTree")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
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
	virtual void HandleSightDetected(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	virtual void HandleDamageDetected(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	virtual void HandleHearingDetected(AActor* Actor, FAIStimulus Stimulus);
	
	UFUNCTION()
	virtual void HandleSightLost(AActor* Actor, FAIStimulus Stimulus);
	
	UFUNCTION()
	virtual void HandleDamageLost(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	virtual void HandleHearingLost(AActor* Actor, FAIStimulus Stimulus);
};
