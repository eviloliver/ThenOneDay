// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MJStatComponentBase.generated.h"

/**
 * Class Description: Character Stat Component
 * Author: 신동민
 * Created Date: 2025.07.17
 * Modified By:
 * Modified Date:
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathDelegate, AActor*, InEffectCauser);

class UGameplayEffect;

UCLASS( ClassGroup=(Stat), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJStatComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMJStatComponentBase();

	virtual void InitializeStat() {};

	FORCEINLINE void SetbIsDead(bool NewbIsDead) {bIsDead = NewbIsDead;}
	FORCEINLINE bool GetbIsDead() const { return bIsDead; }
	
	FORCEINLINE void SetbbIsInitializingStats(bool NewbIsInitializingStats) {bIsInitializingStats = NewbIsInitializingStats;}
	FORCEINLINE bool GetbIsInitializingStats() const { return bIsInitializingStats; }

	virtual void OnDead(AActor* InEffectCauser);

	FOnDeathDelegate OnDeath;

protected:

	UPROPERTY()
	bool bIsDead = false;
	
	bool bIsInitializingStats = false;
	
};
