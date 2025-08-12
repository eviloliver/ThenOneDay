// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTService_MJCheckAttackRange.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "ProjectMJ.h"
#include "VectorTypes.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/MJCharacterBase.h"
#include "Character/Component/MJEnemySkillComponent.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "Components/CapsuleComponent.h"
#include "DataTable/MJSkillDataRow.h"
#include "MJ/Character/MJMonsterCharacter.h"

UBTService_MJCheckAttackRange::UBTService_MJCheckAttackRange()
{
	NodeName = "CheckAttackRange";
	Interval = 0.1f;
	PreTargetLocation = FVector::ZeroVector;
	CurrTargetLocation = FVector::ZeroVector;
}

void UBTService_MJCheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	/*
	 * How to: 타겟이 몬스터의 공격 범위에 들어갔을 때 Maximum 혹은 Minimum 범위에 들어오면 블랙보드 키를 설정
	 */
	CachedOwnerComp = &OwnerComp;
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControlledPawn == nullptr)
	{
		return;
	}

	AMJCharacterBase* Character = Cast<AMJCharacterBase>(ControlledPawn);
	if (Character == nullptr)
	{
		return;
	}
	
	AMJMonsterCharacter* Enemy = Cast<AMJMonsterCharacter>(ControlledPawn);
	if (Enemy == nullptr)
	{
		return;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (Target == nullptr)
	{
		return;
	}
	
	/*
	 * Minjin
	 * HowTo: 설정한 태그를 가지고 있는 태그와 비교해서 구체적인 태그를 가져온다.
	 * 가져온 태그로 Skill Set 가져온다.
	 */

	/*if (!Enemy->HasAnyMatchingGameplayTags(SkillTags))
	{
		MJ_LOG(LogMJ, Log, TEXT("Has not AnyMatchingGameplayTags"));
		return;
	}*/
	
	UMJSkillComponentBase* SkillComp = Enemy->GetSkillComponent();
	FGameplayTag SkillTag = FGameplayTag::EmptyTag;

	for (FGameplayTag HasTag: SkillTags)
	{
		if (SkillComp->GetOwnedSkillMap().Contains(HasTag))
		{
			SkillTag = HasTag;
		}
	}

	if (!SkillTag.IsValid())
	{
		return;
	}
	int32 SkillLevel = SkillComp->GetOwnedSkillMap()[SkillTag].Level;
	// 레벨 정보 가져옴

	UDataTable* SkillDataTable = SkillComp->GetSkillDataTable();
	const FMJSkillDataRow* DataRow = SkillDataTable->FindRow<FMJSkillDataRow>(SkillTag.GetTagName(), TEXT("Find Skill Info"));
	if (!DataRow)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist DataRow"));
		return;
	}

	UCurveTable* CurveTable = DataRow->SkillLevelDataTable.LoadSynchronous();
	if (!CurveTable)
	{
		MJ_LOG(LogMJ, Log, TEXT("Not Exist SkillLevelDataTable"));
		return;
	}
	
	/*
	* SkillRadius
	* SkillRange
	* SkillAttackLocationOffset
	 */
	FRealCurve* SkillRadiusCurve = CurveTable->FindCurve(TEXT("SkillRadius"), TEXT("FindSkillRadius"));
	const float AttackRadius = SkillRadiusCurve->Eval(SkillLevel);

	FRealCurve* SkillRangeCurve = CurveTable->FindCurve(TEXT("SkillRange"), TEXT("FindSkillRange"));
	const float SkillRange = SkillRangeCurve->Eval(SkillLevel);

	FRealCurve* SkillAttackLocationOffsetCurve = CurveTable->FindCurve(TEXT("SkillAttackLocationOffset"), TEXT("FindSkillAttackLocationOffset"));
	const float Offset = SkillAttackLocationOffsetCurve->Eval(SkillLevel);
	
	const float AttackRange = FMath::Max(SkillRange , AttackRadius * 2.0f);

	// float DistanceToTarget = ControlledPawn->GetDistanceTo(Target);
	int32 DistanceToTarget = FMath::FloorToInt(ControlledPawn->GetDistanceTo(Target));

	const float MinimumAttackRange = Character->GetCapsuleComponent()->GetScaledCapsuleRadius() * ((Offset!=0)?Offset:1);	
	const float MaximumAttackRange = MinimumAttackRange + AttackRange;

	DrawDebugCircle(GetWorld(), ControlledPawn->GetActorLocation(), MaximumAttackRange, 16, FColor::Emerald, false, 0.2f, 0, 0, FVector::RightVector,FVector::ForwardVector, false);
	DrawDebugCircle(GetWorld(), ControlledPawn->GetActorLocation(), MinimumAttackRange, 16, FColor::Magenta, false, 0.2f, 0, 0, FVector::RightVector,FVector::ForwardVector, false);
	
	bool IsInAttackRange = DistanceToTarget <= MaximumAttackRange
		&& DistanceToTarget >= MinimumAttackRange;

	// Minjin: 공격 범위에 속할 경우
	if (IsInAttackRange)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsInAttackRange", true);
		return;
	}

	/*
	 * Minjin
	 * 공격 범위에 속하지 않을 경우
	 * 키 값을 지워주고 이동해야 할 위치(KeepDistancePos) 설정해준다.
	 * 타겟 위치 변동이 있을 경우에만.
	 */
	OwnerComp.GetBlackboardComponent()->ClearValue("IsInAttackRange");

	CurrTargetLocation = Target->GetActorLocation();
	if (PreTargetLocation == FVector::ZeroVector)
	{
		PreTargetLocation = CurrTargetLocation;
	}
	else if (PreTargetLocation == CurrTargetLocation)
	{
		return;
	}

	PreTargetLocation = CurrTargetLocation;
	
	const int32 HalfAttackRange = FMath::FloorToInt(MinimumAttackRange + AttackRange * 0.5f);

	FVector EnemyLocation = ControlledPawn->GetActorLocation();
	float Distance = FVector::Dist(EnemyLocation, CurrTargetLocation);

	FVector MoveToLocation = FVector::ZeroVector;
	
	// Minjin: 거리가 MinimumAttackRange 미만일 경우->플레이어와 멀어진다
	if (Distance < MinimumAttackRange)
	{
		FVector AwayDir = (EnemyLocation - CurrTargetLocation).GetSafeNormal();
		FVector RandomDir = FMath::VRandCone(AwayDir, FMath::DegreesToRadians(30.f));
		MoveToLocation = EnemyLocation + RandomDir *(HalfAttackRange - Distance);
	}

	// Minjin: 거리가 MaximumAttackRange보다 멀 경우->플레이어와 가까워진다
	if (Distance > MaximumAttackRange)
	{
		FVector ToDir = (CurrTargetLocation - EnemyLocation).GetSafeNormal();
		
		MoveToLocation = EnemyLocation + ToDir * (Distance - HalfAttackRange);
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector("KeepDistancePos", MoveToLocation);
}

void UBTService_MJCheckAttackRange::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
}
