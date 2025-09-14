// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/MJInventoryComponent.h"
#include "ItemDataRow.h"
#include "MJInventorySlot.h"
#include "MJInventoryWidget.h"
#include "TG/MJGameInstance.h"
#include "UI/MJHUDWidget.h"
#include "UI/MJUIManagerSubsystem.h"
#include "UI/Store/MJStoreComponent.h"
#include "UI/Store/MJStoreWidget.h"

UMJInventoryComponent::UMJInventoryComponent()
{
	ItemEmptyData.ItemTag = FGameplayTag::EmptyTag;
	ItemEmptyData.ItemCount = 0;
}
void UMJInventoryComponent::PickUpItem(FGameplayTag ItemTag, int32 Count, UMJStoreWidget* StoreWidget) 
{
#pragma region InventoryRef
	UMJGameInstance* GI = GetWorld()->GetGameInstance<UMJGameInstance>();
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
		if (StoreWidget)
		{
			StoreWidget->UpdateInventorySlot();
		}
		
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
		// if (NewItemData.Position == -1)
		// {
		// 	UE_LOG(LogTemp,Error,TEXT("자리가 부족합니다"));
		// 	return;
		// }
		
		ItemInInventory.Add(ItemTag, NewItemData);
		ItemTags.Add(ItemTag);
	}
	UpdateSlot(ItemTag);
}

void UMJInventoryComponent::DropItem(FGameplayTag ItemTag, int32 count)
{
	ItemInInventory[ItemTag].ItemCount -= count;
	if (ItemInInventory[ItemTag].ItemCount <= 0)
	{
		ItemEmptyData.Position = ItemInInventory[ItemTag].Position;
		UpdateSlot(ItemEmptyData.ItemTag);
		ItemInInventory.Remove(ItemTag);
		return;
	}

	UpdateSlot(ItemTag);
}

void UMJInventoryComponent::UpdateSlot(FGameplayTag ItemTag)
{
#pragma region Inventory
	UMJGameInstance* GI = GetWorld()->GetGameInstance<UMJGameInstance>();
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
	if (ItemTag == ItemEmptyData.ItemTag)
    {
		InventorySlot[ItemEmptyData.Position]->SetInventoryItemData({FGameplayTag::EmptyTag, 0, ItemEmptyData.Position});
		InventorySlot[ItemEmptyData.Position]->SetItemCount(0);
		InventorySlot[ItemEmptyData.Position]->SetText(FText::GetEmpty());
		InventorySlot[ItemEmptyData.Position]->SetImage(nullptr);

		return;	
    }

	InventorySlot[ItemInInventory[ItemTag].Position]->SetInventoryItemData(ItemInInventory[ItemTag]);
	InventorySlot[ItemInInventory[ItemTag].Position]->SetItemData(*GI->ItemDataTable->FindRow<FItemDataRow>(ItemTag.GetTagName(),TEXT("Inventory")));
	
	InventorySlot[ItemInInventory[ItemTag].Position]->SetItemCount(ItemInInventory[ItemTag].ItemCount);
	InventorySlot[ItemInInventory[ItemTag].Position]->SetText(GI->ItemDataTable->FindRow<FItemDataRow>(ItemTag.GetTagName(),TEXT("Inventory"))->ItemID);
	InventorySlot[ItemInInventory[ItemTag].Position]->SetImage(GI->ItemDataTable->FindRow<FItemDataRow>(ItemTag.GetTagName(),TEXT("Inventory"))->Icon);


}

void UMJInventoryComponent::ZeroItem(FGameplayTag ItemTag)
{
	if (ItemInInventory[ItemTag].ItemCount == 0)
	{
		ItemTag = FGameplayTag::EmptyTag;
	}
	
}
