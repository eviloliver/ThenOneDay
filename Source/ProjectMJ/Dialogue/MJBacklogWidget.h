// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MJBacklogWidget.generated.h"

/**
 * 
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
