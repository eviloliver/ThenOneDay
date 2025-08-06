// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MJPlayMontage.generated.h"

/**
  * Class Description: BTTask_Play Montage
 * Author: Lee Ju Hyeon
 * Created Date: 2025.08.05.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
class UBehaviorTreeComponent;
UCLASS()
class PROJECTMJ_API UBTTask_MJPlayMontage : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_MJPlayMontage();

	UPROPERTY(EditAnywhere, Category="Animation")
	TObjectPtr<UAnimMontage> MontagePlay;
	UPROPERTY(EditAnywhere,Category="Animation")
	FName SessionName;

	UFUNCTION()
	void JumpToSection(UAnimInstance* AnimInstance);

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* AnimMontage, bool bInterrupted);
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	FTimerHandle WaitTimerHandle;
	UBehaviorTreeComponent* CachedComponent;

};
