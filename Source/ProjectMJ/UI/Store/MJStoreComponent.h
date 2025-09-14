// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Dialogue/MJDialogueComponent.h"
#include "MJStoreComponent.generated.h"


class UMJInventoryComponent;
struct FGameplayTag;
/*
* Class Description: 상점 시스템 / 상인 NPC에게 달아줘야 함
* Author: 이지수
* Created Date: 2025.07.13
* Last Modified By: 지수
* Last Modified Date: 2025.08.09
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
class PROJECTMJ_API UMJStoreComponent : public UMJDialogueComponent
{
	GENERATED_BODY()

protected:
	int32 SlotCount;
	int32 InvenSlotCount;
	bool bIsOpened = false;
	bool bIsStoreRoot = false;

	FGameplayTag CurrentItemTag;
	int32 CurrentPrice;
	int32 CurrentQuantity;

	TArray<FGameplayTag> ItemTagForStore;
	
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnStoreUpdatedEvent OnStoreUpdated;

public:
	void UpdateStore(); // 바인딩했던 슬롯들 정보 채우기용
	void UpdateInventory(UMJInventoryComponent* InvenComp);

	UFUNCTION()
	void TryPurchase();

	UFUNCTION()
	void TrySale();
	
	int32 GetSlotCount() const {return SlotCount;}
	
	//다이어로그 선택지 기능 추가를 위한 함수
	UFUNCTION()
	void BindButtons();
	UFUNCTION()
	void ShowStory();
	UFUNCTION()
	void ShowStore();
	UFUNCTION()
	void ExitDialogue();
	UFUNCTION()
	void DialogueEnd();
	UFUNCTION()
	void SetChoiceWidgetText();
	//

	// 구매 시 PopUp
	
	bool GetIsOpened() const {return bIsOpened;}
    void SetbIsOpened(bool bValue) {bIsOpened = bValue;}
	bool GetIsStoreRoot() const {return bIsStoreRoot;}
    void SetbIsStoreRoot(bool bValue) {bIsStoreRoot = bValue;};

	void SetSlotCount(int32 Value) {SlotCount = Value;}
	void SetInvenSlotCount(int32 Value) {InvenSlotCount = Value;}

	void SetItemData(TArray<FGameplayTag> ItemTags, int32 slotCount, UMJInventoryComponent* InvenComp);
};
