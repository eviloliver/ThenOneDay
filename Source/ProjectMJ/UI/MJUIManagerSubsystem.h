// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MJUIManagerSubsystem.generated.h"

/**
 * Class Description: UI를 띄우고 내리기 위한 싱글톤 매니저
 * Author: 이지수
 * Created Date: 2025-06-20
 * Last Modified By: 이지수
 * Last Modified Date: 2025-06-26
 */

class UWidgetComponent;
class UMJBossHpBarWidget;
class UMJDialogueWidget;
class UMJDialogueComponent;
class UMJHUDWidget;
class UMJCharacterAttributeSet;
class UMJAbilitySystemComponent;

UCLASS()
class PROJECTMJ_API UMJUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMJUIManagerSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// HUD
	void ShowHUD(class AMJPlayerState* PlayerState, class AMJPlayerController* PC, class UMJPlayerStatComponent* Stat);
	UMJHUDWidget* GetHUDWidget() {return HUDWidget;}

	// Dialouge Section
	void SetDialogueVisibility();
	
	// StatPanel Section
	void ShowStatPanel();

	// Inventory Section
	void ShowInventory();

	// Store Section
	void ShowStore();
	
protected:
	UPROPERTY()
	TObjectPtr<UMJHUDWidget> HUDWidget;

	UPROPERTY()
	TSubclassOf<UMJHUDWidget> HUDWidgetClass;
};
