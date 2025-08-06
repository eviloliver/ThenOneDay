// ThenOneDayStudio


#include "MJ/AI/BTTask_MJPlayMontage.h"
#include "BTTask_MJPlayMontage.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_MJPlayMontage::UBTTask_MJPlayMontage()
{
	NodeName=TEXT("Play Montage");

	bNotifyTick = false;
}


EBTNodeResult::Type UBTTask_MJPlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Pawn = Controller->GetPawn();
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player)
	{
		return EBTNodeResult::Failed;
	}
	
	UAnimInstance* Anim = Pawn->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance();
	if (!Anim)
	{
		return EBTNodeResult::Failed;
	}

	CachedComponent = &OwnerComp;
	if (!MontagePlay)
	{
		return EBTNodeResult::Failed;
	}
	FVector AILocation = Pawn->GetActorLocation();
	FVector TargetLocation = Player->GetActorLocation();
	TargetLocation.Z = AILocation.Z;

	FRotator LookAtRotation = (TargetLocation - AILocation).Rotation();

	Pawn->SetActorRotation(LookAtRotation);


	Pawn->FindComponentByClass<USkeletalMeshComponent>()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	
	Anim->Montage_Play(MontagePlay);
	if (SessionName != NAME_None)
	{
		Pawn->GetWorldTimerManager().SetTimer(
			WaitTimerHandle,
			FTimerDelegate::CreateUObject(this, &UBTTask_MJPlayMontage::JumpToSection, Anim),
			3.0f,
			false
		);
		UBlackboardComponent* board = OwnerComp.GetBlackboardComponent();
		board->SetValueAsBool(TEXT("IsPatten"), false);

	}
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &UBTTask_MJPlayMontage::OnMontageEnded);
	Anim->Montage_SetEndDelegate(EndDelegate, MontagePlay);
	
	return EBTNodeResult::InProgress;
}

void UBTTask_MJPlayMontage::JumpToSection(UAnimInstance* AnimInstance)
{
	if (AnimInstance && MontagePlay)
	{
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
