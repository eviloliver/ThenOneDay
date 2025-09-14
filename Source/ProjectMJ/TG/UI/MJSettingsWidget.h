// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJChildMenuBaseWidget.h"
#include "MJSettingsWidget.generated.h"

class USlider;
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
class PROJECTMJ_API UMJSettingsWidget : public UMJChildMenuBaseWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> ComboBox_WindowMode;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> ComboBox_Resolution;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> ComboBox_Graphics;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Back;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> MasterVolumeSlider;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> MusicVolumeSlider;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> SFXVolumeSlider;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundClass> MasterSoundClass;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundClass> MusicSoundClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundClass> SFXSoundClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundMix> SoundMixModifier;
	

	UFUNCTION()
	void ComboBox_WindowModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void ComboBox_ResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void ComboBox_GraphicsChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnClicked_Back();

	UFUNCTION()
	void MasterVolumeValueChanged(float NewValue);

	UFUNCTION()
	void MusicVolumeValueChanged(float NewValue);
	
	UFUNCTION()
	void SFXVolumeValueChanged(float NewValue);
	



	

	
};
