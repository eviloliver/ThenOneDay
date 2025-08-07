// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_PlayerActionChargeSkill.h"

#include "MJGA_PlayerActionInstantSkill.h"
#include "MotionWarpingComponent.h"
#include "ProjectMJ.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/AbilityTasks/MJAT_GetMousePosition.h"
#include "Character/MJCharacterBase.h"
#include "Character/Component/MJAbilityContextComponent.h"
#include "Kismet/KismetMathLibrary.h"

UMJGA_PlayerActionChargeSkill::UMJGA_PlayerActionChargeSkill()
{
	bIsCharging = false;
}

void UMJGA_PlayerActionChargeSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	bIsCharging = true;

	UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	if (!ASC)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist ASC"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("Character.State.IsCharging"));

	UMJAT_GetMousePosition* GetMousePositionTask = UMJAT_GetMousePosition::CreateTask(this);
	GetMousePositionTask->OnCompleted.AddDynamic(this, &UMJGA_PlayerActionChargeSkill::OnMousePositionReady);
	GetMousePositionTask->OnFailed.AddDynamic(this, &UMJGA_PlayerActionChargeSkill::OnMousePositionFailed);

	GetMousePositionTask->ReadyForActivation();
}

void UMJGA_PlayerActionChargeSkill::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMJGA_PlayerActionChargeSkill::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                                  const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	if (!bIsCharging || CurrentChargeTime < MinChargeTime)
	{
		MJ_LOG(LogMJ, Warning, TEXT("A:"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	PlayReleaseMontage();
}

void UMJGA_PlayerActionChargeSkill::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	if (UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(ActorInfo->AbilitySystemComponent))
	{
		ASC->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag("Character.State.IsCharging"));
	}

	bIsCharging = false;

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMJGA_PlayerActionChargeSkill::OnMousePositionReady(const FVector& MouseLocation)
{
	if (!SkillChargeAnimMontage)
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

	UMJAbilityContextComponent* MJAbilityContextComponent = AMJCharacter->FindComponentByClass<UMJAbilityContextComponent>();
	if (MJAbilityContextComponent)
	{
		MJAbilityContextComponent->LastTargetedMouseLocation = MouseLocation;
	}

	FVector CharacterLocation = AMJCharacter->GetActorLocation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CharacterLocation, MouseLocation);
	TargetRotation.Pitch = 0;
	TargetRotation.Roll = 0;

	UMotionWarpingComponent* MotionWarpingComponent = AMJCharacter->FindComponentByClass<UMotionWarpingComponent>();
	if (MotionWarpingComponent)
	{
		FMotionWarpingTarget Target = {};
		Target.Location = MouseLocation;
		Target.Rotation = TargetRotation;
		Target.Name = FName("Target");

		MotionWarpingComponent->AddOrUpdateWarpTarget(Target);
	}


	UAbilityTask_PlayMontageAndWait* PlayChargeMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayCharge"), SkillChargeAnimMontage, 1.0f);

	PlayChargeMontage->ReadyForActivation();
}

void UMJGA_PlayerActionChargeSkill::OnMousePositionFailed(const FVector& IgnoreLocation)
{
	OnMousePositionReady(GetAvatarActorFromActorInfo()->GetActorForwardVector() * 100.f + GetAvatarActorFromActorInfo()->GetActorLocation());
}

void UMJGA_PlayerActionChargeSkill::OnReleaseMontageComplete()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UMJGA_PlayerActionChargeSkill::PlayReleaseMontage()
{
	if (CurrentActorInfo->AnimInstance.IsValid())
	{
		CurrentActorInfo->AnimInstance->Montage_Stop(0.1f, SkillChargeAnimMontage);
	}

	// Release몽타주 재생
	if (SkillActionAnimMontage)
	{
		UAbilityTask_PlayMontageAndWait* ReleaseMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAction"), SkillActionAnimMontage);

		ReleaseMontageTask->OnCompleted.AddDynamic(this, &UMJGA_PlayerActionChargeSkill::OnReleaseMontageComplete);
		ReleaseMontageTask->OnInterrupted.AddDynamic(this, &UMJGA_PlayerActionChargeSkill::OnReleaseMontageComplete);
		ReleaseMontageTask->OnCancelled.AddDynamic(this, &UMJGA_PlayerActionChargeSkill::OnReleaseMontageComplete);

		ReleaseMontageTask->ReadyForActivation();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}
