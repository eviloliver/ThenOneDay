// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MJDialogueRow.h"
#include "MJDialogueComponent.generated.h"

/**
 * Class Description: Player와 상호작용할 Actor한테 달아주면 되는 Component, 위젯의 동작 담당
 * Author: 이지수
 * Created Date: 2025.06.12
 * Last Modified By: 이지수
 * Last Modified Date: 2025.06.12
 */

class UMJDialogueWidget;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMJDialogueComponent();

protected:	
	// UDataTable 이 들어올 수 있는 방 -> 세입자를 넣어 줘야함 (포인터 == 누군가를 가리킬 수 있음)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Component")
	UDataTable* DialogueTable;

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	int32 CurrentIndex;
public:
	bool IsDialogueEnd() const;
	
	// Refactoring
	void FloatLine();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void TurnOver();
	
	void UpdateBacklog();

	void SetIndex(int index) {CurrentIndex = index;}
	
	const FMJDialogueRow* GetCurrentRow() const;
	const FMJDialogueRow* GetPreviousRow() const;
	UMJDialogueWidget* GetDialogueWidget();
};
