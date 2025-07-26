// ThenOneDayStudio


#include "MJ/Drop/MJTargetingProjectileBase.h"

#include "NiagaraComponent.h"
#include "ProjectMJ.h"
#include "Character/MJPlayerCharacter.h"
#include "Character/Component/MJPlayerSkillComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Physics/MJCollision.h"

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
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMJTargetingProjectileBase::OnSphereOverlap);
	TargetLocationChanged.BindUObject(this, &AMJTargetingProjectileBase::OnTargetUpdated);
	
	// TODO: 플레이어한테 죽었을 때만 생성, Target이 플레이어인지 확인한다.
	// 나이아가라 시스테에 FX 적용?
	
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
	
	ProjectileMovement->bIsHomingProjectile = true;
	ProjectileMovement->HomingAccelerationMagnitude = 300.0f;
	ProjectileMovement->HomingTargetComponent = Target->GetRootComponent();

	// Minjin: 지금은 HomingTargetComponent없으면 Projectile이 안 움직임(velocity 문제)
	if(!ProjectileMovement->HomingTargetComponent.IsValid())
	{
		MJ_LOG(LogMJ, Warning, TEXT("HomingTarget is not Valid."));
		Destroy();
	}
}

void AMJTargetingProjectileBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (Target->GetActorLocation() != CurrentTargetLocation)
	{
		PreTargetLocation = CurrentTargetLocation;
		CurrentTargetLocation = Target->GetActorLocation();
	
		TargetLocationChanged.ExecuteIfBound();
	}

	// if (GEngine)
	// {
	// 	GEngine->AddOnScreenDebugMessage(
	// 		-1, 3.f, FColor::Green,FString::Printf(TEXT("Velocity> %ls"), *ProjectileMovement->Velocity.ToString()));
	// }
}

void AMJTargetingProjectileBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// HitFX
	// skill 전달
	// 나를 때린 애면 성공? 플레이어면 성공?
	AMJPlayerCharacter* Player = Cast<AMJPlayerCharacter>(OtherActor);
	if (Player == nullptr)
	{
		return;
	}
	// Minjin: HitFX가 플레이어한테서 일어나야 될 것 같음- 공격이 아니고 흡수라서
	//NiagaraComponent->SetAsset(HitFX);

	Player->SkillComponent->LearnSkill(SkillTag);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 3.f, FColor::Green,TEXT("Learn Skill!"));
	}
	
	Destroy();
}

void AMJTargetingProjectileBase::OnTargetUpdated()
{
	FVector ProjectileLocation = GetActorLocation();
	FVector PlayerLocation = Target->GetActorLocation();
	
	FRotator GoalRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileLocation, PlayerLocation);
	
	SetActorRotation(GoalRotation);

	FRotator ProjectileRotation = GetActorRotation();
	FVector Velocity = GetVelocity();
	double Length = Velocity.Length();
	
	FVector NewVelocity = UKismetMathLibrary::CreateVectorFromYawPitch(ProjectileRotation.Yaw, ProjectileRotation.Pitch, Length);
	ProjectileMovement->Velocity = NewVelocity;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 3.f, FColor::Green,FString::Printf(TEXT("NewVelocity.Size()> %f"), NewVelocity.Size()));
	}
}

