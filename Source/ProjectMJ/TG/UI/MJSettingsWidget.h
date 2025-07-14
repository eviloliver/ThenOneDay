// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJSettingsWidget.generated.h"

class UButton;
class UComboBoxString;

/**
 * Class Description: Settings Widget
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-14
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-14
 */
UCLASS()
class PROJECTMJ_API UMJSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> ComboBox_WindowMode;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> ComboBox_Resolution;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> ComboBox_Graphics;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Back;
	
	
	UPROPERTY()
	TEnumAsByte<EWindowMode::Type> WindowMode = EWindowMode::Type::Fullscreen;
	

	UFUNCTION()
	void ComboBox_WindowModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void ComboBox_ResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void ComboBox_GraphicsChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnClicked_Back();




	

	
};
