// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJInteractableActor.h"
#include "GameFramework/Actor.h"
#include "MJPortalToDungeon.generated.h"

UCLASS()
class PROJECTMJ_API AMJPortalToDungeon : public AMJInteractableActor
{
	GENERATED_BODY()
	
public:	
	AMJPortalToDungeon();

	virtual void Execute() override;
protected:

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
};
