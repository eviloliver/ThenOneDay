// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJInteractableActorBase.h"
#include "GameFramework/Actor.h"
#include "MJPortalToDungeon.generated.h"

UCLASS()
class PROJECTMJ_API AMJPortalToDungeon : public AMJInteractableActorBase
{
	GENERATED_BODY()
	
public:	
	AMJPortalToDungeon();

	virtual void Execute() override;
};
