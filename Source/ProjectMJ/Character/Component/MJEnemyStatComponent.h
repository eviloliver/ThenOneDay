// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/MJStatComponentBase.h"
#include "MJEnemyStatComponent.generated.h"

/**
 * Class Description: 몬스터는 GameInstance에 있는 DataTable에서 CurveTable을 바로 접근
 * Author: 신동민
 * Created Date: 2025.07.17
 * Modified By:
 * Modified Date:
 */
UCLASS()
class PROJECTMJ_API UMJEnemyStatComponent : public UMJStatComponentBase
{
	GENERATED_BODY()

public:
	UMJEnemyStatComponent();

	virtual void InitializeStat() override;

};
