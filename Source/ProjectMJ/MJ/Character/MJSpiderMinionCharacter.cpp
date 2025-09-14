// ThenOneDayStudio


#include "MJ/Character/MJSpiderMinionCharacter.h"
#include "AnimInstance/MJAnimInstanceBase.h"

void AMJSpiderMinionCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	
}

void AMJSpiderMinionCharacter::SetbIsOpen(bool Value)
{
	UMJAnimInstanceBase* AnimInstance = Cast<UMJAnimInstanceBase>(GetMesh()->GetAnimInstance());
	AnimInstance->SetbIsOpen(Value);
}
