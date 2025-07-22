// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MJStaticAISpawnRow.generated.h"

/**
 * Class Description: static AI Spawn Data Row
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-17
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-17
 */
USTRUCT(BlueprintType)
struct FMJStaticAISpawnDataRow : public  FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActor> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnWeight;

	
};