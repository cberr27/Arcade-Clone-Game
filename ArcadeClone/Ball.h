// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class APaddle_PlayerController;
class UProjectileMovementComponent;
class USoundBase;

UCLASS()
class ARCADECLONE_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	virtual void Launch();

	UPROPERTY()
	bool BallLaunched;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Ball = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UProjectileMovementComponent* ProjectileMovement = nullptr;


	FVector BallSpawnLocation = FVector(0.0f, 0.0f, 0.0f);
	FRotator BallSpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters BallSpawnInfo;


	APawn* MyPawn = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		UStaticMeshComponent* GetBall();

	UFUNCTION()
		void MultiplyBall();

	UFUNCTION()
		void SlowBall();

	UPROPERTY(EditAnywhere)
		USoundBase* SlowBallSound = nullptr;

	UPROPERTY(EditAnywhere)
		USoundBase* MultiplyBallSound = nullptr;

private: 

	UFUNCTION()
		void MoveWithPadddle();
};
