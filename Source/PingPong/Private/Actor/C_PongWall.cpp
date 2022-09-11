// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/C_PongWall.h"
#include "Components/BoxComponent.h"

// Sets default values
AC_PongWall::AC_PongWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PongWallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PongWallMesh"));
	RootComponent = PongWallMeshComponent;
	
	PongWallBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("PongWallCollision"));
	PongWallBoxComponent->SetupAttachment(RootComponent);
	PongWallBoxComponent->SetBoxExtent(FVector(100.f, 2500.f, 100.f));
	PongWallBoxComponent->SetCollisionProfileName("PhysicsActor");
}

// Called when the game starts or when spawned
void AC_PongWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_PongWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

