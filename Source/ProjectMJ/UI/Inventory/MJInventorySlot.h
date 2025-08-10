// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJInventoryComponent.h"
#include "ItemDataRow.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "MJInventorySlot.generated.h"

/**
* Class Description: 인벤토리 슬롯 위젯
 * Author: 이지수
 * Created Date: 2025.08.10
 * Last Modified By: 
 * Last Modified Date: 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseEnterEvent, UMJInventorySlot*, Slot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseLeaveEvent, UMJInventorySlot*, Slot);
class UBorder;
class UTextBlock;
class UImage;
class UMJDragWidget;
class UMJInventoryTooltip;

UCLASS()
class PROJECTMJ_API UMJInventorySlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> Border;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image;

	UPROPERTY()
	TObjectPtr<UTextBlock> Text;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemCount;
	
	TObjectPtr<UTexture2D> Texture;

	// visual
	FLinearColor DefaultBorderColor;
	FLinearColor ClickedBorderColor;
	
	// for drag&drop
	FInventoryItemData InventoryData;
	FItemDataRow ItemData;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UMJDragWidget> DragWidgetClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UMJInventoryTooltip> TooltipWidgetClass;

	UPROPERTY()
	TObjectPtr<UMJInventoryTooltip> Tooltip = nullptr;
	
	FVector2D ScreenPos;
public:
	// Delegate
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnMouseEnterEvent OnMouseEntered;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnMouseLeaveEvent OnMouseLeaved;

	//
	int32 SlotPosition;
	bool bIsOccupied = false;
	virtual void NativeConstruct() override;
	
	void SetImage(UTexture2D* ItemTexture);
	void SetText(FText text);
	void SetItemCount(int count)
	{
		ItemCount->SetText(FText::AsNumber(count));
		if (count == 0)
		{
			ItemCount->SetText(FText::GetEmpty());
		}
	};
	void SetIsOccupied(bool b) {bIsOccupied = b;}
	
	void SetInventoryItemData(FInventoryItemData data){InventoryData = data;}
	void SetItemData(FItemDataRow data){ItemData = data;}
	
	UImage* GetImage() {return Image;}
	UTextBlock* GetText() {return Text;}
	UTexture2D* GetItemTexture() {return Texture;}
	int32 GetSlotPosition() {return SlotPosition;}
	FVector2D GetScreenPos() {return ScreenPos;}
	
	FItemDataRow GetItemData() {return ItemData;};
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	// virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
};
	
