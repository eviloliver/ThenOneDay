// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "MJEffectComponentBase.generated.h"

/**
 * Class Description: 캐릭터로 부터 나오는 VFX/SFX 를 재생하는 컴포넌트
 * Author: 신동민
 * Created Date: 2025.07.21
 * Description of Change: 
 * Modified By:
 * Modified Date:
 */

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS( ClassGroup=("VFX/SFX"), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJEffectComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMJEffectComponentBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnStatusTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	void ApplyPoisonEffect();
	void RemovePoisonEffect();
	void ApplyStunEffect();
	void RemoveStunEffect();
	void ApplyBurningEffect();
	void RemoveBurningEffect();
	void ApplyFrozenEffect();
	void RemoveFrozenEffect();

protected:

	// Status Section
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX|StatusEffects")
	TObjectPtr<UNiagaraSystem> PoisonVFX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX|StatusEffects")
	TObjectPtr<USoundBase> PoisonSFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX|StatusEffects")
	TObjectPtr<UNiagaraSystem> StunVFX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX|StatusEffects")
	TObjectPtr<USoundBase> StunSFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX|StatusEffects")
	TObjectPtr<UNiagaraSystem> BurningVFX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX|StatusEffects")
	TObjectPtr<USoundBase> BurningSFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX|StatusEffects")
	TObjectPtr<UNiagaraSystem> FrozenVFX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX|StatusEffects")
	TObjectPtr<USoundBase> FrozenSFX;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActivePoisonVFX;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveStunVFX;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveBurningVFX;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveFrozenVFX;
		
};
