// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJInteractionWidget.generated.h"

class UBorder;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Key;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Test;
	
public:
	void SetText(FString text);
	void PlayTestAnimation();
};
