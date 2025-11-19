// ThenOneDayStudio


#include "MJ/AI/BTTask_MJSkillAttack.h"

#include "AIController.h"
#include "ProjectMJ.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Component/MJEnemySkillComponent.h"
#include "MJ/Character/MJMonsterCharacter.h"

UBTTask_MJSkillAttack::UBTTask_MJSkillAttack()
{
	NodeName = TEXT("SkillAttack");
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTTask_MJSkillAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AMJMonsterCharacter* Monster = Cast<AMJMonsterCharacter>(ControlledPawn);
	if (Monster == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UAbilitySystemComponent* ASC = Monster->GetAbilitySystemComponent();
	UMJEnemySkillComponent* SkillComponent = Monster->GetSkillComponent();
	
	SkillComponent->ActivateIdentitySkill();
	Handle = ASC->OnAbilityEnded.AddLambda(
	[&](const FAbilityEndedData& EndedData)
	{
		MJ_LOG(LogMJ, Error,TEXT("A"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	});

	MJ_LOG(LogMJ, Warning, TEXT("Skill Attack"));
	
	return EBTNodeResult::InProgress;
}

void UBTTask_MJSkillAttack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControlledPawn == nullptr)
	{
		return;
	}
	
	AMJMonsterCharacter* Monster = Cast<AMJMonsterCharacter>(ControlledPawn);
	if (Monster == nullptr)
	{
		return;
	}
	UAbilitySystemComponent* ASC = Monster->GetAbilitySystemComponent();
	ASC->OnAbilityEnded.Remove(Handle);
	MJ_LOG(LogMJ, Error,TEXT("Remove Handle."));
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
