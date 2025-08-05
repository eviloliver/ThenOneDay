// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJInteractableActorBase.h"
#include "GameFramework/Actor.h"
#include "MJPortalToTown.generated.h"

/**
 * Class Description: Portal to Town
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-24
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-24
 */
UCLASS()
class PROJECTMJ_API AMJPortalToTown : public AMJInteractableActorBase
{
	GENERATED_BODY()
	
public:	
	AMJPortalToTown();
	
	virtual void Execute() override;
	
};
