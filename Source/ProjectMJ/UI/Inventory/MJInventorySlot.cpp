// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/MJInventorySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMJInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	Texture = nullptr;
}

void UMJInventorySlot::SetImage(UTexture2D* ItemTexture)
{
	this->Texture = ItemTexture;
	if (Image && ItemTexture)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(ItemTexture);
		Image->SetBrush(Brush);
		Image->SetBrushSize({200,200}); // 텍스처 사이즈 조절용 // 더 이상 사용되지 않는다면서 왜 적용은 되는거 같을까
	}
}

void UMJInventorySlot::SetText(FText newtext)
{
	Text->SetText(newtext);
}