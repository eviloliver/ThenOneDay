// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MJGA_PlayerActionInstantSkill.h"

#include "MJGA_AIActionInstantAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystem/AbilityTasks/MJAT_GetMousePosition.h"
#include "Character/MJCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UMJGA_PlayerActionInstantSkill::UMJGA_PlayerActionInstantSkill()
{
}

void UMJGA_PlayerActionInstantSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMJAT_GetMousePosition* GetMousePositionTask = UMJAT_GetMousePosition::CreateTask(this);
	GetMousePositionTask->OnCompleted.AddDynamic(this, &UMJGA_PlayerActionInstantSkill::OnMousePositionReady);
	GetMousePositionTask->OnFailed.AddDynamic(this, &UMJGA_PlayerActionInstantSkill::OnMousePositionFailed);

	GetMousePositionTask->ReadyForActivation();
}

void UMJGA_PlayerActionInstantSkill::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMJGA_PlayerActionInstantSkill::EndAbility(const FGameplayAbilitySpecHandle Handle,
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

void UMJGA_PlayerActionInstantSkill::OnMousePositionReady(const FVector& MouseLocation)
{
	if (!SkillActionAnimMontage)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}

	AMJCharacterBase* AMJCharacter = Cast<AMJCharacterBase>(CurrentActorInfo->AvatarActor.Get());
	if (!AMJCharacter)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}

	FVector CharacterLocation = AMJCharacter->GetActorLocation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CharacterLocation, MouseLocation);
	TargetRotation.Pitch = 0;
	TargetRotation.Roll = 0;

	// TODO: 모션 워핑 사용할 예정 -동민-
	AMJCharacter->SetActorRotation(TargetRotation);

	AMJCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);
	UAbilityTask_PlayMontageAndWait* PlayAttackMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), SkillActionAnimMontage, 1.0f);

	PlayAttackMontage->OnCompleted.AddDynamic(this, &UMJGA_PlayerActionInstantSkill::OnCompleteCallback);
	PlayAttackMontage->OnInterrupted.AddDynamic(this, &UMJGA_PlayerActionInstantSkill::OnInterruptedCallback);
	PlayAttackMontage->OnCancelled.AddDynamic(this, &UMJGA_PlayerActionInstantSkill::OnInterruptedCallback);

	PlayAttackMontage->ReadyForActivation();
}

void UMJGA_PlayerActionInstantSkill::OnMousePositionFailed(const FVector& IgnoreLocation)
{
	// 마우스가 없으면 앞을 향한 동작인데. AI까지 적용시키기엔 문제가 많음
	OnMousePositionReady(GetAvatarActorFromActorInfo()->GetActorForwardVector() * 100.f + GetAvatarActorFromActorInfo()->GetActorLocation());
}

void UMJGA_PlayerActionInstantSkill::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMJGA_PlayerActionInstantSkill::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
