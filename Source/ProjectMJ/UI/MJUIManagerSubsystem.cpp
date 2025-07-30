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
#include "TG/GameState/MJGameStateDungeon.h"
#include "TG/UI/MJBossHpBarWidget.h"
#include "TG/UI/MJGameFlowHUDWidget.h"


UMJUIManagerSubsystem::UMJUIManagerSubsystem()
{
	static ConstructorHelpers::FClassFinder<UMJDialogueWidget> DialogueWidgetRef(TEXT("/Game/UI/WBP/Dialogue/BP_MJDialogueWidget.BP_MJDialogueWidget_C"));
	if (DialogueWidgetRef.Succeeded())
	{
		DialogueWidgetClass = DialogueWidgetRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UMJHUDWidget> HUDWidgetRef(TEXT("/Game/UI/WBP/HUD/WBP_HUD.WBP_HUD_C"));
	if (HUDWidgetRef.Succeeded())
	{
		HUDWidgetClass = HUDWidgetRef.Class;
	}
}

void UMJUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	
	// EnemyHPBarWidgetClass = LoadClass<UMJEnemyHPBar>(
	// 	nullptr,
	// 	TEXT("/Game/UI/WBP/World/Bar/WBP_EnemyHPBar.WBP_EnemyHPBar_C"));
	//
	// EnemyHPBarWidget = CreateWidget<UMJEnemyHPBar>(GetWorld(),EnemyHPBarWidgetClass );
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

void UMJUIManagerSubsystem::UnresisterWorldUI(UWidgetComponent* WidgetComp)
{
	WorldUIs.Remove(WidgetComp);
	WidgetComp->SetVisibility(false);
}