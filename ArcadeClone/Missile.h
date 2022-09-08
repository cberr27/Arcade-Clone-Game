// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Missile.generated.h"

class UBoxComponent;

UCLASS()
class ARCADECLONE_API AMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Missile = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision = nullptr;

	UPROPERTY(VisibleAnywhere)
		FVector MissileScale = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere)
		float MissileLaunchSpeed = 200.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
