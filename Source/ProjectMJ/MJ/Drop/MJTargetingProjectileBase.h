// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "MJTargetingProjectileBase.generated.h"

DECLARE_DELEGATE(FOnLocationChangedDelegate);

class UProjectileMovementComponent;
class UNiagaraComponent;
class USphereComponent;
class AMJCharacterBase;
class UNiagaraSystem;
/**
 * Class Description: 나이아가라 적용. 이벤트 처리
 * Author: Kim Minjin
 * Created Date: 2025.07.24.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API AMJTargetingProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMJTargetingProjectileBase();

	void SetTarget(AActor* TargetActor) {Target = TargetActor;};

	void SetSkillTag(const FGameplayTag& Tag) {SkillTag = Tag;}

	FOnLocationChangedDelegate TargetLocationChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnTargetUpdated();

	UFUNCTION()
	virtual void OnEnded(UNiagaraComponent* PSystem);
	
	UPROPERTY()
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> MuzzleFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> ProjectileFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> HitFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> Target;
	
	FGameplayTag SkillTag;
	
	FVector PreTargetLocation;
	FVector CurrentTargetLocation;
	
	UPROPERTY(EditDefaultsOnly) // TG : 25.08.11
	TObjectPtr<USoundCue> OverlapSFX;
	
};
