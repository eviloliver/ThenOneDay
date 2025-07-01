// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/MJInventoryComponent.h"
#include "InventoryItemData.h"
#include "MJInventorySlot.h"
#include "MJInventoryWidget.h"
#include "TG/MJGameInstanceTG.h"
#include "UI/MJHUDWidget.h"
#include "UI/MJUIManagerSubsystem.h"

UMJInventoryComponent::UMJInventoryComponent()
{

}

void UMJInventoryComponent::SetItemDataToWidget(FName ItemName)
{
	UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
	if (!GI || !GI->ItemDataTable)
	{
		UE_LOG(LogTemp,Error,TEXT("게임인스턴스를 제대로 못 받아왔나보다"));
		return;
		// 못 받아왔던 이유 -> GameInstance를 다른 걸 쓰고 있었음.. 프로젝트 세팅에서 수정 잘하자
	}
	
	UMJUIManagerSubsystem* UIManager = GI->GetSubsystem<UMJUIManagerSubsystem>();
	if (!UIManager)
	{
		return; // 잘 받아오는거 확인 완료
	}
	
	TArray<UMJInventorySlot*> InventorySlot = UIManager->GetHUDWidget()->GetInventoryWidget()->GetInventorySlot();
	if (!UIManager->GetHUDWidget())
	{
		return;
	}
	if (!UIManager->GetHUDWidget()->GetInventoryWidget())
	{
		return;
	}
	
	for (int i = 0; i < InventorySlot.Num(); i++)
	{
		if (!InventorySlot[i])
		{
			return;
		}
		
		if (InventorySlot[i]->GetItemTexture() == nullptr)
		{			
			UE_LOG(LogTemp,Error,TEXT("인벤이 비어있다~"));
			InventorySlot[i]->SetText(GI->ItemDataTable->FindRow<FInventoryItemData>(ItemName,TEXT("Inventory"))->ItemID);
			InventorySlot[i]->SetImage(GI->ItemDataTable->FindRow<FInventoryItemData>(ItemName,TEXT("Inventory"))->Icon);
			// 아이템을 주웟을때 tmap에다가 정보를 넣어....
			return;
		}
	}			
}

void UMJInventoryComponent::PickUpItem(FName ItemName) // 
{
	if (ItemInInventory.Contains(ItemName))
	{
		ItemInInventory[ItemName].ItemCount++;
	}
	else
	{
		FItemData NewItem;
		NewItem.ItemName = ItemName;
		NewItem.ItemCount = 1;
		//안겹치게 아이템 위치 정해주는 코드
		ItemInInventory.Add(ItemName,NewItem);
	}
}

void UMJInventoryComponent::DropItem(FName ItemName)
{
	
}
