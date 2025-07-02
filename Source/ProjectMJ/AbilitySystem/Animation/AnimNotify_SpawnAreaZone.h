// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AnimNotify_SpawnAreaZone.generated.h"

/**
 * Class Description: MeleeAttackHitCheck과 현재 기능은 똑같지만 분리와 확장을 고려해서 만듦
 * Author: 신동민
 * Created Date: 2025_07_02
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UAnimNotify_SpawnAreaZone : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_SpawnAreaZone();

protected:
	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, Meta = (Categories = Event))
	FGameplayTag TriggerGameplayTag;
};
