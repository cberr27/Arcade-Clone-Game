// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Paddle_PlayerController.generated.h"

class ABall;
class APaddle;
class ABrick;

UCLASS()
class ARCADECLONE_API APaddle_PlayerController : public APlayerController
{
	GENERATED_BODY()

		APaddle_PlayerController();

	UFUNCTION()
		virtual void  SetupInputComponent() override;

protected:

	virtual void BeginPlay() override;

	void MoveHorizontal(float AxisValue);
	void IncreasePaddleSize();
	void SlowBall();
	void MultiplyBall();
	void LaunchMissile();
	void LaunchBall();

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABall> BallObj;

	APaddle* MyPawn = nullptr;

	ABall* MyBall = nullptr;
	FVector SpawnLocation = FVector(10.0f, 0.0f, 40.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;



public:

	UFUNCTION()
	void SpawnNewBall();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool GameIsOver;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool LevelComplete;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 BallCount = 4;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABrick> BricksClass;

	UFUNCTION()
		void WinGame();

	// Abilities Available Count
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 PaddleIncrease_Count = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 SlowBall_Count = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 MultiplyBall_Count = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Missile_Count = 0;

	ABall* BallActors = nullptr;

	// Float to determine how long between Right/Left missile launches
	UPROPERTY(EditAnywhere)
		float MissileLaunchSpeed = 0.5f;

	// Integer to determine total balls that can exit in world
	UPROPERTY(EditAnywhere)
		int32 BallsThatCanExistInWorld = 8;
	
private:

	UFUNCTION()
		void RemoveLife();
};
