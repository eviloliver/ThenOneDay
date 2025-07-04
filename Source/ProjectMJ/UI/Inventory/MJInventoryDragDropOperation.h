// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJInventoryComponent.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDataRow.h"
#include "MJInventoryDragDropOperation.generated.h"
/**
 * 
 */
class UMJInventorySlot;
UCLASS()
class PROJECTMJ_API UMJInventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UMJInventorySlot* SourceSlot;

	UPROPERTY()
	FInventoryItemData InventoryItemData;

	UPROPERTY()
	FItemDataRow ItemData;
};
