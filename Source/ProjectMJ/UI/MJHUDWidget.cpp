// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MJHUDWidget.h"
#include "MJHealthBarWidget.h"
#include "MJManaBarWidget.h"
#include "MJExperienceWidget.h"
#include "MJStatWidget.h"

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
