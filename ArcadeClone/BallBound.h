// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallBound.generated.h"

class UBoxComponent;
class APaddle_PlayerController;
class ABall;
class ADrop;
class AMissile;

UCLASS()
class ARCADECLONE_API ABallBound : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallBound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision = nullptr;

	APaddle_PlayerController* PlayerController = nullptr;
	ABall* MyBall = nullptr;
	ADrop* MyDrop = nullptr;
	AMissile* Missile = nullptr;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndexType, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
