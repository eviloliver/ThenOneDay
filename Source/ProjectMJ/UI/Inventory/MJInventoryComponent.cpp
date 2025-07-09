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

void UMJInventoryComponent::PickUpItem(FName ItemName) 
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

	
	if (ItemInInventory.Contains(ItemName)) // 인벤토리 내에 ItemName을 가진 아이템이 있다면 개수만 늘리고 같은 칸에 들어가야 함
	{
		ItemInInventory[ItemName].ItemCount++;
	}
	else // 인벤에 없는 템이라면 
	{
		FInventoryItemData NewItem;
		NewItem.ItemName = ItemName;
		NewItem.ItemCount = 1;

		// for문 순회를 통해 공백을 만나면 그 위치를 반환해서 넣기
		for (int i = 0; i < InventorySlot.Num(); i++)
		{
			if (!InventorySlot[i]->bIsOccupied)
			{
				NewItem.Position = InventorySlot[i]->SlotPosition;
				InventorySlot[i]->SetIsOccupied(true);
				break;
			}
		}
		if (NewItem.Position == -1)
		{
			UE_LOG(LogTemp,Error,TEXT("자리가 부족합니다"));
			return;
		}
		ItemInInventory.Add(ItemName,NewItem); // 구조체에 위정보를 가진 새로운 아이템 추가
	}
	
	// 추가된 아이템 정보를 위젯으로 업데이트
	UpdateSlot(ItemName);
}

void UMJInventoryComponent::DropItem(FName ItemName)
{
	// 티맵의 아이템을 지워야 하지 않을까
	ItemInInventory.Remove(ItemName); // 나중에 전체가 아니라 일부만 버리고 싶게 할 때는 입력받은 숫자만큼 카운트만 줄이기??
}

void UMJInventoryComponent::UpdateSlot(FName ItemName)
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
	InventorySlot[ItemInInventory[ItemName].Position]->SetInventoryItemData(ItemInInventory[ItemName]);
	InventorySlot[ItemInInventory[ItemName].Position]->SetItemData(*GI->ItemDataTable->FindRow<FItemDataRow>(ItemName,TEXT("Inventory")));
	
	InventorySlot[ItemInInventory[ItemName].Position]->SetItemCount(ItemInInventory[ItemName].ItemCount);
	InventorySlot[ItemInInventory[ItemName].Position]->SetText(GI->ItemDataTable->FindRow<FItemDataRow>(ItemName,TEXT("Inventory"))->ItemID);
	InventorySlot[ItemInInventory[ItemName].Position]->SetImage(GI->ItemDataTable->FindRow<FItemDataRow>(ItemName,TEXT("Inventory"))->Icon);
}
