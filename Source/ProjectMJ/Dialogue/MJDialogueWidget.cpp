// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/MJDialogueWidget.h"
#include "MJBacklogWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMJDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (BacklogWidget)
	{
		BacklogWidget->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("Dialogue Widget Constructed"));
	}
}

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

void UMJDialogueWidget::SetImageOpacity(const FString& SpeakerName)
{
	if (!PlayerImage)
		return;
	if (!NPCImage)
		return;
	
	if (SpeakerName == TEXT("태관"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Image Opacity"));
		PlayerImage->SetOpacity(1.0f);
		NPCImage->SetOpacity(0.3f);
	}

	if (SpeakerName == TEXT("주현"))
	{
		NPCImage->SetOpacity(1.0f);
		PlayerImage->SetOpacity(0.3f);
	}
}

void UMJDialogueWidget::ShowBacklog()
{
	if (BacklogWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		BacklogWidget->SetVisibility(ESlateVisibility::Hidden);
		BacklogKey->SetOpacity(1.0f);
	}
	else if (BacklogWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		BacklogWidget->SetVisibility(ESlateVisibility::Visible);
		BacklogKey->SetOpacity(0.2f);
	}
}
