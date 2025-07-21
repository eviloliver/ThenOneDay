// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MJAT_GetMousePosition.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMousePositionResultDelegate, const FVector&, MouseLocation);

/**
 * Class Description: 마우스 위치를 받아오는 AbilityTask
 * Author: 신동민
 * Created Date: 2025.07.18
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

UCLASS()
class PROJECTMJ_API UMJAT_GetMousePosition : public UAbilityTask
{
	GENERATED_BODY()
public:
	UMJAT_GetMousePosition();

	UFUNCTION(BlueprintCallable, Category = "AbilityTasks", meta = (DisplayName = "GetMousePosition", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UMJAT_GetMousePosition* CreateTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;

public:
	UPROPERTY(BlueprintAssignable)
	FMousePositionResultDelegate OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FMousePositionResultDelegate OnFailed;
};
