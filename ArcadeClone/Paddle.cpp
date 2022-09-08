// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "Missile.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SM_Paddle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle Mesh"));
	RootComponent = SM_Paddle;

	SM_Paddle->SetEnableGravity(false);
	SM_Paddle->SetConstraintMode(EDOFMode::XZPlane);
	SM_Paddle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Paddle->SetCollisionProfileName(TEXT("PhysicsActor"));

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));

	// Create Scene Components to Launch Missiles acording to Paddle Location
	LeftMissileLauncher = CreateDefaultSubobject<USceneComponent>(TEXT("Left Missile Launcher"));
	LeftMissileLauncher->SetRelativeLocation(LeftSpawnLocation);
	LeftMissileLauncher->SetRelativeRotation(SpawnRotation);
	LeftMissileLauncher->SetupAttachment(RootComponent);

	RightMissileLauncher = CreateDefaultSubobject<USceneComponent>(TEXT("Right Missile Launcher"));
	RightMissileLauncher->SetRelativeLocation(RightSpawnLocation);
	RightMissileLauncher->SetRelativeRotation(SpawnRotation);
	RightMissileLauncher->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();

	// Set Variables
	PaddleInreased = false;
	
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	KeepPaddleAtZPosition();
	KeepLaunchersAtPosition();

	if (MissileLaunched)
	{
		LaunchMissile();
	}
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APaddle::MoveHorizontal(float AxisValue)
{
	AddMovementInput(FVector(AxisValue, 0.0f, 0.0f), 1.0f, false);
}


void APaddle::LaunchMissile()
{
	if (PaddleInreased)
	{
		return;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), MissileLaunchSound);

	MissileLaunched = true;
		if (MissileDecider == 1)
		{
			MyLeftMissile = GetWorld()->SpawnActor<AMissile>(MissObj, LeftMissileLauncher->GetRelativeLocation(), SpawnRotation, SpawnInfo);
			MissileDecider = 2;
		}
		else if (MissileDecider == 2)
		{
			MyRightMissile = GetWorld()->SpawnActor<AMissile>(MissObj, RightMissileLauncher->GetRelativeLocation(), SpawnRotation, SpawnInfo);
			MissileDecider = 1;
		}

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &APaddle::ResetLaunchTimer, MissileLaunchDuration, false);
}

void APaddle::ResetLaunchTimer()
{
	MissileLaunched = false;
}

void APaddle::KeepPaddleAtZPosition()
{
	if (this->GetActorLocation().Z != 20.f)
	{
		this->SetActorLocation(FVector(this->GetActorLocation().X, GetActorLocation().Y, 20.f));
	}
}

void APaddle::KeepLaunchersAtPosition()
{
	LeftMissileLauncher->SetRelativeLocation(FVector(this->GetActorLocation().X - 27.0f, 0.0f, this->GetActorLocation().Z + 10.0f));
	RightMissileLauncher->SetRelativeLocation(FVector(this->GetActorLocation().X + 27.0f, 0.0f, this->GetActorLocation().Z + 10.0f));
}

void APaddle::IncreaseSizeOfMesh()
{
	if (PaddleInreased)
	{
		return;
	}
	
	UGameplayStatics::PlaySound2D(GetWorld(), PaddleIncreaseSound);
	FVector NewScale = FVector(PaddleIncreaseSize, 1.0f, 1.0f);
	SM_Paddle->SetRelativeScale3D(NewScale);
	PaddleInreased = true;
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &APaddle::ResetSizeOfMesh, IncreasePaddleTime, false);

}

void APaddle::ResetSizeOfMesh()
{
	FVector NewScale = FVector(1.0f, 1.0f, 1.0f);
	SM_Paddle->SetRelativeScale3D(NewScale);
	PaddleInreased = false;
}