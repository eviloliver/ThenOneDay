// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJInteractableActor.h"
#include "GameFramework/Actor.h"
#include "MJSavePointActor.generated.h"

/**
 * Class Description: SavePoint
 * Author: Cha Tae Gwan
 * Created Date: 2025-08-05
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-08-05
 */
UCLASS()
class PROJECTMJ_API AMJSavePointActor : public AMJInteractableActor
{
	GENERATED_BODY()
	
public:	
	AMJSavePointActor();

	virtual void Execute() override;

};
