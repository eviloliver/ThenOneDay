// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MJInventoryTooltip.generated.h"

/**
 * 
 */
class USizeBox;
class UTextBlock;
UCLASS()
class PROJECTMJ_API UMJInventoryTooltip : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Description;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
public:
	//virtual void NativeConstruct() override;
	
	void SetDescription(FText Text) {Description->SetText(Text);}
	void SetItemName(FText Text){ItemName->SetText(Text);}
};
