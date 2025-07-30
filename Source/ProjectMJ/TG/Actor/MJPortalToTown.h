// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MJPortalToTown.generated.h"

class USphereComponent;
/**
 * Class Description: Portal to Town
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-24
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-24
 */
UCLASS()
class PROJECTMJ_API AMJPortalToTown : public AActor
{
	GENERATED_BODY()
	
public:	
	AMJPortalToTown();

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> Collision;

	virtual void BeginPlay() override;

	UFUNCTION()
	void GotoTown( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
