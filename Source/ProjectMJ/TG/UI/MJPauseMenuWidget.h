// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJChildMenuBaseWidget.h"
#include "MJPauseMenuWidget.generated.h"

class USpacer;
class UButton;

/**
 * Class Description: PauseMenu Widget
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-14
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-14
 */
UCLASS()
class PROJECTMJ_API UMJPauseMenuWidget : public UMJChildMenuBaseWidget
{
	GENERATED_BODY()
public:

	UFUNCTION()
	UUserWidget* GetSettingsWidget();

	UFUNCTION()
	UUserWidget* GetForceExitCautionWidget();

	void SetPlayerController(APlayerController* PC);
	

protected:
	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;

	// WeakPtr of MJPC
	TWeakObjectPtr<APlayerController> PC;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SettingsWidgetClass;

	UPROPERTY()
	TObjectPtr<UMJChildMenuBaseWidget> SettingsWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMJChildMenuBaseWidget> PopUpMsgnWidgetClass;

	UPROPERTY()
	TObjectPtr<UMJChildMenuBaseWidget> PopUpMsgWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Resume;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Settings;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_GotoTown;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_MainMenu;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_QuitGame;
	
	UFUNCTION()
	void OnClicked_Resume();
	
	UFUNCTION()
	void OnClicked_SaveGame();

	UFUNCTION()
	void OnClicked_Settings();
	
	UFUNCTION()
	void OnClicked_GotoTown();
	
	UFUNCTION()
	void OnClicked_MainMenu();

	UFUNCTION()
	void OnClicked_QuitGame();

	
	
};
