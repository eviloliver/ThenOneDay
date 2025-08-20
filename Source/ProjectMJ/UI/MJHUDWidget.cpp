// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MJHUDWidget.h"

#include "MJUIToggle.h"
#include "UI/Bar/MJHealthBarWidget.h"
#include "Bar/MJManaBarWidget.h"
#include "Bar/MJStaminaBar.h"
#include "Bar/MJExperienceWidget.h"
#include "Character/Component/MJPlayerStatComponent.h"
#include "Components/Button.h"
#include "Dialogue/MJDialogueWidget.h"
#include "World/MJStatWidget.h"
#include "Inventory/MJInventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Skill/MJSkillWidget.h"
#include "Store/MJStoreWidget.h"
#include "TG/UI/MJBossHpBarWidget.h"
#include "Tutorial/MJMouseWidget.h"
#include "Tutorial/MJTutorialInstruction.h"

void UMJHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (StatPanel)
	{
		StatPanel->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Inventory)
	{
		Inventory->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Store)
	{
		Store->SetVisibility(ESlateVisibility::Hidden);
	}

	const FString CurrentLevel = UGameplayStatics::GetCurrentLevelName(this, true);
	if (Dialogue)
	{
		if (CurrentLevel.Equals(TEXT("Tutorial_StartStory")))
		{
			Dialogue->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			Dialogue->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (LeftMouse)
	{
		LeftMouse->SetVisibility(ESlateVisibility::Hidden);
	}

	if (RightMouse)
	{
		RightMouse->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Shift)
	{
		Shift->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Instruction)
	{
		Instruction->SetVisibility(ESlateVisibility::Hidden);
	}

	if (UIToggle)
	{
		UIToggle->GetInventoryButton()->OnClicked.AddDynamic(this, &ThisClass::ShowInventory);
		UIToggle->GetStatPanelButton()->OnClicked.AddDynamic(this, &ThisClass::ShowStatPanel);
		UIToggle->GetSkillWidgetButton()->OnClicked.AddDynamic(this, &ThisClass::SetSkillWidgetVisibility);
	}

	if (SkillWidget)
	{
		SkillWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMJHUDWidget::ToggleWidget(UUserWidget* Widget)
{
	const bool bIsVisible = (Widget->GetVisibility() == ESlateVisibility::Visible);
	Widget->SetVisibility(bIsVisible ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
}

void UMJHUDWidget::BindAtrributesToChildren(UMJAbilitySystemComponent* ASC, UMJCharacterAttributeSet* AttributeSet, UMJPlayerStatComponent* Stat)
{
	if (HealthBar)
	{
		HealthBar->BindToAttributes(ASC,AttributeSet);
	}

	if (StaminaBar)
	{
		StaminaBar->BindToAttributes(ASC,AttributeSet);
	}

	if (StatPanel)
	{
		StatPanel->BindToAttribute(ASC,AttributeSet,Stat);
	}
}

void UMJHUDWidget::ShowStatPanel()
{
	ToggleWidget(StatPanel);
}

void UMJHUDWidget::ShowInventory()
{
	ToggleWidget(Inventory);
}

void UMJHUDWidget::ShowStore()
{
	if (Store->GetVisibility() == ESlateVisibility::Visible)
	{
		Store->SetVisibility(ESlateVisibility::Hidden);
		Store->CloseWidget();
	}
	else if (Store->GetVisibility() == ESlateVisibility::Hidden)
	{
		Store->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMJHUDWidget::SetSkillWidgetVisibility()
{
	ToggleWidget(SkillWidget);
}

void UMJHUDWidget::SetDialogueVisibility()
{
	ToggleWidget(Dialogue);
}

void UMJHUDWidget::SetLeftMouseVisibility()
{
	ToggleWidget(LeftMouse);
}

void UMJHUDWidget::SetRightMouseVisibility()
{
	ToggleWidget(RightMouse);
}

void UMJHUDWidget::SetShiftVisibility()
{
	ToggleWidget(Shift);
}

void UMJHUDWidget::SetInstructionWidgetVisibility()
{
	ToggleWidget(Instruction);
}

void UMJHUDWidget::SetInstructionText(const FString& InInstruction)
{
	Instruction->SetInstructionText(InInstruction);
}

