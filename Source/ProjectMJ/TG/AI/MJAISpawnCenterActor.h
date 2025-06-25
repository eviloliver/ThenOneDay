// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MJAISpawnCenterActor.generated.h"
/**
 * Class Description: Sphere Actor will be the Centor of the AISpawn
 * Author: Cha Tae Gwan
 * Created Date: 2025-06-23
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-06-23
 */
UCLASS()
class PROJECTMJ_API AMJAISpawnCenterActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMJAISpawnCenterActor();


protected:

	TObjectPtr<UStaticMeshComponent> Mesh;


};
