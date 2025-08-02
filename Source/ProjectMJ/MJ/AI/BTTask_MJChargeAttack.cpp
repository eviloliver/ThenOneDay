// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJChargeAttack.h"
#include "AIController.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "ProjectMJ.h"
#include "Character/Component/MJEnemySkillComponent.h"

UBTTask_MJChargeAttack::UBTTask_MJChargeAttack()
{
	NodeName = TEXT("ChargeAttack");
}

EBTNodeResult::Type UBTTask_MJChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	FGameplayTag SkillTypeTag = FGameplayTag::RequestGameplayTag(FName("Skill.Charge"));
	FGameplayTag AttackTag = SkillComponent->GetEquippedSkillMap()[SkillTypeTag];

	if (!AttackTag.IsValid())
	{
		return EBTNodeResult::Failed;
	}

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
	
	return EBTNodeResult::InProgress;
}
