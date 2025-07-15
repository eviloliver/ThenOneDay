// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MJStoreComponent.generated.h"

/*
* Class Description: 상점 시스템 / 상인 NPC에게 달아줘야 함
* Author: 이지수
* Created Date: 2025.07.13
* Last Modified By: 
* Last Modified Date:
* */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoreUpdatedEvent, int32, SlotCount);
USTRUCT(BlueprintType)
struct FStoreData
{
	GENERATED_BODY()

	UPROPERTY()
	FName ItemName;

	UPROPERTY()
	int32 ItemValue;

	UPROPERTY()
	int ItemCount;

	bool IsSoldOut() const
	{
		return ItemCount == 0;
	}
	
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJStoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMJStoreComponent();
	
protected:
	int32 SlotCount;
	
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnStoreUpdatedEvent OnStoreUpdated;

public:	
	void UpdateStore(); // 바인딩했던 슬롯들 정보 채우기용

	int32 GetSlotCount() const {return SlotCount;};

		
};
