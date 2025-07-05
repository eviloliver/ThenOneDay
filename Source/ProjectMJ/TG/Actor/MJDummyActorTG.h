// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TG/Interface/MJAIEventManager.h"
#include "TG/Interface/MJInstancedActorInterface.h"
#include "MJDummyActorTG.generated.h"
/**
 * Class Description: 맵 간 이동 시 액터 복원 확인을 위한 더미 액터
 * Author: 차태관
 * Created Date: 2025-06-13
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-13
 * Last Modified By: 차태관
 * Last Modified Date: 2025-06-25
 */
UCLASS()
class PROJECTMJ_API AMJDummyActorTG : public AActor, public IMJInstancedActorInterface
{
	GENERATED_BODY()
	
public:	
	AMJDummyActorTG();

protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


};
