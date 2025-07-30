// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MJPortalToDungeon.generated.h"

class USphereComponent;
UCLASS()
class PROJECTMJ_API AMJPortalToDungeon : public AActor
{
	GENERATED_BODY()
	
public:	
	AMJPortalToDungeon();
	
protected:
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void GotoDungeon( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnAudioFinish(); 
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	TObjectPtr<USoundCue> CollisionSFX; 


};
