// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/MJDialogueComponent.h"

#include "MJBacklogWidget.h"
#include "MJDialogueWidget.h"
#include "TG/MJGameInstanceTG.h"
#include "UI/MJHUDWidget.h"
#include "UI/MJUIManagerSubsystem.h"

UMJDialogueComponent::UMJDialogueComponent()
{
	DialogueTable = nullptr; // 내가 블프에서 직접 넣어줘야 함
	CurrentIndex = 0;
	
	// 생성될 때는 인덱스 0의 대사를 띄워줘야겠제
}

void UMJDialogueComponent::TurnOver() // x키가 눌리면 이 함수가 실행되어야 함
{
	// Skip Typing
	if (GetDialogueWidget()->GetIsTyping())
	{
		GetDialogueWidget()->SkipTyping();
		return;
	}
	
	// Next Script
	++ CurrentIndex;
	
	if (IsDialogueEnd())
    {
    	GetWorld()->GetGameInstance<UMJGameInstanceTG>()->GetSubsystem<UMJUIManagerSubsystem>()
    	->GetHUDWidget()->HideDialogue();
		return;
    }
	
	FloatLine();
	GetDialogueWidget()->SetImageOpacity(GetCurrentRow()->Speaker);
	
	// // BackLog
	// if (!GetDialogueWidget()->GetBacklogWidget())
	// {
	// 	return;
	// }
	// GetDialogueWidget()->GetBacklogWidget()->AddLine(*GetPreviousRow());
}

bool UMJDialogueComponent::IsDialogueEnd() const
{
	return (CurrentIndex >= DialogueTable->GetRowNames().Num());
}

void UMJDialogueComponent::FloatLine()
{
	GetDialogueWidget()->SetTextBlock(GetCurrentRow()->Script, GetCurrentRow()->Speaker);
	GetDialogueWidget()->StartTyping(GetCurrentRow()->Script,0.05);
}

const FMJDialogueRow* UMJDialogueComponent::GetCurrentRow() const
{
	if (DialogueTable && DialogueTable->GetRowNames().IsValidIndex(CurrentIndex))
	{
		return DialogueTable->FindRow<FMJDialogueRow>(DialogueTable->GetRowNames()[CurrentIndex], TEXT(""));
	}
	return nullptr;
}

const FMJDialogueRow* UMJDialogueComponent::GetPreviousRow() const // 백로그용
{	
	if (DialogueTable && DialogueTable->GetRowNames().IsValidIndex(CurrentIndex -1))
    {
    	return DialogueTable->FindRow<FMJDialogueRow>(DialogueTable->GetRowNames()[CurrentIndex -1], TEXT(""));
    }
	return nullptr;
}

UMJDialogueWidget* UMJDialogueComponent::GetDialogueWidget()
{
	if (GetWorld() && GetWorld()->GetGameInstance<UMJGameInstanceTG>() &&
		GetWorld()->GetGameInstance<UMJGameInstanceTG>()->GetSubsystem<UMJUIManagerSubsystem>() &&
		GetWorld()->GetGameInstance<UMJGameInstanceTG>()->GetSubsystem<UMJUIManagerSubsystem>()->GetHUDWidget())
	{
		return 	GetWorld()->GetGameInstance<UMJGameInstanceTG>()->GetSubsystem<UMJUIManagerSubsystem>()
        	->GetHUDWidget()->GetDialogueWidget();
	}
	return nullptr;
}
