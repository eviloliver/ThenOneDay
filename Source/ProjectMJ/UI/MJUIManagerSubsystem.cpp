// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MJUIManagerSubsystem.h"
#include "MJHUDWidget.h"
#include "Dialogue/MJDialogueWidget.h"
#include "Dialogue/MJBacklogWidget.h"
#include "Dialogue/MJDialogueComponent.h"
#include "Player/MJPlayerState.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "Bar/MJEnemyHPBar.h"
#include "Components/WidgetComponent.h"
#include "Controller/MJPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Inventory/MJInventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TG/GameState/MJGameStateDungeonTG.h"
#include "TG/UI/MJBossHpBarWidget.h"


void UMJUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	HUDWidgetClass = LoadClass<UMJHUDWidget>(
		nullptr,
		TEXT("/Game/UI/WBP/HUD/WBP_HUD.WBP_HUD_C"));
}

void UMJUIManagerSubsystem::ShowHUD(AMJPlayerState* PlayerState, AMJPlayerController* PC)
{
	HUDWidget = CreateWidget<UMJHUDWidget>(PC, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
		
		if (PlayerState) 
		{
			auto* MJASC = Cast<UMJAbilitySystemComponent>(PlayerState->GetAbilitySystemComponent());
			HUDWidget->BindAtrributesToChildren(MJASC,PlayerState->GetCharacterAttributeSet());
		}

		AMJGameStateDungeonTG* MJDungeonState = Cast<AMJGameStateDungeonTG>(UGameplayStatics::GetGameState(GetWorld()));
		if (MJDungeonState)
		{
			MJDungeonState->OnAIBossSpawned.AddDynamic(this,&UMJUIManagerSubsystem::OnBossSpawned);
		}
	}
}

void UMJUIManagerSubsystem::SetDialogueVisibility()
{
	HUDWidget->SetDialogueVisibility();
}

void UMJUIManagerSubsystem::ShowStatPanel()
{
	HUDWidget->ShowStatPanel();
}

void UMJUIManagerSubsystem::ShowInventory()
{
	HUDWidget->ShowInventory();
}

void UMJUIManagerSubsystem::ShowStore()
{
	HUDWidget->ShowStore();
}

//충돌나면 World UI 부분 없는걸로 선택 ㄱㄱ 지운거맞음

//
void UMJUIManagerSubsystem::OnBossSpawned()
{
	HUDWidget->GetBossHpBarWidget()->BindToAttributes();
	HUDWidget->ShowBossHpBar();
}
