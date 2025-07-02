// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MJProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class PROJECTMJ_API AMJProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AMJProjectileBase();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	// UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))

protected:

	UPROPERTY()
	TObjectPtr<USphereComponent> Sphere;


};
