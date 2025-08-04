// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "MJGC_ProjectileExplosion.generated.h"

/**
 * Class Description: 투사체 직선 이동
 * Author: 신동민
 * Created Date: 2025.07.31
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

class UNiagaraSystem;

UCLASS()
class PROJECTMJ_API UMJGC_ProjectileExplosion : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

public:
	UMJGC_ProjectileExplosion();

	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayCue")
	TObjectPtr<UNiagaraSystem> ExplosionVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayCue")
	float Scale;

	//TODO: Sound

};
