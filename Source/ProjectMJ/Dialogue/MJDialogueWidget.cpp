// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/MJDialogueWidget.h"
#include "Components/TextBlock.h"
#include "Controller/MJPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UMJDialogueWidget::StartTyping(const FString& InText, float TypingSpeed)
{
	FullText = InText;
	CurrentCharIndex = 0;
	bIsTyping = true;
	Text->SetText(FText::FromString(TEXT(""))); // 빈문자열로 초기화해서 한글자씩 나타날 수 있도록 하기

	if (GetWorld()->GetTimerManager().IsTimerActive(TypingTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(
	   TypingTimerHandle,
	   this,
	   &UMJDialogueWidget::UpdateTyping,
	   TypingSpeed,
	   true 
   );
}

void UMJDialogueWidget::UpdateTyping()
{
	if (CurrentCharIndex < FullText.Len())
	{
		FString CurrentText = FullText.Left(CurrentCharIndex + 1);
		Text->SetText(FText::FromString(CurrentText));
		CurrentCharIndex++;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
		bIsTyping = false;
	}
}

void UMJDialogueWidget::SkipTyping()
{
	if (bIsTyping)
	{
		GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
		Text->SetText(FText::FromString(FullText));
		bIsTyping = false;
	}
}
