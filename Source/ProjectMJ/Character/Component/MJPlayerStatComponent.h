// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/MJStatComponentBase.h"
#include "MJPlayerStatComponent.generated.h"

/**
 * Class Description: 플레이어는 GameInstance에 있는 CurveTable을 바로 접근
 * Author: 신동민
 * Created Date: 2025.07.17
 * Modified By:
 * Modified Date:
 */

class UCurveTable;

UCLASS()
class PROJECTMJ_API UMJPlayerStatComponent : public UMJStatComponentBase
{
	GENERATED_BODY()

public:
	UMJPlayerStatComponent();

	virtual void InitializeStat() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	TObjectPtr<UCurveTable> PlayerStatTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 PlayerLevel = 1;
};
