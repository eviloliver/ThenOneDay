// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJBacklogWidget.generated.h"

/*
 * Class Description: Backlog를 띄우는 위젯 클래스
 * Author: 이지수
 * Created Date: 2025.06.17
 * Last Modified By: 이지수
 * Last Modified Date: 2025.06.17
 */
class UScrollBox;
UCLASS()
class PROJECTMJ_API UMJBacklogWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* BacklogScrollBox;

public:
	UFUNCTION()
	void AddLine(const FMJDialogueRow& Row);

	UFUNCTION()
	void ClearBacklog();
};
