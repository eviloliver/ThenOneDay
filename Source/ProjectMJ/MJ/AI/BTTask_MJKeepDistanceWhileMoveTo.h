// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJKeepDistanceWhileMoveTo.generated.h"

namespace EPathFollowingResult
{
	enum Type : int;
}

/**
 * Class Description: 타겟과 거리를 유지하며 이동
 * Author: Kim Minjin
 * Created Date: 2025.07.01.
 * Last Modified By: Kim Minjin
 * Last Modified Date: (2025.08.10.) 하드코딩 수정했으나 사용 X
 */
UCLASS()
class PROJECTMJ_API UBTTask_MJKeepDistanceWhileMoveTo : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MJKeepDistanceWhileMoveTo();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tag", meta=(Categories = "Skill"))
	FGameplayTag SkillTag;

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	UBehaviorTreeComponent* CachedOwnerComp;
};
