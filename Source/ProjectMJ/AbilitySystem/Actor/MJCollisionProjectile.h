// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "MJCollisionProjectile.generated.h"

/**
 * Class Description: 콜리전만 생성하는 발사제 - 나이아가라는 
 * Author: Kim Minjin
 * Created Date: 2025.07.03
 * Last Modified By:
 * Last Modified Date:
 */
UCLASS()
class PROJECTMJ_API AMJCollisionProjectile : public AMJProjectileBase
{
	GENERATED_BODY()

public:
	AMJCollisionProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
	virtual void OnNiagaraEnded(UNiagaraComponent* PSystem);
};
