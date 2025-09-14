// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "MJSkillDropTest.generated.h"

/**
 * Class Description: SkillDropTest-테스트용
 * Author: Kim Minjin
 * Created Date: 2025.07.
 * Last Modified By: (Last Modifier)
 * Last Modified Date: (Last Modified Date)
 */
UCLASS()
class PROJECTMJ_API AMJSkillDropTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMJSkillDropTest();

	void SetSkillTag(const FGameplayTag& Tag) { SkillTag = Tag;}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	
	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	FGameplayTag SkillTag;
	
public:	

};
