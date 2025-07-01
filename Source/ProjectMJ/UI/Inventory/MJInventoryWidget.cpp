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

	// 격자 생성
	for (int Row = 0; Row < 4; ++Row)
	{
		for (int Col = 0; Col < 4; ++Col)
		{
			UMJInventorySlot* NewSlot = CreateWidget<UMJInventorySlot>(this, InventorySlotClass);
			GridPanel->AddChildToGrid(NewSlot, Row, Col);
			InventorySlots.Add(NewSlot);
		}
	}
}
