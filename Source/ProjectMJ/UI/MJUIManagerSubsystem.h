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

UCLASS()
class PROJECTMJ_API UMJUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// HUD
	void ShowHUD(class AMJPlayerState* PlayerState);
	
	// Dialogue Section
	void ShowDialogue(UMJDialogueComponent* DialogueComp);
	void NextDialogue(UMJDialogueComponent* DialogueComp);
	void HideDialogue();
	
	void SetDialogue(const UMJDialogueComponent* DialogueComp) const;
	
	//BackLog Section
	void ShowBacklog();

	// StatPanel Section
	void ShowStatPanel();

protected:
	UPROPERTY()
	UMJDialogueWidget* DialogueWidget;
	TSubclassOf<class UMJDialogueWidget> DialogueWidgetClass;

	UMJHUDWidget* HUDWidget;
	TSubclassOf<class UMJHUDWidget> HUDWidgetClass;
	bool bIsDialogueActive;
};
