// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "MJInventoryComponent.generated.h"

class UMJStoreComponent;
class UMJStoreWidget;
/**
* Class Description: 인벤토리 컴포넌트 / 캐릭터가 들고 있음 / 인벤토리 위젯의 아이템 정보를 갱신하는 역할
 * Author: 이지수
 * Created Date: 2025.06.26
 * Last Modified By: 
 * Last Modified Date: 
 */
USTRUCT(BlueprintType)
struct FInventoryItemData // 변할 수 있는 데이터값 // 인벤토리 아이템의 정보
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayTag ItemTag;
	
	// UPROPERTY()
	// FName ItemName;
	
	UPROPERTY()
	int32 ItemCount = 0;

	UPROPERTY()
	int32 Position = -1;

	bool IsEmpty() const
	{
		return ItemCount == 0;
	}
};

//class UMJInventorySlot;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UMJInventoryComponent();

protected:
	int32 Position;

	FInventoryItemData ItemEmptyData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TMap<FGameplayTag, FInventoryItemData> ItemInInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FGameplayTag> ItemTags;
public:
	void PickUpItem(FGameplayTag ItemTag, int32 Count, UMJStoreWidget* StoreWidget = nullptr);
	void DropItem(FGameplayTag ItemTag,  int32 count);
	void UpdateSlot(FGameplayTag ItemTag);

	void SetPosition(FGameplayTag ItemTag, int32 NewPosition) {ItemInInventory[ItemTag].Position = NewPosition;};

	void ZeroItem(FGameplayTag ItemTag);
	TMap<FGameplayTag, FInventoryItemData> GetItemInInventory() {return ItemInInventory;}
	TArray<FGameplayTag> GetItemTags() {return ItemTags;}
};
