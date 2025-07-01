// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MJAIControllerBaseTG.generated.h"

class UBehaviorTreeComponent;
struct FAIStimulus;
/**
 * Class Description: AIControellerBase class 
 * Author: Cha Tae Gwan
 * Created Date: 2025-06-28
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-06-28
 */
UCLASS()
class PROJECTMJ_API AMJAIControllerBaseTG : public AAIController
{
	GENERATED_BODY()

public:
	AMJAIControllerBaseTG();

protected:

	virtual void PostInitializeComponents() override;
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;
	
	virtual FGenericTeamId GetGenericTeamId() const override;
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	UFUNCTION(BlueprintCallable)
	virtual void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI|BehaviorTree")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
	FGenericTeamId TeamId;
	
	

	
	
};
