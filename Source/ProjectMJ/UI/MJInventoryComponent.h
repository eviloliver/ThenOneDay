// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MJInventoryWidget.h"
#include "Components/ActorComponent.h"
#include "MJInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<FName> RowNames;
	
public:	
	void SetItemData(UDataTable* ItemDataTable, int32 Index, UMJInventoryWidget* InventoryWidget);
};
