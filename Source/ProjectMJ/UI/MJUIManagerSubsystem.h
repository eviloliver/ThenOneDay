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
class UMJEnemyHPBar;
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
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// HUD
	void ShowHUD(class AMJPlayerState* PlayerState, class AMJPlayerController* PC);
	UMJHUDWidget* GetHUDWidget() {return HUDWidget;}
	
	// Dialogue Section
	void ShowDialogue(UMJDialogueComponent* DialogueComp);
	void NextDialogue(UMJDialogueComponent* DialogueComp);
	void HideDialogue();
	
	void SetDialogue(const UMJDialogueComponent* DialogueComp) const;
	
	//BackLog Section
	void ShowBacklog();

	// StatPanel Section
	void ShowStatPanel();

	// Inventory Section
	void ShowInventory();

	// Store Section
	void ShowStore();

	// World UI
	void ResisterWorldUI(UWidgetComponent* WidgetComp,UMJAbilitySystemComponent* ASC, UMJCharacterAttributeSet* AttributeSet);
	void UnresisterWorldUI(UWidgetComponent* WidgetComp);

	// BossHpBar Section
	UFUNCTION()
	void OnBossSpawned();

	//UMJInventoryWidget* GetInventoryWidget() {return InventoryWidget;};
	UMJHUDWidget* GetHUDWidget() {return HUDWidget;};
	
protected:
	UPROPERTY()
	TObjectPtr<UMJDialogueWidget> DialogueWidget;

	UPROPERTY()
	TSubclassOf<UMJDialogueWidget> DialogueWidgetClass;

	bool bIsDialogueActive;

	UPROPERTY()
	TObjectPtr<UMJHUDWidget> HUDWidget;

	UPROPERTY()
	TSubclassOf<UMJHUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UMJEnemyHPBar> EnemyHPBarWidget;
	
	UPROPERTY()
	TArray<TWeakObjectPtr<UWidgetComponent>> WorldUIs;
};
