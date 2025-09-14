// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "MJItemBase.generated.h"

class UMJNameBarWidgetComponent;
class UDataTable;
class UMJInventoryComponent;
UCLASS()
class PROJECTMJ_API AMJItemBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FGameplayTag ItemTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TObjectPtr<UMJNameBarWidgetComponent> NameBarWidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> MeshComp; //
public:
	AMJItemBase();

	virtual	void BeginPlay() override;
	FGameplayTag GetItemTag() {return ItemTag;}
};
