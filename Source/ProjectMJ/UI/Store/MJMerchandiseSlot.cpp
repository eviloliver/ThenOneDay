// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store/MJMerchandiseSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMJMerchandiseSlot::SetImage(UTexture2D* ItemTexture)
{
	if (MerImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(ItemTexture);
		Brush.ImageSize = FVector2D(40,40);
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
	if (Price)
	{
		Price->SetText(FText::AsNumber(price));	
	}
}