// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MJDamageComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMJ_API UMJDamageComponent : public UWidgetComponent
{
	GENERATED_BODY()

	UMJDamageComponent();
protected:
	
public:
	void SetWidget();
};
