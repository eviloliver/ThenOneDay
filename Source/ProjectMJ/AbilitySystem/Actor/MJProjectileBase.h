// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Struct/MJSkillProjectileParams.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "MJProjectileBase.generated.h"

/**
 * Class Description: Projectile Actor
 * Author: 신동민
 * Created Date: 2025.07.03
 * Last Modified By:
 * Last Modified Date:
 */

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraSystem;
class USoundBase;

UCLASS()
class PROJECTMJ_API AMJProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AMJProjectileBase();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite)
	FMJSkillProjectileParams ProjectileParams;

	void InitProjectileParams(const FMJSkillProjectileParams& InParams);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY()
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile|GameplayCue", meta = (Categories = "GameplayCue"))
	FGameplayTag HitGameplayCueTag;

	UPROPERTY(EditAnywhere, Category = "SFX")
	TObjectPtr<USoundBase> HitSFX;

	// float LifeSpan;
};
