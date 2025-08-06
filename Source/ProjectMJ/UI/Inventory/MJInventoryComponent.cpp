// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/MJInventoryComponent.h"
#include "ItemDataRow.h"
#include "MJInventorySlot.h"
#include "MJInventoryWidget.h"
#include "TG/MJGameInstanceTG.h"
#include "UI/MJHUDWidget.h"
#include "UI/MJUIManagerSubsystem.h"

UMJInventoryComponent::UMJInventoryComponent()
{
	
}
void UMJInventoryComponent::PickUpItem(FGameplayTag ItemTag, int32 Count) 
{
#pragma region InventoryRef
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
	}
#pragma endregion
	if (Count == 0)
	{
		return;
	}
	
	if (ItemInInventory.Contains(ItemTag))
	{
		ItemInInventory[ItemTag].ItemCount += Count;
	}
	else
	{
		FInventoryItemData NewItemData;
		NewItemData.ItemTag = ItemTag;
		NewItemData.ItemCount = Count;

		// for문 순회를 통해 공백을 만나면 그 위치를 반환해서 넣기
		for (int i = 0; i < InventorySlot.Num(); i++)
		{
			if (!InventorySlot[i]->bIsOccupied)
			{
				NewItemData.Position = InventorySlot[i]->SlotPosition;
				InventorySlot[i]->SetIsOccupied(true);
				break;
			}
		}
		if (NewItemData.Position == -1)
		{
			UE_LOG(LogTemp,Error,TEXT("자리가 부족합니다"));
			return;
		}
		
		ItemInInventory.Add(ItemTag, NewItemData);
	}
	UpdateSlot(ItemTag);
}

void UMJInventoryComponent::DropItem(FGameplayTag ItemTag)
{
	// 티맵의 아이템을 지워야 하지 않을까
	//ItemInInventory.Remove(ItemName); // 나중에 전체가 아니라 일부만 버리고 싶게 할 때는 입력받은 숫자만큼 카운트만 줄이기??
}

void UMJInventoryComponent::UpdateSlot(FGameplayTag ItemTag)
{
#pragma region Inventory
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
	}
#pragma endregion inventory
	// Test
	InventorySlot[ItemInInventory[ItemTag].Position]->SetInventoryItemData(ItemInInventory[ItemTag]);
	InventorySlot[ItemInInventory[ItemTag].Position]->SetItemData(*GI->ItemDataTable->FindRow<FItemDataRow>(ItemTag.GetTagName(),TEXT("Inventory")));
	
	InventorySlot[ItemInInventory[ItemTag].Position]->SetItemCount(ItemInInventory[ItemTag].ItemCount);
	InventorySlot[ItemInInventory[ItemTag].Position]->SetText(GI->ItemDataTable->FindRow<FItemDataRow>(ItemTag.GetTagName(),TEXT("Inventory"))->ItemID);
	InventorySlot[ItemInInventory[ItemTag].Position]->SetImage(GI->ItemDataTable->FindRow<FItemDataRow>(ItemTag.GetTagName(),TEXT("Inventory"))->Icon);
}
