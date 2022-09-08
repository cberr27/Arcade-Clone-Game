// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

class UBoxComponent;
class APaddle_PlayerController;
class USoundBase;
class ADrop;

UCLASS()
class ARCADECLONE_API ABrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Brick = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision = nullptr;

		APaddle_PlayerController* PlayerController = nullptr;

		UPROPERTY(EditAnywhere)
			TSubclassOf<ADrop> DropObj;

		ADrop* MyDrop = nullptr;
		FVector DropSpawnLocation = FVector(0.0f, 0.0f, 0.0f);
		FRotator DropSpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters DropSpawnInfo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float SpeedModifierOnBounce = 1.01f;

	/*UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
			FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void DestroyBrick();

	UFUNCTION()
		void SpawnDrop();

	UPROPERTY(EditAnywhere)
		float DropPercentage = 0.5f;

	UPROPERTY(EditAnywhere)
		int32 BrickLife = 1;

	UPROPERTY(EditAnywhere)
		USoundBase* DestroySound = nullptr;
	 
};
