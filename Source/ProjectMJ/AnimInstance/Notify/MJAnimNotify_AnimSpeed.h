// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "MJAnimNotify_AnimSpeed.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJAnimNotify_AnimSpeed : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, Category="Rate")
	float NewPlayRate;
	
	UFUNCTION()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


};
