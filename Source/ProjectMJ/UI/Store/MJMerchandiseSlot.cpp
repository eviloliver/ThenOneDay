// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store/MJMerchandiseSlot.h"


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
	}
	SetQuantity(Quantity);
}
