// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "MJStoreWidget.generated.h"


class UMJPlayerStatComponent;
class UTextBlock;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickedYes);

class UMJPopupWidget;
class UScrollBox;
class UMJMerchandiseSlot;
UCLASS()
class PROJECTMJ_API UMJStoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ScrollBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> InvenScrollBox;
	
	UPROPERTY(meta = (BindWidget))
	TArray<TObjectPtr<UMJMerchandiseSlot>> MerchandiseSlots;

	UPROPERTY(meta = (BindWidget))
	TArray<TObjectPtr<UMJMerchandiseSlot>> InventorySlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Store)
	TSubclassOf<UMJMerchandiseSlot> MerchandiseSlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Store)
	TSubclassOf<UMJMerchandiseSlot> InventorySlotClass;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJPopupWidget> PurchasePopup;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJPopupWidget> SellPopup;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AvailableGold;

	UPROPERTY()
	UMJPlayerStatComponent* StatCompRef;
public:
	virtual void NativeConstruct() override;

	void UpdateInventorySlot();
	
	TArray<UMJMerchandiseSlot*> GetMerchandiseSlots() {return MerchandiseSlots;}
	TArray<UMJMerchandiseSlot*> GetInventorySlots() {return InventorySlots;}
	
	void SetStatComponent(UMJPlayerStatComponent* StatComp);
	
	UFUNCTION()
	void SetAvailableGold(int32 Gold);

	// 구매 팝업 관련
	UFUNCTION()
	void Onclicked_PurchaseButton();
	UFUNCTION()
	void OnClicked_PurchasePopupYes();
	UFUNCTION()
	void OnClicked_PurchasePopupNo();


	// 판매 팝업관련
	UFUNCTION()
	void Onclicked_SellButton();
	UFUNCTION()
	void OnClicked_SellPopupYes();
	UFUNCTION()
	void OnClicked_SellPopupNo();

	UMJPopupWidget* GetPurchasePopup() {return PurchasePopup;};
	void CloseWidget();
	
	FOnClickedYes OnClickedPurchaseYes;
	FOnClickedYes OnClickedSellYes;
};
