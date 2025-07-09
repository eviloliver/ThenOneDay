// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TG/Interface/MJBossEventManagerTG.h"
#include "TG/Struct/MJDungeonSessionDataStruct.h"
#include "MJGameStateDungeonTG.generated.h"

/**
 * Class Description: 던전의 상태를 저장할 GameState
 * Author: 차태관
 * Created Date: 2025-06-13
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-13
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMJAIBossOnHealthChangedSignature, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMJAIBossOnSpawnedSignature, float, Health);

UCLASS()
class PROJECTMJ_API AMJGameStateDungeonTG : public AGameStateBase, public IMJBossEventManagerTG
{
	GENERATED_BODY()
	
public:
	AMJGameStateDungeonTG();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable)
	void SetDungeonSessionData(FMJDungeonSessionData& DungeonSessionData);
	
	UFUNCTION(BlueprintCallable)
	void SaveToInstancedDungeonSessionData(uint8 SaveToNum);

	UFUNCTION()
	void LoadFromInstancedDungeonSessionData(uint8 LoadFromNum);

	UPROPERTY(BlueprintAssignable)
	FMJAIBossOnHealthChangedSignature OnAIBossHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FMJAIBossOnSpawnedSignature OnAIBossSpawned;

	UFUNCTION(BlueprintCallable)
	virtual void PublishOnBossHealthChanged(float Delta) override;

	UFUNCTION(BlueprintCallable)
	virtual void PublishOnBossSpawned(float Health) override;
	
protected:
	
	UPROPERTY(BlueprintReadOnly)
	FMJDungeonSessionData LoadedDungeonSessionData;

	UPROPERTY(BlueprintReadOnly)
	uint8 LoadedDungeonNodeNum;
	
		


	
};
