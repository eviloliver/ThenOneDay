// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MJExtensionComponent.generated.h"

/**
* Class Description: Find Pawn in all actors
 * Author: Lee JuHyeon
 * Created Date: 2025_06_19
 * Last Modified By: Lee JuHyeon
 * Last Modified Date: Add Find Pawn(Template)
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMJ_API UMJExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties


protected:

	template<class T>
	T* GetOwningPawn()const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter get GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return  GetOwningPawn<APawn>();
	}

	template<class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Template Parameter get GetPawn must be derived from AController");
		return  GetOwningPawn(APawn)()->GetController<T>();
	}
		
};
