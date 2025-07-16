// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJAttack.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "ProjectMJ.h"
#include "Abilities/GameplayAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MJ/Interface/MJCharacterAIInterface.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "Character/Component/MJSkillComponentBase.h"

UBTTask_MJAttack::UBTTask_MJAttack()
{
}

EBTNodeResult::Type UBTTask_MJAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	UMJSkillComponentBase* SkillComponent = Monster->GetSkillComponent();
	FGameplayTag AttackTag = Monster->GetAttackTag();

	FDelegateHandle Handle;
	Handle = ASC->OnAbilityEnded.AddLambda(
	[&, AttackTag, Handle](const FAbilityEndedData& EndedData)
	{
		MJ_LOG(LogMJ, Error,TEXT("A"));
		if (EndedData.AbilityThatEnded->AbilityTags.HasTagExact(AttackTag))
		{
			MJ_LOG(LogMJ, Error,TEXT("AA"));
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			ASC->OnAbilityEnded.Remove(Handle);
		}
	});
	MJ_LOG(LogMJ, Error,TEXT("AAA"));
	SkillComponent->ActivateSkill(AttackTag);
	
	// IMJCharacterAIInterface* AIPawn = Cast<IMJCharacterAIInterface>(ControlledPawn);
	// if (AIPawn == nullptr)
	// {
	// 	return EBTNodeResult::Failed;
	// }
	//
	// AIPawn->AttackByAI();
	
	return EBTNodeResult::Succeeded;
}
