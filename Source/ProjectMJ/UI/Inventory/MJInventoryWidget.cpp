// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/MJInventoryWidget.h"
#include "MJInventorySlot.h"
#include "MJInventoryTooltip.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridPanel.h"

void UMJInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	InventorySlots.Empty();
	
	if (!GridPanel ||!InventorySlotClass)
	{
		return;
	}
	
	Tooltip = CreateWidget<UMJInventoryTooltip>(this,TooltipWidgetClass);

	// 격자 비율 조정 (안하면 격자 크기 다 다름)
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
	//
	
	// 격자 Row * Col개 만큼 생성 후 슬롯 배치
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
		InventorySlots[i]->SetPadding(FMargin(5.f));
	}
	//
	
	// Delegate
	for (UMJInventorySlot* InvSlot : InventorySlots)
	{
		if (InvSlot)
		{
			InvSlot->OnMouseEntered.AddDynamic(this,&UMJInventoryWidget::ShowTooltip);
			InvSlot->OnMouseLeaved.AddDynamic(this,&UMJInventoryWidget::HideTooltip);
		}
	}
	//
	
}

void UMJInventoryWidget::ShowTooltip(UMJInventorySlot* InvSlot)
{
	if (!Tooltip)
	{
		UE_LOG(LogTemp, Error, TEXT("Tooltip is null!"));
		return;
	}
	if (!InvSlot)
	{
		UE_LOG(LogTemp, Error, TEXT("InvSlot is null!"));
		return;
	}
	if (InvSlot->GetItemData().Description.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Description is null!"));
		return;
	}
	
	CanvasPanel->AddChildToCanvas(Tooltip);

	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Tooltip->Slot))
	{
		CanvasSlot->SetAutoSize(true);
		FVector2D MousePos;
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this); // DPI 스케일 값
        // scale을 구해야 마우스 좌표가 DPI 보정되어서 가져와진다
		if (GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePos.X, MousePos.Y))
		{
			MousePos /= Scale; 
			CanvasSlot->SetPosition(MousePos);
		}
		else // 드롭할 때 마우스 위치를 위 함수(GetMousePosition)로 못찾아서 대신 아래 방법씀
		{
			// 그냥 일단 드롭 후에는 안뜨게 할개..
			CanvasPanel->RemoveChild(Tooltip);
			// FVector2D ScreenPos = InvSlot->GetScreenPos() / Scale;
			// CanvasSlot->SetPosition(ScreenPos);
		}
	}
	
	Tooltip->SetDescription(InvSlot->GetItemData().Description);
	Tooltip->SetItemName(InvSlot->GetItemData().ItemID);
}

void UMJInventoryWidget::HideTooltip(UMJInventorySlot* InvSlot)
{
	CanvasPanel->RemoveChild(Tooltip);
}