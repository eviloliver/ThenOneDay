// ThenOneDayStudio


#include "AbilitySystem/Abilities/MJGA_NiagaraSkill.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystemInstanceController.h"
#include "ProjectMJ.h"
#include "AbilitySystem/TargetActor/MJTA_CustomTrace.h"

UMJGA_NiagaraSkill::UMJGA_NiagaraSkill()
{
}

void UMJGA_NiagaraSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(),
				AttackVFX,
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				FVector(1.0f));

	
	// AttackVFX->GetEmitterHandle(0).GetEmitterData()->GetEventHandlers();
	FString EmitterName = AttackVFX->GetEmitterHandle(0).GetUniqueInstanceName();

	AEmitter* Emitter = Cast<AEmitter>(NiagaraComp->GetSystemInstance()->GetEmitters()[0]->GetEmitter());
	if (Emitter == nullptr)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Emitter is nullptr."))
	}

}

void UMJGA_NiagaraSkill::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
}
