// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MJGameInstanceDM.generated.h"

/**
  * Class Description: 나만의 작은 게임 인스턴스
 * Author: 신동민
 * Created Date: 2025_06_27
 * Last Modified By:
 * Last Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJGameInstanceDM : public UGameInstance
{
	GENERATED_BODY()
public:
	UMJGameInstanceDM() {};

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> SkillDataTable;

};