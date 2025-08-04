// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "MJMerchandiseSlot.generated.h"

/**
 * Class Description: 상점 슬롯 위젯
 * Author: 이지수
 * Created Date: 2025.07.13
 * Last Modified By: 2025.08.04
 * Last Modified Date: 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMerchandiseSlotEvent, FGameplayTag&, ItemTag, int32, Price);

struct FGameplayTag;
class UMJPopupWidget;
class UButton;
class UTextBlock;
class UImage;

UCLASS()
class PROJECTMJ_API UMJMerchandiseSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> MerImage;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Description;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PriceText;

	int32 Price;
	
	UPROPERTY()
	FGameplayTag ItemTag;
	
public:
	void NativeConstruct() override;

	UButton* GetButton() { return Button; }
	
	void SetItemTag(FGameplayTag tag);
	void SetImage(UTexture2D* ItemTexture);
	void SetItemName(FText itemName);
	void SetDescription(FText description);
	void SetPrice(int32 price);

	UFUNCTION()
	void OnClicked_Slot();

	FOnMerchandiseSlotEvent OnMerchandiseSlotEvent;
};
