// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJInventoryWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;

UCLASS()
class PROJECTMJ_API UMJInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* image;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* text;

public:
	void SetImage();
	void SetText(FText text);

	UImage* GetImage() {return image;};
	UTextBlock* GetText() {return text;};
};
