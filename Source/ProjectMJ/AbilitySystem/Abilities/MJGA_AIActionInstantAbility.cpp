// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGA_AIActionInstantAbility.h"

#include "MotionWarpingComponent.h"
#include "Character/MJCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MJ/AI/MJMonsterAIControllerBase.h"
#include "MJ/Character/MJMonsterCharacter.h"

UMJGA_AIActionInstantAbility::UMJGA_AIActionInstantAbility()
{
	
}

void UMJGA_AIActionInstantAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!SkillActionAnimMontage)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	AMJCharacterBase* AMJCharacter = Cast<AMJCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!AMJCharacter)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	// AMJCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);

	FVector CharacterLocation = AMJCharacter->GetActorLocation();

	AMJMonsterCharacter* EnemyCharacter = Cast<AMJMonsterCharacter>(AMJCharacter);
	if (!EnemyCharacter)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	AMJMonsterAIControllerBase* AIController = Cast<AMJMonsterAIControllerBase>(EnemyCharacter->GetController());
	if (!AIController)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	AActor* TargetActor = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("Target"));
	if (!TargetActor)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CharacterLocation, TargetActor->GetActorLocation());
	TargetRotation.Pitch = 0;
	TargetRotation.Roll = 0;

	// Minjin: 현재 Turn 오류 때문에 안 씀
	UMotionWarpingComponent* MotionWarpingComponent = AMJCharacter->FindComponentByClass<UMotionWarpingComponent>();
	if (MotionWarpingComponent)
	{
		FMotionWarpingTarget Target = {};
		Target.Location = TargetActor->GetActorLocation();
		Target.Rotation = TargetRotation;
		Target.Name = FName("T");

		MotionWarpingComponent->AddOrUpdateWarpTarget(Target);
	}
	
	UAbilityTask_PlayMontageAndWait* PlayAttackMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), SkillActionAnimMontage, 1.0f);

	PlayAttackMontage->OnCompleted.AddDynamic(this, &UMJGA_AIActionInstantAbility::OnCompleteCallback);
	PlayAttackMontage->OnInterrupted.AddDynamic(this, &UMJGA_AIActionInstantAbility::OnInterruptedCallback);
	PlayAttackMontage->OnCancelled.AddDynamic(this, &UMJGA_AIActionInstantAbility::OnInterruptedCallback);

	PlayAttackMontage->ReadyForActivation();
}

void UMJGA_AIActionInstantAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}

void UMJGA_AIActionInstantAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	AMJCharacterBase* AMJCharacter = Cast<AMJCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!AMJCharacter)
	{
		return; 
	}
	AMJCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void UMJGA_AIActionInstantAbility::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_AIActionInstantAbility::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
