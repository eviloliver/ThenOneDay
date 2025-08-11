// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/MJAT_GetMousePosition.h"

UMJAT_GetMousePosition::UMJAT_GetMousePosition()
{
}

UMJAT_GetMousePosition* UMJAT_GetMousePosition::CreateTask(UGameplayAbility* OwningAbility)
{
	UMJAT_GetMousePosition* NewTask = NewAbilityTask<UMJAT_GetMousePosition>(OwningAbility);
	return NewTask;
	
}

void UMJAT_GetMousePosition::Activate()
{
	Super::Activate();

	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	if (!PlayerController)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnFailed.Broadcast(FVector::ZeroVector);
		}
		EndTask();
		return;
	}
	FHitResult HitResult;

	// TODO: 이거 TraceChannel 땅만 감지하는걸로 만들어서 쓰자
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (HitResult.bBlockingHit)
		{
			OnCompleted.Broadcast(HitResult.Location);
		}
		else
		{
			OnFailed.Broadcast(FVector::ZeroVector);
		}
	}
	EndTask();
}