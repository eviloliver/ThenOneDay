// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJMainMenuWidget.generated.h"

class UMJChildMenuBaseWidget;
class UButton;
/**
 * Class Description: MainMenu Widget
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-14
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-14
 */
UCLASS()
class PROJECTMJ_API UMJMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUserWidget> NewGamePopUpWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMJChildMenuBaseWidget> NewGamePopUpWidget;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUserWidget> LoadGameWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMJChildMenuBaseWidget> LoadGameWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUserWidget> SettingsWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMJChildMenuBaseWidget> SettingsWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_NewGame;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_LoadGame;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Settings;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Quit;
	
	UFUNCTION()
	void OnClicked_NewGame();
	
	UFUNCTION()
	void OnClicked_LoadGame();

	UFUNCTION()
	void OnClicked_Settings();

	UFUNCTION()
	void OnClicked_Quit();
	
	
	
	
};
