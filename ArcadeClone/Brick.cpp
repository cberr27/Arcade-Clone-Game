// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Ball.h"
#include "Paddle_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "Drop.h"
#include "Sound/SoundBase.h"

// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Brick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brick Mesh"));
	SM_Brick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Brick->SetEnableGravity(false);
	RootComponent = SM_Brick;

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Box_Collision->SetBoxExtent(FVector(26.0f, 11.0f, 11.0f));
	Box_Collision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();

	//Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABrick::OnOverlapBegin);
	SM_Brick->OnComponentHit.AddDynamic(this, &ABrick::OnHit);

	PlayerController = Cast<APaddle_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ABrick::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//}

void ABrick::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(TEXT("Ball")))
	{
		ABall* MyBall = Cast<ABall>(OtherActor);

		FVector BallVelocity = MyBall->GetVelocity();
		BallVelocity *= (SpeedModifierOnBounce - 1.0f);

		MyBall->GetBall()->SetPhysicsLinearVelocity(BallVelocity, true);

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABrick::DestroyBrick, 0.1f, false);
	}
	if (OtherActor->ActorHasTag(TEXT("Missile")))

	{
		FTimerHandle UnusedHandle;
		OtherActor->Destroy();
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABrick::DestroyBrick, 0.1f, false);
	}
}

void ABrick::DestroyBrick()
{
	BrickLife--;
	if (BrickLife == 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), DestroySound);
		DropSpawnLocation = this->GetActorLocation();
		this->Destroy();
		SpawnDrop();
		if (PlayerController)
		{
			PlayerController->WinGame();
		}
	}
}

void ABrick::SpawnDrop()
{
	float DropDecider_RandomPercentage = FMath::RandRange(1, 20);
	float PercentageDrop = (DropDecider_RandomPercentage / DropPercentage)/100;
	//UE_LOG(LogTemp, Error, TEXT("Drop Percentage = %f"), PercentageDrop);
	if (PercentageDrop >= 0.2f)
	{
		return;
	}
	float RandomNumber = FMath::RandRange(0, 3);
	if (DropObj)
	{
		MyDrop = GetWorld()->SpawnActor<ADrop>(DropObj, DropSpawnLocation, DropSpawnRotation, DropSpawnInfo);
		MyDrop->ChooseDrop(RandomNumber);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Nope"));
	}

}

