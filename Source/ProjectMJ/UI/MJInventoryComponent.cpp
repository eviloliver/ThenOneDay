// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MJInventoryComponent.h"

#include "InventoryItemData.h"


void UMJInventoryComponent::SetItemData(UDataTable* ItemDataTable, int32 Index, UMJInventoryWidget* InventoryWidget)
{
	InventoryWidget->SetText(ItemDataTable->FindRow<FInventoryItemData>(RowNames[Index],TEXT("Inventory"))->ItemID);
}
