// Fill out your copyright notice in the Description page of Project Settings.


#include "Drop.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstance.h"
#include "Paddle_PlayerController.h"
#include "Sound/SoundBase.h"


// Sets default values
ADrop::ADrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Drop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Drop Mesh"));
	SM_Drop->SetSimulatePhysics(true);
	SM_Drop->SetEnableGravity(true);
	SM_Drop->SetConstraintMode(EDOFMode::XZPlane);
	SM_Drop->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Drop->SetCollisionProfileName(TEXT("PhysicsActor"));
	RootComponent = SM_Drop;

	BallColor[4] = CreateDefaultSubobject<UMaterialInstance>(TEXT("Material Color"));


}

// Called when the game starts or when spawned
void ADrop::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APaddle_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void ADrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADrop::ChooseDrop(int32 DropNumber)
{
	//UE_LOG(LogTemp, Warning, TEXT("Drop Number = %i"), DropNumber);
	DropNum = DropNumber;
	ChooseMaterial(DropNumber);
}

void ADrop::EnableEffect()
{
	UGameplayStatics::PlaySound2D(GetWorld(), DropCaughtSound);

	switch (DropNum)
	{
	case 0:

		if (PlayerController == nullptr)
		{
			return;
		}
		PlayerController->PaddleIncrease_Count++;
		this->Destroy();
		return;
	case 1:
		if (PlayerController == nullptr)
		{
			return;
		}
		PlayerController->MultiplyBall_Count++;
		this->Destroy();
		return;
	case 2:
		if (PlayerController == nullptr)
		{
			return;
		}
		PlayerController->SlowBall_Count++;
		this->Destroy();
		return;
	case 3:
		if (PlayerController == nullptr)
		{
			return;
		}
		PlayerController->Missile_Count++;
		this->Destroy();
		return;
	default:
		this->Destroy();
		return;
	}
}
void ADrop::ChooseMaterial(int32 MaterialColor)
{
	if (SM_Drop == nullptr || BallColor[MaterialColor] == nullptr)
	{
		return;
	}
	this->SM_Drop->SetMaterial(0, BallColor[MaterialColor]);
}