// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "MJBossMonsterCharacter.generated.h"

/**
 * Class Description: Boss Character
 * Author: Lee JuHyeon
 * Created Date: 2025.08.19.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API AMJBossMonsterCharacter : public AMJMonsterCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	void OnHealthChanged(const FOnAttributeChangeData& Data);
	FORCEINLINE UMJCharacterAttributeSet* GetAttributeSet() { return CharacterAttributeSet; }

private: 
	bool bHasTriggerPatten;
};
