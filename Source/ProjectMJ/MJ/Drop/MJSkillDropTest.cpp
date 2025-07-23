// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ/Drop/MJSkillDropTest.h"

#include "GameplayTagContainer.h"
#include "Character/MJPlayerCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AMJSkillDropTest::AMJSkillDropTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);

	Trigger->SetBoxExtent(FVector(15.0f, 15.0f, 30.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(
		TEXT("/Script/Engine.StaticMesh'/Game/Assets/StylizedLandscapeKit/Meshes/Flowers_02_SM.Flowers_02_SM'"));
	if (MeshRef.Object)
	{
		Mesh->SetStaticMesh(MeshRef.Object);
	}
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	// 임시 테스트
	//SkillTag = FGameplayTag::RequestGameplayTag(FName("Skill.Instant.AirArrow"));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMJSkillDropTest::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AMJSkillDropTest::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMJSkillDropTest::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (!SkillTag.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Skill is not Valid"));
		Destroy();
		return;
	}
	
	AMJPlayerCharacter* Player = Cast<AMJPlayerCharacter>(OtherActor);
	if (Player)
	{
		Player->LearnSkill(SkillTag);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("LearnSkill!"));
		Destroy();	
	}
}

