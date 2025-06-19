// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MJWeaponBase.generated.h"

class UBoxComponent;
/*
 * Class Description: WeaponData Base
 * Author: Lee JuHyeon
 * Created Date: 2025_06_18
 * Last Modified By:Create WeaponData 
 * Last Modified Date: 2025_06_18
*/
UCLASS()
class PROJECTMJ_API AMJWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMJWeaponBase();

protected:
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Mesh")
	TObjectPtr<UStaticMeshComponent>WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr <UBoxComponent> WeaponCollision;

public:
	FORCEINLINE UBoxComponent* GetWeaponCollision() { return WeaponCollision; }

};
