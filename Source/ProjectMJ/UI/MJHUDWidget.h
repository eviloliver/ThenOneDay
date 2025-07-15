// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJHUDWidget.generated.h"

/**
 * Class Description: HUD
 * Author: 이지수
 * Created Date: 2025.06.26
 * Last Modified By: 
 * Last Modified Date: 
 */

class UMJHealthBarWidget;
class UMJManaBarWidget;
class UMJExperienceWidget;
class UMJStatWidget;
class UMJInventoryWidget;
class UMJStoreWidget;

UCLASS()
class PROJECTMJ_API UMJHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UMJHealthBarWidget* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UMJManaBarWidget* ManaBar;

	UPROPERTY(meta = (BindWidget))
	UMJExperienceWidget* ExpBar;

	UPROPERTY(meta = (BindWidget))
	UMJStatWidget* StatPanel;

	UPROPERTY(meta = (BindWidget))
	UMJInventoryWidget* Inventory;

	UPROPERTY(meta = (BindWidget))
	UMJStoreWidget* Store;

public:
	UFUNCTION()
	virtual void NativeConstruct() override;
	
	void BindAtrributesToChildren(class UMJAbilitySystemComponent* ASC, class UMJCharacterAttributeSet* AttributeSet);
	void ShowStatPanel();
	void ShowInventory();
	void ShowStore();

	UMJInventoryWidget* GetInventoryWidget() {return Inventory;};
	UMJStoreWidget* GetStoreWidget() {return Store;};

};
