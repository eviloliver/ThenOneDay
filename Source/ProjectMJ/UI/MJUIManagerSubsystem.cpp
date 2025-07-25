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
#include "TG/UI/MJGameFlowHUDWidget.h"


void UMJUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	DialogueWidgetClass = LoadClass<UMJDialogueWidget>(
			nullptr,
			TEXT("/Game/UI/WBP/Dialogue/BP_MJDialogueWidget.BP_MJDialogueWidget_C"));

	HUDWidgetClass = LoadClass<UMJHUDWidget>(
		nullptr,
		TEXT("/Game/UI/WBP/HUD/WBP_HUD.WBP_HUD_C"));

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

void UMJUIManagerSubsystem::ShowDialogue(UMJDialogueComponent* DialogueComp) // 위젯 띄우기만 하는 함수
{
	if (!DialogueWidgetClass)
		return;
	
	// 위젯 생성
	if (!DialogueWidget)
	{
		DialogueWidget = CreateWidget<UMJDialogueWidget>(GetWorld(), DialogueWidgetClass);
		if (!DialogueWidget)
			return;

		DialogueWidget->AddToViewport();
	}
	
	DialogueComp->StartDialogue(); // 데이터테이블을 불러오고, index를 0으로 설정
	
	SetDialogue(DialogueComp); // 인덱스 0일 때의 대사들이 세팅되어 타이핑된다
}

void UMJUIManagerSubsystem::NextDialogue(UMJDialogueComponent* DialogueComp)
{
	if (DialogueWidget)
	{
		if (DialogueWidget->GetIsTyping())
		{
			DialogueWidget->SkipTyping();
			return;
		}
		
		DialogueComp->NextDialogue(); // 인덱스 +1
		
		SetDialogue(DialogueComp); // +1된 row를 가져와 타이핑 >> 순서 중요

		if (DialogueComp->IsDialogueEnd())
		{
			HideDialogue();
		}
	}
}

void UMJUIManagerSubsystem::SetDialogue(const UMJDialogueComponent* DialogueComp) const
{
	if (const FMJDialogueRow* Row = DialogueComp->GetCurrentRow())
	{
		DialogueWidget->ShowDialogue(*Row);
		DialogueWidget->StartTyping(Row->Text, 0.08f);
		DialogueWidget->SetImageOpacity(Row->Speaker);
	}

	if (const FMJDialogueRow* PrevRow = DialogueComp->GetPreviousRow())
	{
		if (DialogueWidget->BacklogWidget)
		{
			DialogueWidget->BacklogWidget->AddLine(*PrevRow);
		}
	}
}

void UMJUIManagerSubsystem::HideDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
       	DialogueWidget = nullptr;
	}
}

void UMJUIManagerSubsystem::ShowBacklog()
{
	DialogueWidget->ShowBacklog();
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

// World UI
void UMJUIManagerSubsystem::ResisterWorldUI(UWidgetComponent* WidgetComp,UMJAbilitySystemComponent* ASC, UMJCharacterAttributeSet* AttributeSet)
{
	if (WidgetComp && !WorldUIs.Contains(WidgetComp))
	{
		WorldUIs.Add(WidgetComp);
		
		// Enemy HPBar
		UMJEnemyHPBar* HPBarWidget = Cast<UMJEnemyHPBar>(WidgetComp->GetUserWidgetObject());
		if (HPBarWidget && ASC && AttributeSet)
		{
			HPBarWidget->BindToAttributes(ASC, AttributeSet);
		}
	}
}

void UMJUIManagerSubsystem::UnresisterWorldUI(UWidgetComponent* WidgetComp)
{
	WorldUIs.Remove(WidgetComp);
	WidgetComp->SetVisibility(false);
}