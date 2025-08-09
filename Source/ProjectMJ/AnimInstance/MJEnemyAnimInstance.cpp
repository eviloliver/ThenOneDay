// ThenOneDayStudio


#include "AnimInstance/MJEnemyAnimInstance.h"

#include "GameplayTagContainer.h"
#include "ProjectMJ.h"
#include "AbilitySystem/MJAbilitySystemComponent.h"
#include "Character/MJCharacterBase.h"

UMJEnemyAnimInstance::UMJEnemyAnimInstance()
{
}

void UMJEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	AActor* OwningActor = GetOwningActor();
	AMJCharacterBase* Character = Cast<AMJCharacterBase>(OwningActor);
	if (Character == nullptr)
	{
		MJ_LOG(LogMJ, Warning, TEXT("Character nullptr."));
		return;
	}

	// Minjin: IsInActivated 태그를 처음부터 부여 - 비활성화로 만듦
	FGameplayTag InActivatedTag = FGameplayTag::RequestGameplayTag(TEXT("Character.State.IsInactivated"));
	
	Character->ASC->AddLooseGameplayTag(InActivatedTag);
	bIsInActivated = true;

	Character->ASC->RegisterGameplayTagEvent(InActivatedTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UMJEnemyAnimInstance::TagConditionChanged);
}

void UMJEnemyAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UMJEnemyAnimInstance::TagConditionChanged(const FGameplayTag InTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		bIsInActivated = true;
	}
	else
	{
		bIsInActivated = false;
	}
}
