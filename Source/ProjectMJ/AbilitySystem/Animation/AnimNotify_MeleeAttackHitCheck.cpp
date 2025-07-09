// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Animation/AnimNotify_MeleeAttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"

UAnimNotify_MeleeAttackHitCheck::UAnimNotify_MeleeAttackHitCheck()
{
}

FString UAnimNotify_MeleeAttackHitCheck::GetNotifyName_Implementation() const
{
	return TEXT("MeleeAttackHitCheck");
}

void UAnimNotify_MeleeAttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();
		if (OwnerActor)
		{
			FGameplayEventData PayloadData;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggerGameplayTag, PayloadData);
		}
		
	}
}
