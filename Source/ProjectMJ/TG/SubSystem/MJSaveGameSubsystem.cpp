// Fill out your copyright notice in the Description page of Project Settings.


#include "MJSaveGameSubsystem.h"

#include "MoviePlayer.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "Character/MJPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TG/Struct/MJSaveGame.h"

UMJSaveGameSubsystem::UMJSaveGameSubsystem()
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> LoadingScreenRef(TEXT("/Game/TG/MapTestWBP/WBP_LoadingScreen.WBP_LoadingScreen_C"));
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

void UMJSaveGameSubsystem::CreateSaveGame()
{
	SaveGameData = CastChecked<UMJSaveGame>(UGameplayStatics::CreateSaveGameObject(UMJSaveGame::StaticClass()));
	if (SaveGameData)
	{
		//SaveGameToSlot(nullptr);
	}
}

void UMJSaveGameSubsystem::LoadSaveGame(AMJPlayerCharacter* Player)
{
	if (!Player) return;
	
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		MJ_LOG(LogTG, Log, TEXT("No save found. Saving current character state as default."));

		SaveGameData = CastChecked<UMJSaveGame>(UGameplayStatics::CreateSaveGameObject(UMJSaveGame::StaticClass()));
		SaveGameToSlot(Player); // Save as Default
		return;
	}
	
	SaveGameData = Cast<UMJSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (SaveGameData)
	{
		if (Player)
		{
			UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(Player->GetAbilitySystemComponent());
	 		if (MJASC)
	 		{
	 			UMJCharacterAttributeSet* MJCAS = const_cast<UMJCharacterAttributeSet*>(MJASC->GetSet<UMJCharacterAttributeSet>());
				if (MJCAS)
				{
					//SaveGameData->GetAttributeSaveData().ApplyTo(MJASC);
				}
	 		}
			
			MJ_LOG(LogTG,Log,TEXT("loaded health : %f"), MJASC->GetNumericAttribute(UMJCharacterAttributeSet::GetHealthAttribute()));
		}
	}
}

void UMJSaveGameSubsystem::SaveGameToSlot(AMJPlayerCharacter* Player)
{
	if (SaveGameData)
	{
		if (Player)
		{
			UMJAbilitySystemComponent* MJASC = Cast<UMJAbilitySystemComponent>(Player->GetAbilitySystemComponent());

			if (MJASC)
			{
			
				UMJCharacterAttributeSet* MJCAS = const_cast<UMJCharacterAttributeSet*>(MJASC->GetSet<UMJCharacterAttributeSet>());
				if (MJCAS)
				{
					//SaveGameData->GetAttributeSaveData() = FCharacterAttributeSaveData::FromAttributeSet(MJCAS);
				}
			}
			
			MJ_LOG(LogTG,Log,TEXT("saved health : %f"), SaveGameData->GetAttributeSaveData().Health);
		}
		else
		{
			bool bSaved = false;
			MJ_LOG(LogTG, Log, TEXT("Character Info Save success: %s"), bSaved ? TEXT("true") : TEXT("false"));
		}
		
		bool bSaved = UGameplayStatics::SaveGameToSlot(SaveGameData, SaveSlotName, UserIndex);
		MJ_LOG(LogTG, Log, TEXT("Save success: %s"), bSaved ? TEXT("true") : TEXT("false"));
		
	}
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
