// ThenOneDayStudio


#include "UI/Store/MJStoreSlotBase.h"
#include "GameplayTagContainer.h"
#include "UI/Store/MJPopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMJStoreSlotBase::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &ThisClass::TryPurchase);
	PlusButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked_PlusButton);
	MinusButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked_MinusButton);
	PlusTenButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked_PlusTenButton);
	MinusTenButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked_MinusTenButton);
}

void UMJStoreSlotBase::SetItemTag(FGameplayTag tag)
{
	ItemTag = tag;
}

void UMJStoreSlotBase::SetImage(UTexture2D* ItemTexture)
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

void UMJStoreSlotBase::SetItemName(FText itemName)
{
	if (ItemName)
	{
		ItemName->SetText(itemName);
	}
}

void UMJStoreSlotBase::SetDescription(FText description)
{
	if (Description)
	{
		Description->SetText(description);
	}
}

void UMJStoreSlotBase::SetPrice(int price)
{
	if (PriceText)
	{
		PriceText->SetText(FText::FromString(FString::Printf(TEXT("%d G"), price)));
	}
	Price = price;
}

void UMJStoreSlotBase::InitializeQuantity()
{
	Quantity = 0;
	SetQuantity(Quantity);
}

void UMJStoreSlotBase::SetQuantity(int32 delta)
{
	QuantityText->SetText(FText::AsNumber(delta));
	Quantity = delta;
}

void UMJStoreSlotBase::TryPurchase()
{
	UE_LOG(LogTemp, Display, TEXT("TryPurchase BUTTON CLICKED"));
	OnMerchandiseSlotEvent.Broadcast(ItemTag,Price,Quantity);
}

void UMJStoreSlotBase::OnClicked_PlusButton()
{
	Quantity ++;
	if (Quantity >= MaxQuantity)
	{
		Quantity = MaxQuantity;
	}
	SetQuantity(Quantity);
}

void UMJStoreSlotBase::OnClicked_MinusButton()
{
	if (Quantity == 0)
	{
		SetQuantity(Quantity);
		return;
	}
	
	Quantity --;
	
	SetQuantity(Quantity);
}

void UMJStoreSlotBase::OnClicked_PlusTenButton()
{
	Quantity += 10;
	if (Quantity >= MaxQuantity)
	{
		Quantity = MaxQuantity;
	}
	SetQuantity(Quantity);
}

void UMJStoreSlotBase::OnClicked_MinusTenButton()
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

