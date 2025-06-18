// Fill out your copyright notice in the Description page of Project Settings.


#include "MJGameModeTownTG.h"

#include "MJGameStateDungeonTG.h"
#include "MJGameInstanceTG.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/MJCharacterAttributeSet.h"
#include "Character/MJPlayerCharacter.h"
#include "Controller/MJPlayerController.h"
#include "Internationalization/StringTableCore.h"
#include "Internationalization/StringTableRegistry.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MJPlayerState.h"

AMJGameModeTownTG::AMJGameModeTownTG()
{
	MJ_LOG(LogTG,Log,TEXT("New GameMode Instance Created"));
}

void AMJGameModeTownTG::BeginPlay()
{
	Super::BeginPlay();
	
}
