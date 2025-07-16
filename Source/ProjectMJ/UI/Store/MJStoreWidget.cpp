// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store/MJStoreWidget.h"

#include "MJStoreComponent.h"
#include "Components/ScrollBox.h"
#include "UI/Store/MJMerchandiseSlot.h"

void UMJStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!ScrollBox || !MerchandiseSlotClass) 
    {
    	UE_LOG(LogTemp,Error,TEXT("머가 없다"));
    	return;
    }
	
	for (int i = 0; i < 5; i++)
    {
    	UE_LOG(LogTemp,Error,TEXT("Widget안에 슬롯 생성햇다"));
        UMJMerchandiseSlot* NewSlot = CreateWidget<UMJMerchandiseSlot>(this, MerchandiseSlotClass);
        ScrollBox->AddChild(NewSlot);
        MerchandiseSlots.Add(NewSlot);
    }
}

void UMJStoreWidget::ShowMerchandiseSlots(int32 SlotCount) // 업데이트 할라면 nativeConstruct에 있으면 안될 것 같음..
{

}
