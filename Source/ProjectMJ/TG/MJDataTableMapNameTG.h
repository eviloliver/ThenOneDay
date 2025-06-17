// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MJDataTableMapNameTG.generated.h"

/**
 * Class Description: 테스트용 Datatable Row
 * Author: 차태관
 * Created Date: 2025-06-15
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-15
 */
USTRUCT(BlueprintType)
struct FMJDataTableMapNameTG : public  FTableRowBase
{
public:
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MapName;

	
};