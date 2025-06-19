// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/MJAT_Trace.h"
#include "AbilitySystem/TargetActor/MJTA_Trace.h"
#include "AbilitySystemComponent.h"


UMJAT_Trace::UMJAT_Trace()
{

}

UMJAT_Trace* UMJAT_Trace::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<class AMJTA_Trace> TargetActorClass)
{
	UMJAT_Trace* NewTask = NewAbilityTask<UMJAT_Trace>(OwningAbility);
	NewTask->TargetActorClass = TargetActorClass;
	return NewTask;
}

void UMJAT_Trace::Activate()
{
	Super::Activate();

	SpawnAndInitializeTargetActor();
	FinalizeTargetActor();

	SetWaitingOnAvatar();
}

void UMJAT_Trace::OnDestroy(bool bInOwnerFinished)
{
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->Destroy();
	}

	Super::OnDestroy(bInOwnerFinished);
}

void UMJAT_Trace::SpawnAndInitializeTargetActor()
{
	SpawnedTargetActor = Cast<AMJTA_Trace>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetActorClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->SetShowDebug(true);
		SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &UMJAT_Trace::OnTargetDataReadyCallback);
	}
}

void UMJAT_Trace::FinalizeTargetActor()
{
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	if (ASC)
	{
		const FTransform SpawnTransform = ASC->GetAvatarActor()->GetTransform();
		SpawnedTargetActor->FinishSpawning(SpawnTransform);

		ASC->SpawnedTargetActors.Push(SpawnedTargetActor);
		SpawnedTargetActor->StartTargeting(Ability);
		SpawnedTargetActor->ConfirmTargeting();
	}
}

void UMJAT_Trace::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast(DataHandle);
	}

	EndTask();
}
