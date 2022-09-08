// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Missile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Missile Mesh"));
	SM_Missile->SetSimulatePhysics(true);
	SM_Missile->SetEnableGravity(false);
	SM_Missile->SetConstraintMode(EDOFMode::XZPlane);
	SM_Missile->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Missile->SetCollisionProfileName(TEXT("PhysicsActor"));
	RootComponent = SM_Missile;

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Box_Collision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	SM_Missile->AddImpulse(FVector(0.0f, 0.0f, MissileLaunchSpeed));
	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AMissile::OnOverlapBegin);
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMissile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* 
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag(TEXT("Ball")) 
		&& !OtherActor->ActorHasTag(TEXT("Paddle")) 
		&& !OtherActor->ActorHasTag(TEXT("Drop"))
		&& OtherActor != this && OtherActor->ActorHasTag(TEXT("Wall")))
		{
			this->Destroy();
		}
}
