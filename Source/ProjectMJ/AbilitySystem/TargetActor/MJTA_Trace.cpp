// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/MJTA_Trace.h"
#include "AbilitySystem/Attributes/MJCharacterSkillAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ProjectMJ.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

AMJTA_Trace::AMJTA_Trace()
{
}

void AMJTA_Trace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
}

void AMJTA_Trace::ConfirmTargetingAndContinue()
{
	Super::ConfirmTargetingAndContinue();
}

FGameplayAbilityTargetDataHandle AMJTA_Trace::MakeTargetData() const
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (!ASC)
	{
		MJ_LOG(LogMJ, Error, TEXT("ASC not found!"));
		return FGameplayAbilityTargetDataHandle();
	}

	const UMJCharacterSkillAttributeSet* SkillAttributeSet = ASC->GetSet<UMJCharacterSkillAttributeSet>();
	if (!SkillAttributeSet)
	{
		MJ_LOG(LogMJ, Error, TEXT("SkillAttributeSet not found!"));
		return FGameplayAbilityTargetDataHandle();
	}

	FHitResult OutHitResult;
	const float AttackRange = SkillAttributeSet->GetSkillRange();
	const float AttackRadius = SkillAttributeSet->GetSkillRadius();

	FCollisionQueryParams Params(SCENE_QUERY_STAT(UABTA_Trace), false, Character);
	const FVector Forward = Character->GetActorForwardVector();
	const FVector Start = Character->GetActorLocation() + Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + Forward * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(AttackRadius), Params);

	FGameplayAbilityTargetDataHandle DataHandle;
	if (HitDetected)
	{
		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(OutHitResult);
		DataHandle.Add(TargetData);
	}

#if ENABLE_DRAW_DEBUG

	if (bShowDebug)
	{
		FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
		float CapsuleHalfHeight = AttackRange * 0.5f;
		FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
		DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor, false, 5.0f);
	}

#endif

	return DataHandle;
}

