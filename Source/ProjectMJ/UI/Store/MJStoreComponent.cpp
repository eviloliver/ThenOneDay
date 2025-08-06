// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store/MJStoreComponent.h"
#include "MJMerchandiseSlot.h"
#include "MJStoreWidget.h"
#include "Components/Button.h"
#include "Dialogue/MJDialogueChoiceWidget.h"
#include "Dialogue/MJDialogueWidget.h"
#include "TG/MJGameInstanceTG.h"
#include "UI/MJHUDWidget.h"
#include "UI/MJUIManagerSubsystem.h"
#include "UI/Inventory/ItemDataRow.h"

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
		// UI 갱신
		//MerSlot[i]->SetStoreComp(this);
		MerSlot[i]->SetItemTag(GI->ItemDataTable->FindRow<FItemDataRow>(MerchandiseRow[i], TEXT(""))->ItemTag);
		MerSlot[i]->SetImage(GI->ItemDataTable->FindRow<FItemDataRow>(MerchandiseRow[i], TEXT(""))->Icon);
		MerSlot[i]->SetItemName(GI->ItemDataTable->FindRow<FItemDataRow>(MerchandiseRow[i], TEXT(""))->ItemID);
		MerSlot[i]->SetDescription(GI->ItemDataTable->FindRow<FItemDataRow>(MerchandiseRow[i], TEXT(""))->Description);
		MerSlot[i]->SetPrice(GI->ItemDataTable->FindRow<FItemDataRow>(MerchandiseRow[i], TEXT(""))->Price);

		// 바인딩
		MerSlot[i]->GetButton()->OnClicked.AddDynamic(this, &ThisClass::TryPurchase);
	}
}

void UMJStoreComponent::TryPurchase()
{
	// 구매하시겠어요 팝업을 뜨게 함
	GetWorld()->GetGameInstance<UMJGameInstanceTG>()->
	GetSubsystem<UMJUIManagerSubsystem>()->GetHUDWidget()->GetStoreWidget()->Onclicked_Slot();
}

// void UMJStoreComponent::UpdateQuantity(int32 Quantity)
// {
// 	CurrentQuantity += Quantity;
//  	OnQuantityUpdated.Broadcast(CurrentQuantity);
// }

void UMJStoreComponent::DialogueEnd()
{
	SetIndex(0);
	bIsOpened = true;
}

void UMJStoreComponent::SetChoiceWidgetText()
{
	GetDialogueWidget()->GetDialogueChoiceWidget()->SetTextBlock(
     	GetCurrentRow()->Choices[0].ChoiceText,
     	GetCurrentRow()->Choices[1].ChoiceText,
     	GetCurrentRow()->Choices[2].ChoiceText);
}

void UMJStoreComponent::BindButtons()
{
	if (CurrentIndex == 0)
	{
		GetDialogueWidget()->GetDialogueChoiceWidget()->GetQuestButton()->OnClicked.AddDynamic(this, &UMJStoreComponent::ShowStory);
		GetDialogueWidget()->GetDialogueChoiceWidget()->GetPointButton()->OnClicked.AddDynamic(this, &UMJStoreComponent::ShowStore);
		GetDialogueWidget()->GetDialogueChoiceWidget()->GetExitButton()->OnClicked.AddDynamic(this, &UMJStoreComponent::ExitDialogue);
	}
	SetChoiceWidgetText();
}

void UMJStoreComponent::ShowStory() // Story 클릭 시 
{
	++ CurrentIndex;
	if (!IsDialogueEnd())
	{
		FloatLine();
		GetDialogueWidget()->SetImageOpacity(GetCurrentRow()->Speaker);
	}
	GetDialogueWidget()->GetDialogueChoiceWidget()->SetVisibility(ESlateVisibility::Hidden);
}

void UMJStoreComponent::ShowStore()
{
	CurrentIndex = DialogueTable->GetRowNames().Num() - 1; 
	GetDialogueWidget()->SetTextBlock(GetCurrentRow()->ScriptForStore, GetCurrentRow()->Speaker);
	GetDialogueWidget()->StartTyping(GetCurrentRow()->ScriptForStore,0.05);
	GetDialogueWidget()->SetImageOpacity(GetCurrentRow()->Speaker);
	GetDialogueWidget()->GetDialogueChoiceWidget()->SetVisibility(ESlateVisibility::Hidden);
	bIsStoreRoot = true;
}

void UMJStoreComponent::ExitDialogue()
{
	CurrentIndex =  DialogueTable->GetRowNames().Num() -1;
	GetDialogueWidget()->SetTextBlock(GetCurrentRow()->ScriptForExit, GetCurrentRow()->Speaker);
	GetDialogueWidget()->StartTyping(GetCurrentRow()->ScriptForExit,0.05);
	GetDialogueWidget()->SetImageOpacity(GetCurrentRow()->Speaker);
	GetDialogueWidget()->GetDialogueChoiceWidget()->SetVisibility(ESlateVisibility::Hidden);
}


