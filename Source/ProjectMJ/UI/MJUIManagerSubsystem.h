// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MJUIManagerSubsystem.generated.h"

/**
 * Class Description: UI를 띄우고 내리기 위한 싱글톤 매니저
 * Author: 이지수
 * Created Date: 2025-06-20
 * Last Modified By: 
 * Last Modified Date: 
 */

class UMJDialogueWidget;
class UMJBacklogWidget;
class UMJDialogueComponent;

UCLASS()
class PROJECTMJ_API UMJUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Dialogue Section
	void ShowDialogue(UMJDialogueComponent* DialogueComp);
	void NextDialogue(UMJDialogueComponent* DialogueComp);
	void HideDialogue();
	
	void SetDialogue(const UMJDialogueComponent* DialogueComp) const;
	
	//BackLog Section
	void ShowBacklog();

protected:
	UPROPERTY()
	UMJDialogueWidget* DialogueWidget;

	TSubclassOf<class UMJDialogueWidget> DialogueWidgetClass;

	bool bIsDialogueActive;
};
