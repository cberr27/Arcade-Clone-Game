// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

class UFloatingPawnMovement;
class AMissile;
class USceneComponent;
class USoundBase;

UCLASS()
class ARCADECLONE_API APaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* SM_Paddle = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UFloatingPawnMovement* FloatingMovement = nullptr;

	UPROPERTY(EditAnywhere)
		USceneComponent* LeftMissileLauncher = nullptr;

	UPROPERTY(EditAnywhere)
		USceneComponent* RightMissileLauncher = nullptr;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AMissile> MissObj;

	AMissile* MyRightMissile = nullptr;
	AMissile* MyLeftMissile = nullptr;
	FVector RightSpawnLocation = FVector(27.0f, 0.0f, 10.0f);
	FVector LeftSpawnLocation = FVector(-27.0f, 0.0f, 10.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void MoveHorizontal(float AxisValue);

	UFUNCTION(BlueprintCallable)
		void IncreaseSizeOfMesh();

	UFUNCTION(BlueprintCallable)
		void ResetSizeOfMesh();

	UFUNCTION()
		void LaunchMissile();

	UPROPERTY(EditAnywhere, BluePrintReadOnly)
		float IncreasePaddleTime = 5.0f;

	UPROPERTY(EditAnywhere, BluePrintReadOnly)
		bool PaddleInreased = false;

	UPROPERTY(EditAnywhere, BluePrintReadOnly)
		bool MissileLaunched = false;

	UPROPERTY(EditAnywhere, BluePrintReadOnly)
		float PaddleIncreaseSize = 1.5f;

	UPROPERTY(EditAnywhere, BluePrintReadOnly)
		float MissileLaunchDuration = 1.0f;

	UPROPERTY(EditAnywhere)
		USoundBase* PaddleIncreaseSound = nullptr;

	UPROPERTY(EditAnywhere)
		USoundBase* MissileLaunchSound = nullptr;

private:

	int32 MissileDecider = 1;

	void KeepPaddleAtZPosition();

	void KeepLaunchersAtPosition();

	void ResetLaunchTimer();

};
