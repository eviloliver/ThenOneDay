// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MJHUDWidget.h"
#include "MJHealthBarWidget.h"
#include "MJManaBarWidget.h"
#include "MJExperienceWidget.h"
#include "MJStatWidget.h"
#include "Inventory/MJInventoryWidget.h"

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
}

void UMJHUDWidget::BindAtrributesToChildren(UMJAbilitySystemComponent* ASC, UMJCharacterAttributeSet* AttributeSet)
{
	if (HealthBar)
	{
		HealthBar->BindToAttributes(ASC,AttributeSet);
	}

	if (ManaBar)
	{
		ManaBar->BindToAttributes(ASC,AttributeSet);
	}

	if (ExpBar)
	{
		ExpBar->BindToAttributes(ASC,AttributeSet);
	}

	if (StatPanel)
	{
		StatPanel->BindToAttribute(ASC,AttributeSet);
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