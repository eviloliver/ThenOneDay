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
public:
	virtual void NativeConstruct() override;
	
	TArray<UMJInventorySlot*> GetInventorySlot() {return InventorySlots;}
	
};
