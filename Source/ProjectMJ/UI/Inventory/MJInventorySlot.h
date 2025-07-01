// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJInventorySlot.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;

UCLASS()
class PROJECTMJ_API UMJInventorySlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* Image;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text;

	UTexture2D* Texture;

public:
	virtual void NativeConstruct() override;
	
	void SetImage(UTexture2D* ItemTexture);
	void SetText(FText text);

	UImage* GetImage() {return Image;}
	UTextBlock* GetText() {return Text;}
	UTexture2D* GetItemTexture() {return Texture;};
};
	
