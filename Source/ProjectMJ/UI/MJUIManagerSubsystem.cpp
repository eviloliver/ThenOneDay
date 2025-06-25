// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MJUIManagerSubsystem.h"
#include "Dialogue/MJDialogueWidget.h"
#include "Dialogue/MJBacklogWidget.h"
#include "Dialogue/MJDialogueComponent.h"
#include "UObject/ConstructorHelpers.h"

void UMJUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Log, TEXT("으앵"));
	DialogueWidgetClass = LoadClass<UMJDialogueWidget>(
			nullptr,
			TEXT("/Game/Dialogue/Widget/BP_MJDialogueWidget.BP_MJDialogueWidget_C"));

}

void UMJUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UMJUIManagerSubsystem::ShowDialogue(UMJDialogueComponent* DialogueComp) // 위젯 띄우기만 하는 함수
{
	if (!DialogueWidgetClass)
		return;
	
	// 위젯 생성
	if (!DialogueWidget)
	{
		DialogueWidget = CreateWidget<UMJDialogueWidget>(GetWorld(), DialogueWidgetClass);
		if (!DialogueWidget)
			return;

		DialogueWidget->AddToViewport();
	}
	
	DialogueComp->StartDialogue(); // 데이터테이블을 불러오고, index를 0으로 설정
	
	SetDialogue(DialogueComp); // 인덱스 0일 때의 대사들이 세팅되어 타이핑된다
}

void UMJUIManagerSubsystem::NextDialogue(UMJDialogueComponent* DialogueComp)
{
	if (DialogueWidget)
	{
		if (DialogueWidget->GetIsTyping())
		{
			DialogueWidget->SkipTyping();
			return;
		}
		
		DialogueComp->NextDialogue(); // 인덱스 +1
		
		SetDialogue(DialogueComp); // +1된 row를 가져와 타이핑 >> 순서 중요
		

		if (DialogueComp->IsDialogueEnd())
		{
			HideDialogue();
		}
	}
}

void UMJUIManagerSubsystem::SetDialogue(const UMJDialogueComponent* DialogueComp) const
{
	if (const FMJDialogueRow* Row = DialogueComp->GetCurrentRow())
	{
		DialogueWidget->ShowDialogue(*Row);
		DialogueWidget->StartTyping(Row->Text, 0.08f);
		DialogueWidget->SetImageOpacity(Row->Speaker);
	}

	if (const FMJDialogueRow* PrevRow = DialogueComp->GetPreviousRow())
	{
		if (DialogueWidget->BacklogWidget)
		{
			DialogueWidget->BacklogWidget->AddLine(*PrevRow);
		}
	}
}

void UMJUIManagerSubsystem::HideDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
       	DialogueWidget = nullptr;
	}
}

void UMJUIManagerSubsystem::ShowBacklog()
{
	DialogueWidget->ShowBacklog();
}


