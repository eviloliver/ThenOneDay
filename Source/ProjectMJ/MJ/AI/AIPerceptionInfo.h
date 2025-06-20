
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETeam_ID: uint8
{
	PLAYER = 0 UMETA(DisplayName = "PLAYER")/*플레이어*/,
	NPC UMETA(DisplayName = "NPC")/*NPC*/,
	MONSTER UMETA(DisplayName = "MONSTER")/*몬스터*/,
	NONE = 255	UMETA(DisplayName = "NONE") /*기본값. Neutral로 처리됩니다*/

};
