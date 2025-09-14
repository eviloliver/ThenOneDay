// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_MJSpawnTargetProjectile.generated.h"

class AMJTargetingProjectileBase;
/**
 * Class Description: 타게팅 발사체 스폰. 노티파이를 통해 스폰됨
 * Author: Kim Minjin
 * Created Date: 2025.07.26.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API UNotify_MJSpawnTargetProjectile : public UAnimNotify
{
	GENERATED_BODY()

public:
	UNotify_MJSpawnTargetProjectile();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AMJTargetingProjectileBase> TargetingProjectile;
	
};
