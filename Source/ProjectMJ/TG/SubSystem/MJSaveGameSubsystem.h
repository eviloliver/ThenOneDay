// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MJSaveGameSubsystem.generated.h"

/**
 * Class Description: GameInstance Subsystem saves GameData
 * Author: Cha Tae Gwan
 * Created Date: 2025-06-20
 * Last Modified By: Cha Tae Gwan
 * Last Modified Date: 2025-06-20
 */
UCLASS()
class PROJECTMJ_API UMJSaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UMJSaveGameSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	UMJSaveGame* GetSaveGameData();

	UFUNCTION(BlueprintCallable)
	FString GetSaveSlotName() const;

	UFUNCTION(BlueprintCallable)
	int32 GetUserIndex() const;

	UFUNCTION(BlueprintCallable)
	void CreateSaveGame();
	
	UFUNCTION(BlueprintCallable)
	void LoadSaveGame(AMJPlayerCharacter* Player);

	UFUNCTION(BlueprintCallable)
	void SaveGameToSlot(AMJPlayerCharacter* Player);


	// Loading Screen Section
	
	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoadedWorld);

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UUserWidget> LoadingScreen;
	
protected:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMJSaveGame> SaveGameData;
	
	const FString SaveSlotName = TEXT("DefaultSaveGameSlot");

	const int32 UserIndex = 0;
	
};
