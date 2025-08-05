// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "MJGA_ChargeSkill.generated.h"

/**
 * Class Description: 플레이어의 스킬을 Instant, Charging, Passive로 구분
 * Charge는 우클릭을 길게 눌렀다 땠 을때 발동하는 스킬
 * Author: 신동민
 * Created Date: 2025.06.24
 * Description of Change: 차징 애니메이션 추가
 * Modified By: 신동민
 * Modified Date: 2025.08.06
 */
UCLASS()
class PROJECTMJ_API UMJGA_ChargeSkill : public UMJGA_GameplayAbility
{
	GENERATED_BODY()

public:
	UMJGA_ChargeSkill();

};
