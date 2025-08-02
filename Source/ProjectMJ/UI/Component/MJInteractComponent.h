// ThenOneDayStudio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MJInteractComponent.generated.h"
/**
 * Class Description: 상호작용이 필요한 액터에게 심어주는 컴포넌트 예 NPC - Dialogue, Store 등
 * Author: 이지수
 * Created Date: 2025_07-23
 * Last Modified By: Lee JuHyeon
 * Last Modified Date: Add Using Func from BP 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStoreOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStoreClose);

UENUM(BlueprintType)
enum class EMJInteractionType : uint8
{
	None,
	Dialogue,
	Store
};

class UMJInteractionComponent;
class UMJDialogueComponent;
class UMJStoreComponent;
class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJInteractComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UMJInteractionComponent> WidgetComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlay")
	TObjectPtr<UMaterialInterface> OverlayMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UMJDialogueComponent> DialogueComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UMJStoreComponent> StoreComponent;

	
public:
	UMJInteractComponent();

	void OnBeginInteract();
	void OnEndInteract();
	void EvaluateType();
	void StartInteraction();
	void ProceedInteraction();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMJInteractionType CurrentType;

	FOnDialogueEnd OndialogueEnd;
	FOnStoreOpen OnstoreOpen;
	FOnStoreClose OnstoreClose;
};