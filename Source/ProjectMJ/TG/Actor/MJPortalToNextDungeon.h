// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TG/Interface/MJInstancedActorInterface.h"
#include "MJPortalToNextDungeon.generated.h"

class UMJMiniMapIconMeshComponent;
class USoundCue;
/**
 * Class Description: (currently not using) PortalToNextDungeon
 * Author: Cha Tae Gwan
 * Created Date: 2025_07_29
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025_07_29
 */
UCLASS()
class PROJECTMJ_API AMJPortalToNextDungeon : public AActor, public IMJInstancedActorInterface
{
	GENERATED_BODY()
	
public:	
	AMJPortalToNextDungeon();

protected:
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> CollisionSFX;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMJMiniMapIconMeshComponent> MiniMapIconMesh;
	
	
	
};
