// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJKeepDistanceWhileMoveTo.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "ProjectMJ.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Component/MJEnemySkillComponent.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "Components/CapsuleComponent.h"
#include "DataTable/MJSkillDataRow.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "Navigation/PathFollowingComponent.h"

UBTTask_MJKeepDistanceWhileMoveTo::UBTTask_MJKeepDistanceWhileMoveTo()
{
	NodeName = TEXT("KeepDistanceMove");
}

EBTNodeResult::Type UBTTask_MJKeepDistanceWhileMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CachedOwnerComp = &OwnerComp;

	AAIController* OwnerController = OwnerComp.GetAIOwner();
	if (OwnerController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* ControlledPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AMJCharacterBase* Character = Cast<AMJCharacterBase>(ControlledPawn);
	if (Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	AMJMonsterCharacter* Enemy = Cast<AMJMonsterCharacter>(ControlledPawn);
	if (Enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (TargetPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	/*
	 * Minjin
	 * HowTo: 설정한 태그(스킬타입)를 통해 가지고 있는 태그와 비교해서 구체적인 태그를 가져온다.
	 * 가져온 태그로 Skill Set 가져온다.
	 * 
	 */
	
	UMJSkillComponentBase* SkillComp = Enemy->GetSkillComponent();
	int32 SkillLevel = SkillComp->GetOwnedSkillMap()[SkillTag].Level;
	// 레벨 정보 가져옴

	UDataTable* SkillDataTable = SkillComp->GetSkillDataTable();
	const FMJSkillDataRow* DataRow = SkillDataTable->FindRow<FMJSkillDataRow>(SkillTag.GetTagName(), TEXT("Find Skill Info"));
	if (!DataRow)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist DataRow"));
		return EBTNodeResult::Failed;		return EBTNodeResult::Failed;
	}

	UCurveTable* CurveTable = DataRow->SkillLevelDataTable.LoadSynchronous();
	if (!CurveTable)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist SkillLevelDataTable"));
		return EBTNodeResult::Failed;
	}
	
	FRealCurve* SkillRadiusCurve = CurveTable->FindCurve(TEXT("SkillRadius"), TEXT("FindSkillRadius"));
	const float AttackRadius = SkillRadiusCurve->Eval(SkillLevel);

	FRealCurve* SkillRangeCurve = CurveTable->FindCurve(TEXT("SkillRange"), TEXT("FindSkillRange"));
	const float SkillRange = SkillRangeCurve->Eval(SkillLevel);

	FRealCurve* SkillAttackLocationOffsetCurve = CurveTable->FindCurve(TEXT("SkillAttackLocationOffset"), TEXT("FindSkillAttackLocationOffset"));
	const float Offset = SkillAttackLocationOffsetCurve->Eval(SkillLevel);
	
	const float AttackRange = FMath::Max(SkillRange , AttackRadius * 2.0f);

	const  float MinimumAttackRange = Character->GetCapsuleComponent()->GetScaledCapsuleRadius() * ((Offset!=0)?Offset:1);	
	const float MaximumAttackRange = MinimumAttackRange + AttackRange;

	const int32 HalfAttackRange = FMath::FloorToInt(MinimumAttackRange + AttackRange * 0.5f);

	FVector AILocation = ControlledPawn->GetActorLocation();
	FVector TargetLocation = TargetPawn->GetActorLocation();
	float Distance = FVector::Dist(AILocation, TargetLocation);

	FVector MoveToLocation = FVector::ZeroVector;
	
	// Minjin: 거리가 MinimumAttackRange 미만일 경우->플레이어와 멀어진다
	if (Distance < MinimumAttackRange)
	{
		FVector AwayDir = (AILocation - TargetLocation).GetSafeNormal();
		FVector RandomDir = FMath::VRandCone(AwayDir, FMath::DegreesToRadians(30.f));
		MoveToLocation = AILocation + RandomDir *(HalfAttackRange - Distance);
		
		// OwnerController->MoveToLocation(MoveToLocation);
	
		// return EBTNodeResult::Succeeded;
	}

	// Minjin: 거리가 MaximumAttackRange보다 멀 경우->플레이어와 가까워진다
	if (Distance > MaximumAttackRange)
	{
		FVector ToDir = (TargetLocation - AILocation).GetSafeNormal();
		
		MoveToLocation = AILocation + ToDir * (Distance - HalfAttackRange);

		// // Minjin: AcceptanceRadius 0.0f로 설정-> 정확히 목표지점에 와야 도착으로 간주
		// OwnerController->MoveToLocation(MoveToLocation, 0.0f, false);
		
		// return EBTNodeResult::Succeeded;
	}

	// // Minjin: Min~Max 범위에 있을 경우->제자리
	// OwnerController->StopMovement();


	// 이동 요청 생성
	FAIMoveRequest MoveReq;
	MoveReq.SetGoalLocation(MoveToLocation);
	MoveReq.SetAcceptanceRadius(0.0f);
	MoveReq.SetUsePathfinding(true);

	FPathFollowingRequestResult MoveResult = OwnerController->MoveTo(MoveReq);


	// 델리게이트 등록 (이동 완료 시 OnMoveCompleted 호출)
	if (MoveResult.Code == EPathFollowingRequestResult::RequestSuccessful)
	{
		OwnerController->ReceiveMoveCompleted.AddDynamic(this, &UBTTask_MJKeepDistanceWhileMoveTo::OnMoveCompleted);
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_MJKeepDistanceWhileMoveTo::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* OwnerController = OwnerComp.GetAIOwner();
	if (OwnerController)
	{
		OwnerController->StopMovement();
		OwnerController->ReceiveMoveCompleted.RemoveDynamic(this, &UBTTask_MJKeepDistanceWhileMoveTo::OnMoveCompleted);
	}
	return EBTNodeResult::Aborted;
}

void UBTTask_MJKeepDistanceWhileMoveTo::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (!CachedOwnerComp) return;

	AAIController* OwnerController = CachedOwnerComp->GetAIOwner();
	OwnerController->ReceiveMoveCompleted.RemoveDynamic(this, &UBTTask_MJKeepDistanceWhileMoveTo::OnMoveCompleted);

	if (Result == EPathFollowingResult::Success)
	{
		FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Failed);
	}
}
