// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/MJPlayerEffectComponent.h"

#include "MJPlayerStatComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ProjectMJ.h"
#include "Character/MJCharacterBase.h"

UMJPlayerEffectComponent::UMJPlayerEffectComponent()
{
	
}

void UMJPlayerEffectComponent::PlayLevelUpEffect()
{
	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnerCharacter"));
		return;
	}

	if (LevelUpVFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), LevelUpVFX, OwnerCharacter->GetActorLocation());
	}

	if (LevelUpSFX)
	{
		// TODO: SFX 재생
	}
}

void UMJPlayerEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	AMJCharacterBase* OwnerCharacter = Cast<AMJCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		MJ_LOG(LogMJ, Error, TEXT("Not Exist OwnerCharacter"));
		return;
	}

	UMJPlayerStatComponent* StatComponent = OwnerCharacter->FindComponentByClass<UMJPlayerStatComponent>();
	if (StatComponent)
	{
		StatComponent->OnLevelUp.AddDynamic(this, &UMJPlayerEffectComponent::OnOwnerLevelUp);
	}

}

void UMJPlayerEffectComponent::OnOwnerLevelUp(int32 NewLevel)
{
	PlayLevelUpEffect();
}
