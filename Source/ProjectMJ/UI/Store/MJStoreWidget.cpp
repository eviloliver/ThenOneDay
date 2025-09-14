// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store/MJStoreWidget.h"
#include "MJPopupWidget.h"
#include "MJSalesSlot.h"
#include "Character/Component/MJPlayerStatComponent.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "UI/Store/MJMerchandiseSlot.h"

void UMJStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 상점에 슬롯채우기
	if (!ScrollBox || !MerchandiseSlotClass) 
    {
    	UE_LOG(LogTemp,Error,TEXT("상점용 슬롯 클래스가 없다"));
    	return;
    }
	
	for (int i = 0; i < 4; i++)
    {
        UMJMerchandiseSlot* NewSlot = CreateWidget<UMJMerchandiseSlot>(this, MerchandiseSlotClass);
		ScrollBox->AddChild(NewSlot);
        MerchandiseSlots.Add(NewSlot);
    }
	//
		
	//Delegate
	PurchasePopup->SetVisibility(ESlateVisibility::Hidden);
	PurchasePopup->GetYesButton()->OnClicked.AddDynamic(this,&UMJStoreWidget::OnClicked_PurchasePopupYes);
	PurchasePopup->GetNoButton()->OnClicked.AddDynamic(this,&UMJStoreWidget::OnClicked_PurchasePopupNo);

	SellPopup->SetVisibility(ESlateVisibility::Hidden);
	SellPopup->GetYesButton()->OnClicked.AddDynamic(this,&UMJStoreWidget::OnClicked_SellPopupYes);
	SellPopup->GetNoButton()->OnClicked.AddDynamic(this,&UMJStoreWidget::OnClicked_SellPopupNo);
	//
}

void UMJStoreWidget::UpdateInventorySlot()
{
	if (!InvenScrollBox || !InventorySlotClass) 
	{
		return;
	}
	
	UMJSalesSlot* NewSlot = CreateWidget<UMJSalesSlot>(this, InventorySlotClass);
	InvenScrollBox->AddChild(NewSlot);
	InventorySlots.Add(NewSlot);
}

void UMJStoreWidget::SetStatComponent(UMJPlayerStatComponent* StatComp)
{
	StatCompRef = StatComp;
	if (StatCompRef)
	{
		SetAvailableGold(StatCompRef->GetGold()); // 초기화
    	StatCompRef->OnGoldChange.AddDynamic(this,&UMJStoreWidget::SetAvailableGold);
	}
}

void UMJStoreWidget::SetAvailableGold(int32 Gold)
{
	AvailableGold->SetText(FText::FromString(FString::FromInt(Gold)));
}

void UMJStoreWidget::Onclicked_PurchaseButton()
{
	PurchasePopup->SetVisibility(ESlateVisibility::Visible);
}

void UMJStoreWidget::OnClicked_PurchasePopupYes()
{
	PurchasePopup->SetVisibility(ESlateVisibility::Hidden);
	OnClickedPurchaseYes.Broadcast();
}

void UMJStoreWidget::OnClicked_PurchasePopupNo()
{
	PurchasePopup->SetVisibility(ESlateVisibility::Hidden);
}

void UMJStoreWidget::Onclicked_SellButton()
{
	SellPopup->SetVisibility(ESlateVisibility::Visible);
}

void UMJStoreWidget::OnClicked_SellPopupYes()
{
	SellPopup->SetVisibility(ESlateVisibility::Hidden);
	OnClickedSellYes.Broadcast();
}

void UMJStoreWidget::OnClicked_SellPopupNo()
{
	SellPopup->SetVisibility(ESlateVisibility::Hidden);
}

void UMJStoreWidget::CloseWidget()
{
	// 팝업이 열린 상태로 상점을 닫는 경우, 나중에 다시 켰을 때 팝업이 꺼져있게 하기 위함
	PurchasePopup->SetVisibility(ESlateVisibility::Hidden);
	SellPopup->SetVisibility(ESlateVisibility::Hidden);

	// 늘려놨던 개수들도 리셋
	for (int i =0; i < MerchandiseSlots.Num(); i++)
	{
		MerchandiseSlots[i]->InitializeQuantity();
	}
	for (int i =0; i < InventorySlots.Num(); i++)
	{
		InventorySlots[i]->InitializeQuantity();
	}
	
}


