// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Character/Component/MJStatComponentBase.h"
#include "MJEnemyStatComponent.generated.h"

/**
 * Class Description: 몬스터는 GameInstance에 있는 DataTable에서 CurveTable을 바로 접근
 * Author: 신동민
 * Created Date: 2025.07.17
 * Modified By: Kim Minjin
 * Modified Date: (2025.07.17.) InitializeStat 구현
 */
UCLASS()
class PROJECTMJ_API UMJEnemyStatComponent : public UMJStatComponentBase
{
	GENERATED_BODY()

public:
	UMJEnemyStatComponent();

	virtual void InitializeStat() override;
	void SetStatTable(UCurveTable *AttributeCurve){EnemyStatTable = AttributeCurve;}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	TObjectPtr<UCurveTable> EnemyStatTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 EnemyLevel = 1;
};
