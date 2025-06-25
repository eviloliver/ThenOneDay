// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AnimNotify_MeleeAttackHitCheck.generated.h"

/**
 * Class Description: 근접 공격(Melee Attack) 관련 애니메이션 몽타주에서 활용할 AnimNotify
 * Author: 신동민
 * Created Date: 2025_06_20
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UAnimNotify_MeleeAttackHitCheck : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_MeleeAttackHitCheck();

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, Meta = (Categories = Event))
	FGameplayTag TriggerGameplayTag;

	// Combo Attack ??
	// 디아블로, PoE, SoD는 없는데 로스트 아크는 있는 것
};
