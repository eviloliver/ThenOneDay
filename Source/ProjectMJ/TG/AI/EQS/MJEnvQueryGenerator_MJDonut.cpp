// Fill out your copyright notice in the Description page of Project Settings.


#include "MJEnvQueryGenerator_MJDonut.h"

#include "EnvironmentQuery/EQSTestingPawn.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_Donut.h"
#include "Kismet/GameplayStatics.h"


UMJEnvQueryGenerator_MJDonut::UMJEnvQueryGenerator_MJDonut(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Center = UEnvQueryContext_Querier::StaticClass();
	InnerRadius.DefaultValue = 700.0f;
	OuterRadius.DefaultValue = 1300.0f;
	NumberOfRandomPoints.DefaultValue = 10;
	NumberOfRings.DefaultValue = 3;
	PointsPerRing.DefaultValue = 8;
	ArcDirection.DirMode = EEnvDirection::TwoPoints;
	ArcDirection.LineFrom = UEnvQueryContext_Querier::StaticClass();
	ArcDirection.Rotation = UEnvQueryContext_Querier::StaticClass();
	ArcAngle.DefaultValue = 360.f;
	bUseSpiralPattern = false;

	ProjectionData.TraceMode = EEnvQueryTrace::Navigation;
}

void UMJEnvQueryGenerator_MJDonut::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	// Didn`t Call Super cuz it`s customization of Engine API.
	//Super::GenerateItems(QueryInstance);

	TArray<FVector> CenterPoints;
	QueryInstance.PrepareContext(Center, CenterPoints);

	if (CenterPoints.Num() <= 0)
	{
		return;
	}

	UObject* BindOwner = QueryInstance.Owner.Get();
	InnerRadius.BindData(BindOwner, QueryInstance.QueryID);
	OuterRadius.BindData(BindOwner, QueryInstance.QueryID);

	FVector::FReal InnerRadiusValue = InnerRadius.GetValue();
	FVector::FReal OuterRadiusValue = OuterRadius.GetValue();
	int32 NumPoints = NumberOfRandomPoints.GetValue();

	if ((InnerRadiusValue < 0.) || (OuterRadiusValue <= 0.) ||
		(InnerRadiusValue > OuterRadiusValue))
	{
		return;
	}

	TArray<FNavLocation> Points;
	Points.Reserve(NumPoints);
	
	for (int32 PointIdx = 0 ; PointIdx < NumPoints ; ++PointIdx)
	{
		FVector Dir = FMath::VRand();
		Dir.Z = 0.f;
		Dir.Normalize();
		
		float Dist = FMath::FRandRange(InnerRadiusValue,OuterRadiusValue);
		FVector Location = CenterPoints[0] + Dir * Dist;
		
		const FNavLocation PointPos = FNavLocation(Location);
		Points.Add(PointPos);
	}

#if WITH_EDITOR
	// Not properly working now
	if (ShowDebugDonut) 
	{
		AActor* TestingPawn = UGameplayStatics::GetActorOfClass(GetWorld(),AEQSTestingPawn::StaticClass());

		if (TestingPawn)
		{
			if (TestingPawn->IsSelected())
			{
				//DrawDebugCircle(GetWorld(), CenterPoints[0], InnerRadiusValue, 20, FColor::Red, false,ShowDebugLifeTime,0,5.0f,FVector(1,0,0), FVector(0,1,0), false);
				//DrawDebugCircle(GetWorld(), CenterPoints[0], OuterRadiusValue, 20, FColor::Red, false,ShowDebugLifeTime,0,5.0f,FVector(1,0,0), FVector(0,1,0), false);
			}
			else
			{
				FlushPersistentDebugLines(GetWorld());
			}
		}
	}
#endif

	ProjectAndFilterNavPoints(Points, QueryInstance);
	StoreNavPoints(Points, QueryInstance);
}
