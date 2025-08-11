// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJDragWidget.generated.h"

/**
* Class Description: 인벤토리 내 슬롯을 집으면 뜨는 드래그 위젯
 * Author: 이지수
 * Created Date: 2025.
 * Last Modified By: 
 * Last Modified Date: 
 */
class UImage;
UCLASS()
class PROJECTMJ_API UMJDragWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> DragImage;

public:
	void SetDragImage(UTexture2D* ItemTexture);
	
};
