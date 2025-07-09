// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/MJDragWidget.h"
#include "Components/Image.h"

void UMJDragWidget::SetDragImage(UTexture2D* ItemTexture)
{
	{
		if (DragImage && ItemTexture)
		{
			FSlateBrush Brush;
			Brush.SetResourceObject(ItemTexture);
			Brush.ImageSize = FVector2D(80,80);
			DragImage->SetBrush(Brush);
		}
	}
}
