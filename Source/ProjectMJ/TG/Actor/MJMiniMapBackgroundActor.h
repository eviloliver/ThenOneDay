// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MJMiniMapBackgroundActor.generated.h"


/**
 * Class Description: MinMapBackgroundActor
 * Author: Cha Tae Gwan
 * Created Date: 2025_07_31
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025_07_31
 */
UCLASS()
class PROJECTMJ_API AMJMiniMapBackgroundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMJMiniMapBackgroundActor();

protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	

};
