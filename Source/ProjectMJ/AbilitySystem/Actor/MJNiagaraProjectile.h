// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "MJNiagaraProjectile.generated.h"

/**
 * Class Description: 나이아가라 자연스럽게 사라지는 발사체
 * Author: Kim Minjin
 * Created Date: 2025.08.24.
 * Last Modified By:
 * Last Modified Date:
 */
UCLASS()
class PROJECTMJ_API AMJNiagaraProjectile : public AMJProjectileBase
{
	GENERATED_BODY()

public:
	AMJNiagaraProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
	virtual void OnNiagaraEnded(UNiagaraComponent* PSystem);
};
