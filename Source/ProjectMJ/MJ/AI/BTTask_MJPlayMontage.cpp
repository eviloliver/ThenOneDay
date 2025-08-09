// ThenOneDayStudio


#include "MJ/AI/BTTask_MJPlayMontage.h"
#include "BTTask_MJPlayMontage.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MJ/Character/MJMonsterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Component/MJEnemySkillComponent.h"

UBTTask_MJPlayMontage::UBTTask_MJPlayMontage()
{
	NodeName=TEXT("Play Montage");

	bNotifyTick = false;
}


EBTNodeResult::Type UBTTask_MJPlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	AMJMonsterCharacter* Monster = Cast<AMJMonsterCharacter>(ControlledPawn);
	if (!Monster)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player)
	{
		return EBTNodeResult::Failed;
	}
	
	UAnimInstance* Anim = ControlledPawn->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance();
	if (!Anim)
	{
		return EBTNodeResult::Failed;
	}

	CachedComponent = &OwnerComp;
	
	FVector AILocation = ControlledPawn->GetActorLocation();
	FVector TargetLocation = Player->GetActorLocation();
	TargetLocation.Z = AILocation.Z;

	FRotator LookAtRotation = (TargetLocation - AILocation).Rotation();

	ControlledPawn->SetActorRotation(LookAtRotation);


	ControlledPawn->FindComponentByClass<USkeletalMeshComponent>()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	
	UAbilitySystemComponent* ASC = Monster->GetAbilitySystemComponent();
	UMJEnemySkillComponent* SkillComponent = Monster->GetSkillComponent();


	//Anim->Montage_Play(MontagePlay);
	if (!Anim->IsAnyMontagePlaying())
	{
		SkillComponent->ActivateIdentitySkill();
	}
	if (SessionName != NAME_None)
	{
		ControlledPawn->GetWorldTimerManager().SetTimer(
			WaitTimerHandle,
			FTimerDelegate::CreateUObject(this, &UBTTask_MJPlayMontage::JumpToSection, Anim),
			3.0f,
			false
		);
		UBlackboardComponent* board = OwnerComp.GetBlackboardComponent();
		board->SetValueAsBool(TEXT("IsPatten"), false);

	}
	Anim->OnMontageEnded.AddDynamic(this, &UBTTask_MJPlayMontage::OnMontageEnded);
	
	return EBTNodeResult::InProgress;
}

void UBTTask_MJPlayMontage::JumpToSection(UAnimInstance* AnimInstance)
{
	if (AnimInstance )
	{
		MontagePlay = AnimInstance->GetCurrentActiveMontage();
		AnimInstance->Montage_JumpToSection(SessionName, MontagePlay);
	}

}

void UBTTask_MJPlayMontage::OnMontageEnded(UAnimMontage* AnimMontage, bool bInterrupted)
{
	if (CachedComponent)
	{
				
		FinishLatentTask(*CachedComponent, EBTNodeResult::Succeeded);
	}
}
