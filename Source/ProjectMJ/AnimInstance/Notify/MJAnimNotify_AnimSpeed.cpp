// ThenOneDayStudio


#include "AnimInstance/Notify/MJAnimNotify_AnimSpeed.h"
#include "Components/SkeletalMeshComponent.h"

void UMJAnimNotify_AnimSpeed::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	
	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}
	AnimInstance->Montage_SetPlayRate(
		AnimInstance->GetCurrentActiveMontage(),
		NewPlayRate
	);
}
