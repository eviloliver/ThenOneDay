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
struct FItemData // 변하는 데이터값
{
	GENERATED_BODY()

	UPROPERTY()
	FName ItemName;

	UPROPERTY()
	int32 ItemCount;

	UPROPERTY()
	int32 PositionRow; 

	UPROPERTY()
	int32 PositionCol;
	
};

class UMJInventorySlot;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UMJInventoryComponent();

public:	
	void SetItemDataToWidget(FName ItemName);
	void PickUpItem(FName ItemName);
	void DropItem(FName ItemName);
	//void ChangeItemPosition(변수고민해라);
	
protected:
	UPROPERTY()
	TMap<FName,FItemData> ItemInInventory; // 내가 가지고 있는 아이템의 정보
};
