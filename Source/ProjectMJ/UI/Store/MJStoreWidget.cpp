// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store/MJStoreWidget.h"

#include "MJPopupWidget.h"
#include "MJStoreComponent.h"
#include "Character/Component/MJPlayerStatComponent.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
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
        UMJMerchandiseSlot* NewSlot = CreateWidget<UMJMerchandiseSlot>(this, MerchandiseSlotClass);
		ScrollBox->AddChild(NewSlot);
        MerchandiseSlots.Add(NewSlot);
    }
	
	Popup->SetVisibility(ESlateVisibility::Hidden);
	Popup->GetYesButton()->OnClicked.AddDynamic(this,&UMJStoreWidget::OnClicked_PopupYes);
	Popup->GetNoButton()->OnClicked.AddDynamic(this,&UMJStoreWidget::OnClicked_PopupNo);
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

void UMJStoreWidget::Onclicked_Slot()
{
	Popup->SetVisibility(ESlateVisibility::Visible);
	for (int i =0; i < MerchandiseSlots.Num(); i++)
	{
		MerchandiseSlots[i]->GetButton()->SetIsEnabled(false);
	}
}

void UMJStoreWidget::OnClicked_PopupYes()
{
	Popup->SetVisibility(ESlateVisibility::Hidden);
	for (int i =0; i < MerchandiseSlots.Num(); i++)
	{
		MerchandiseSlots[i]->GetButton()->SetIsEnabled(true);
	}
	OnClickedYes.Broadcast();
}

void UMJStoreWidget::OnClicked_PopupNo()
{
	Popup->SetVisibility(ESlateVisibility::Hidden);
	for (int i =0; i < MerchandiseSlots.Num(); i++)
	{
		MerchandiseSlots[i]->GetButton()->SetIsEnabled(true);
	}
}

void UMJStoreWidget::CloseWidget()
{
	Popup->SetVisibility(ESlateVisibility::Hidden);
	for (int i =0; i < MerchandiseSlots.Num(); i++)
	{
		MerchandiseSlots[i]->InitializeQuantity();
	}
	
}


