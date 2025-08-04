// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store/MJMerchandiseSlot.h"
#include "GameplayTagContainer.h"
#include "UI/Store/MJPopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMJMerchandiseSlot::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this,&UMJMerchandiseSlot::OnClicked_Slot);
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
	};
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

void UMJMerchandiseSlot::OnClicked_Slot()
{
	OnMerchandiseSlotEvent.Broadcast(ItemTag, Price);
}
