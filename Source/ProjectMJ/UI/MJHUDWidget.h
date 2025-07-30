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

class UMJBossHpBarWidget;
class UMJHealthBarWidget;
class UMJManaBarWidget;
class UMJStaminaBar;
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
	TObjectPtr<UMJHealthBarWidget> HealthBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJManaBarWidget> ManaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJStaminaBar> StaminaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJExperienceWidget> ExpBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJStatWidget> StatPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJInventoryWidget> Inventory;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJStoreWidget> Store;

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
