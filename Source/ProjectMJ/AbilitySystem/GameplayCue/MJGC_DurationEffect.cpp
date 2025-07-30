// ThenOneDayStudio


#include "AbilitySystem/GameplayCue/MJGC_DurationEffect.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ProjectMJ.h"
#include "Character/MJCharacterBase.h"

AMJGC_DurationEffect::AMJGC_DurationEffect()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMJGC_DurationEffect::BeginPlay()
{
	Super::BeginPlay();
}

bool AMJGC_DurationEffect::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (!MyTarget)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist Target"));
		return false;
	}

	if (!ActiveNiagaraSystem)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist ActiveNiagaraSystem"));
		return false;
	}

	USceneComponent* AttachComponent = MyTarget->GetRootComponent();
	AMJCharacterBase* Character = Cast<AMJCharacterBase>(MyTarget);

	if (Character && Character->GetMesh())
	{
		AttachComponent = Character->GetMesh();
	}

	if (!AttachComponent)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist AttachComponent"));
		return false;
	}

	ActiveNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
		ActiveNiagaraSystem,
		AttachComponent,
		ActiveNiagaraSystemSocketName,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::Type::SnapToTarget,
		true,
		true,
		ENCPoolMethod::None,
		true
	);
	
	return true;
}

bool AMJGC_DurationEffect::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (!ActiveNiagaraComponent)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist ActiveNiagaraComponent"));
		return false;
	}
	ActiveNiagaraComponent->Deactivate();
	ActiveNiagaraComponent->DestroyComponent();

	return true;
}

bool AMJGC_DurationEffect::WhileActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{

	return true;
}
