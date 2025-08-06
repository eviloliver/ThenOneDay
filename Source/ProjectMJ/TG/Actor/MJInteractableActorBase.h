// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MJInteractableActorBase.generated.h"


class UMJInteractComponent;
class USphereComponent;
class USoundCue;
/**
 * Class Description: AMJInteractableActor Base
 * Author: Cha Tae Gwan
 * Created Date: 2025-08-05
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-08-05
 */
UCLASS()
class PROJECTMJ_API AMJInteractableActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AMJInteractableActorBase();

	virtual void Execute();
	
protected:
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> SphereCollision;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMJInteractComponent> InteractComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> CollisionSFX;

};
