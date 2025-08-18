// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "MJSpiderMinionCharacter.generated.h"

/**
 * Class Description: SpiderMinion
 * Author: Lee JuHyeon
 * Created Date: 2025.08.11.

 */
UCLASS()
class PROJECTMJ_API AMJSpiderMinionCharacter : public AMJMonsterCharacter
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetbIsOpen(bool Value);

};
