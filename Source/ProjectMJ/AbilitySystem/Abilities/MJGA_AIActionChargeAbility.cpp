// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_AIActionChargeAbility.h"

#include "MotionWarpingComponent.h"
#include "AIController.h"
#include "ProjectMJ.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/MJCharacterBase.h"
#include "Character/Component/MJAbilityContextComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MJ/AI/MJMonsterAIControllerBase.h"

UMJGA_AIActionChargeAbility::UMJGA_AIActionChargeAbility()
{
	ChargeTime = 0.3f;
}

void UMJGA_AIActionChargeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AMJCharacterBase* SourceCharacter = Cast<AMJCharacterBase>(ActorInfo->AvatarActor.Get());
	if (!SourceCharacter)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist SourceCharacter"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AMJMonsterAIControllerBase* AIController = Cast<AMJMonsterAIControllerBase>(SourceCharacter->GetController());
	if (!AIController)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist AIController"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist BlackboardComponent"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("Target"));
	if (!TargetActor)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist TargetActor"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	FVector AimLocation = TargetActor->GetActorLocation();

	UMJAbilityContextComponent* ContextComponent = SourceCharacter->FindComponentByClass<UMJAbilityContextComponent>();
	if (ContextComponent)
	{
		ContextComponent->LastTargetedMouseLocation = AimLocation;
	}

	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(SourceCharacter->GetActorLocation(), AimLocation);
	TargetRotation.Pitch = 0;
	TargetRotation.Roll = 0;

	UMotionWarpingComponent* MotionWarpingComponent = SourceCharacter->FindComponentByClass<UMotionWarpingComponent>();
	if (MotionWarpingComponent)
	{
		FMotionWarpingTarget Target = {};
		Target.Location = TargetActor->GetActorLocation();
		Target.Rotation = TargetRotation;
		Target.Name = FName("T");

		MotionWarpingComponent->AddOrUpdateWarpTarget(Target);
	}

	UAbilityTask_PlayMontageAndWait* ChargeTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("Charging"), SkillChargeAnimMontage, 1.0f);
	ChargeTask->ReadyForActivation();

	UAbilityTask_WaitDelay* DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, ChargeTime);
	DelayTask->OnFinish.AddDynamic(this, &UMJGA_AIActionChargeAbility::OnChargeDelayFinished);
	DelayTask->ReadyForActivation();
}

void UMJGA_AIActionChargeAbility::OnChargeDelayFinished()
{
	PlayReleaseMontage();
}

void UMJGA_AIActionChargeAbility::OnReleaseMontageComplete()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);

}

void UMJGA_AIActionChargeAbility::PlayReleaseMontage()
{
	if (CurrentActorInfo->AnimInstance.IsValid() && SkillChargeAnimMontage)
	{
		CurrentActorInfo->AnimInstance->Montage_Stop(0.1f, SkillChargeAnimMontage);
	}

	if (SkillActionAnimMontage)
	{
		UAbilityTask_PlayMontageAndWait* ReleaseTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("ActionChargeAttack"), SkillActionAnimMontage, 1.0f);

		ReleaseTask->OnCompleted.AddDynamic(this, &UMJGA_AIActionChargeAbility::OnReleaseMontageComplete);
		ReleaseTask->OnInterrupted.AddDynamic(this, &UMJGA_AIActionChargeAbility::OnReleaseMontageComplete);
		ReleaseTask->OnCancelled.AddDynamic(this, &UMJGA_AIActionChargeAbility::OnReleaseMontageComplete);

		ReleaseTask->ReadyForActivation();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

}
