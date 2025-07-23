// Fill out your copyright notice in the Description page of Project Settings.


#include "MJSaveGameSubsystem.h"

#include "MoviePlayer.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/Struct/MJSaveGame.h"

UMJSaveGameSubsystem::UMJSaveGameSubsystem()
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> LoadingScreenRef(TEXT("/Game/TG/TestWBP/WBP_LoadingScreen.WBP_LoadingScreen_C"));
	if (LoadingScreenRef.Succeeded())
	{
		LoadingScreen = LoadingScreenRef.Class;
	}
}

void UMJSaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMJSaveGameSubsystem::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMJSaveGameSubsystem::EndLoadingScreen);
}

void UMJSaveGameSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
	//SaveGameToCurrentSlotNum();
	
}

void UMJSaveGameSubsystem::BeginLoadingScreen(const FString& MapName)
{
	
	FLoadingScreenAttributes LoadingScreenAttr;

	UUserWidget* Buffer = CreateWidget<UUserWidget>(GetGameInstance(), LoadingScreen);
		
	LoadingScreenAttr.WidgetLoadingScreen = Buffer->TakeWidget();
	LoadingScreenAttr.bAutoCompleteWhenLoadingCompletes = false;
	LoadingScreenAttr.MinimumLoadingScreenDisplayTime = 2.0f;
 
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttr);
}

void UMJSaveGameSubsystem::EndLoadingScreen(UWorld* InLoadedWorld)
{
	
}

UMJSaveGame* UMJSaveGameSubsystem::GetSaveGameData()
{
	return SaveGameData;	
}

FString UMJSaveGameSubsystem::GetSaveSlotName() const
{
	return SaveSlotName;
}

int32 UMJSaveGameSubsystem::GetUserIndex() const
{
	return UserIndex;
}

void UMJSaveGameSubsystem::SaveGameToCurrentSlotNum()
{

	UMJGameInstanceTG* MJGI = Cast<UMJGameInstanceTG>(GetGameInstance());
	if (MJGI)
	{
		const int32 SlotNum = MJGI->GetPlayerSessionDataRef().SaveGameSlotNum;

		if (MJGI->GetPlayerSessionDataRef().SaveGameSlotNum == INDEX_NONE)
		{
			return;
		}
		
		const FString SlotName = FString::Printf(TEXT("Slot_%d"), SlotNum);

		UMJSaveGame* SaveGame = Cast<UMJSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		if (!SaveGame)
		{
			SaveGame = Cast<UMJSaveGame>(UGameplayStatics::CreateSaveGameObject(UMJSaveGame::StaticClass()));
			SaveGame->SlotNum = SlotNum;
		}

		SaveGame->PlayerName = MJGI->GetPlayerSessionDataRef().PlayerName;
		SaveGame->PlayerLevel = MJGI->GetPlayerSessionDataRef().PlayerLevel;
		SaveGame->PlayerExp = MJGI->GetPlayerSessionDataRef().PlayerExp;
		SaveGame->SlotNum = MJGI->GetPlayerSessionDataRef().SaveGameSlotNum;
		SaveGame->RecentPlayedDateTime = FDateTime::Now();

		UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, 0);
	}
	
	
}

void UMJSaveGameSubsystem::LoadGameFromSlotNum(int8 SlotNum)
{
	
	UMJGameInstanceTG* MJGI = Cast<UMJGameInstanceTG>(GetGameInstance());
	if (MJGI)
	{
		const FString SlotName = FString::Printf(TEXT("Slot_%d"), SlotNum);
		if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
		{
			UMJSaveGame* SaveGame = Cast<UMJSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

			MJGI->GetPlayerSessionDataRef().PlayerName = SaveGame->PlayerName;
			MJGI->GetPlayerSessionDataRef().PlayerLevel = SaveGame->PlayerLevel;
			MJGI->GetPlayerSessionDataRef().PlayerExp = SaveGame->PlayerExp;
			MJGI->GetPlayerSessionDataRef().SaveGameSlotNum = SaveGame->SlotNum;
			
		}
	}
}
