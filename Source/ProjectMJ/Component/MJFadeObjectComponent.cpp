// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MJFadeObjectComponent.h"
#include "Materials/MaterialInterface.h"
#include "Engine.h"

#include "Kismet/GameplayStatics.h"
void FFadeSystemStuc::NewElement(TObjectPtr<UPrimitiveComponent> _Primitive, const TArray<UMaterialInterface*>& _MaterialInt, const TArray<UMaterialInstanceDynamic*>& _MID, float _FadeCount, bool _bToHide)
{
	PrimitiveComp = _Primitive;
	BaseMatInterface = _MaterialInt;
	FadeMID = _MID;
	FadeCount = _FadeCount;
	bToHide = _bToHide;
}
void FFadeSystemStuc::SetToHide(bool _ToHide)
{
	bToHide = _ToHide;
}
void FFadeSystemStuc::SetHideAndFade(bool _ToHide, float _FadeCount)
{
	bToHide = _ToHide;
	FadeCount = _FadeCount;

}
void FFadeSystemStuc::Destroy()
{
	PrimitiveComp = nullptr;
}
// Sets default values for this component's properties
UMJFadeObjectComponent::UMJFadeObjectComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	CurrentFade = 0.0;
	FadeNowID = 0;
	bIsEnabled = true;
	bIsActivate = true;
	bIsTraceComplex = false;

	AddObjectInterval = 0.1f;
	CalcFadeInterval = 0.05f;
	
	WorkDistance = 5000.0f;
	FadeRate = 10.0f;

	CapsuleRadius = 34.0f;
	
	NearObjectFade = 0.3f;
	FarObjectFade = 0.1f;

	ImmediatelyFade = 0.5;

	ObjectTypes.Add(ECC_WorldStatic);
}


// Called when the game starts
void UMJFadeObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Controller == nullptr)
	{
		return;
	}
	if (Controller->IsLocalController())
	{
		GetOwner()->GetWorld()->GetTimerManager().SetTimer(TimerHandle_AddObjectsTimer, this, &ThisClass::AddObjectHideTimer, AddObjectInterval,true);
		GetOwner()->GetWorld()->GetTimerManager().SetTimer(TimerHandle_ObjectComputeTimer, this, &ThisClass::FadeWorkTimer, CalcFadeInterval, true);
		
		GetOwner()->GetWorld()->GetTimerManager().PauseTimer(TimerHandle_ObjectComputeTimer);
		GetOwner()->GetWorld()->GetTimerManager().PauseTimer(TimerHandle_AddObjectsTimer);

		SetActivate(bIsActivate);
	}
		
	
}

void UMJFadeObjectComponent::AddObjectHideTimer()
{
	UGameplayStatics::GetAllActorsOfClass(this, PlayerClass, CharacterArray);

	for (AActor* CurrentActor : CharacterArray)
	{
		const FVector TraceStart=GEngine->GetFirstLocalPlayerController(GetOwner()->GetWorld())->PlayerCameraManager->GetCameraLocation();
		const FVector TraceEnd = CurrentActor->GetActorLocation();
		FVector TraceLength = TraceStart - TraceEnd;
		const FQuat AcQuat = CurrentActor->GetActorQuat();

		if (TraceLength.Size() < WorkDistance)
		{
			FCollisionQueryParams TraceParams(TEXT("FadeObjectsTrace"), bIsTraceComplex, GetOwner());

			TraceParams.AddIgnoredActors(ActorIgnore);
			TraceParams.bReturnPhysicalMaterial = false;
			TraceParams.bTraceComplex = bIsTraceComplex;

			TArray<FHitResult>HitArray;
			TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;

			for (int i = 0; i < ObjectTypes.Num(); i++)
			{
				traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ObjectTypes[i].GetValue()));
			}
			GetOwner()->GetWorld()->SweepMultiByObjectType(HitArray, TraceStart, TraceEnd, AcQuat, traceObjectTypes,
				FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight), TraceParams);

			for (int IHit = 0; IHit < HitArray.Num(); IHit++)
			{
				if (HitArray[IHit].bBlockingHit && IsValid(HitArray[IHit].GetComponent())
					&& !FadeObjectsHit.Contains(HitArray[IHit].GetComponent()))
				{
					FadeObjectsHit.AddUnique(HitArray[IHit].GetComponent());
				}
			}
		}
	}

	for (int IObject = 0; IObject < FadeObjectsHit.Num(); IObject++)
	{
		if (!FadeObjectTemp.Contains(FadeObjectsHit[IObject]))
			{

			FadeObjectTemp.AddUnique(FadeObjectsHit[IObject]);
			
			TArray<UMaterialInterface*> IBaseMaterials;
			TArray<UMaterialInstanceDynamic*> IMID;
			
			IBaseMaterials.Empty();
			IMID.Empty();

			for (int Nm = 0; Nm < FadeObjectsHit[IObject]->GetNumMaterials(); Nm++)
			{
				IMID.Add(UMaterialInstanceDynamic::Create(FadeMaterial, FadeObjectsHit[IObject]));
				IBaseMaterials.Add(FadeObjectsHit[IObject]->GetMaterial(Nm));

				FadeObjectsHit[IObject]->SetMaterial(Nm, IMID.Last());

			}
			FFadeSystemStuc NewObject;
			NewObject.NewElement(FadeObjectsHit[IObject], IBaseMaterials, IMID, ImmediatelyFade, true);
			NewObject.CameraCollsion = FadeObjectsHit[IObject]->GetCollisionResponseToChannel(ECC_Camera);

			FadeObject.Add(NewObject);

			FadeObjectsHit[IObject]->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
			}
	}
	for (int Fot = 0; Fot < FadeObjectTemp.Num(); ++Fot)
	{
		if (!FadeObjectsHit.Contains(FadeObjectTemp[Fot]))
		{
			FadeObject[Fot].SetToHide(false);
		}
	}
	FadeObjectsHit.Empty();

}

