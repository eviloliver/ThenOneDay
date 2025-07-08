// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MJDataTable_Wave.generated.h"

/**
 * Class Description: Wave Datatable Row
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-03
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-03
 */
USTRUCT(BlueprintType)
struct FMJWaveDataRow : public  FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8 WaveNum;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemyCount;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<TSubclassOf<AActor>, int32> EnemyPool;
};