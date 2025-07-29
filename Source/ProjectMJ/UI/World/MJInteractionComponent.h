// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MJInteractionComponent.generated.h"

class UMJUIManagerSubsystem;
/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent))
class PROJECTMJ_API UMJInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()

	UMJInteractionComponent();
	
public:
	void SetInteractionWidget();
	void Active(FString key);
	void Deactive();
	
};
