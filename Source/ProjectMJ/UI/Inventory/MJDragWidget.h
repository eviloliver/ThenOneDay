// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJDragWidget.generated.h"

/**
 * 
 */
class UImage;
UCLASS()
class PROJECTMJ_API UMJDragWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* DragImage;

public:
	void SetDragImage(UTexture2D* ItemTexture);
	
};
