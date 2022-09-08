// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"


// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	RootComponent = SM_Ball;

	SM_Ball->SetSimulatePhysics(true);
	SM_Ball->SetEnableGravity(false);
	SM_Ball->SetConstraintMode(EDOFMode::XZPlane);
	SM_Ball->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Ball->SetCollisionProfileName(TEXT("PhysicsActor"));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.1f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->Velocity.X = 0.0f;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveWithPadddle();
}

void ABall::Launch()
{
	if (!BallLaunched)
	{
		SM_Ball->AddImpulse(FVector(0.0f, 0.0f, 160.f), FName(), true);
		BallLaunched = true;
	}

}

UStaticMeshComponent* ABall::GetBall()
{
	return SM_Ball;
}

void ABall::MoveWithPadddle()
{
	if (!MyPawn)
	{
		return;
	}

	if (BallLaunched)
	{
		return;
	}

	float PawnXLocation = MyPawn->GetActorLocation().X;
	float PawnYLocation = MyPawn->GetActorLocation().Y;

	FVector MoveLocation = FVector(PawnXLocation, PawnYLocation, 40.0f);

	this->SetActorLocation(MoveLocation);

}

void ABall::MultiplyBall()
{
	if (!BallLaunched)
	{
		return;
	}


	UGameplayStatics::PlaySound2D(GetWorld(), MultiplyBallSound);

		FVector SpawnLocation = FVector(this->GetActorLocation());
		FRotator SpawnRotation = FRotator(this->GetActorRotation());
		ABall* SpawnedBall = GetWorld()->SpawnActor<ABall>(this->GetClass(), SpawnLocation, SpawnRotation, BallSpawnInfo);
		SpawnedBall->Launch();
		SpawnedBall->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
		SpawnedBall->ProjectileMovement->SetVelocityInLocalSpace(this->GetVelocity());
		SpawnedBall->SM_Ball->AddImpulse(FVector(45.0f, 0.0f, 0.0f));
}


void ABall::SlowBall()
{
	UGameplayStatics::PlaySound2D(GetWorld(), SlowBallSound);

	for (TObjectIterator<ABall> BallItr; BallItr; ++BallItr)
	{
		ABall* BallActor = BallItr.operator*();
		if (BallActor->GetVelocity().Z >100)
		{
			BallActor->SM_Ball->AddImpulse(FVector(0.0f, 0.0f, -60.0f));
		}
	}
}