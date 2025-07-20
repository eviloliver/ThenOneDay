// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/AI/BTTask_MJNormalAttack.h"
#include "AIController.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Character/Component/MJSkillComponentBase.h"
#include "ProjectMJ.h"

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
	UMJSkillComponentBase* SkillComponent = Monster->GetSkillComponent();
	
	FGameplayTag SkillTypeTag = FGameplayTag::RequestGameplayTag(FName("Skill.Normal"));
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
