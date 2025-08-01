// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "MJForestCreatureCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API AMJForestCreatureCharacter : public AMJMonsterCharacter
{
	GENERATED_BODY()

public:
	AMJForestCreatureCharacter();

	virtual void BeginPlay() override;


private:

	
};
