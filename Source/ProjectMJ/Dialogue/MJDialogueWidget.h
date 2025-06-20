// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
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
	UFUNCTION()
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowDialogue(const FMJDialogueRow& DialogueRow);

	void ShowBacklog();

	//Typing Section
	void StartTyping(const FString& InText, float TypingSpeed = 0.05f);
	void UpdateTyping();
	void SkipTyping();

	// Image
	void SetImageOpacity(const FString& SpeakerName);
	
	UPROPERTY(meta = (BindWidget))
	class UMJBacklogWidget* BacklogWidget;
	
	bool GetIsTyping() {return bIsTyping;}

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock*	Text;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PlayerImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* NPCImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* BacklogKey;
	
	FTimerHandle TypingTimerHandle;
	FString FullText;
	int32 CurrentCharIndex;
	bool bIsTyping = false;

	

};
