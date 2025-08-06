// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/MJStatComponentBase.h"
#include "MJPlayerStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpDelegate, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExperienceChanged, float, TotalExperience, float, ExpForNextLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChangeDelegate, int32, NewGold);

/**
 * Class Description: 플레이어는 GameInstance에 있는 CurveTable을 바로 접근
 * Author: 신동민
 * Created Date: 2025.07.17
 * Description of Change: 레벨 업 추가
 * Modified By: 신동민
 * Modified Date: 2025.07.21
 */

class UCurveTable;

UCLASS()
class PROJECTMJ_API UMJPlayerStatComponent : public UMJStatComponentBase
{
	GENERATED_BODY()

public:
	UMJPlayerStatComponent();

	virtual void InitializeStat() override;

	UFUNCTION(BlueprintCallable, Category = "Stat|Experience")
	void GainExperience(int32 GainedExp);

	UFUNCTION(Category = "Stat|Gold")
	void GainGold(int32 GainedGold);

	UFUNCTION(Category = "Stat|Gold")
	void SpendGold(int32 UsedGold);

	UPROPERTY(BlueprintAssignable, Category = "Stat|Experience")
	FOnLevelUpDelegate OnLevelUp;

	UPROPERTY(BlueprintAssignable, Category = "Stat|Experience")
	FOnExperienceChanged OnExperienceChanged;

	UPROPERTY(BlueprintAssignable, Category = "Stat|Gold")
	FOnGoldChangeDelegate OnGoldChange;
	
	FORCEINLINE int32 GetPlayerLevel() const { return PlayerLevel; }
	FORCEINLINE float GetTotalCumulativeExperience() const { return TotalCumulativeExperience; }
	FORCEINLINE float GetExperienceForNextLevel() const { return ExperienceForNextLevel; }
	FORCEINLINE int32 GetGold() const { return Gold; }
	FORCEINLINE void SetPlayerLevel(int32 NewPlayerLevel) {PlayerLevel = NewPlayerLevel;}
	FORCEINLINE void SetTotalCumulativeExperience(float NewExp){ TotalCumulativeExperience = NewExp;}


	float GetNumerator();
	float GetDenominator();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	TObjectPtr<UCurveTable> PlayerStatTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat|Level")
	int32 PlayerLevel = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Experience")
	float TotalCumulativeExperience = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Experience")
	float ExperienceForNextLevel = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Gold")
	int32 Gold = 100; // 테스트용으로 100

	float Numerator;
	float Denominator;

	
private:
	void CheckForLevelUp();
	float GetTotalExperienceForLevel(int32 Level) const;
};
