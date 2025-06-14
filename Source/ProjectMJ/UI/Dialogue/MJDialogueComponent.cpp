// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Dialogue/MJDialogueComponent.h"

UMJDialogueComponent::UMJDialogueComponent()
{
	DialogueTable = nullptr;
	CurrentIndex = 0;
	RowNames.Empty();
}

void UMJDialogueComponent::StartDialogue()
{
	// BeginPlay에 이미 있는 코드인데 또 필요할지 모르겠다 흠
	if (DialogueTable)
	{
		RowNames = DialogueTable->GetRowNames();
		CurrentIndex = 0;
	}
}

void UMJDialogueComponent::NextDialogue()
{
	++CurrentIndex;
}

bool UMJDialogueComponent::IsDialogueEnd() const
{
	return (CurrentIndex >= RowNames.Num());
}

const FMJDialogueRow* UMJDialogueComponent::GetCurrentRow() const
{
	if (DialogueTable && RowNames.IsValidIndex(CurrentIndex))
	{
		return DialogueTable->FindRow<FMJDialogueRow>(RowNames[CurrentIndex], TEXT(""));
		// ? : TEXT("")는 그냥 디버깅용 메세지
	}
	
	return nullptr;
}
