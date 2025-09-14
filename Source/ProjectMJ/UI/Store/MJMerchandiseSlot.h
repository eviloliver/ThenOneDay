// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJStoreSlotBase.h"
#include "MJMerchandiseSlot.generated.h"

/**
 * Class Description: 상점 구매창 내 슬롯
 * Author: 이지수
 * Created Date: 2025.07.13
 * Last Modified By: 2025.08.09
 * Last Modified Date: 
 */

class UMJStoreComponent;
struct FGameplayTag;
class UMJPopupWidget;
class UButton;
class UTextBlock;
class UImage;

UCLASS()
class PROJECTMJ_API UMJMerchandiseSlot : public UMJStoreSlotBase
{
	GENERATED_BODY()

public:
	virtual void OnClicked_PlusButton() override;
	virtual void OnClicked_MinusButton() override;
	virtual void OnClicked_PlusTenButton() override;
	virtual void OnClicked_MinusTenButton() override;
	
};
