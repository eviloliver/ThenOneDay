// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MJInventoryComponent.generated.h"

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
	FName ItemName;
	
	UPROPERTY()
	int32 ItemCount;

	UPROPERTY()
	int32 Position;

	bool IsEmpty() const
	{
		return ItemCount == 0;
	}
};


class UMJInventorySlot;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UMJInventoryComponent();

public:	
	void PickUpItem(FName ItemName);
	void DropItem(FName ItemName);
	//void ChangeItemPosition(변수고민해라 >> 아마 어떤아이템인지(fname), 개수);
	void UpdateSlot(FName ItemName);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Inventory")
	TMap<FName,FInventoryItemData> ItemInInventory; // 내가 가지고 있는 아이템의 정보 맵
};
