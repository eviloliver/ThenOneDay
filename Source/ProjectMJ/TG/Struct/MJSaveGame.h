// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "MJSaveGame.generated.h"

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
	UPROPERTY(SaveGame)
	int8 SlotNum = -1;

	UPROPERTY(BlueprintReadOnly, SaveGame)
	FString PlayerName;

	UPROPERTY(BlueprintReadOnly, SaveGame)
	int32 PlayerLevel = 1;
	
	UPROPERTY(BlueprintReadOnly, SaveGame)
	int32 PlayerExp;

	UPROPERTY(BlueprintReadOnly, SaveGame)
	FDateTime RecentPlayedDateTime;
	
	UPROPERTY(BlueprintReadOnly, SaveGame)
	FDateTime SaveGameCreatedDateTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FSkillData> CurrentOwnedSkillMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TMap<FGameplayTag, FGameplayTag> CurrentEquippedSkillMap;

	void SetCurrentOwnedSKillMap(TMap<FGameplayTag, FSkillData> Input)
	{
		CurrentOwnedSkillMap.Empty();
		for (auto Iter : Input)
		{
			CurrentOwnedSkillMap.Add(Iter);
		}
	}
	
	void SetCurrentEquippedSkillMap(TMap<FGameplayTag, FGameplayTag> Input)
	{
		CurrentEquippedSkillMap.Empty();
		for (auto Iter : Input)
		{
			CurrentEquippedSkillMap.Add(Iter);
		}
	}
	
};
