// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MJGameModeBase.h"

#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Character/MJPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MJPlayerState.h"
#include "TG/MJGameInstanceTG.h"
#include "TG/GameState/MJGameStateDungeonTG.h"

AMJGameModeBase::AMJGameModeBase()
{
	// static ConstructorHelpers::FObjectFinder<UStringTable> MapNamesRef(TEXT("/Script/Engine.StringTable'/Game/Blueprint/GameData/TG_MapNames.TG_MapNames'"));
	// if (MapNamesRef.Object)
	// {
	// 	MapNames = MapNamesRef.Object;
	// }

	//MapNames = FStringTableRegistry::Get().FindStringTable(FName(TEXT("/Script/Engine.StringTable'/Game/Blueprint/GameData/TG_MapNames.TG_MapNames'")));
	MJ_LOG(LogTG,Warning,TEXT("Ptr : %p"),this);
	bUseSeamlessTravel = true;
}


bool AMJGameModeBase::TravelToMap(const FString MapName)
{
	bool bAbsolute = false;
	if (CanServerTravel(MapName, bAbsolute))
	{
		GetWorld()->GetAuthGameMode()->bUseSeamlessTravel = true;

		
		UMJAbilitySystemComponent* ASC = Cast<UMJAbilitySystemComponent>(Cast<AMJPlayerState>(UGameplayStatics::GetPlayerState(this,0))->GetAbilitySystemComponent());

		if (ASC)
		{
		//	ASC->SetNumericAttributeBase(UMJCharacterAttributeSet::GetHealthAttribute(),ASC->GetSet<UMJCharacterAttributeSet>()->GetHealth() + 10.f);
			
		}
		
		GetWorld()->ServerTravel(MapName, bAbsolute);
	}
	else
	{
		MJ_LOG(LogTemp,Warning,TEXT("Can`t Travel to %s"), *MapName);
	}

	return false;
}

void AMJGameModeBase::GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList)
{
	Super::GetSeamlessTravelActorList(bToTransition, ActorList);

	AActor* Player = UGameplayStatics::GetActorOfClass(this, AMJPlayerCharacter::StaticClass());

	ActorList.Add(Player);
	
	// if (AMJPlayerController* PC = Cast<AMJPlayerCharacter>(Player)->GetController<AMJPlayerController>())
	// {
	// 	ActorList.Add(PC);
	//
	// 	if (AMJPlayerState* PS = PC->GetPlayerState<AMJPlayerState>())
	// 	{
	// 		ActorList.Add(PS);
	// 	}
	// }
	
}

void AMJGameModeBase::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
}

bool AMJGameModeBase::TravelToMapByNode(const FString MapName, const uint8 NodeNum)
{

	UMJGameInstanceTG* MJGI = GetGameInstance<UMJGameInstanceTG>();
	if (MJGI)
	{
		MJGI->GetPlayerSessionDataRef().CurrentDungeonMapNum = NodeNum;
		
		AMJPlayerState* PS = Cast<AMJPlayerState>(UGameplayStatics::GetPlayerState(this,0));

		if (PS)
		{
			PS->GetPlayerSessionData().CurrentDungeonMapNum = NodeNum;
		}
		
		AMJGameStateDungeonTG* MJGS = GetGameState<AMJGameStateDungeonTG>();
		if (MJGS)
		{
			MJGS->SaveDungeonSessionDataToGameInstance();
		}
		
	}
	

	if (TravelToMap(MapName))
	{
		return true;
	}

	return false;
}
