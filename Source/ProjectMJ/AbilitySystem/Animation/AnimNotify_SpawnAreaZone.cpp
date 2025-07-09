// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Animation/AnimNotify_SpawnAreaZone.h"
#include "AbilitySystemBlueprintLibrary.h"

UAnimNotify_SpawnAreaZone::UAnimNotify_SpawnAreaZone()
{
}

FString UAnimNotify_SpawnAreaZone::GetNotifyName_Implementation() const
{
	return TEXT("Spawn AreaZone Notify");
}

void UAnimNotify_SpawnAreaZone::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
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
