// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MJTutorialCollision.generated.h"

class UBoxComponent;

UENUM(BlueprintType)
enum class ECollisionType : uint8
{
	AttackTutorial,
	InstantSkillTutorial,
	ChargeSkillTutorial
};

UCLASS()
class PROJECTMJ_API AMJTutorialCollision : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	TObjectPtr<UBoxComponent> CollisionBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString InstructionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECollisionType CollisionType;
	
public:	
	AMJTutorialCollision();

	ECollisionType GetCollisionType() { return CollisionType; }
	FString GetInstructionText() { return InstructionText; }

	void Hide();
};
