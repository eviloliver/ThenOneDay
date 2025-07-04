// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MJProjectileDataAsset.generated.h"

/**
 * Class Description: 투사체 태그로 실제 투사체 클래스 매핑하는 데이터 에셋
 * Author: 신동민
 * Created Date: 2025.07.04
 * Last Modified By:
 * Last Modified Date:
 */

class AMJProjectileBase;

UCLASS()
class PROJECTMJ_API UMJProjectileDataAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (Categories = "Projectile"))
	TMap<FGameplayTag, TSubclassOf<AMJProjectileBase>> ProjectileMap;

	TSubclassOf<AMJProjectileBase> FindProjectileClassForTag(const FGameplayTag& Tag) const;

};
