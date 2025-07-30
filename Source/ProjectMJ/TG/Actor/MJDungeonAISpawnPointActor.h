// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MJDungeonAISpawnPointActor.generated.h"

/**
 * Class Description: static Spawning Point Actor
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-03
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-03
 */
UCLASS()
class PROJECTMJ_API AMJDungeonAISpawnPointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMJDungeonAISpawnPointActor();

	UPROPERTY(EditAnywhere)
	uint8 NumberToSpawn;

protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
};
