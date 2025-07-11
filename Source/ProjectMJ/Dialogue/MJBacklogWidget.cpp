// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/MJBacklogWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Dialogue/MJDialogueRow.h"
#include "Fonts/SlateFontInfo.h"

void UMJBacklogWidget::AddLine(const FMJDialogueRow& Row) // 함수명 수정하기 > AddLine으로
{
	if (!BacklogScrollBox) return;
	
	FString Line = Row.Speaker + TEXT(" : ") + Row.Text;
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(BacklogScrollBox);
	
	if (NewTextBlock)
	{
		// 폰트 변경
		FSlateFontInfo FontInfo;
		FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Game/UI/Font/CookieRun_Regular_Font.CookieRun_Regular_Font"));
		FontInfo.Size = 15;
		NewTextBlock->SetFont(FontInfo);
		
		
		NewTextBlock->SetText(FText::FromString(Line));
		BacklogScrollBox->AddChild(NewTextBlock);

		// 텍스트 색 변경
		FSlateColor SetColor = FSlateColor(FLinearColor::White);
		NewTextBlock->SetColorAndOpacity(SetColor);

		// 대사 행 간격
		if (UScrollBoxSlot* ScrollSlot = Cast<UScrollBoxSlot>(NewTextBlock->Slot))
		{
			ScrollSlot->SetPadding(FMargin(20, 5, 20, 5));
		}
	}
}

void UMJBacklogWidget::ClearBacklog()
{
	if (BacklogScrollBox)
	{
		BacklogScrollBox->ClearChildren();
	}
}
