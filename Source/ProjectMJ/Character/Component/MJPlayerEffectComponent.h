// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/MJEffectComponentBase.h"
#include "MJPlayerEffectComponent.generated.h"

/**
 * Class Description: 캐릭터 레벨업 할 때, 이펙트 재생
 * Author: 신동민
 * Created Date: 2025.07.21
 * Description of Change:
 * Modified By:
 * Modified Date:
 */

class UNiagaraSystem;

UCLASS()
class PROJECTMJ_API UMJPlayerEffectComponent : public UMJEffectComponentBase
{
	GENERATED_BODY()
public:
	UMJPlayerEffectComponent();

	UFUNCTION(BlueprintCallable)
	void PlayLevelUpEffect();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOwnerLevelUp(int32 NewLevel);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX|LevelUp")
	TObjectPtr<UNiagaraSystem> LevelUpVFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX|LevelUp")
	TObjectPtr<USoundBase> LevelUpSFX;
};
