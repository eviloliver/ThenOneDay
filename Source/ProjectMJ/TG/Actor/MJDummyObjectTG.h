// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TG/Interface/MJInstancedActorInterface.h"
#include "MJDummyObjectTG.generated.h"

UCLASS()
class PROJECTMJ_API AMJDummyObjectTG : public AActor, public IMJInstancedActorInterface
{
	GENERATED_BODY()
	
public:	
	AMJDummyObjectTG();
	
protected:


	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
