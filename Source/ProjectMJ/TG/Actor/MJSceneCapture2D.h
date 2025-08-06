// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "MJSceneCapture2D.generated.h"

class UProceduralMeshComponent;


/**
 * Class Description: SceneCapture2D
 * Author: Cha Tae Gwan
 * Created Date: 2025_07_31
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025_07_31
 */
UCLASS()
class PROJECTMJ_API AMJSceneCapture2D : public ASceneCapture2D
{
	GENERATED_BODY()

public:

	AMJSceneCapture2D();

	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> MiniMapBackgroundActor;

protected:

	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnActorSpawned(AActor* InputActor);

	UFUNCTION()
	void OnActorDestroyed(AActor* InputActor);
	
	UPROPERTY()
	TWeakObjectPtr<ACharacter> Player;

	UPROPERTY(EditDefaultsOnly)
	float CameraHeight;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterial> ProceduralMeshMaterial;

	
};

