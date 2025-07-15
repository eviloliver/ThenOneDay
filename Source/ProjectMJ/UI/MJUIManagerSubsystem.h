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

class UMJDialogueWidget;
class UMJBacklogWidget;
class UMJDialogueComponent;
class UMJHUDWidget;
class UMJInventoryWidget;

UCLASS()
class PROJECTMJ_API UMJUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// HUD
	void ShowHUD(class AMJPlayerState* PlayerState, class AMJPlayerController* PC);
	
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

	//UMJInventoryWidget* GetInventoryWidget() {return InventoryWidget;};
	UMJHUDWidget* GetHUDWidget() {return HUDWidget;};
	
protected:
	UPROPERTY()
	UMJDialogueWidget* DialogueWidget;

	UPROPERTY()
	TSubclassOf<class UMJDialogueWidget> DialogueWidgetClass;

	bool bIsDialogueActive;

	UPROPERTY()
	UMJHUDWidget* HUDWidget;

	UPROPERTY()
	TSubclassOf<class UMJHUDWidget> HUDWidgetClass;
	
	//UMJInventoryWidget* InventoryWidget;
	//TSubclassOf<class UMJInventoryWidget> InventoryWidgetClass;
};
