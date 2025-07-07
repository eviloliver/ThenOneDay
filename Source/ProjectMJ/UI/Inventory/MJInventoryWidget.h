// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJInventorySlot.h"
#include "Blueprint/UserWidget.h"
#include "MJInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UGridPanel* GridPanel;
	
	UPROPERTY(meta = (BindWidget))
	TArray<UMJInventorySlot*> InventorySlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	TSubclassOf<UMJInventorySlot> InventorySlotClass;
	
	int32 SlotIndex;
	bool bIsOccupied;

	// 아래 숫자 조절로 인벤토리 칸 조절 가능함
	int32 Row = 6;
	int32 Col = 7;
public:
	virtual void NativeConstruct() override;

	bool GetIsOccupied(){return bIsOccupied;}
	void SetIsOccupied(bool b){bIsOccupied = b;}
	
	TArray<UMJInventorySlot*> GetInventorySlot() {return InventorySlots;}
	
};
