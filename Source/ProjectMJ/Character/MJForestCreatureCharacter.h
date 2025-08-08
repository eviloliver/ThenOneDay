// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "MJForestCreatureCharacter.generated.h"

/**
 * 
 */
class UMJCharacterAttributeSet;
UCLASS()
class PROJECTMJ_API AMJForestCreatureCharacter : public AMJMonsterCharacter
{
	GENERATED_BODY()

public:
	AMJForestCreatureCharacter();

	virtual void BeginPlay() override;
	virtual float GetAIMaximumAttackRange() override;
	virtual float GetAIMinimumAttackRange() override;

	FORCEINLINE UMJCharacterAttributeSet* GetAttributeSet() { return CharacterAttributeSet; }

private:

	
};
