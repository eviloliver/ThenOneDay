// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MJAnimMontageDataAsset.generated.h"

/**
 * Class Description: 애니메이션 몽타주 태그로 실제 애니메이션 몽타주에 매핑하는 데이터 에셋
 * Author: 신동민
 * Created Date: 2025.07.04
 * Last Modified By:
 * Last Modified Date:
 */

class UAnimMontage;

UCLASS()
class PROJECTMJ_API UMJAnimMontageDataAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "AnimMontage", meta = (Categories = "Animation"))
	TMap<FGameplayTag, TObjectPtr<UAnimMontage>> AnimMontageMap;

public:
	UAnimMontage* FindAnimMontageForTag(const FGameplayTag& Tag) const;

};
