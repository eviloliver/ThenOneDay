// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/MJBacklogWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Dialogue/MJDialogueRow.h"

void UMJBacklogWidget::AddLine(const FMJDialogueRow& Row) // 함수명 수정하기 > AddLine으로
{
	if (!BacklogScrollBox) return;
	
	FString Line = Row.Speaker + TEXT(" : ") + Row.Text;
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(BacklogScrollBox);
	
	if (NewTextBlock)
	{
		NewTextBlock->SetText(FText::FromString(Line));
		BacklogScrollBox->AddChild(NewTextBlock);

		// 텍스트 색 변경방법
		FSlateColor SetColor = FSlateColor(FLinearColor::Blue);
		NewTextBlock->SetColorAndOpacity(SetColor);
	}
}

void UMJBacklogWidget::ClearBacklog()
{
	if (BacklogScrollBox)
	{
		BacklogScrollBox->ClearChildren();
	}
}
