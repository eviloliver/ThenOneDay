// ThenOneDayStudio


#include "MJ/AI/BTTask_MJSkillAttack.h"

#include "AIController.h"
#include "ProjectMJ.h"
#include "Character/Component/MJEnemySkillComponent.h"
#include "MJ/Character/MJMonsterCharacter.h"

UBTTask_MJSkillAttack::UBTTask_MJSkillAttack()
{
	NodeName = TEXT("SkillAttack");
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

	MJ_LOG(LogMJ, Warning, TEXT("Skill Attack"));
	
	return EBTNodeResult::Succeeded;
}
