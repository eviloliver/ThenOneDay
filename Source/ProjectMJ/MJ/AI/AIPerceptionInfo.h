
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETeam_ID: uint8
{
	// 몬스터는 플레이어를 적으로 인식합니다.
	PLAYER = 0 UMETA(DisplayName = "PLAYER"),
	// 몬스터는 NPC를 적으로 인식하지 않습니다(Neutral로 인식).
	NPC UMETA(DisplayName = "NPC"),
	// 몬스터의 기본 설정입니다.
	MONSTER UMETA(DisplayName = "MONSTER"),
	// 기본값. Neutral로 처리됩니다.
	NONE = 255	UMETA(DisplayName = "NONE")

};
