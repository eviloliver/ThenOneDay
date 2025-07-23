// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "MJItemBase.generated.h"

class UDataTable;
class UMJInventoryComponent;
UCLASS()
class PROJECTMJ_API AMJItemBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FGameplayTag ItemTag;
	
public:
	FGameplayTag GetItemTag() {return ItemTag;}
};
