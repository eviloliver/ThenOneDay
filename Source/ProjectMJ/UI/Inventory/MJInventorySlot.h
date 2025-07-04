// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJInventoryComponent.h"
#include "ItemDataRow.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MJInventorySlot.generated.h"

/**
* Class Description: 인벤토리 슬롯 위젯
 * Author: 이지수
 * Created Date: 2025.07.02
 * Last Modified By: 
 * Last Modified Date: 
 */

class UTextBlock;
class UImage;
class UMJDragWidget;

UCLASS()
class PROJECTMJ_API UMJInventorySlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* Image;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemCount;
		
	UTexture2D* Texture;

	// for drag&drop
	FInventoryItemData InventoryData;
	FItemDataRow ItemData;
	TMap<FName,FInventoryItemData> ItemInInventory;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UMJDragWidget> DragWidgetClass;
	
	
public:
	int32 SlotPosition;
	virtual void NativeConstruct() override;
	
	void SetImage(UTexture2D* ItemTexture);
	void SetText(FText text);
	void SetItemCount(int count) {ItemCount->SetText(FText::AsNumber(count));};
	void SetItemInInventory(TMap<FName,FInventoryItemData> map){ItemInInventory = map;}
	
	void SetInventoryItemData(FInventoryItemData data){InventoryData = data;}
	void SetItemData(FItemDataRow data){ItemData = data;}
	
	UImage* GetImage() {return Image;}
	UTextBlock* GetText() {return Text;}
	UTexture2D* GetItemTexture() {return Texture;}

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
	
