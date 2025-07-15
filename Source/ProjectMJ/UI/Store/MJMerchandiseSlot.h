// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJMerchandiseSlot.generated.h"

/**
 * Class Description: 상점 슬롯 위젯
 * Author: 이지수
 * Created Date: 2025.07.13
 * Last Modified By: 
 * Last Modified Date: 
 */
class UTextBlock;
class UImage;
UCLASS()
class PROJECTMJ_API UMJMerchandiseSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* MerImage;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Description;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Price;

public:
	void SetImage(UTexture2D* ItemTexture);
	void SetItemName(FText itemName);
	void SetDescription(FText description);
	void SetPrice(int32 price);
};
