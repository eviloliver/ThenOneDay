// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/MJInventorySlot.h"
#include "MJDragWidget.h"
#include "MJInventoryDragDropOperation.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMJInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	
	Texture = nullptr;
	InventoryData = { NAME_None, 0, SlotPosition }; // 공백아이템
}

void UMJInventorySlot::SetImage(UTexture2D* ItemTexture)
{
	//this->Texture = ItemTexture;
	if (Image)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(ItemTexture);
		Image->SetBrush(Brush);
		Image->SetBrushSize({200,200}); // 텍스처 사이즈 조절용 // 더 이상 사용되지 않는다면서 왜 적용은 되는거 같을까
		Image->SetOpacity(1.0); // 이미지 들어가기전에 자꾸 인벤배경색(반투명)을 가려서 에디터에서 0으로 해놓은거 먹으면 밝혀주는 용도
	}
	if (!ItemTexture)
	{
		Image->SetOpacity(0.0);
	}
	
}

void UMJInventorySlot::SetText(FText newtext)
{
	if (Text)
	{
		Text->SetText(newtext);
	}
}

FReply UMJInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!InventoryData.IsEmpty())
	{
		if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
        {
        	UE_LOG(LogTemp, Log, TEXT("드래그 감지 시작 슬롯: %d, 아이템: %s, 아이템 : %s"), InventoryData.Position, *InventoryData.ItemName.ToString(), *ItemData.ItemID.ToString());
              	return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
        }
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UMJInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation) // Jisoo : 드래그 시 작동하는 함수
{
	UMJInventoryDragDropOperation* DragOperation = NewObject<UMJInventoryDragDropOperation>();
    DragOperation->SourceSlot = this;
    DragOperation->InventoryItemData = InventoryData;
    DragOperation->ItemData = ItemData;
	UE_LOG(LogTemp, Log, TEXT("드래그 감지 시작 슬롯: %d, 아이템: %s, 아이템 : %s"), DragOperation->InventoryItemData.Position, * DragOperation->InventoryItemData.ItemName.ToString(), *DragOperation->ItemData.ItemID.ToString());

	UMJDragWidget* DragWidget = CreateWidget<UMJDragWidget>(GetWorld(),DragWidgetClass);
    if (DragWidget)
    {
    	DragWidget->SetDragImage(DragOperation->ItemData.Icon);
    	DragOperation->DefaultDragVisual = DragWidget;
    }
	
	OutOperation = DragOperation; // jisoo : 내가 만든 드래그 시스템의 포인터를 할당하는 것.
	
}

bool UMJInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	UMJInventoryDragDropOperation* DragOperation = Cast<UMJInventoryDragDropOperation>(InOperation);
	
	if (!DragOperation)
	{
		return false;
	}
	
	if (DragOperation && DragOperation->SourceSlot && DragOperation->SourceSlot != this)
	{
		if (!InventoryData.IsEmpty())
		{
			UE_LOG(LogTemp, Error, TEXT("드롭완료"));
            FInventoryItemData Temp = InventoryData;
            FItemDataRow Temp2 = ItemData; 
            
            // 드래그 받는 슬롯의 정보를 갱신
            InventoryData =  DragOperation->InventoryItemData;
            ItemData = DragOperation->ItemData;
            
            // 드래그 눌렸던 슬롯의 정보를 갱신
            DragOperation->SourceSlot->SetInventoryItemData(Temp);
            DragOperation->SourceSlot->SetItemData(Temp2);

			//바뀐 정보를 바탕으로 UI 갱신
            SetImage(ItemData.Icon);
            SetText(ItemData.ItemID);
            SetItemCount(InventoryData.ItemCount);
            DragOperation->SourceSlot->SetImage(Temp2.Icon);
            DragOperation->SourceSlot->SetText(Temp2.ItemID);
            DragOperation->SourceSlot->SetItemCount(Temp.ItemCount);
		}
		else // 공백칸과의 교환일 시
		{
			UE_LOG(LogTemp, Error, TEXT("<공백과 교환>"));
			InventoryData =  DragOperation->InventoryItemData;
			ItemData = DragOperation->ItemData;
			
			DragOperation->SourceSlot->SetInventoryItemData({ NAME_None, 0, SlotPosition });

			SetImage(ItemData.Icon);
			SetText(ItemData.ItemID);
			SetItemCount(InventoryData.ItemCount);
			
			DragOperation->SourceSlot->SetImage(nullptr);
			DragOperation->SourceSlot->SetText(FText::GetEmpty());
			DragOperation->SourceSlot->ItemCount->SetText(FText::GetEmpty());
		}
		
		return true;
	}
	return false;
}

