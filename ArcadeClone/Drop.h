// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Drop.generated.h"

class UBoxComponent;
class APaddle_PlayerController;
class USoundBase;

UCLASS()
class ARCADECLONE_API ADrop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Drop = nullptr;

	APaddle_PlayerController* PlayerController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void ChooseDrop(int32 DropNumber);

	UFUNCTION(BlueprintCallable)
		void EnableEffect();

	UPROPERTY(EditAnywhere)
		class UMaterialInstance* BallColor[4];

	UPROPERTY(EditAnywhere)
		USoundBase* DropCaughtSound = nullptr;

private:


	UPROPERTY()
		int32 DropNum = 0;

	UFUNCTION()
		void ChooseMaterial(int32 MaterialColor);
};
