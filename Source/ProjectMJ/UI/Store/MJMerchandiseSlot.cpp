// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store/MJMerchandiseSlot.h"
#include "GameplayTagContainer.h"
#include "MJStoreComponent.h"
#include "UI/Store/MJPopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMJMerchandiseSlot::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &ThisClass::TryPurchase);
	PlusButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked_PlusButton);
	MinusButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked_MinusButton);
	PlusTenButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked_PlusTenButton);
	MinusTenButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked_MinusTenButton);
}

void UMJMerchandiseSlot::SetItemTag(FGameplayTag tag)
{
	ItemTag = tag;
}

void UMJMerchandiseSlot::SetImage(UTexture2D* ItemTexture)
{
	if (MerImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(ItemTexture);
		Brush.ImageSize = FVector2D(80,80);
		MerImage->SetBrush(Brush);
		MerImage->SetOpacity(1.0);
	}
}

void UMJMerchandiseSlot::SetItemName(FText itemName)
{
	if (ItemName)
	{
		ItemName->SetText(itemName);
	}
}

void UMJMerchandiseSlot::SetDescription(FText description)
{
	if (Description)
	{
		Description->SetText(description);
	}
}

void UMJMerchandiseSlot::SetPrice(int price)
{
	if (PriceText)
	{
		PriceText->SetText(FText::AsNumber(price));	
	}
	Price = price;
}

void UMJMerchandiseSlot::InitializeQuantity()
{
	Quantity = 0;
	SetQuantity(Quantity);
}

void UMJMerchandiseSlot::SetQuantity(int32 delta)
{
	QuantityText->SetText(FText::AsNumber(delta));
	Quantity = delta;
}

void UMJMerchandiseSlot::TryPurchase()
{
	OnMerchandiseSlotEvent.Broadcast(ItemTag,Price,Quantity);
}

void UMJMerchandiseSlot::OnClicked_PlusButton()
{
	Quantity ++;
	SetQuantity(Quantity);
}

void UMJMerchandiseSlot::OnClicked_MinusButton()
{
	if (Quantity == 0)
	{
		SetQuantity(Quantity);
		return;
	}
	
	Quantity --;
	SetQuantity(Quantity);
}

void UMJMerchandiseSlot::OnClicked_PlusTenButton()
{
	Quantity += 10;
	SetQuantity(Quantity);
}

void UMJMerchandiseSlot::OnClicked_MinusTenButton()
{
	Quantity -= 10;
	if (Quantity <= 0)
	{
		Quantity = 0;
		// SetQuantity(Quantity);
		// return;
	}
	SetQuantity(Quantity);
}





