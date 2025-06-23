// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"
#include "Engine/TriggerBox.h"
#include "MJAISpawnTriggerBox.generated.h"

struct FEnvQueryResult;
class UEnvQuery;
/**
 * Class Description: TriggerBox which spawns AI 
 * Author: Cha Tae Gwan
 * Created Date: 2025-06-23
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-06-23
 */
UCLASS()
class PROJECTMJ_API AMJAISpawnTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	AMJAISpawnTriggerBox();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UEnvQuery> EQSQuery;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawnTargetActor;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> SpawnCenterActor;
	
protected:
	virtual void PostInitializeComponents() override;
	
	
	UFUNCTION()
	void OnBeginOverlap( AActor* OverlappedActor, AActor* OtherActor);
	
	void OnQueryFininshed(TSharedPtr<FEnvQueryResult> Result);
	
};
