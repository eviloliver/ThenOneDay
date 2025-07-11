// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJInventorySlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "MJInventoryWidget.generated.h"

/**
 * 
 */

class UMJInventorySlot;
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

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UMJInventoryTooltip> TooltipWidgetClass;

	UPROPERTY()
	UMJInventoryTooltip* Tooltip;
	
	int32 SlotIndex;
	bool bIsOccupied;

	// 아래 숫자 조절로 인벤토리 칸 조절 가능함
	int32 Row = 6;
	int32 Col = 7;
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ShowTooltip(UMJInventorySlot* InvSlot);

	UFUNCTION()
	void HideTooltip(UMJInventorySlot* InvSlot);
	bool GetIsOccupied() {return bIsOccupied;}
	void SetIsOccupied(bool b) {bIsOccupied = b;}

	void SetCanvasPanel();
	
	TArray<UMJInventorySlot*> GetInventorySlot() {return InventorySlots;}
	
};
