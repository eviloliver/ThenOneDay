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
 * Last Modified By: 김민진
 * Last Modified Date: (25.08.24.)상속받아서 쓸 수 있게 private 영역을 protected로 변경,
 * 나이아가라 스케일 계산 변경, OnSphereHit Detroy 주석 처리, 디버그 구 추가
 */

class UMJProjectileReactionBehaviorBase;
class UMJProjectileMovementBehaviorBase;
class UNiagaraComponent;
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

	virtual void Tick(float DeltaSeconds) override;

	void InitProjectile(const FMJSkillProjectileParams& InParams, TSubclassOf<UMJProjectileMovementBehaviorBase> InMovementBehaviorClass, const TArray<TSubclassOf<UMJProjectileReactionBehaviorBase>>& InReactionBehaviorClasses);

	FORCEINLINE USphereComponent* GetSphere() const { return Sphere; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	UPROPERTY(BlueprintReadWrite)
	FMJSkillProjectileParams ProjectileParams;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior")
	TObjectPtr<UMJProjectileMovementBehaviorBase> MovementBehavior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior")
	TArray<TObjectPtr<UMJProjectileReactionBehaviorBase>> ReactionBehaviors;

/*private:*/
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (Categories = "GameplayCue"))
	FGameplayTag HitGameplayCueTag;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float VFXRatio = 1.0f;

	UPROPERTY(EditAnywhere, Category = "SFX")
	TObjectPtr<USoundBase> HitSFX;

};
