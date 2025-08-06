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

class UMJStoreComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMerchandiseSlotEvent,
	FGameplayTag&, ItemTag, int32, Price, int32, Quantity);

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
	UPROPERTY()
	TObjectPtr<UMJStoreComponent> StoreComponent;
	
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
	
	// 개수 조절
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PlusButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MinusButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PlusTenButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MinusTenButton;
	
	FGameplayTag ItemTag;
	int32 Price;
	int32 Quantity = 0;
    	
public:
	virtual void NativeConstruct() override;

	UButton* GetButton() { return Button; }
	UButton* GetPlusButton() { return PlusButton; }
	UButton* GetMinusButton() { return MinusButton; }
	
	void SetItemTag(FGameplayTag tag);
	void SetImage(UTexture2D* ItemTexture);
	void SetItemName(FText itemName);
	void SetDescription(FText description);
	void SetPrice(int32 price);
	void InitializeQuantity();

	UFUNCTION()
	void SetQuantity(int32 delta);
	
	UFUNCTION()
	void TryPurchase();

	UFUNCTION()
	void OnClicked_PlusButton();
	UFUNCTION()
	void OnClicked_MinusButton();
	UFUNCTION()
	void OnClicked_PlusTenButton();
	UFUNCTION()
	void OnClicked_MinusTenButton();

	FOnMerchandiseSlotEvent OnMerchandiseSlotEvent;
};
