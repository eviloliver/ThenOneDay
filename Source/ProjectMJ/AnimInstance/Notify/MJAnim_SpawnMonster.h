// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "MJAnim_SpawnMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJAnim_SpawnMonster : public UAnimNotify
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Pawn")
	TSubclassOf<APawn> SpawnMonster;

	UPROPERTY(EditAnywhere,Category="Pawn")
	int32 SpawnCount;
	UPROPERTY(EditAnywhere,Category="Pawn")
	float OuterRadius;

	UPROPERTY(EditAnywhere,Category="Pawn")
	bool ForwordSpawn;

	UFUNCTION()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:

	TArray<FVector> SpawnLocation;

	float MinDistance = 30.f;
};
