// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJNormalAttack.h"
#include "AIController.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "ProjectMJ.h"
#include "Character/Component/MJEnemySkillComponent.h"

UBTTask_MJNormalAttack::UBTTask_MJNormalAttack()
{
	NodeName = TEXT("Normal Attack");
}

EBTNodeResult::Type UBTTask_MJNormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	SkillComponent->ActivateNormalSkill();

	MJ_LOG(LogMJ, Warning, TEXT("Normal Attack"));
	
	return EBTNodeResult::Succeeded;
}
