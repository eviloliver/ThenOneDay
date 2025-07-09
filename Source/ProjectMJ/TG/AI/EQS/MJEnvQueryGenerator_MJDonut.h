// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_Donut.h"
#include "MJEnvQueryGenerator_MJDonut.generated.h"

/**
 * Class Description: EQS Query which generate random points in donut range
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-03
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-03
 */
UCLASS()
class PROJECTMJ_API UMJEnvQueryGenerator_MJDonut : public UEnvQueryGenerator_Donut
{
	GENERATED_BODY()

public:
	UMJEnvQueryGenerator_MJDonut(const FObjectInitializer& ObjectInitializer);
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = Generator)
	FAIDataProviderIntValue NumberOfRandomPoints;

	UPROPERTY(EditDefaultsOnly, Category = Debug)
	bool ShowDebugDonut = true;

	UPROPERTY(EditDefaultsOnly, Category = Debug)
	float ShowDebugLifeTime = 3.0f;
	
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;
	
};
