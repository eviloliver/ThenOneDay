// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "MJDialogueRow.h"
#include "MJDialogueWidget.generated.h"

/**
 * Class Description: 다이어로그 위젯을 화면에 띄우기 위한 클래스 / BP_DialogueWidget의 부모 클래스로, 그래프에서 데이터 테이블 연동해줘야 함
 * Author: 이지수
 * Created Date: 2025.06.12
 * Last Modified By: 이지수
 * Last Modified Date: 2025.06.12
 */
class UTextBlock;

UCLASS()
class PROJECTMJ_API UMJDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowDialogue(const FMJDialogueRow& DialogueRow);

	//Typing Function
	UFUNCTION()
	void StartTyping(const FString& InText, float TypingSpeed = 0.05f);

	UFUNCTION()
	void UpdateTyping();

	UFUNCTION()
	void SkipTyping();
	
	UPROPERTY(meta = (BindWidget))
	class UMJBacklogWidget* BacklogWidget;
	
	bool GetIsTyping() {return bIsTyping;}

protected:
	//Typing Function
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock*	Text;

	// UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	// UButton* BacklogButton;
	
	FTimerHandle TypingTimerHandle;
	FString FullText;
	int32 CurrentCharIndex;
	bool bIsTyping = false;

	

};
