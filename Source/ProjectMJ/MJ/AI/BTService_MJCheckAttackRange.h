// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_MJCheckAttackRange.generated.h"

/**
 * Class Description: ServiceNode-타겟이 공격범위에 들어와 있는지 확인(근거리, 원거리)
 * Author: Kim Minjin
 * Created Date: 2025.06.25.
 * Last Modified By: Kim Minjin
 * Last Modified Date: (2025.08.10.) 하드코딩 수정. 스킬 태그를 받아와 스킬의 공격범위를 체크. KeepDistancePos 설정
 */

UCLASS()
class PROJECTMJ_API UBTService_MJCheckAttackRange : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_MJCheckAttackRange();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tag", meta=(Categories = "Skill"))
	FGameplayTagContainer SkillTags;

	FVector PreTargetLocation;
	FVector CurrTargetLocation;
};
