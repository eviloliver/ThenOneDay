// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Bar/MJExperienceWidget.h"

#include "NiagaraCommon.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "Character/MJPlayerCharacter.h"
#include "Character/Component/MJPlayerStatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMJExperienceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMJPlayerCharacter* Player = Cast<AMJPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		if (UMJPlayerStatComponent* StatComponent = Player->FindComponentByClass<UMJPlayerStatComponent>())
		{
			StatComponent->OnExperienceChanged.AddDynamic(this, &UMJExperienceWidget::OnExperienceChanged);
			InitializeWidget(StatComponent->GetNumerator(), StatComponent->GetDenominator());
		}
	}
}

void UMJExperienceWidget::InitializeWidget(float Current, float ExpForNextLevel)
{
	CurrentExp = Current;
	MaxExp = ExpForNextLevel;
	
	CurrentPercent= (MaxExp > 0.f) ? CurrentExp / MaxExp : 0.f;
	TargetPercent = (MaxExp > 0.f) ? CurrentExp / MaxExp : 0.f;
	
	if (ExpBar)
	{
		ExpBar->SetPercent(CurrentPercent);
	}
	if (Percent)
	{
		float percent = CurrentPercent * 100.f;
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.1f%% ( %.0f / %.0f )"),percent, CurrentExp , MaxExp)));
	}
}

void UMJExperienceWidget::OnExperienceChanged(float Current, float ExpForNextLevel)
{
	CurrentExp = Current;
	MaxExp = ExpForNextLevel;
	
	TargetPercent = (MaxExp > 0.f) ? CurrentExp / MaxExp : 0.f;
	
	if (Percent)
	{
		float percent = CurrentPercent * 100.f;
		Percent->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%( %.0f / %.0f )"),percent, CurrentExp , MaxExp)));
	}
}

void UMJExperienceWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (FMath::Abs(CurrentPercent- TargetPercent) > KINDA_SMALL_NUMBER)
	{
		CurrentPercent = FMath::FInterpTo(CurrentPercent, TargetPercent, InDeltaTime, LerpSpeed);
		if (ExpBar)
		{
			ExpBar->SetPercent(CurrentPercent);
		}
	}
}