void UMJFadeObjectComponent::FadeWorkTimer()
{
	if (FadeObject.Num() > 0)
	{
		for (int IObject = 0; IObject < FadeObject.Num(); ++IObject)
		{
			float AdaptiveFade;
			int FniD = IObject;
			
			if (FniD == FadeObject.Num())
			{
				AdaptiveFade = NearObjectFade;
			}
			else
			{
				AdaptiveFade = FarObjectFade;
			}

			for (int i = 0; i < FadeObject[IObject].FadeMID.Num(); i++)
			{
				float TargetF;
				const float CurrentF = FadeObject[IObject].FadeCount;
				if (FadeObject[IObject].bToHide)
				{
					TargetF = AdaptiveFade;
				}
				else
				{
					TargetF = 1.0f;
				}
				const float NewFade = FMath::FInterpConstantTo(CurrentF, TargetF, GetOwner()->GetWorld()->GetDeltaSeconds(), FadeRate);

				FadeObject[IObject].FadeMID[i]->SetScalarParameterValue("Fade", NewFade);
				CurrentFade = NewFade;

				FadeObject[IObject].SetHideAndFade(FadeObject[IObject].bToHide, NewFade);
			}
			if (CurrentFade == 1.0f)
			{
				for (int IBaseMat = 0; IBaseMat < FadeObject[FniD].BaseMatInterface.Num(); ++IBaseMat)
				{
					FadeObject[FniD].PrimitiveComp->SetMaterial(IBaseMat, FadeObject[FniD].BaseMatInterface[IBaseMat]);
				}

				FadeObject[FniD].PrimitiveComp->SetCollisionResponseToChannel(ECC_Camera, FadeObject[FniD].CameraCollsion);
				FadeObject.RemoveAt(FniD);
				FadeObjectTemp.RemoveAt(FniD);
			}
		}

	}

}

void UMJFadeObjectComponent::SetEnable(bool _bIsEnable)
{
	bIsEnabled = _bIsEnable;
}

void UMJFadeObjectComponent::SetActivate(bool _bIsActive)
{
	bIsActivate = _bIsActive;

	if (!bIsActivate)
	{
		GetOwner()->GetWorld()->GetTimerManager().PauseTimer(TimerHandle_ObjectComputeTimer);
		GetOwner()->GetWorld()->GetTimerManager().PauseTimer(TimerHandle_AddObjectsTimer);
	}
	else
	{
		GetOwner()->GetWorld()->GetTimerManager().UnPauseTimer(TimerHandle_ObjectComputeTimer);
		GetOwner()->GetWorld()->GetTimerManager().UnPauseTimer(TimerHandle_AddObjectsTimer);
	}
}


// Called every frame
void UMJFadeObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

