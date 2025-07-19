// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/MJInteractionWidget.h"
#include "Components/TextBlock.h"

void UMJInteractionWidget::SetText(FString text)
{
	UE_LOG(LogTemp, Display, TEXT("텍스트 적용됏다"));
	Key->SetText(FText::FromString(text));
}
