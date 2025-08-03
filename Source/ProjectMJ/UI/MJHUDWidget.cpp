// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MJHUDWidget.h"
#include "UI/Bar/MJHealthBarWidget.h"
#include "Bar/MJManaBarWidget.h"
#include "Bar/MJStaminaBar.h"
#include "Bar/MJExperienceWidget.h"
#include "Character/Component/MJPlayerStatComponent.h"
#include "Dialogue/MJDialogueWidget.h"
#include "World/MJStatWidget.h"
#include "Inventory/MJInventoryWidget.h"
#include "Store/MJStoreWidget.h"
#include "TG/UI/MJBossHpBarWidget.h"

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

	if (Dialogue)
	{
		Dialogue->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMJHUDWidget::BindAtrributesToChildren(UMJAbilitySystemComponent* ASC, UMJCharacterAttributeSet* AttributeSet, UMJPlayerStatComponent* Stat)
{
	if (HealthBar)
	{
		HealthBar->BindToAttributes(ASC,AttributeSet);
	}

	if (ManaBar)
	{
		ManaBar->BindToAttributes(ASC,AttributeSet);
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
	if (StatPanel->GetVisibility() == ESlateVisibility::Visible)
	{
		StatPanel->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (StatPanel->GetVisibility() == ESlateVisibility::Hidden)
	{
		StatPanel->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMJHUDWidget::ShowInventory()
{
	if (Inventory->GetVisibility() == ESlateVisibility::Visible)
	{
		Inventory->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (Inventory->GetVisibility() == ESlateVisibility::Hidden)
	{
		Inventory->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMJHUDWidget::ShowStore()
{
	if (Store->GetVisibility() == ESlateVisibility::Visible)
	{
		Store->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (Store->GetVisibility() == ESlateVisibility::Hidden)
	{
		Store->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMJHUDWidget::SetDialogueVisibility()
{
	if (Dialogue->GetVisibility() == ESlateVisibility::Visible)
	{
		Dialogue->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (Dialogue->GetVisibility() == ESlateVisibility::Hidden)
	{
		Dialogue->SetVisibility(ESlateVisibility::Visible);
	}
}

