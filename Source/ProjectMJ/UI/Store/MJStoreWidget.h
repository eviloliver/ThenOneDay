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
	TArray<TObjectPtr<UMJMerchandiseSlot>> MerchandiseSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	TSubclassOf<UMJMerchandiseSlot> MerchandiseSlotClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJPopupWidget> Popup;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AvailableGold;

	UPROPERTY()
	UMJPlayerStatComponent* StatCompRef;
public:
	virtual void NativeConstruct() override;

	TArray<UMJMerchandiseSlot*> GetMerchandiseSlots() {return MerchandiseSlots;}

	
	void SetStatComponent(UMJPlayerStatComponent* StatComp);
	
	UFUNCTION()
	void SetAvailableGold(int32 Gold);
	UFUNCTION()
	void Onclicked_Slot();
	UFUNCTION()
	void OnClicked_PopupYes();
	UFUNCTION()
	void OnClicked_PopupNo();
	
	FOnClickedYes OnClickedYes;
};
