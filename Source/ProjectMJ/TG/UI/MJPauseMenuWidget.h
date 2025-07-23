// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJChildMenuBaseWidget.h"
#include "MJPauseMenuWidget.generated.h"

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
	

protected:

	virtual void NativeConstruct() override;
	
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SettingsWidgetClass;

	UPROPERTY()
	TObjectPtr<UMJChildMenuBaseWidget> SettingsWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Resume;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Settings;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_MainMenu;
	
	UFUNCTION()
	void OnClicked_Resume();

	UFUNCTION()
	void OnClicked_Settings();

	UFUNCTION()
	void OnClicked_MainMenu();
	
};
