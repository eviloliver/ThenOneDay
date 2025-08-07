// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJInteractableActorBase.h"
#include "GameFramework/Actor.h"
#include "TG/Interface/MJInstancedActorInterface.h"
#include "MJPortalToNextDungeon.generated.h"

class UMJMiniMapIconMeshComponent;
/**
 * Class Description: (currently not using) PortalToNextDungeon
 * Author: Cha Tae Gwan
 * Created Date: 2025_07_29
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025_07_29
 */
UCLASS()
class PROJECTMJ_API AMJPortalToNextDungeon : public AMJInteractableActorBase, public IMJInstancedActorInterface
{
	GENERATED_BODY()
	
public:	
	AMJPortalToNextDungeon();

	virtual void Execute() override;

protected:

	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMJMiniMapIconMeshComponent> MiniMapIconMesh;
	
	
	
};
