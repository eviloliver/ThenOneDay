// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store/MJStoreComponent.h"
#include "MJMerchandiseSlot.h"
#include "MJStoreWidget.h"
#include "TG/MJGameInstanceTG.h"
#include "UI/MJHUDWidget.h"
#include "UI/MJUIManagerSubsystem.h"
#include "UI/Inventory/ItemDataRow.h"

// Sets default values for this component's properties
UMJStoreComponent::UMJStoreComponent()
{

}

void UMJStoreComponent::UpdateStore()
{
	UMJGameInstanceTG* GI = GetWorld()->GetGameInstance<UMJGameInstanceTG>();
	if (!GI ||!GI->ItemDataTable)
	{
		return;
	}

	TArray<UMJMerchandiseSlot*> MerSlot = GI->GetSubsystem<UMJUIManagerSubsystem>()->GetHUDWidget()->GetStoreWidget()->GetMerchandiseSlots();
	if (!GI->GetSubsystem<UMJUIManagerSubsystem>()
		|| !GI->GetSubsystem<UMJUIManagerSubsystem>()->GetHUDWidget()
		|| !GI->GetSubsystem<UMJUIManagerSubsystem>()->GetHUDWidget()->GetStoreWidget()
		)
	{
		return;
	}
	for (int i = 0; i < MerSlot.Num(); i++)
	{
		if (!MerSlot[i])
		{
			return;
		}
	}

	TArray<FName> MerchandiseRow;
	TArray<FName> Rownames = GI->ItemDataTable->GetRowNames();

	for (const FName& RowName : Rownames)
	{
		FItemDataRow* Row = GI->ItemDataTable->FindRow<FItemDataRow>(RowName, TEXT(""));
		if (Row && Row->IsMerchandise) // 상품인 것들만 모아서
		{
			MerchandiseRow.Add(RowName); // 새로 담아내자
		}
	}
	
	SlotCount = FMath::Min(MerSlot.Num(), MerchandiseRow.Num());
	
	for (int i = 0; i < SlotCount; i++)
	{
		MerSlot[i]->SetImage(GI->ItemDataTable->FindRow<FItemDataRow>(MerchandiseRow[i], TEXT(""))->Icon);
		MerSlot[i]->SetItemName(GI->ItemDataTable->FindRow<FItemDataRow>(MerchandiseRow[i], TEXT(""))->ItemID);
		MerSlot[i]->SetDescription(GI->ItemDataTable->FindRow<FItemDataRow>(MerchandiseRow[i], TEXT(""))->Description);
		MerSlot[i]->SetPrice(GI->ItemDataTable->FindRow<FItemDataRow>(MerchandiseRow[i], TEXT(""))->Price);
	}
}