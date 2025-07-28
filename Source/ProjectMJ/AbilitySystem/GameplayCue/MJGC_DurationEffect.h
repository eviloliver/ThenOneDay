// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "MJGC_DurationEffect.generated.h"

/**
 * Class Description: 지속적인 효과를 주는 Effect에 부여하는 GameplayCue
 * Author: 신동민
 * Created Date: 2025.07.28
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class PROJECTMJ_API AMJGC_DurationEffect : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public:
	AMJGC_DurationEffect();

protected:
	virtual void BeginPlay() override;

	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool WhileActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayCue")
	TObjectPtr<UNiagaraSystem> ActiveNiagaraSystem;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayCue")
	FName ActiveNiagaraSystemSocketName;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveNiagaraComponent;

	// TODO: SFX


};
