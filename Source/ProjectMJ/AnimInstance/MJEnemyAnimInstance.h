// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AnimInstance/MJAnimInstanceBase.h"
#include "MJEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJEnemyAnimInstance : public UMJAnimInstanceBase
{
	GENERATED_BODY()

public:
	UMJEnemyAnimInstance();
	
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds)override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Animation|LocomotionData")
	bool bIsInActivated;

	UFUNCTION()
	void TagConditionChanged(const FGameplayTag InTag, int32 NewCount);
};
