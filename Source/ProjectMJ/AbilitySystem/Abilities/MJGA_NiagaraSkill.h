// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MJGA_GameplayAbility.h"
#include "MJGA_NiagaraSkill.generated.h"

class UNiagaraSystem;
class AMJTA_CustomTrace;
/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJGA_NiagaraSkill : public UMJGA_GameplayAbility
{
	GENERATED_BODY()

public:
	UMJGA_NiagaraSkill();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected:
	UFUNCTION()
	void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	TObjectPtr<UNiagaraSystem> AttackVFX;
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Effects")
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Effects")
	TSubclassOf<UGameplayEffect> StatusGameplayEffectClass;

	UPROPERTY(EditAnywhere, Category = "GAS")
	AMJTA_CustomTrace* TargetActorClass;

	UPROPERTY(EditAnywhere, Category = "GameplayCue" , meta = (Categories = "GameplayCue"))
	FGameplayTag GameplayCueTag;
};
