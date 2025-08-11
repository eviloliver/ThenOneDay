// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_DrawMarker.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ProjectMJ.h"
#include "Character/Component/MJAbilityContextComponent.h"

UMJGA_DrawMarker::UMJGA_DrawMarker()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMJGA_DrawMarker::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	MJ_LOG(LogMJ, Warning, TEXT("AAAAAAA"));

	AActor* Character = GetAvatarActorFromActorInfo();
	if (!Character)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist Character"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	UWorld* World = Character->GetWorld();
	if (!World)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist World"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (!NiagaraSystem)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Not Exist NiagaraSystem"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	FVector TargetWorldLocation = FVector::ZeroVector;
	FVector GroundNormal = FVector::UpVector;

	UMJAbilityContextComponent* ContextComponent = Character->FindComponentByClass<UMJAbilityContextComponent>();
	if (ContextComponent)
	{
		TargetWorldLocation = ContextComponent->LastTargetedMouseLocation;
	}

	const FVector SpawnLocation = TargetWorldLocation + GroundNormal * ZOffset;
	const FRotator SpawnRotation = FRotationMatrix::MakeFromZ(GroundNormal).Rotator();

	UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, NiagaraSystem, SpawnLocation, SpawnRotation);
	if (NiagaraComponent)
	{
		NiagaraComponent->SetAutoDestroy(true);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
