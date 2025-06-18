// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/MJAT_Trace.h"
#include "AbilitySystem/TargetActor/MJTA_Trace.h"

UMJAT_Trace::UMJAT_Trace()
{

}

UMJAT_Trace* UMJAT_Trace::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<class AMJTA_Trace> TargetActorClass)
{
	UMJAT_Trace* NewTask = NewAbilityTask<UMJAT_Trace>(OwningAbility);
	// NewTask->TargetActorClass = TargetActorClass;
	return NewTask;
}

void UMJAT_Trace::Activate()
{
	Super::Activate();
}

void UMJAT_Trace::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

void UMJAT_Trace::SpawnAndInitializeTargetActor()
{
}

void UMJAT_Trace::FinalizeTargetActor()
{
}

void UMJAT_Trace::OnTargetDataReadyCallBack(const FGameplayAbilityTargetDataHandle& DataHandle)
{
}
