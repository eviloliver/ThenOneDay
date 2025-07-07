// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/MJInventoryWidget.h"

#include "Components/GridPanel.h"

void UMJInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventorySlots.Empty();

	if (!GridPanel ||!InventorySlotClass)
	{
		return;
	}
	// 격자 비율 맞추기
	GridPanel->SetColumnFill(0, 1.0f);
	GridPanel->SetRowFill(0, 1.0f);

	for (int i = 1; i < Row; ++i)
	{
		for (int j = 1; j < Col; ++j)
		{
			GridPanel->SetRowFill(i, 1.0f);
			GridPanel->SetColumnFill(j, 1.0f);
		}
	}
	
	// 격자 생성
	for (int i = 0; i < Row; ++i)
	{
		for (int j = 0; j < Col; ++j)
		{
			UMJInventorySlot* NewSlot = CreateWidget<UMJInventorySlot>(this, InventorySlotClass);
			GridPanel->AddChildToGrid(NewSlot, i, j);
			InventorySlots.Add(NewSlot);
		}
	}
	for (int i = 0; i < InventorySlots.Num(); i++)
	{
		InventorySlots[i]->SlotPosition = i;
	}

}
