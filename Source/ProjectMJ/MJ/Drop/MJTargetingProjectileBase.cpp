// ThenOneDayStudio


#include "MJ/Drop/MJTargetingProjectileBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ProjectMJ.h"
#include "AbilitySystem/Actor/MJProjectileBase.h"
#include "Character/MJPlayerCharacter.h"
#include "Character/Component/MJPlayerSkillComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Physics/MJCollision.h"
#include "Sound/SoundCue.h"

// Sets default values
AMJTargetingProjectileBase::AMJTargetingProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere Section
	Sphere = CreateDefaultSubobject<USphereComponent>("Projectile");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(CCHANNEL_MJPROJECTILE);
	Sphere->SetCollisionProfileName(CRPOFILE_MJPROJECTILE);

	// Niagara Section
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	NiagaraComponent->SetupAttachment(RootComponent);
	
	// Movement Section
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AMJTargetingProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	UNiagaraComponent* MuzzleFxComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, MuzzleFX, GetActorLocation());

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMJTargetingProjectileBase::OnSphereOverlap);
	TargetLocationChanged.BindUObject(this, &AMJTargetingProjectileBase::OnTargetUpdated);
	
	FVector ProjectileLocation = GetActorLocation();
	CurrentTargetLocation = Target->GetActorLocation();

	PreTargetLocation = CurrentTargetLocation;
	FRotator GoalRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileLocation, CurrentTargetLocation);
	
	SetActorRotation(GoalRotation);

	FRotator ProjectileRotation = GetActorRotation();
	FVector Velocity = GetVelocity();
	double Length = Velocity.Length();
	FVector NewVelocity = UKismetMathLibrary::CreateVectorFromYawPitch(ProjectileRotation.Yaw, ProjectileRotation.Pitch, Length);
	ProjectileMovement->Velocity = NewVelocity;
	
	ProjectileMovement->InitialSpeed = 300.0f; 
	ProjectileMovement->MaxSpeed = 600.0f;
	
	ProjectileMovement->bIsHomingProjectile = true;
	ProjectileMovement->HomingAccelerationMagnitude = 300.0f;
	ProjectileMovement->HomingTargetComponent = Target->GetRootComponent();
	
	if(!ProjectileMovement->HomingTargetComponent.IsValid())
	{
		MJ_LOG(LogMJ, Warning, TEXT("HomingTarget is not Valid."));
		Destroy();
	}
}

void AMJTargetingProjectileBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FVector TargetLocation = Target->GetActorLocation();
	if (TargetLocation != CurrentTargetLocation)
	{
		PreTargetLocation = CurrentTargetLocation;
		CurrentTargetLocation = TargetLocation;
		
		TargetLocationChanged.ExecuteIfBound();
	}

	float Distance = GetDistanceTo(Target);
	ProjectileMovement->MaxSpeed = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 600.0f), FVector2D(1.0f, 600.0f), Distance);
	// MJ_LOG(LogMJ, Warning, TEXT("MaxSpeed: %f"), ProjectileMovement->MaxSpeed);
	
	// if (GEngine)
	// {
	// 	GEngine->AddOnScreenDebugMessage(
	// 		-1, 3.f, FColor::Green,FString::Printf(TEXT("Velocity> %f"), ProjectileMovement->Velocity.Size()));
	// }
}

void AMJTargetingProjectileBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Minjin: Target과 같으면 성공
	if (OtherActor != Target)
	{
		return;
	}
	
	// Minjin: 플레이어라면 skill 전달
	AMJPlayerCharacter* Player = Cast<AMJPlayerCharacter>(OtherActor);
	if (Player)
	{
		if (SkillTag.IsValid())
		{
			Player->SkillComponent->LearnSkill(SkillTag);
			UGameplayStatics::PlaySound2D(GetWorld(),OverlapSFX);
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1, 3.f, FColor::Green,TEXT("Learn Skill!"));
			}
		}
	}

	UNiagaraComponent* FxComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
	HitFX,
	Player->GetMesh(),
	FName("Aim_Target")/*SweepResult.BoneName*/,
	FVector::ZeroVector,            // 시작 위치
	FRotator::ZeroRotator,
	EAttachLocation::Type::SnapToTarget, // 처음 위치는 유지, 이후엔 부모 따라감
	true,                                // bAutoDestroy
	true,
	ENCPoolMethod::None,
	true
	);
	//FxComp->OnSystemFinished.AddDynamic(this, &AMJTargetingProjectileBase::OnEnded);;

	Destroy();
}

void AMJTargetingProjectileBase::OnTargetUpdated()
{
	FVector ProjectileLocation = GetActorLocation();
	FRotator GoalRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileLocation, CurrentTargetLocation);
	
	SetActorRotation(GoalRotation);

	FRotator ProjectileRotation = GetActorRotation();
	FVector Velocity = GetVelocity();
	double Length = Velocity.Length();
	
	FVector NewVelocity = UKismetMathLibrary::CreateVectorFromYawPitch(ProjectileRotation.Yaw, ProjectileRotation.Pitch, Length);
	ProjectileMovement->Velocity = NewVelocity;
}

void AMJTargetingProjectileBase::OnEnded(UNiagaraComponent* PSystem)
{
	MJ_LOG(LogMJ, Warning, TEXT("Projectile is Destroyed"));
	Destroy();
}

