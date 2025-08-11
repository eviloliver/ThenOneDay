// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "MJStoreSlotBase.generated.h"

/**
* Class Description: 스토어 위젯의 슬롯들 부모님
 * Author: 이지수
 * Created Date: 2025.08.09
 * Last Modified By: 
 * Last Modified Date: 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMerchandiseSlotEvent,	FGameplayTag&, ItemTag, int32, Price, int32, Quantity);

class UMJStoreComponent;
struct FGameplayTag;
class UMJPopupWidget;
class UButton;
class UTextBlock;
class UImage;
UCLASS()
class PROJECTMJ_API UMJStoreSlotBase : public UUserWidget
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

	bool IsEmpty = true;

	int32 MaxQuantity = 0;
    	
public:
	UFUNCTION()
	virtual void NativeConstruct();

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
	virtual void TryPurchase();

	UFUNCTION()
	virtual void OnClicked_PlusButton();
	UFUNCTION()
	virtual void OnClicked_MinusButton();
	UFUNCTION()
	virtual void OnClicked_PlusTenButton();
	UFUNCTION()
	virtual void OnClicked_MinusTenButton();

	FOnMerchandiseSlotEvent OnMerchandiseSlotEvent;

	bool GetIsEmpty() { return IsEmpty; }
	void SetIsEmpty(bool isEmpty) { IsEmpty = isEmpty; }
	void SetMaxQuantity(int32 maxQuantity) { MaxQuantity = maxQuantity; }
	
};
