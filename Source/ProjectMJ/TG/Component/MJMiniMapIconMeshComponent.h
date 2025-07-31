// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MJMiniMapIconMeshComponent.generated.h"

/**
 * Class Description: MiniMapIconMeshComponent
 * Author: Cha Tae Gwan
 * Created Date: 2025-07-31
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-07-31
 */
UCLASS(Blueprintable)
class PROJECTMJ_API UMJMiniMapIconMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UMJMiniMapIconMeshComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> PlayerIcon;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> EnemyIcon;
	
};
