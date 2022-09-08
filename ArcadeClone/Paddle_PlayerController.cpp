// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "Drop.h"
#include "Containers/Array.h"
#include "EngineUtils.h"

APaddle_PlayerController::APaddle_PlayerController()
{
}

void APaddle_PlayerController::BeginPlay()
{
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);

	FViewTargetTransitionParams Params;
	SetViewTarget(CameraActors[0], Params);

	SpawnNewBall();

	MyPawn = Cast<APaddle>(GetPawn());

	// Set Variables
	GameIsOver = false;
	LevelComplete = false;
}

void APaddle_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	EnableInput(this);

	// Axis Input Binding
	InputComponent->BindAxis(TEXT("MoveHorizontal"), this, &APaddle_PlayerController::MoveHorizontal);

	// Action Input Binding
	InputComponent->BindAction(TEXT("LaunchBall"), IE_Pressed, this, &APaddle_PlayerController::LaunchBall);
	InputComponent->BindAction(TEXT("IncreasePaddleSize"), IE_Pressed, this, &APaddle_PlayerController::IncreasePaddleSize);
	InputComponent->BindAction(TEXT("MultiplyBall"), IE_Pressed, this, &APaddle_PlayerController::MultiplyBall);
	InputComponent->BindAction(TEXT("SlowBallSpeed"), IE_Pressed, this, &APaddle_PlayerController::SlowBall);
	InputComponent->BindAction(TEXT("LaunchMissile"), IE_Pressed, this, &APaddle_PlayerController::LaunchMissile);
}

void APaddle_PlayerController::MoveHorizontal(float AxisValue)
{
	if (MyPawn) 
	{
		MyPawn->MoveHorizontal(AxisValue);
	}

}

void APaddle_PlayerController::IncreasePaddleSize()
{
	if (MyPawn == nullptr)
	{
		return;
	}

	if (PaddleIncrease_Count == 0)
	{
		return;
	}
	if (!MyBall->BallLaunched)
	{
		return;
	}
	PaddleIncrease_Count--;
	MyPawn->IncreaseSizeOfMesh();
}

void APaddle_PlayerController::SlowBall()
{
	// Check if Ball Actors exist in World
	BallActors = Cast<ABall>(UGameplayStatics::GetActorOfClass(GetWorld(), BallObj));

	if (MyBall == nullptr && BallActors == nullptr)
	{
		return;
	}

	if (SlowBall_Count == 0)
	{
		return;
	}

	if (!MyBall->BallLaunched)
	{
		return;
	}

	SlowBall_Count--;
	BallActors->SlowBall();
}

void APaddle_PlayerController::MultiplyBall()
{
	// Check if ball actors exist in world
	BallActors = Cast<ABall>(UGameplayStatics::GetActorOfClass(GetWorld(), BallObj));

	if (MyBall == nullptr && BallActors == nullptr)
	{
		return;
	}

	if (MultiplyBall_Count == 0)
	{
		return;
	}

	if (!MyBall->BallLaunched)
	{
		return;
	}

	// Get all actors of class Ball in world
	TArray<AActor*> AllBallActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BallObj, AllBallActors);

	MultiplyBall_Count--;

	// Set Limit of total balls being able to exit in world at the same time
			if (AllBallActors.Num() >= BallsThatCanExistInWorld)
			{
			return;
			}
			BallActors->MultiplyBall();
}

void APaddle_PlayerController::LaunchMissile()
{
	if (MyPawn->MissileLaunched == true)
	{
		return;
	}
	if (MyPawn->PaddleInreased == true)
	{
		return;
	}
	if (!MyBall->BallLaunched)
	{
		return;
	}
	if (Missile_Count == 0)
	{
		return;
	}
	Missile_Count--;
	MyPawn->MissileLaunched = true;
}

void APaddle_PlayerController::LaunchBall()
{
	MyBall->Launch();
}

void APaddle_PlayerController::SpawnNewBall()
{
	RemoveLife();

	if (GameIsOver)
	{
		return;
	}

	// Get total ball actors in world
	TArray<AActor*> FoundBalls;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BallObj, FoundBalls);
	int32 TotalBalls = FoundBalls.Num();

	// If a single ball actors exit then another one won't spawn with paddle
	if (TotalBalls > 0)
	{
		return;
	}

	// Spawn launchable ball
	if (BallObj)
	{
		MyBall = GetWorld()->SpawnActor<ABall>(BallObj, SpawnLocation, SpawnRotation, SpawnInfo);
	}
}

void APaddle_PlayerController::RemoveLife()
{
	// Find total balls in world
	TArray<AActor*> FoundBalls;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BallObj, FoundBalls);
	int32 TotalBalls = FoundBalls.Num();

	if (TotalBalls != 0)
	{
		return;
	}


	BallCount--;

	// Player lose if no more balls left to spawn
	if (BallCount == 0)
	{
		GameIsOver = true;
		UE_LOG(LogTemp, Error, TEXT("Game Over"));
		DisableInput(this);
		
		if (BallObj)
		{
			MyBall->Destroy();
		}
	}
}

void APaddle_PlayerController::WinGame()
{
	// Find total bricks in world
	TArray<AActor*> FoundBricks;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BricksClass, FoundBricks);
	int32 TotalBricks = FoundBricks.Num();

	// if bricks are all destroyed then player wins game
	if (TotalBricks == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Level Complete"));
		LevelComplete = true;
		DisableInput(this);
		if (BallObj)
		{
			MyBall->Destroy();
		}
	}
}