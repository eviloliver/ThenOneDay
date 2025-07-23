// Fill out your copyright notice in the Description page of Project Settings.


#include "MJInteractionWidget.h"
#include "Components/TextBlock.h"

void UMJInteractionWidget::SetText(FString text)
{
	Key->SetText(FText::FromString(text));
}

void UMJInteractionWidget::PlayTestAnimation()
{
	if (Test)
	{
		PlayAnimation(Test,0.f,0);
	}
}
