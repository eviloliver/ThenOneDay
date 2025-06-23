// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJCharacterAttributeSaveDataStruct.h"
#include "GameFramework/SaveGame.h"
#include "MJSaveGame.generated.h"

struct FGameplayAttributeData;
class UMJCharacterAttributeSet;
/**
 * Class Description: 게임을 저장할 데이터들을 모아놓은 USaveGame 클래스
 * Author: 차태관
 * Created Date: 2025-06-11
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-21
 */
UCLASS()
class PROJECTMJ_API UMJSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UMJSaveGame();

	FCharacterAttributeSaveData& GetAttributeSaveData();
	
protected:

	UPROPERTY(BlueprintReadOnly, SaveGame)
	FString PlayerName;
	
	UPROPERTY(BlueprintReadOnly, SaveGame)
	FCharacterAttributeSaveData AttributeSaveData;
	

	
	
};
