// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJStoreWidget.generated.h"

/**
 * 
 */
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

public:
	virtual void NativeConstruct() override;

	TArray<UMJMerchandiseSlot*> GetMerchandiseSlots() {return MerchandiseSlots;}

	void ShowMerchandiseSlots(int32 SlotCount);
};
