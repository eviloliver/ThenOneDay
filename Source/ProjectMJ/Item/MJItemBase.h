// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemIndex; // 각각의 아이템에 넘버를 지정해두고 이걸로 지정하면 될 거 같음

public:
	
	UDataTable* GetItemData(){return ItemDataTable;}
	int32 GetItemIndex() {return ItemIndex;}
};
