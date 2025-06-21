// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "MJPlayerStructType.generated.h"

class UMJPlayerLinkAnimLayer;

USTRUCT(BlueprintType)
struct FMJPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UMJPlayerLinkAnimLayer> WeaponAnimLayerToLink;
};

