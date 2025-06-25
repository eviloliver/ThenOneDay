// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MJAT_Trace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);

/**
 * Class Description: 스킬 시전 시, 충돌 판정을 하는 TA를 생성하는 Task
 * Author: 신동민
 * Created Date: 2025_06_18
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */

class AMJTA_Trace;

UCLASS()
class PROJECTMJ_API UMJAT_Trace : public UAbilityTask
{
	GENERATED_BODY()

public:
	UMJAT_Trace();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "WaitForTrace", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UMJAT_Trace* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<AMJTA_Trace> TargetActorClass);

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	void SpawnAndInitializeTargetActor();
	void FinalizeTargetActor();

protected:
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle);
public:
	UPROPERTY(BlueprintAssignable)
	FTraceResultDelegate OnComplete;

protected:
	UPROPERTY()
	TSubclassOf<AMJTA_Trace> TargetActorClass;

	UPROPERTY()
	TObjectPtr<AMJTA_Trace> SpawnedTargetActor;
};
