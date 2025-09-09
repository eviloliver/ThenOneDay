// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJHUDWidget.generated.h"

/**
 * Class Description: HUD
 * Author: 이지수
 * Created Date: 2025.06.26
 * Last Modified By: 
 * Last Modified Date: 
 */

class UBorder;
class UMJTutorialInstruction;
class UMJMouseWidget;
class UMJEquipedSkillWidget;
class UMJSkillWidget;
class UMJUIToggle;
class UMJDialogueWidget;
class UMJBossHpBarWidget;
class UMJHealthBarWidget;
class UMJManaBarWidget;
class UMJStaminaBar;
class UMJExperienceWidget;
class UMJStatWidget;
class UMJInventoryWidget;
class UMJStoreWidget;

UCLASS()
class PROJECTMJ_API UMJHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJHealthBarWidget> HealthBar;

	// UPROPERTY(meta = (BindWidget))
	// TObjectPtr<UMJManaBarWidget> ManaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJStaminaBar> StaminaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJExperienceWidget> ExpBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJStatWidget> StatPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJInventoryWidget> Inventory;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJStoreWidget> Store;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJDialogueWidget> Dialogue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJUIToggle> UIToggle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJSkillWidget> SkillWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJEquipedSkillWidget> EquipedSkillWidget;


	// Tutorial Widget
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> TutorialMouse;

	UPROPERTY(EditDefaultsOnly, Category = SettingWidgetClass)
	TSubclassOf<UMJMouseWidget> LeftMouseClass;

	UPROPERTY(EditDefaultsOnly, Category = SettingWidgetClass)
	TSubclassOf<UMJMouseWidget> RightMouseClass;

	UPROPERTY(EditDefaultsOnly, Category = SettingWidgetClass)
	TSubclassOf<UMJMouseWidget> RightPressMouseClass;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJMouseWidget> Shift;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMJTutorialInstruction> Instruction;

	
public:
	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ToggleWidget(UWidget* Widget);
	
	UFUNCTION()
	void BindAtrributesToChildren(class UMJAbilitySystemComponent* ASC, class UMJCharacterAttributeSet* AttributeSet, class UMJPlayerStatComponent* Stat);

	UFUNCTION()
	void ShowStatPanel();

	UFUNCTION()
	void ShowInventory();

	UFUNCTION()
	void ShowStore();

	UFUNCTION()
	void SetSkillWidgetVisibility();
	
	UFUNCTION()
	void SetDialogueVisibility();

	UFUNCTION()
	void SetTutorialMouse(TSubclassOf<UMJMouseWidget> NewWidget);

	UFUNCTION()
	void SetMouseVisibility();
	
	UFUNCTION()
	void SetLeftMouse() {SetTutorialMouse(LeftMouseClass);}

	UFUNCTION()
	void SetRightMouse() {SetTutorialMouse(RightMouseClass);}

	UFUNCTION()
	void SetRightPressMouse() {SetTutorialMouse(RightPressMouseClass);}
	
	UFUNCTION()
	void ShowShift();

	UFUNCTION()
	void HideShift();

	UFUNCTION()
	void SetInstructionWidgetVisibility();

	UFUNCTION()
	void SetInstructionText(const FString& InInstruction);

	//
	UMJInventoryWidget* GetInventoryWidget() {return Inventory;};
	UMJStoreWidget* GetStoreWidget() {return Store;};
	UMJDialogueWidget* GetDialogueWidget() {return Dialogue;};
	UMJSkillWidget* GetSkillWidget() {return SkillWidget;};
	UMJEquipedSkillWidget* GetEquipedSkillWidget() {return EquipedSkillWidget;}

};
