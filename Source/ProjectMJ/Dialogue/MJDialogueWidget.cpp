// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/MJDialogueWidget.h"
#include "MJBacklogWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

void UMJDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (BacklogWidget)
	{
		BacklogWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMJDialogueWidget::SetTextBlock(const FString& InText,const FString& speaker)
{
	// 여기서 크래시가 난다면 component에 DT를 넣었는지 확인해보세요
	if (Text)
	{
		Text->SetText(FText::FromString(InText));
	}
	
	if (Speaker)
	{
		Speaker->SetText(FText::FromString(speaker));
	}
}

void UMJDialogueWidget::SetNPCImage(UTexture2D* InNPCImage)
{
	if (NPCImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(InNPCImage);
		NPCImage->SetBrush(Brush);
	}
}

void UMJDialogueWidget::SetPlayerImage(UTexture2D* InPlayerImage)
{
	if (PlayerImage)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(InPlayerImage);
		PlayerImage->SetBrush(Brush);
	}
}

void UMJDialogueWidget::StartTyping(const FString& InText, float TypingSpeed)
{
	FullText = InText;
	UE_LOG(LogTemp, Display, TEXT("Text: %s"), *FullText);
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
		UE_LOG(LogTemp, Display, TEXT("SkipTyping"));
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
	
	if (SpeakerName == TEXT("Player"))
	{
		PlayerImage->SetOpacity(1.0f);
		NPCImage->SetOpacity(0.3f);
	}
	else
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
